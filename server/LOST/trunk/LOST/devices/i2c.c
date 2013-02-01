#include <stdlib.h>
#include <stdio.h>

#include <dev/twif.h>
#include <dev/irqreg.h>

#include <sys/event.h>
#include <sys/atom.h>
#include <sys/timer.h>
#include <sys/event.h>
#include <sys/thread.h>
#include <sys/heap.h>

#include "i2c.h"

volatile uint8_t i2c_mutex;

uint8_t lb_tw_mm_sla = 0;
uint8_t lb_tw_mm_adr = 0;
uint8_t lb_tw_mm_err = 0;

uint8_t lb_tw_mt_len = 0;
uint8_t lb_tw_mt_idx = 0;
uint8_t *lb_tw_mt_buf = NULL;

uint8_t lb_tw_mr_len = 0;
uint8_t lb_tw_mr_idx = 0;
uint8_t *lb_tw_mr_buf = NULL;

static void Lb_TwInterrupt(void *arg)
{
    uint8_t twsr;

    /*
     * Read the status and interpret its contents.
     */
    twsr = inb(TWSR) & 0xF8;
    switch (twsr) {

    /*
     * 0x08: Start condition has been transmitted.
     * 0x10: Repeated start condition has been transmitted.
     */
    case TW_START:
    case TW_REP_START:
        /* We are entering the master mode. Mark the interface busy. */
        lb_tw_mt_idx = 0;
        lb_tw_mr_idx = 0;

        /*
         * If in data are necessary, transmit SLA+R. Logic will
         * switch to master receiver mode.
         */
        if (lb_tw_mr_len) {
            outb(TWDR, lb_tw_mm_sla | 1);
        }
        else {
            outb(TWDR, lb_tw_mm_sla);
        }

        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE));
        break;

    /*
     * 0x18: SLA+W has been transmitted and ACK has been received.
     */
    case TW_MT_SLA_ACK:
    	/* Send the address register */
        outb(TWDR, lb_tw_mm_adr);
        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE));
        break;

    /*
     * 0x28: Data byte has been transmitted and ACK has been received.
     */
    case TW_MT_DATA_ACK:
        /*
         * If outgoing data left to send, put the next byte in the data
         * register.
         */
        if (lb_tw_mt_idx < lb_tw_mt_len) {
            outb(TWDR, lb_tw_mt_buf[lb_tw_mt_idx]);
            lb_tw_mt_idx++;
            outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE));
            break;
        }
        else {
        	/* Send a STOP */
        	outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE));
        	if((lb_tw_mt_idx==0) && (lb_tw_mt_len==0)) { lb_tw_mt_idx++; }
        }

    /*
     * 0x20: SLA+W has been transmitted, but not acknowledged.
     * 0x30: Data byte has been transmitted, but not acknowledged.
     * 0x48: SLA+R has been transmitted, but not acknowledged.
     */
    case TW_MT_SLA_NACK:
    case TW_MT_DATA_NACK:
    case TW_MR_SLA_NACK:
        /* Set unique error code. */
        lb_tw_mm_err = TWERR_SLA_NACK;

        /* Send a STOP */
        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE));
        break;

    /*
     * 0x40: SLA+R has been transmitted and ACK has been received.
     */
    case TW_MR_SLA_ACK:
    case TW_MR_DATA_ACK:
        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE));
        break;


    /*
     * 0x50: Data byte has been received and acknowledged.
     */
    case TW_MR_DATA_ACK:
        /*
         * Store the data byte in the master receive buffer.
         */
        if (lb_tw_mr_idx < lb_tw_mr_len) {
            lb_tw_mr_buf[lb_tw_mr_idx] = inb(TWDR);
            lb_tw_mr_idx++;
            outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE));
        }
        if (lb_tw_mr_idx >= lb_tw_mr_len) {
            /* Send a STOP */
            outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE));
        }


        break;

    /*
     * 0x58: Data byte has been received, but not acknowledged.
     */
    case TW_MR_DATA_NACK:
        /* Set unique error code. */
        lb_tw_mm_err = TWERR_SLA_NACK;

        /* Send a STOP */
        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE));

        break;

    /*
     * 0x00: Bus error.
     * 0x38: Arbitration lost while in master mode.
     */
    case TW_BUS_ERROR:
    case TW_MT_ARB_LOST:
        tw_mm_err = TWERR_BUS;
        outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE));

        break;
    }
}

int Lb_TwMasterTransact(uint8_t sla, uint8_t adr, uint8_t *txdata, uint16_t txlen, uint8_t *rxdata, uint16_t rxlen, uint32_t timeout)
{
  uint32_t tmo=0;

  /* Check the pointer on data area */
  if(data==NULL) { return 6; }

  /* Wait for the hardware interface to be free */
  tmo = timeout; while(tmo > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(1); tmo--; } }
  /* Return if impossible to take the semaphore : do nothing */
  if(tmo == 0) { return TWERR_IF_LOCKED; }

  /* Set all parameters for master mode */
  lb_tw_mm_sla = sla << 1;
  lb_tw_mm_adr = adr;
  lb_tw_mm_err = 0;
  lb_tw_mt_len = txlen;
  lb_tw_mt_buf = txdata;
  lb_tw_mr_len = rxlen;
  lb_tw_mr_buf = rxdata;

  uint8_t twsr = inb(TWSR);
  if((twsr & 0xF8) != 0x00)
  {

  }

  if(rxlen > 0)
  {
    lb_tw_mt_len = 0;  lb_tw_mr_len = 0;
    /* Send a START*/
    outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE));
    /* Wait for the address to be sent */
    tmo = timeout; while(tmo > 0) { if(lb_tw_mt_idx == 1) { break; } else { NutSleep(1); tmo--; } }
    /* Return if impossible to take the semaphore : do nothing */
    if(tmo == 0) { i2c_mutex = 0; if(lb_tw_mm_err>0) { return lb_tw_mm_err; } else { return TWERR_BUS; } }

    lb_tw_mt_len = 0;  lb_tw_mr_len = rxlen;
    /* Send a START*/
    outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE));
    /* Wait for the address to be sent */
    tmo = timeout; while(tmo > 0) { if(lb_tw_mr_idx == rxlen) { break; } else { NutSleep(1); tmo--; } }
    /* Return if impossible to take the semaphore : do nothing */
    if(tmo == 0) { i2c_mutex = 0; if(lb_tw_mm_err>0) { return lb_tw_mm_err; } else { return TWERR_BUS; } }
  }
  else
  {
    lb_tw_mt_len = txlen;  lb_tw_mr_len = 0;
    /* Send a START*/
    outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE));
    /* Wait for the address to be sent */
    tmo = timeout; while(tmo > 0) { if(lb_tw_mt_idx == txlen) { break; } else { NutSleep(1); tmo--; } }
    /* Return if impossible to take the semaphore : do nothing */
    if(tmo == 0) { i2c_mutex = 0; if(lb_tw_mm_err>0) { return lb_tw_mm_err; } else { return TWERR_BUS; } }
  }
  i2c_mutex = 0;
    return ;
}

uint8_t i2c_init(void)
{
  uint32_t val = 0;

  /* Lock the hardware interface */
  i2c_mutex = 1;

  /* Set the pin as input with pull-up */
  cbi(DDRD,0);
  cbi(DDRD,1);
  sbi(PORTD,0);
  sbi(PORTD,1);

  /* Set as I2C master */
  if (NutRegisterIrqHandler(&sig_2WIRE_SERIAL, Lb_TwInterrupt, 0)) { return -1; }

  /*
   * Set address register, enable general call address, set transfer
   * speed and enable interface.
   */
  outb(TWAR, 0x02);
  /* Set the bus speed */
  val = 50000; /* MAX = 409582 */
  TwIOCtl(TWI_SETSPEED, &val);
  outb(TWCR, _BV(TWINT));
  outb(TWCR, _BV(TWEN) | _BV(TWIE));

  /* Reset the global variables */
  lb_tw_mm_sla = 0;
  lb_tw_mm_adr = 0;
  lb_tw_mm_err = 0;
  lb_tw_mt_len = 0;
  lb_tw_mt_buf = NULL;
  lb_tw_mr_siz = 0;
  lb_tw_mr_buf = NULL;

  /* Authorize the use of the hardware interface */
  i2c_mutex = 0;

  return 0;
}

void i2c_reset(void)
{
  /* Clear the interrupt */
  TWCR = (1<<TWINT);
  /* Wait a little bit */
  NutSleep(1);
  /* Generate a STOP */
  TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
  /* Wait a little bit */
  NutSleep(1);
  /* Stop the I2C core component */
  TWCR = 0;
  /* Wait a little bit */
  NutSleep(1);
  /* Start the I2C core component */
  TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
  /* Initialize TWI */
  i2c_init();
  /* Wait a little bit */
  NutSleep(1);
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  int nb_rec = 0;
  int ret = 0;

  /* Check the pointer on data area */
  if(data==NULL) { return 6; }

  /* Do the exchange and check the returned number of data */
  nb_rec = TwMasterTransact(sla, &addr, (uint16_t) 1, data, (uint16_t) nb, (uint32_t) 500);
  /* Check the error occurred */
  ret = TwMasterError();
  /* If an error is detected */
  if((nb_rec != nb) || (ret != 0))
  {
    /* Reset the I2C hardware interface */
    i2c_reset();
    /* If no error on transmission, set the returned value to indicate that the error occurred on the number of data */
    if(ret == 0) { ret = 8; }
  }

  /* Clear the data if not received */
  if(nb_rec < 0) { nb_rec = 0; }
  while(nb_rec < nb ) { data[nb_rec] = 0; nb_rec++; }

  /* Wait a little bit */
  NutSleep(1);

  return ret;
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint16_t i = 0;
  uint8_t* buff=NULL;
  int nb_rec = 0;
  int ret = 0;


    /* Execute the transmission */
    nb_rec = TwMasterTransact(sla, buff, (uint16_t) (((uint16_t)nb)+1), NULL, (uint16_t) 0, (uint32_t) 100);
    /* Check the error occurred */
    ret = TwMasterError();
    /* If an error is detected */
    if((nb_rec != 0) || (ret != 0))
    {
      /* Reset the I2C hardware interface */
      i2c_reset();
      /* If no error on transmission, set the returned value to indicate that the error occurred on the number of data */
      if(ret == 0) { ret = 11; }
    }

    if((nb_rec == 0) && (ret == 0))
    {
      /* No error, so break the loop */
      break;
    }
    NutSleep(5);

  /* Wait a little bit */
  NutSleep(1);

  return ret;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for address 0 */
  return i2c_set(0, addr, nb, data);
}
