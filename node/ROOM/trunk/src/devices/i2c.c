#include <util/twi.h>
#include "../global.h"
#include "uart.h"
#include "relay.h"
#include "../apps/node.h"
#include "i2c.h"

volatile u08 tw_sm_sla;   /* Slave address received. */
volatile u08 tw_sm_adr;   /* Slave memory address received. */

volatile u16 tw_st_idx;  /* Current slave transmit buffer index. */
volatile u16 tw_sr_idx;  /* Current slave receive buffer index. */

#define TWGO    (_BV(TWINT) | _BV(TWEN) | _BV(TWIE))

/*
 * TWI interrupt handler.
 */
SIGNAL(SIG_2WIRE_SERIAL)
{
    u08 twsr;

    /*
     * Read the status and interpret its contents.
     */
    twsr = TWSR & 0xF8;
//uart_printf((u08*)"twsr=0x%x\n",twsr);
    switch (twsr) {

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

        /* We are entering the slave receive mode. Mark the interface busy. */
        tw_sm_sla = TWDR;
        TWCR = TWGO | _BV(TWEA);
        tw_sr_idx = 0;
//uart_printf((u08*)"TW SR Sla=0x%x\n",tw_sm_sla);
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
        if(tw_sr_idx==0)
        {
          tw_sm_adr = TWDR;
//uart_printf((u08*)"TW SR ADR=0x%x\n",tw_sm_adr);
        }
        else
        {
          if(tw_sr_idx <= NODE_REG_MAX)
          {
            node[tw_sm_adr+tw_sr_idx-1] = TWDR;
//uart_printf((u08*)"TW SR data=0x%x\n",node[tw_sm_adr+tw_sr_idx-1]);
          }
          else
          {
//uart_puts((u08*)"TW SR over\n");
          }
        }
        if(tw_sr_idx <= NODE_REG_MAX)
        {
          tw_sr_idx++;
        }
        /*
         * If more space is available for incoming data, then continue
         * receiving. Otherwise do not acknowledge new data bytes.
         */
        TWCR = TWGO | _BV(TWEA);
        break;

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
//uart_puts((u08*)"TW SR Nack\n");
        tw_sr_idx = NODE_REG_MAX+1;
        TWCR = TWGO | _BV(TWEA);
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
//uart_puts((u08*)"TW SR Stop\n");
        tw_sr_idx = NODE_REG_MAX+1;
        TWCR = TWGO | _BV(TWEA);
        break;

    /*
     * 0xA8: Own SLA+R has been received and acknowledged.
     * 0xB0: Arbitration lost in master mode. Own SLA has been received
     *       and acknowledged.
     */
    case TW_ST_SLA_ACK:
    case TW_ST_ARB_LOST_SLA_ACK:
        /* Reset transmit index and fall through for outgoing data. */
        tw_sm_sla = TWDR;
        tw_st_idx = 0;
        if(tw_st_idx < NODE_REG_MAX)
        {
          TWDR = node[tw_sm_adr+tw_st_idx];
        }
        else
        {
          /* No more data. Continue sending dummies. */
          TWDR = 0;
        }
        if(tw_st_idx < NODE_REG_MAX)
        {
          tw_st_idx++;
        }
        TWCR = TWGO | _BV(TWEA);
//uart_printf((u08*)"TW ST Sla=0x%x\n",tw_sm_sla);
//uart_printf((u08*)"TW ST ADR=0x%x\n",tw_sm_adr);
        break;

    /*
     * 0xB8: Data bytes has been transmitted and acknowledged.
     */
    case TW_ST_DATA_ACK:
        /*
         * If outgoing data left to send, put the next byte in the
         * data register. Otherwise transmit a dummy byte.
         */
        if(tw_st_idx < NODE_REG_MAX)
        {
          TWDR = node[tw_sm_adr+tw_st_idx];
//uart_printf((u08*)"TW ST data=0x%x\n",node[tw_sm_adr+tw_st_idx]);
        }
        else
        {
//uart_puts((u08*)"TW ST over !\n");
          /* No more data. Continue sending dummies. */
          TWDR = 0;
        }
        if(tw_st_idx < NODE_REG_MAX)
        {
          tw_st_idx++;
        }

        TWCR = TWGO | _BV(TWEA);
        break;

    /*
     * 0xC0: Data byte has been transmitted, but not acknowledged.
     * 0xC8: Last data byte has been transmitted and acknowledged.
     */
    case TW_ST_DATA_NACK:
    case TW_ST_LAST_DATA:
//uart_puts((u08*)"TW ST Nack\n");
        /* Transmit start condition, if a master transfer is waiting. */
        tw_st_idx = NODE_REG_MAX;
        TWCR = TWGO | _BV(TWEA);
        break;

    /*
     * 0x00: Bus error.
     */
    case TW_BUS_ERROR:
uart_puts((u08*)"TW Error\n");
        tw_sr_idx = NODE_REG_MAX+1;
        tw_st_idx = NODE_REG_MAX;
        TWCR = TWGO | _BV(TWEA) | _BV(TWSTO);
        break;

    default:
        TWCR = TWGO | _BV(TWEA);
uart_puts((u08*)"TW Default\n");
        break;
    }
}


void i2c_init(void)
{
  /* No pull-up on SDA, external pull-up is used */
  cbi(PORTC, 4);
  /* SDA is an input line */
  cbi(DDRC, 4);
  /* No pull-up on SCL, external pull-up is used */
  cbi(PORTC, 5);
  /* Slave Mode : SCL is an input line */
  cbi(DDRC, 5);

  TWAR = ((0x02) << 1) | 0x01;
//TWCR = _BV(TWINT);
  TWCR = _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
//TWCR=0x45;
uart_printf((u08*)"TWCR=0x%x\n",TWCR);
uart_printf((u08*)"TWAR=0x%x\n",TWAR);
}

void i2c_adr_set(u08 adr)
{
  TWAR = ((adr) << 1) | 0x01; /* Adress and Broadcast */
}
