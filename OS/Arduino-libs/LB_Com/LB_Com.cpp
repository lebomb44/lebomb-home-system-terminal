#include <inttypes.h>
#include <Arduino.h> 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/crc16.h>
#include "wiring_private.h"
#include <Fifo_U08/Fifo_U08.h>
#include "LB_Com.h"

Fifo_U08 * uart_rx_fifo = NULL;
Fifo_U08 * uart_tx_fifo = NULL;

LB_Com::LB_Com()
{
  this->init();
}

void LB_Com::init(void)
{
  uint16_t i = 0;

  this->rx_fifo.init();
  for(i=0; i<(LB_COM_DATA_MAX_SIZE); i++)
  {
    this->rxData[i] = 0;
  }
  this->rx_step = 0;
  this->tx_fifo.init();

  uart_rx_fifo = &(this->rx_fifo);
  uart_tx_fifo = &(this->tx_fifo);

  sbi(UCSR0B, RXEN0);
  sbi(UCSR0B, TXEN0);
  sbi(UCSR0B, RXCIE0);
  cbi(UCSR0B, UDRIE0);
}

void LB_Com::run(void)
{
  uint8_t dataU08 = 0;

  if(false == this->rxIsReady())
  {
    if(false == this->rx_fifo.isEmpty())
    {
      dataU08 = this->rx_fifo.pop();
      if(0 < this->rx_step)
      {
        if(this->rx_step < LB_COM_DATA_MAX_SIZE+1)
        {
          if(1+4+this->rxGetLen() == this->rx_step)
          {
            uint8_t crc = 0;
            uint16_t i = 0;
            for(i=0; i<(this->rx_step-1); i++)
            {
              crc = _crc_ibutton_update(crc, this->rxData[i]);
            }
            if(dataU08 == crc) { this->rx_step++; }
            else { this->rxRelease(); }
          }
          else
          {
            this->rxData[this->rx_step-1] = dataU08;
            this->rx_step++;
          }
        }
        else { this->rxRelease(); }
      }
      if(0 == this->rx_step) { if(0xAA == dataU08) { this->rx_step++; } }
    }
  }
}

bool LB_Com::rxIsReady(void)
{
  if(1+4+this->rxGetLen() < this->rx_step) { return true; }
  else { return false; }
}

uint8_t LB_Com::rxGetSrc(void)
{
  return this->rxData[0];
}

uint8_t LB_Com::rxGetDst(void)
{
  return this->rxData[1];
}

uint8_t LB_Com::rxGetCmd(void)
{
  return this->rxData[2];
}

uint8_t LB_Com::rxGetLen(void)
{
  return this->rxData[3];
}

uint8_t * LB_Com::rxGetData(void)
{
  return &(this->rxData[4]);
}

void LB_Com::rxRelease(void)
{
  uint16_t i = 0;

  for(i=0; i<(LB_COM_DATA_MAX_SIZE); i++)
  {
    this->rxData[i] = 0;
  }
  this->rx_step = 0;
}

bool LB_Com::txIsReady(void)
{
  !(this->tx_fifo.isFull());
}

void LB_Com::send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  uint16_t i = 0;
  uint8_t crc = 0;
  this->send_char(0xAA); crc = _crc_ibutton_update(crc, 0xAA);
  this->send_char(src); crc = _crc_ibutton_update(crc, src);
  this->send_char(dst); crc = _crc_ibutton_update(crc, dst);
  this->send_char(cmd); crc = _crc_ibutton_update(crc, cmd);
  this->send_char(len); crc = _crc_ibutton_update(crc, len);
  for(i=0; i<len ; i++)
  {
    this->send_char(data[i]); crc = _crc_ibutton_update(crc, data[i]);
  }
  this->send_char(crc);

}

void LB_Com::send_char(uint8_t data)
{
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(data); sbi(UCSR0B, UDRIE0);
}

ISR(USART_RX_vect)
{
  uart_rx_fifo->push(UDR0);
}

ISR(USART_UDRE_vect)
{
  if(true == uart_tx_fifo->isEmpty())
  {
    cbi(UCSR0B, UDRIE0);
  }
  else
  {
    UDR0 = uart_tx_fifo->pop();
  }
}
