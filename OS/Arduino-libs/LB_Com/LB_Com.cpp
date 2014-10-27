#include <inttypes.h>
#include <Arduino.h> 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/crc16.h>
#include "wiring_private.h"
#include "LB_Com.h"

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

  sbi(UCSRB, RXEN);
  sbi(UCSRB, TXEN);
  sbi(UCSRB, RXCIE);
  cbi(UCSRB, UDRIE);
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
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(0xAA); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, 0xAA);
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(src); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, src);
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(dst); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, dst);
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(cmd); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, cmd);
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(len); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, len);
  for(i=0; i<len ; i++)
  {
	  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(data[i]); sbi(UCSRB, UDRIE); crc = _crc_ibutton_update(crc, data[i]);
  }
  while(true == this->tx_fifo.isFull()); this->tx_fifo.push(crc); sbi(UCSRB, UDRIE);

}

Fifo_U08 * uart_rx_fifo = NULL;
ISR(USART_RX_vect)
{
  uart_rx_fifo->push(UDR);
}

Fifo_U08 * uart_tx_fifo = NULL;
ISR(UART_UDRE_vect)
{
  if(true == uart_tx_fifo->isEmpty())
  {
    cbi(UCSRB, UDRIE);
  }
  else
  {
    UDR = uart_tx_fifo->pop();
  }
}
