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

#include <util/crc16.h>

#include "i2c.h"

#define I2C_ERR_OK	         0
#define I2C_ERR_TIMEOUT      1
#define I2C_ERR_BUS          2
#define I2C_ERR_IF_LOCKED    3
#define I2C_ERR_MT_SLA_NACK  4
#define I2C_ERR_MT_DATA_NACK 5
#define I2C_ERR_MR_SLA_NACK  6
#define I2C_ERR_MR_DATA_NACK 7
#define I2C_ERR_BAD_TX_ARG   8
#define I2C_ERR_BAD_RX_ARG   9
#define I2C_ERR_BAD_TRX_ARG  10

#define I2C_CRC_INITIAL_VALUE 0x00

volatile uint8_t i2c_mutex;

uint8_t i2c_mm_sla = 0;
uint8_t i2c_mm_adr = 0;
uint8_t i2c_mm_crc = I2C_CRC_INITIAL_VALUE;
uint8_t i2c_sl_crc = I2C_CRC_INITIAL_VALUE;
uint8_t i2c_mm_err = 0;


uint16_t i2c_mt_len = 0;
uint16_t i2c_mt_idx = 0;
uint8_t *i2c_mt_buf = NULL;

uint16_t i2c_mr_len = 0;
uint16_t i2c_mr_idx = 0;
uint8_t i2c_mr_buf[255] = {0};

static void I2C_Interrupt(void *arg)
{
    uint8_t twsr;
    arg = arg;

    /*
     * Read the status and interpret its contents.
     */
    twsr = TWSR & 0xF8;
    switch (twsr) {

    /*
     * 0x08: Start condition has been transmitted.
     */
    case TW_START:
        /* We are entering the master mode. Mark the interface busy. */
        i2c_mt_idx = 0;
        i2c_mr_idx = 0;
		i2c_mm_crc = I2C_CRC_INITIAL_VALUE;
		i2c_sl_crc = I2C_CRC_INITIAL_VALUE;
//printf("Start\n");
        /* Send the slave address in SLA+T */
        TWDR = i2c_mm_sla;
        /* Add the SLA to the CRC */
        i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mm_sla);
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * 0x10: Repeated start condition has been transmitted.
     */
    case TW_REP_START:
        /* We are entering the master mode. Mark the interface busy. */
        i2c_mt_idx = 0;
        i2c_mr_idx = 0;
		i2c_mm_crc = I2C_CRC_INITIAL_VALUE;
		i2c_sl_crc = I2C_CRC_INITIAL_VALUE;
//printf("Rep Start\n");

        /*
         * If in data are necessary, transmit SLA+R. Logic will
         * switch to master receiver mode.
         */
        if(0 < i2c_mr_len) {
            TWDR = i2c_mm_sla | 1;
            /* Add the SLA to the CRC */
			i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mm_sla);
            TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
        }
        else {
            /* Stop the transmission because we should not be in a REPEATED START if we are in MT mode */
            TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        }

        break;

    /*
     * 0x18: SLA+W has been transmitted and ACK has been received.
     */
    case TW_MT_SLA_ACK:
        /* Send the address register */
//printf("MT SLA ACK\n");
        TWDR = i2c_mm_adr;
        /* Add the ADR to the CRC */
        i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mm_adr);
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);

        break;

    /*
     * 0x20: SLA+W has been transmitted, but not acknowledged.
     */
    case TW_MT_SLA_NACK:
        /* Set error code */
        i2c_mm_err = I2C_ERR_MT_SLA_NACK;
//printf("MT SLA NACK\n");

        /* Send a STOP */
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * 0x28: Data byte has been transmitted and ACK has been received.
     */
    case TW_MT_DATA_ACK:
//printf("MT DATA ACK\n");
    	/* If we have to receive data, send len, crc and a REPEATED START */
        if(0 < i2c_mr_len) {
            /* Set the data in the register */
            if(0 == i2c_mt_idx) {
                TWDR = i2c_mr_len;
                i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mr_len);
            }
            /* Increment step */
            i2c_mt_idx++;
            /* Start transition */
            if(i2c_mt_idx < 2) {
                TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
            }
            else {
                TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE);
            }
        }
        else {
            /* Set the data in the register */
            if(0 == i2c_mt_idx) {
                TWDR = i2c_mt_len;
                i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mt_len);
            }
            else {
                /* If outgoing data left to send, put the next byte in the data register */
                if (i2c_mt_idx < (i2c_mt_len + 1)) {
                    TWDR = i2c_mt_buf[i2c_mt_idx-1];
                    i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mt_buf[i2c_mt_idx-1]);
                }
                else {
                    if (i2c_mt_idx == (i2c_mt_len + 1)) {
                        TWDR = i2c_mm_crc;
                    }
                }
            }
            /* Increment step */
            i2c_mt_idx++;
            /* Start transition */
            if (i2c_mt_idx < (i2c_mt_len + 3)) {
                TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
            }
            else {
                TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
            }
        }
        break;

    /*
     * 0x30: Data byte has been transmitted, but not acknowledged.
     */
    case TW_MT_DATA_NACK:
//printf("MT_DATA_NACK\n");
        /* Set error code */
        i2c_mm_err = I2C_ERR_MT_DATA_NACK;

        /* Send a STOP */
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * 0x40: SLA+R has been transmitted and ACK has been received.
     */
    case TW_MR_SLA_ACK:
//printf("MR_SLA_ACK\n");
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * 0x48: SLA+R has been transmitted, but not acknowledged.
     */
    case TW_MR_SLA_NACK:
//printf("MR_SLA_NACK\n");
        /* Set unique error code. */
        i2c_mm_err = I2C_ERR_MR_SLA_NACK;

        /* Send a STOP */
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * 0x50: Data byte has been received and acknowledged.
     */
    case TW_MR_DATA_ACK:
//printf("MR_DATA_ACK\n");
        /*
         * Store the data byte in the master receive buffer.
         */
        /* Get the data in the register */
        if (i2c_mr_idx < i2c_mr_len) {
        	i2c_mr_buf[i2c_mr_idx] = TWDR;
			i2c_mm_crc = _crc_ibutton_update(i2c_mm_crc, i2c_mr_buf[i2c_mr_idx]);
            /* Increment step */
            i2c_mr_idx++;
            /* Start transmition */
            TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
        }
		else {
            i2c_sl_crc = TWDR;
            /* Increment step */
            i2c_mr_idx++;
            /* Send a STOP */
            TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        }
        break;

    /*
     * 0x58: Data byte has been received, but not acknowledged.
     */
    case TW_MR_DATA_NACK:
//printf("MR_DATA_NACK\n");
        /* Set error code */
        i2c_mm_err = I2C_ERR_MR_DATA_NACK;

        /* Send a STOP */
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);
        break;

    /*
     * Default.
     */
    default:
//printf("Default\n");
    	i2c_mm_err = I2C_ERR_BUS;
        TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN) | _BV(TWIE);

        break;
    }
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
  if (NutRegisterIrqHandler(&sig_2WIRE_SERIAL, I2C_Interrupt, 0)) { return -1; }

  /*
   * Set address register, enable general call address, set transfer
   * speed and enable interface.
   */
  TWAR = 0x02;
  /* Set the bus speed */
  val = 50000; /* MAX = 409582 */
  TwIOCtl(TWI_SETSPEED, &val);
  TWCR = _BV(TWINT);
  TWCR = _BV(TWEA) | _BV(TWEN) | _BV(TWIE);

  /* Reset the global variables */
  i2c_mm_sla = 0;
  i2c_mm_adr = 0;
  i2c_mm_err = 0;
  i2c_mt_len = 0;
  i2c_mt_buf = NULL;
  i2c_mr_len = 0;

  /* Authorize the use of the hardware interface */
  i2c_mutex = 0;

  return 0;
}

void i2c_reset(void)
{
  /* Clear the interrupt */
  TWCR = _BV(TWINT);
  /* Wait a little bit */
  NutSleep(1);
  /* Generate a STOP */
  TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTO) | _BV(TWEN);
  /* Wait a little bit */
  NutSleep(1);
  /* Stop the I2C core component */
  TWCR = 0;
  /* Wait a little bit */
  NutSleep(1);
  /* Start the I2C core component */
  TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
  /* Initialize TWI */
  i2c_init();
  /* Wait a little bit */
  NutSleep(1);
}

uint8_t i2c_transact(uint8_t sla, uint8_t adr, uint8_t txlen, uint8_t *txdata, uint8_t rxlen, uint8_t *rxdata)
{
  uint32_t tmo = 0;
  uint16_t i = 0;

  /* Check arguments */
  if(0 < txlen) { if(NULL == txdata) { return I2C_ERR_BAD_TX_ARG; } }
  if(0 < rxlen) { if(NULL == rxdata) { return I2C_ERR_BAD_RX_ARG; } }
  if(!((0 == txlen) ^ (0 == rxlen))) { return I2C_ERR_BAD_TRX_ARG; }

  /* Wait for the hardware interface to be free */
  tmo = 100; while(0 < tmo) { if(0 == i2c_mutex) { i2c_mutex = 1; break; } else { NutSleep(1); tmo--; } }
  /* Return if impossible to take the semaphore : do nothing */
  if(0 == tmo) { return I2C_ERR_IF_LOCKED; }

  /* Check the good health of the bus */
  tmo = 4; while(0 < tmo) { if((0xF8 == (TWSR & 0xF8)) && (0x00 == (TWCR & _BV(TWSTO)))) { break; } else { i2c_reset(); NutSleep(1); tmo--; } }
  /* Return if impossible to force initialization of the bus */
  if(0 == tmo) { i2c_mutex = 0; return I2C_ERR_BUS; }

  /* Set all parameters for master mode */
  i2c_mm_sla = sla << 1;
  i2c_mm_adr = adr;
  i2c_mm_err = I2C_ERR_OK;
  if(0 < rxlen) { i2c_mt_len = 0;     i2c_mr_len = rxlen; }
  else          { i2c_mt_len = txlen; i2c_mr_len = 0;     }
  i2c_mt_idx = 0;
  i2c_mr_idx = 0;
  i2c_mt_buf = txdata;

  /* Send a START */
  TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE);
  /* Wait for the data to be received or sent */
  if(0 < rxlen) { tmo = 30; while(0 < tmo) { if((i2c_mt_idx == 2          ) && (i2c_mr_idx == (rxlen + 1))) { break; } else { NutSleep(1); tmo--; } } }
  else          { tmo = 30; while(0 < tmo) { if((i2c_mt_idx == (txlen + 3)) && (i2c_mr_idx == 0          )) { break; } else { NutSleep(1); tmo--; } } }
  /* Return if time-out */
  if(0 == tmo)
  {
    i2c_reset();
    i2c_mutex = 0;
    if(0 < i2c_mm_err) { return i2c_mm_err; } else { return I2C_ERR_TIMEOUT; }
  }
  else
  {
    if(i2c_sl_crc == i2c_mm_crc)
    {
      for(i=0; i<rxlen; i++)
      {
        rxdata[i] = i2c_mr_buf[i];
        i2c_mutex = 0;
        return I2C_ERR_OK;
      }
    }
	else
    {
      i2c_mutex = 0;
      return I2C_ERR_BUS;
    }
  }
}

uint8_t i2c_get(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint8_t ret = I2C_ERR_BUS;
  uint8_t try = 3;

  while((0 < try) && (I2C_ERR_OK != ret))
  {
    /* Do the exchange and check the returned code */
    ret = i2c_transact(sla, addr, 0, NULL, nb, data);

    /* Wait a little bit */
    NutSleep(1);

    /* Next step */
    try--;
  }

  return ret;
}

uint8_t i2c_set(uint8_t sla, uint8_t addr, uint8_t nb, uint8_t* data)
{
  uint8_t ret = I2C_ERR_BUS;
  uint8_t try = 3;

  while((0 < try) && (I2C_ERR_OK != ret))
  {
    /* Do the exchange and check the returned code */
    ret = i2c_transact(sla, addr, nb, data, 0, NULL);

    /* Wait a little bit */
    NutSleep(1);

    /* Next step */
    try--;
  }

  return ret;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for address 0 */
  return i2c_set(0, addr, nb, data);
}
