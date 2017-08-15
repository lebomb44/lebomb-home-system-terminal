#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

uint8_t _lbcom_gsmTM_init_status = 0;
uint8_t _lbcom_gsmTM_checkpowerup_status = 0;
uint8_t _lbcom_gsmTM_signalstrenght_status = 0;
uint32_t _lbcom_gsmTM_signalstrenght_value = 0;
uint8_t _lbcom_gsmTM_sendsms_status = 0;

void lbcom_gsmTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
       if(ID_GSM_INIT_TM == cmd)         { if(1 == len) { _lbcom_gsmTM_init_status = data[0]; } }
  else if(ID_GSM_CHECKPOWERUP_TM == cmd) { if(1 == len) { _lbcom_gsmTM_checkpowerup_status = data[0]; } }
  else if(ID_GSM_GETSIGNALSTRENGHT_TM == cmd)
  {
    if(5 == len)
    {
      _lbcom_gsmTM_signalstrenght_status = data[0];
      _lbcom_gsmTM_signalstrenght_value = (0xFF000000 & (((uint32_t)data[1])<<24)) | (0x00FF0000 & (((uint32_t)data[2])<<16)) | (0x0000FF00 & (((uint32_t)data[3])<<8)) | (0x000000FF & ((uint32_t)data[4]));
    }
  }
  else if(ID_GSM_SENDSMS_TM == cmd) { if(1 == len) { _lbcom_gsmTM_sendsms_status = data[0]; } }
}

void lbcom_gsmTM_init_status_set(uint8_t status) { _lbcom_gsmTM_init_status = status; }
uint8_t lbcom_gsmTM_init_status_get(void) { return _lbcom_gsmTM_init_status; }

void lbcom_gsmTM_checkpowerup_status_set(uint8_t status) { _lbcom_gsmTM_checkpowerup_status = status; }
uint8_t lbcom_gsmTM_checkpowerup_status_get(void) { return _lbcom_gsmTM_checkpowerup_status; }

void lbcom_gsmTM_signalstrenght_set(uint8_t status, uint32_t value) { _lbcom_gsmTM_signalstrenght_status = status; _lbcom_gsmTM_signalstrenght_value = value; }
uint8_t lbcom_gsmTM_signalstrenght_status_get(void) { return _lbcom_gsmTM_signalstrenght_status; }
uint32_t lbcom_gsmTM_signalstrenght_value_get(void) { return _lbcom_gsmTM_signalstrenght_value; }

void lbcom_gsmTM_sendsms_status_set(uint8_t status) { _lbcom_gsmTM_sendsms_status = status; }
uint8_t lbcom_gsmTM_sendsms_status_get(void) { return _lbcom_gsmTM_sendsms_status; }

