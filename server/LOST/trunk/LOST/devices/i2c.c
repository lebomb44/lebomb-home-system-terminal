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
uint8_t *lb_tw_mt_buf = NULL;
uint8_t lb_tw_mr_siz = 0;
uint8_t *lb_tw_mr_buf = NULL;

static void Lb_TwInterrupt(void *arg)
{
    uint8_t twsr;
    register uint8_t twcr = inb(TWCR);

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
        tw_if_bsy = 1;
        tw_mt_idx = 0;
        tw_mr_idx = 0;

        /*
         * If outgoing data is available, transmit SLA+W. Logic is in
         * master transmit mode.
         */
        if (tw_mt_len) {
            outb(TWDR, tw_mm_sla);
        }

        /*
         * If outgoing data not available, transmit SLA+R. Logic will
         * switch to master receiver mode.
         */
        else {
            outb(TWDR, tw_mm_sla | 1);
        }
        outb(TWCR, TWGO | (twcr & _BV(TWEA)));
        break;

    /*
     * 0x18: SLA+W has been transmitted and ACK has been received.
     * 0x28: Data byte has been transmitted and ACK has been received.
     */
    case TW_MT_SLA_ACK:
    case TW_MT_DATA_ACK:
        /*
         * If outgoing data left to send, put the next byte in the data
         * register.
         */
        if (tw_mt_idx < tw_mt_len) {
            outb(TWDR, tw_mt_buf[tw_mt_idx]);
            /* Late increment fixes ICCAVR bug. Thanks to Andreas Siebert and Michael Fischer. */
            tw_mt_idx++;
            outb(TWCR, TWGO | (twcr & _BV(TWEA)));
            break;
        }

        /*
         * All outgoing data has been sent. If a response is expected,
         * transmit a repeated start condition.
         */
        tw_mt_len = 0;
        if (tw_mr_siz) {
            outb(TWCR, TWGO | (twcr & _BV(TWEA)) | _BV(TWSTA));
            break;
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
        if (twsr == TW_MT_SLA_NACK || twsr == TW_MR_SLA_NACK) {
            tw_mm_err = TWERR_SLA_NACK;
            tw_mt_len = 0;
            tw_mr_siz = 0;
        }

        /* Wake up the application. */
        NutEventPostFromIrq(&tw_mm_que);

        /*
         * Send a stop condition. If we have a listener, generate
         * an acknowlegde on an incoming address byte.
         */
        if(tw_sr_siz) {
            outb(TWCR, TWGO | _BV(TWEA) | _BV(TWSTO));
        }
        else {
            outb(TWCR, TWGO | _BV(TWSTO));
        }

        /* The interface is idle. */
        tw_if_bsy = 0;
        break;

    /*
     * 0x38: Arbitration lost while in master mode.
     */
    case TW_MT_ARB_LOST:
        /*
         * The start condition will be automatically resend after
         * the bus becomes available.
         */
        sbi(TWCR, TWSTA);
        /* The interface is idle. */
        tw_if_bsy = 0;
        break;

    /*
     * 0x50: Data byte has been received and acknowledged.
     */
    case TW_MR_DATA_ACK:
        /*
         * Store the data byte in the master receive buffer.
         */
        tw_mr_buf[tw_mr_idx] = inb(TWDR);
        /* Late increment fixes ICCAVR bug. Thanks to Andreas Siebert and Michael Fischer. */
        tw_mr_idx++;

    /*
     * 0x40: SLA+R has been transmitted and ACK has been received.
     */
    case TW_MR_SLA_ACK:
        /*
         * Acknowledge next data bytes except the last one.
         */
        if (tw_mr_idx + 1 < tw_mr_siz) {
            outb(TWCR, TWGO | _BV(TWEA));
        }
        else {
            outb(TWCR, TWGO);
        }
        break;

    /*
     * 0x58: Data byte has been received, but not acknowledged.
     */
    case TW_MR_DATA_NACK:
        /*
         * Store the last data byte.
         */
        tw_mr_buf[tw_mr_idx] = inb(TWDR);
        /* Late increment fixes ICCAVR bug. Thanks to Andreas Siebert and Michael Fischer. */
        tw_mr_idx++;
        tw_mr_siz = 0;

        /* Wake up the application. */
        NutEventPostFromIrq(&tw_mm_que);

        /*
         * Send a stop condition. If we have a listener, generate
         * an acknowlegde on an incoming address byte.
         */
        if(tw_sr_siz) {
            outb(TWCR, TWGO | _BV(TWEA) | _BV(TWSTO));
        }
        else {
            outb(TWCR, TWGO | _BV(TWSTO));
        }

        /* The interface is idle. */
        tw_if_bsy = 0;
        break;

    /*
     * 0x60: Own SLA+W has been received and acknowledged.
     * 0x68: Arbitration lost as master. Own SLA+W has been received
     *       and acknowledged.
     * 0x70: General call address has been received and acknowledged.
     * 0x78: Arbitration lost as master. General call address has been
     *       received and acknowledged.
     */
    case TW_SR_SLA_ACK:
    case TW_SR_ARB_LOST_SLA_ACK:
    case TW_SR_GCALL_ACK:
    case TW_SR_ARB_LOST_GCALL_ACK:
        /*
         * Do only acknowledge incoming data bytes, if we got receive
         * buffer space. Fetch the slave address from the data register
         * and reset the receive index.
         */
        if (tw_sr_siz) {
            /* We are entering the slave receive mode. Mark the interface busy. */
            tw_if_bsy = 1;

            tw_sm_sla = inb(TWDR);
            outb(TWCR, TWGO | _BV(TWEA));
            tw_sr_idx = 0;
        }

        /*
         * Do not acknowledge incoming data.
         */
        else {
            outb(TWCR, TWGO);
        }
        break;

    /*
     * 0x80: Data byte for own SLA has been received and acknowledged.
     * 0x90: Data byte for general call address has been received and
     *       acknowledged.
     */
    case TW_SR_DATA_ACK:
    case TW_SR_GCALL_DATA_ACK:
        /*
         * If the receive buffer isn't filled up, store data byte.
         */
        if (tw_sr_idx < tw_sr_siz) {
            tw_sr_buf[tw_sr_idx] = inb(TWDR);
            /* Late increment fixes ICCAVR bug. Thanks to Andreas Siebert and Michael Fischer. */
            tw_sr_idx++;
        }
        else {
            tw_sr_siz = 0;
        }

        /*
         * If more space is available for incoming data, then continue
         * receiving. Otherwise do not acknowledge new data bytes.
         */
        if (tw_sr_siz) {
            outb(TWCR, TWGO | _BV(TWEA));
            break;
        }

    /*
     * 0x88: Data byte received, but not acknowledged.
     * 0x98: Data byte for general call address received, but not
     *       acknowledged.
     */
    case TW_SR_DATA_NACK:
    case TW_SR_GCALL_DATA_NACK:
        /*
         * Continue not accepting more data.
         */
        if (tw_mt_len || tw_mr_siz) {
            outb(TWCR, inb(TWCR) | _BV(TWEA) | _BV(TWSTA));
        }
        else {
            outb(TWCR, inb(TWCR) | _BV(TWEA));
        }
        break;

    /*
     * 0xA0: Stop condition or repeated start condition received.
     */
    case TW_SR_STOP:
        /*
         * Wake up the application. If successful, do nothing. This
         * will keep SCL low and thus block the bus. The application
         * must now setup the transmit buffer and re-enable the
         * interface.
         */
        if (tw_sr_que == 0 || tw_sm_err) {
            /*
             * If no one has been waiting on the queue, the application
             * probably gave up waiting. So we continue on our own, either
             * in idle mode or switching to master mode if a master
             * request is waiting.
             */
            if (tw_mt_len || tw_mr_siz) {
                outb(TWCR, TWGO | _BV(TWSTA));
            }
            else {
                outb(TWCR, TWGO);
            }
            tw_if_bsy = 0;
        }
        else {
            NutEventPostFromIrq(&tw_sr_que);
            tw_sr_siz = 0;
            outb(TWCR, twcr & ~(_BV(TWINT) | _BV(TWIE)));
        }
        break;

    /*
     * 0xA8: Own SLA+R has been received and acknowledged.
     * 0xB0: Arbitration lost in master mode. Own SLA has been received
     *       and acknowledged.
     */
    case TW_ST_SLA_ACK:
    case TW_ST_ARB_LOST_SLA_ACK:
        /* Not idle. */
        tw_if_bsy = 1;
        /* Reset transmit index and fall through for outgoing data. */
        tw_st_idx = 0;

    /*
     * 0xB8: Data bytes has been transmitted and acknowledged.
     */
    case TW_ST_DATA_ACK:
        /*
         * If outgoing data left to send, put the next byte in the
         * data register. Otherwise transmit a dummy byte.
         */
        if (tw_st_idx < tw_st_len) {
            outb(TWDR, tw_st_buf[tw_st_idx]);
            /* Do not set acknowledge on the last data byte. */
            /* Early increment fixes ICCAVR bug. Thanks to Andreas Siebert and Michael Fischer. */
            ++tw_st_idx;
            if (tw_st_idx < tw_st_len) {
                outb(TWCR, TWGO | _BV(TWEA));
            }
            else {
                tw_st_len = 0;
                outb(TWCR, TWGO);
            }
            break;
        }

        /* No more data. Continue sending dummies. */
        outb(TWDR, 0);
        outb(TWCR, TWGO);
        break;

    /*
     * 0xC0: Data byte has been transmitted, but not acknowledged.
     * 0xC8: Last data byte has been transmitted and acknowledged.
     */
    case TW_ST_DATA_NACK:
    case TW_ST_LAST_DATA:
        NutEventPostFromIrq(&tw_st_que);

        /* Transmit start condition, if a master transfer is waiting. */
        if (tw_mt_len || tw_mr_siz) {
            outb(TWCR, TWGO | _BV(TWSTA) | /**/ _BV(TWEA));
        }
        /* Otherwise enter idle state. */
        else {
            outb(TWCR, TWGO | _BV(TWEA));
        }
        tw_if_bsy = 0;
        break;

    /*
     * 0x00: Bus error.
     */
    case TW_BUS_ERROR:
        outb(TWCR, inb(TWCR) | _BV(TWSTO));
#if 1
        tw_if_bsy = 0;
        tw_mm_err = TWERR_BUS;
        tw_sm_err = TWERR_BUS;
        NutEventPostFromIrq(&tw_sr_que);
        NutEventPostFromIrq(&tw_st_que);
        NutEventPostFromIrq(&tw_mm_que);
#endif
        break;
    }
}

int Lb_TwMasterTransact(uint8_t sla, uint8_t adr, uint8_t *txdata, uint16_t txlen, uint8_t *rxdata, uint16_t rxsiz, uint32_t tmo)
{
  /* Check the pointer on data area */
  if(data==NULL) { return 6; }

  /* Wait for the hardware interface to be free */
  ret = 10;
  while(tmo > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(1); tmo--; } }
  /* Return if impossible to take the semaphore : do nothing */
  if(tmo == 0) { return TWERR_IF_LOCKED; }

  /* Set all parameters for master mode */
  lb_tw_mm_sla = sla << 1;
  lb_tw_mm_adr = adr;
  lb_tw_mm_err = 0;
  lb_tw_mt_len = txlen;
  lb_tw_mt_buf = txdata;
  lb_tw_mr_siz = rxsiz;
  lb_tw_mr_buf = rxdata;

  /*
   * Send a start condition if the interface is idle. If busy, then
   * the interrupt routine will automatically initiate the transfer
   * as soon as the interface becomes ready again.
   */
  uint8_t twcr = inb(TWCR);
  uint8_t twsr = inb(TWSR);
  if((twsr & 0xF8) == 0x00)
  {
    outb(TWCR, _BV(TWINT) | _BV(TWEA) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE));
  }
  else
  {
    i2c_mutex = 0; return TWERR_BUS;
  }

    /*
     * Wait for master transmission done.
     */
    return rc;
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

  /* Wait for the hardware interface to be free */
  ret = 10;
  while(ret > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(10); ret--; } }
  /* Return if impossible to take the semaphore : do nothing */
  if(ret == 0) { return 7; }

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
  /* Free the hardware interface */
  i2c_mutex = 0;

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

  /* Check the pointer on the data area */
  if(data == NULL) { return 9; }
  /* Allocate a new area in order to build the frame */
  buff = malloc(nb+1);
  /* Check the allocation */
  if(buff == NULL) { return 10; }
  /* Copy the data to the new area */
  if(nb > 0) { for(i=0; i<nb; i++) { buff[i+1] = data[i]; } }
  /* But the first data is the destination address */
  buff[0] = addr;

  /* Do the exchange */
  ret = 0;
  for(i=0; i<3; i++)
  {
    /* Wait for the hardware interface to be free */
    ret = 10;
    while(ret > 0) { if(i2c_mutex == 0) { i2c_mutex = 1; break; } else { NutSleep(10); ret--; } }
    if(ret == 0) { NutSleep(100); ret = 11; continue; }

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
    /* Free the hardware interface */
    i2c_mutex = 0;
    if((nb_rec == 0) && (ret == 0))
    {
      /* No error, so break the loop */
      break;
    }
    NutSleep(5);
  }
  /* Before to exit, free the allocated area */
  free(buff);
  /* Wait a little bit */
  NutSleep(1);

  return ret;
}

uint8_t i2c_broadcast_set(uint8_t addr, uint8_t nb, uint8_t* data)
{
  /* Broadcast is a set for address 0 */
  return i2c_set(0, addr, nb, data);
}
