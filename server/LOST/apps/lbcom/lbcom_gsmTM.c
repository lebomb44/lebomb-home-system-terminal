#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

#include "../../services/web.h"

#include "lbcom_gsmTM.h"

uint8_t _lbcom_gsmTM_init_status = 0;
uint8_t _lbcom_gsmTM_checkpowerup_status = 0;
uint8_t _lbcom_gsmTM_signalstrength_status = 0;
uint16_t _lbcom_gsmTM_signalstrength_value = 0;
uint8_t _lbcom_gsmTM_sendsms_status = 0;

void lbcom_gsmTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
       if(ID_GSM_INIT_TM == cmd)         { if(1 == len) { _lbcom_gsmTM_init_status = data[0]; } }
  else if(ID_GSM_CHECKPOWERUP_TM == cmd) { if(1 == len) { _lbcom_gsmTM_checkpowerup_status = data[0]; } }
  else if(ID_GSM_GETSIGNALSTRENGTH_TM == cmd)
  {
    if(3 == len)
    {
      _lbcom_gsmTM_signalstrength_status = data[0];
      _lbcom_gsmTM_signalstrength_value = (0xFF00 & (((uint16_t)data[1])<<8)) | (0x00FF & ((uint16_t)data[2]));
    }
  }
  else if(ID_GSM_SENDSMS_TM == cmd) { if(1 == len) { _lbcom_gsmTM_sendsms_status = data[0]; } }
}

void lbcom_gsmTM_init_status_set(uint8_t status) { _lbcom_gsmTM_init_status = status; }
uint8_t lbcom_gsmTM_init_status_get(void) { return _lbcom_gsmTM_init_status; }

void lbcom_gsmTM_checkpowerup_status_set(uint8_t status) { _lbcom_gsmTM_checkpowerup_status = status; }
uint8_t lbcom_gsmTM_checkpowerup_status_get(void) { return _lbcom_gsmTM_checkpowerup_status; }

void lbcom_gsmTM_signalstrength_set(uint8_t status, uint16_t value) { _lbcom_gsmTM_signalstrength_status = status; _lbcom_gsmTM_signalstrength_value = value; }
uint8_t lbcom_gsmTM_signalstrength_status_get(void) { return _lbcom_gsmTM_signalstrength_status; }
uint16_t lbcom_gsmTM_signalstrength_value_get(void) { return _lbcom_gsmTM_signalstrength_value; }

void lbcom_gsmTM_sendsms_status_set(uint8_t status) { _lbcom_gsmTM_sendsms_status = status; }
uint8_t lbcom_gsmTM_sendsms_status_get(void) { return _lbcom_gsmTM_sendsms_status; }

int lbcom_gsmTM_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  char* status_s = NULL;
  char* value_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "init");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_init_status_get()); }
      else { lbcom_gsmTM_init_status_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "checkpowerup");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_checkpowerup_status_get()); }
      else { lbcom_gsmTM_checkpowerup_status_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "signalstrength");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n%d\n", lbcom_gsmTM_signalstrength_status_get(), lbcom_gsmTM_signalstrength_value_get()); }
      else
      {
        status_s = NutHttpGetParameter(req, "status");
        value_s = NutHttpGetParameter(req, "value");
        if((NULL != status_s) && (NULL != value_s))
        {
          lbcom_gsmTM_signalstrength_set(strtoul(status_s, NULL, 10), strtoul(value_s, NULL, 10));
        }
      }
    }

    arg_s = NutHttpGetParameter(req, "sendsms");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_sendsms_status_get()); }
      else { lbcom_gsmTM_sendsms_status_set(strtoul(arg_s, NULL, 10)); }
    }

    fflush(stream);
  }

  return 0;
}

int lbcom_gsmTM_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom_GsmTM" , stream);
  fprintf_XML_elt_int("Init"                 , lbcom_gsmTM_init_status_get()          , stream);
  fprintf_XML_elt_int("CheckPowerUp"         , lbcom_gsmTM_checkpowerup_status_get()  , stream);
  fprintf_XML_elt_int("SignalStrength_status", lbcom_gsmTM_signalstrength_status_get(), stream);
  fprintf_XML_elt_int("SignalStrength_value" , lbcom_gsmTM_signalstrength_value_get() , stream);
  fprintf_XML_elt_trailer("LbCom_GsmTM", stream);

  return 0;
}

