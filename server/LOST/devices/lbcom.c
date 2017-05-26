#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../config.h"
#include "uart.h"
#include "lbcom.h"

lbcom_rxData[4+255] = {0};
lbcom_rx_step = 0;

void lbcom_init(void)
{
  lbcom_rxRelease();
}

void lbcom_run(void)
{
  int dataU08 = 0;

  if(0 == lbcom_rxIsReady())
  {
    data = fgetc(uart1_fd);
    if(0 <= data)
    {
      if(0 < lbcom_rx_step)
      {
        if(lbcom_rx_step < LB_COM_DATA_MAX_SIZE+1)
        {
          if(1+4+lbcom_rxGetLen() == lbcom_rx_step)
          {
            uint8_t crc = 0;
            uint16_t i = 0;
            for(i=0; i<(lbcom_rx_step-1); i++)
            {
              crc = _crc_ibutton_update(crc, lbcom_rxData[i]);
            }
            if(data == crc) { lbcom_rx_step++; }
            else { lbcom_rxRelease(); }
          }
          else
          {
            lbcom_rxData[lbcom_rx_step-1] = data;
            lbcom_rx_step++;
          }
        }
        else { lbcom_rxRelease(); }
      }
      if(0 == lbcom_rx_step) { if(0xAA == data) { lbcom_rx_step++; } }
    }
    else
    {
      lbcom_rxRelease();
    }
  }
}

uint8_t lbcom_rxIsReady(void)
{
  if(1+4+lbcom_rxGetLen() < lbcom_rx_step) { return 1; }
  else { return 0; }
}

uint8_t lbcom_rxGetSrc(void)
{
  return lbcom_rxData[0];
}

uint8_t lbcom_rxGetDst(void)
{
  return lbcom_rxData[1];
}

uint8_t lbcom_rxGetCmd(void)
{
  return lbcom_rxData[2];
}

uint8_t lbcom_rxGetLen(void)
{
  return lbcom_rxData[3];
}

uint8_t * lbcom_rxGetData(void)
{
  return &(lbcom_rxData[4]);
}

void lbcom_rxRelease(void)
{
  uint16_t i = 0;

  for(i=0; i<4; i++)
  {
    lbcom_rxData[i] = 0;
  }
  lbcom_rx_step = 0;
}

void lbcom_send(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  uint16_t i = 0;
  uint8_t crc = 0;

  if(NULL == data=) { return; } 
  fputc(0xAA, uart1_fd); crc = _crc_ibutton_update(crc, 0xAA);
  fputc(src, uart1_fd); crc = _crc_ibutton_update(crc, src);
  fputc(dst, uart1_fd); crc = _crc_ibutton_update(crc, dst);
  fputc(cmd, uart1_fd); crc = _crc_ibutton_update(crc, cmd);
  fputc(len, uart1_fd); crc = _crc_ibutton_update(crc, len);
  for(i=0; i<len ; i++)
  {
    fputc(data[i], uart1_fd); crc = _crc_ibutton_update(crc, data[i]);
  }
  fputc(crc, uart1_fd);
  fflush(uart1_fd);
}

uint8_t lbcom_gsm_sms_send_with_phone(char * phone, char * msg)
{
  uint16_t i = 0;
  uint8_t crc = 0;

  int phone_len = 0;
  int msg_len = 0;

  if(10 != strnlen(phone, 10)) { return 1; }
  msg_len = strnlen(msg, 255-10);

  fputc(0xAA, uart1_fd); crc = _crc_ibutton_update(crc, 0xAA);
  fputc(LBCOM_SERVER, uart1_fd); crc = _crc_ibutton_update(crc, LBCOM_SERVER);
  fputc(LBCOM_RFTRX, uart1_fd); crc = _crc_ibutton_update(crc, LBCOM_RFTRX);
  fputc(LBCOM_RFTRX_GSM_SMS_SEND, uart1_fd); crc = _crc_ibutton_update(crc, LBCOM_RFTRX_GSM_SMS_SEND);
  fputc(phone_len+msg_len, uart1_fd); crc = _crc_ibutton_update(crc, phone_len+msg_len);
  for(i=0; i<phone_len; i++)
  {
    fputc(phone[i], uart1_fd); crc = _crc_ibutton_update(crc, phone[i]);
  }
  for(i=0; i<msg_len; i++)
  {
    fputc(msg[i], uart1_fd); crc = _crc_ibutton_update(crc, msg[i]);
  }
  fputc(crc, uart1_fd);
  fflush(uart1_fd);
}

uint8_t lbcom_gsm_sms_send(char * msg)
{
  uint8_t ret1 = 0;
  uint8_t ret2 = 0;

  ret1 = lbcom_gsm_sms_send_with_phone(LOST_GSM1, msg);
  NutSleep(2000);
  ret2 = lbcom_gsm_sms_send_with_phone(LOST_GSM2, msg);

  return (ret1 + ret2);
}

