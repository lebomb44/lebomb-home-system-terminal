#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../../devices/ID.h"

#include "../../services/web.h"

#include "lbcom_homeeasyTM.h"

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
      if(((0xFCE1CE == _lbcom_homeeasyTM_manufacturer) && (0x0 == _lbcom_homeeasyTM_group) && (0x2 == _lbcom_homeeasyTM_device)) \
      || ((0xFCBDD6 == _lbcom_homeeasyTM_manufacturer) && (0x0 == _lbcom_homeeasyTM_group) && (0x2 == _lbcom_homeeasyTM_device)) \
      || ((0xFCDAD2 == _lbcom_homeeasyTM_manufacturer) && (0x0 == _lbcom_homeeasyTM_group) && (0x2 == _lbcom_homeeasyTM_device)) \
      || ((0xFCC302 == _lbcom_homeeasyTM_manufacturer) && (0x0 == _lbcom_homeeasyTM_group) && (0x2 == _lbcom_homeeasyTM_device)))
      {
        if(0 == _lbcom_homeeasyTM_status) {}
        else if(1 == _lbcom_homeeasyTM_status) {}
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

int lbcom_homeeasyTM_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  uint32_t manufacturer = 0;
  uint8_t group = 0;
  uint8_t device = 0;
  uint8_t status = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "code_reset");
    if(arg_s) { lbcom_homeeasyTM_code_reset(); }

    arg_s = NutHttpGetParameter(req, "manufacturer");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%ld\n", lbcom_homeeasyTM_manufacturer_get()); }
      else { manufacturer = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "group");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n", lbcom_homeeasyTM_group_get()); }
      else { group = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "device");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n", lbcom_homeeasyTM_device_get()); }
      else { device = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "status");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n", lbcom_homeeasyTM_status_get()); }
      else { status = strtoul(arg_s, NULL, 10); }
    }

    fflush(stream);
  }

  return 0;
}

int lbcom_homeeasyTM_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom_HomeEasyTM" , stream);
  fprintf_XML_elt_int("Manufacturer", lbcom_homeeasyTM_manufacturer_get(), stream);
  fprintf_XML_elt_int("Group"       , lbcom_homeeasyTM_group_get()       , stream);
  fprintf_XML_elt_int("Device"      , lbcom_homeeasyTM_device_get()      , stream);
  fprintf_XML_elt_int("Status"      , lbcom_homeeasyTM_status_get()      , stream);
  fprintf_XML_elt_trailer("LbCom_HomeEasyTM", stream);

  return 0;
}

