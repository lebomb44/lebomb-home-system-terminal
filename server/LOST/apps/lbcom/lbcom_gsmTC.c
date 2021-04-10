#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/timer.h>

#include <util/crc16.h>

#include "../../devices/lbcomif.h"

#include "../../config.h"

#include "lbcom_gsmTC.h"

void lbcom_gsmTC_init(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_GSM_SLAVE, ID_GSM_INIT_TC, 0, NULL);
}

void lbcom_gsmTC_checkpowerup(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_GSM_SLAVE, ID_GSM_CHECKPOWERUP_TC, 0, NULL);
}

void lbcom_gsmTC_powerupdown(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_GSM_SLAVE, ID_GSM_POWERUPDOWN_TC, 0, NULL);
}

void lbcom_gsmTC_powerreset(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_GSM_SLAVE, ID_GSM_POWERRESET_TC, 0, NULL);
}

void lbcom_gsmTC_getsignalstrength(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_GSM_SLAVE, ID_GSM_GETSIGNALSTRENGTH_TC, 0, NULL);
}

uint8_t lbcom_gsmTC_sms_send_with_phone(char * phone, char * msg)
{
  uint16_t i = 0;
  uint8_t crc = 0x55;

  int phone_len = 0;
  int msg_len = 0;

  phone_len = strnlen(phone, 12);
  if(10 != phone_len) { return 1; }
  msg_len = strnlen(msg, 255-12-1-1);

  lbcomif_sendByte(0xAA);
  lbcomif_sendByte(ID_LOST_MASTER); crc = _crc_ibutton_update(crc, ID_LOST_MASTER);
  lbcomif_sendByte(ID_GSM_SLAVE); crc = _crc_ibutton_update(crc, ID_GSM_SLAVE);
  lbcomif_sendByte(ID_GSM_SENDSMS_TC); crc = _crc_ibutton_update(crc, ID_GSM_SENDSMS_TC);
  lbcomif_sendByte(phone_len+1+msg_len+1); crc = _crc_ibutton_update(crc, phone_len+1+msg_len+1);
  for(i=0; i<phone_len; i++)
  {
    lbcomif_sendByte(phone[i]); crc = _crc_ibutton_update(crc, phone[i]);
  }
  /* Send also end of phone string */
  lbcomif_sendByte(0); crc = _crc_ibutton_update(crc, 0);
  for(i=0; i<msg_len; i++)
  {
    lbcomif_sendByte(msg[i]); crc = _crc_ibutton_update(crc, msg[i]);
  }
  /* Send also aend of msg string */
  lbcomif_sendByte(0); crc = _crc_ibutton_update(crc, 0);
  lbcomif_sendByte(crc);
  lbcomif_flush();

  return 0;
}

uint8_t lbcom_gsmTC_sms_send(char * msg)
{
  uint8_t ret1 = 0;
  uint8_t ret2 = 0;

  ret1 = lbcom_gsmTC_sms_send_with_phone(LOST_GSM1, msg);
  NutSleep(2000);
  ret2 = lbcom_gsmTC_sms_send_with_phone(LOST_GSM2, msg);

  return (ret1 + ret2);
}

int lbcom_gsmTC_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  char* phone_s = NULL;
  char* msg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "init");
    if(arg_s) { lbcom_gsmTC_init(); }

    arg_s = NutHttpGetParameter(req, "checkpowerup");
    if(arg_s) { lbcom_gsmTC_checkpowerup(); }

    arg_s = NutHttpGetParameter(req, "getsignalstrength");
    if(arg_s) { lbcom_gsmTC_getsignalstrength(); }

    arg_s = NutHttpGetParameter(req, "sendsms");
    if(arg_s)
    {
      phone_s = NutHttpGetParameter(req, "phone");
      msg_s = NutHttpGetParameter(req, "msg");
      if((NULL != phone_s) && (NULL != msg_s))
      {
        lbcom_gsmTC_sms_send_with_phone(phone_s, msg_s);
      }
    }

    fflush(stream);
  }

  return 0;
}

