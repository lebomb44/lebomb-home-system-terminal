#include <util/twi.h>
#include <util/crc16.h>
#include "../global.h"
#include "../config.h"
#include "uart.h"
#include "relay.h"
#include "../apps/node.h"
#include "i2c.h"

#define TW_CRC_INITIAL_VALUE 0xFFFF

volatile u08 tw_sm_sla;   /* Slave address received. */
volatile u08 tw_sm_adr;   /* Slave memory address received. */
volatile u08 tw_sm_len;   /* Slave data len to receive or transmit */
volatile u16 tw_sm_crc;   /* Slave crc to receive or transmit */
volatile u16 tw_mm_crc;   /* Master crc to receive */

volatile u16 tw_st_idx;  /* Current slave transmit buffer index. */
volatile u16 tw_sr_idx;  /* Current slave receive buffer index. */
volatile u08 tw_sr_buf[NODE_REG_MAX] = {0}; /* Current slave receive buffer */

#define TWGO    (_BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE))

/*
 * TWI interrupt handler.
 */
SIGNAL(SIG_2WIRE_SERIAL)
{
    u08 twsr = 0;
    u16 i = 0;

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
		tw_sm_crc = TW_CRC_INITIAL_VALUE;
        tw_sm_crc = _crc_ccitt_update(tw_sm_crc, tw_sm_sla);
        tw_sr_idx = 0;
        TWCR = TWGO;
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
        if(0 == tw_sr_idx)
        {
          tw_sm_adr = TWDR;
          tw_sm_crc = _crc_ccitt_update(tw_sm_crc, tw_sm_adr);
//uart_printf((u08*)"TW SR ADR=0x%x\n",tw_sm_adr);
        }
        else
        {
          if(1 == tw_sr_idx)
          {
            tw_sm_len = TWDR;
            tw_sm_crc = _crc_ccitt_update(tw_sm_crc, tw_sm_len);
          }
          else
          {
            if((tw_sm_adr + tw_sm_len) < (NODE_REG_MAX + 1))
            {
              if(tw_sr_idx < (tw_sm_len + 2))
              {
                tw_sr_buf[tw_sr_idx - 2] = TWDR;
                tw_sm_crc = _crc_ccitt_update(tw_sm_crc, tw_sr_buf[tw_sr_idx - 2]);
              }
              else
              {
                if(tw_sr_idx == (tw_sm_len + 2))
                {
                  tw_mm_crc = ~tw_sm_crc;
                  tw_mm_crc = ((((u16) TWDR) << 8) & 0xFF00) | (tw_mm_crc & 0x00FF);
                }
                else
                {
                  if(tw_sr_idx == (tw_sm_len + 3))
                  {
                    tw_mm_crc = (tw_mm_crc & 0xFF00) | (((u16) TWDR) & 0x00FF);
                    if(tw_sm_crc == tw_mm_crc)
                    {
                      for(i=0; i<tw_sm_len; i++)
                      {
                        node[tw_sm_adr + i] = tw_sr_buf[i];
                      }
				    }
                  }
                  else
                  {
                    tw_mm_crc = TWDR;
                  }
                }
              }
//uart_printf((u08*)"TW SR data=0x%x\n",node[tw_sm_adr+tw_sr_idx-1]);
            }
            else
            {
              tw_mm_crc = TWDR;
//uart_puts((u08*)"TW SR over\n");
            }
          }
        }
        if((tw_sm_adr+tw_sr_idx) < (NODE_REG_MAX + 4))
        {
          tw_sr_idx++;
        }
        /*
         * If more space is available for incoming data, then continue
         * receiving. Otherwise do not acknowledge new data bytes.
         */
        TWCR = TWGO;
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
        tw_sm_crc = _crc_ccitt_update(tw_sm_crc, tw_sm_sla);
        tw_st_idx = 0;
        if(0 < tw_sm_len)
        {
          if((tw_sm_adr + tw_st_idx) < NODE_REG_MAX)
          {
            TWDR = node[tw_sm_adr + tw_st_idx];
		    tw_sm_crc = _crc_ccitt_update(tw_sm_crc, node[tw_sm_adr + tw_st_idx]);
          }
          else
          {
            /* No more data. Continue sending dummies. */
            TWDR = 0xFF;
          }
        }
        else
        {
          TWDR = (tw_sm_crc >> 8) & 0x00FF;
		}
        tw_st_idx++;
        TWCR = TWGO;
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
        if(tw_st_idx < tw_sm_len)
        {
          if((tw_sm_adr + tw_st_idx) < NODE_REG_MAX)
          {
            TWDR = node[tw_sm_adr + tw_st_idx];
            tw_sm_crc = _crc_ccitt_update(tw_sm_crc, node[tw_sm_adr + tw_st_idx]);
//uart_printf((u08*)"TW ST data=0x%x\n",node[tw_sm_adr+tw_st_idx]);
          }
          else
          {
//uart_puts((u08*)"TW ST over !\n");
            /* No more data. Continue sending dummies. */
            TWDR = 0xFF;
          }
        }
        else
        {
          if(tw_st_idx == tw_sm_len)
          {
            TWDR = (tw_sm_crc >> 8) & 0x00FF;
          }
          else
          {
            if(tw_st_idx == (tw_sm_len + 1))
            {
              TWDR = tw_sm_crc & 0x00FF;
            }
            else
            {
              TWDR = 0xFF;
            }
          }
        }
        tw_st_idx++;
        TWCR = TWGO;
        break;

    case TW_NO_INFO:
        break;

    case TW_SR_STOP:
    case TW_SR_DATA_NACK:
    case TW_SR_GCALL_DATA_NACK:
    case TW_ST_DATA_NACK:
    case TW_ST_LAST_DATA:
        TWDR = 0xFF;
        TWCR = TWGO;
        break;

    /*
     * 0x00: Bus error.
     */
    case TW_BUS_ERROR:
    default:
        tw_sr_idx = NODE_REG_MAX + 3;
        tw_st_idx = NODE_REG_MAX;
        TWDR = 0xFF;
        TWCR = TWGO | _BV(TWSTO);
//uart_puts((u08*)"TW Default\n");
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

  TWAR = ((NODE_ROOM_CONFIG_ADDR) << 1) | 0x01;
  TWCR = _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
}

void i2c_adr_set(u08 adr)
{
  TWAR = ((adr) << 1) | 0x01; /* Address and Broadcast */
}
