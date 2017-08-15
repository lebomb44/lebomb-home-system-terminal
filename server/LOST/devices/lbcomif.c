#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timer.h>
#include <util/crc16.h>

#include "../config.h"
#include "uart.h"
#include "lbcomif.h"

#define LBCOMIF_FRAME_MAX_SIZE (4+255)

uint8_t lbcomif_rxData[LBCOMIF_FRAME_MAX_SIZE] = {0};
uint16_t lbcomif_rx_step = 0;

void (*lbcomif_SlaveCallBack[256]) (uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data);

uint8_t lbcomif_init(void)
{
  uint16_t i = 0;

  lbcomif_rxRelease();

  for(i=0; i<256; i++) { lbcomif_SlaveCallBack[i] = NULL; }

  return 0;
}

void lbcomif_registerSlaveCallBack(uint8_t cmd, void (*callBack) (uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data))
{
  if(NULL == lbcomif_SlaveCallBack[cmd]) { lbcomif_SlaveCallBack[cmd] = callBack; }
}

void lbcomif_execSlaveCallBack(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  if(NULL != lbcomif_SlaveCallBack[cmd]) { (*lbcomif_SlaveCallBack[cmd])(src, dst, cmd, len, data); }
}

void lbcomif_run(void)
{
  int data = 0;

  if(0 == lbcomif_rxIsReady())
  {
    data = fgetc(uart1_fd);
    if(0 <= data)
    {
      if(0 < lbcomif_rx_step)
      {
        if(lbcomif_rx_step < (LBCOMIF_FRAME_MAX_SIZE+2))
        {
          if(1+4+lbcomif_rxGetLen() == lbcomif_rx_step)
          {
            uint8_t crc = 0;
            uint16_t i = 0;
            for(i=0; i<(lbcomif_rx_step-1); i++)
            {
              crc = _crc_ibutton_update(crc, lbcomif_rxData[i]);
            }
            if(data == crc) { lbcomif_rx_step++; }
            else { lbcomif_rxRelease(); }
          }
          else
          {
            lbcomif_rxData[lbcomif_rx_step-1] = data;
            lbcomif_rx_step++;
          }
        }
        else { lbcomif_rxRelease(); }
      }
      if(0 == lbcomif_rx_step) { if(0xAA == data) { lbcomif_rx_step++; } }
    }
    else
    {
      lbcomif_rxRelease();
    }
  }
}

uint8_t lbcomif_rxIsReady(void)
{
  if(1+4+lbcomif_rxGetLen() < lbcomif_rx_step) { return 1; }
  else { return 0; }
}

uint8_t lbcomif_rxGetSrc(void)
{
  return lbcomif_rxData[0];
}

uint8_t lbcomif_rxGetDst(void)
{
  return lbcomif_rxData[1];
}

uint8_t lbcomif_rxGetCmd(void)
{
  return lbcomif_rxData[2];
}

uint8_t lbcomif_rxGetLen(void)
{
  return lbcomif_rxData[3];
}

uint8_t * lbcomif_rxGetData(void)
{
  return &(lbcomif_rxData[4]);
}

void lbcomif_rxRelease(void)
{
  uint16_t i = 0;

  for(i=0; i<4; i++)
  {
    lbcomif_rxData[i] = 0;
  }
  lbcomif_rx_step = 0;
}

void lbcomif_sendByte(uint8_t byte)
{
  fputc(byte, uart1_fd);
}

void lbcomif_flush(void)
{
  fflush(uart1_fd);
}

void lbcomif_send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  uint16_t i = 0;
  uint8_t crc = 0x55;

  if(NULL == data) { return; } 
  lbcomif_sendByte(0xAA);
  lbcomif_sendByte(src); crc = _crc_ibutton_update(crc, src);
  lbcomif_sendByte(dst); crc = _crc_ibutton_update(crc, dst);
  lbcomif_sendByte(cmd); crc = _crc_ibutton_update(crc, cmd);
  lbcomif_sendByte(len); crc = _crc_ibutton_update(crc, len);
  for(i=0; i<len ; i++)
  {
    lbcomif_sendByte(data[i], uart1_fd); crc = _crc_ibutton_update(crc, data[i]);
  }
  lbcomif_sendByte(crc);
  lbcomif_flush();
}

