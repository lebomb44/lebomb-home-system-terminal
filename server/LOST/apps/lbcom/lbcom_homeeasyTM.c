#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

uint32_t _lbcom_homeeasyTM_manufacturer = 0;
uint8_t _lbcom_homeeasyTM_group = 0;
uint8_t _lbcom_homeeasyTM_device = 0;
uint8_t _lbcom_homeeasyTM_status = 0;

void lbcom_homeeasyTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  if(ID_HOME_EASY_RCV_TM == cmd)
  {
    if(7 == len)
    {
      _lbcom_homeeasyTM_manufacturer = (0xFF000000 & (((uint32_t)data[0])<<24)) | (0x00FF0000 & (((uint32_t)data[1])<<16)) | (0x0000FF00 & (((uint32_t)data[2])<<8)) | (0x000000FF & ((uint32_t)data[3]));
      _lbcom_homeeasyTM_group = data[4];
      _lbcom_homeeasyTM_device = data[5];
      _lbcom_homeeasyTM_status = data[6];
      /* Check the authorized codes */
      if(((0xFCE1CE == manufacturer) && (0x0 == group) && (0x2 == device)) \
      || ((0xFCBDD6 == manufacturer) && (0x0 == group) && (0x2 == device)) \
      || ((0xFCDAD2 == manufacturer) && (0x0 == group) && (0x2 == device)) \
      || ((0xFCC302 == manufacturer) && (0x0 == group) && (0x2 == device)))
      {
        if(0 == status) {}
        else if(1 == status) {}
      }
    }
  }
}

void lbcom_homeeasyTM_code_reset(void)
{ 
  _lbcom_homeeasyTM_manufacturer = 0;
  _lbcom_homeeasyTM_group = 0;
  _lbcom_homeeasyTM_device = 0;
  _lbcom_homeeasyTM_status = 0;
}
uint32_t lbcom_homeeasyTM_manufacturer_get(void) { return _lbcom_homeeasyTM_manufacturer; }
uint8_t lbcom_homeeasyTM_group_get(void) { return _lbcom_homeeasyTM_group; }
uint8_t lbcom_homeeasyTM_device_get(void) { return _lbcom_homeeasyTM_device; }
uint8_t lbcom_homeeasyTM_status_get(void) { return _lbcom_homeeasyTM_status; }

