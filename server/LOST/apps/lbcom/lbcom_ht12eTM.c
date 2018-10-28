#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../../devices/ID.h"

#include "../../services/web.h"

#include "lbcom_ht12eTM.h"

uint16_t _lbcom_ht12eTM_address = 0;
uint8_t _lbcom_ht12eTM_data = 0;

void lbcom_ht12eTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  if(ID_HT12E_RCV_TM == cmd)
  {
    if(3 == len)
    {
      _lbcom_ht12eTM_address = (0xFF00 & (((uint16_t)data[0])<<8)) | (0x00FF & ((uint16_t)data[1]));
      _lbcom_ht12eTM_data = data[2];
    }
  }
}

void lbcom_ht12eTM_code_reset(void)
{ 
  _lbcom_ht12eTM_address = 0;
  _lbcom_ht12eTM_data = 0;
}
uint16_t lbcom_ht12eTM_address_get(void) { return _lbcom_ht12eTM_address; }
uint8_t lbcom_ht12eTM_data_get(void) { return _lbcom_ht12eTM_data; }

int lbcom_ht12eTM_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  uint16_t address = 0;
  uint8_t data = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "code_reset");
    if(arg_s) { lbcom_ht12eTM_code_reset(); }

    arg_s = NutHttpGetParameter(req, "address");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%X\n", lbcom_ht12eTM_address_get()); }
      else { address = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "data");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%X\n", lbcom_ht12eTM_data_get()); }
      else { data = strtoul(arg_s, NULL, 10); }
    }

    fflush(stream);
  }

  return 0;
}

int lbcom_ht12eTM_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom_HT12ETM" , stream);
  fprintf_XML_elt_int("Address", lbcom_ht12eTM_address_get(), stream);
  fprintf_XML_elt_int("Data"   , lbcom_ht12eTM_data_get()   , stream);
  fprintf_XML_elt_trailer("LbCom_HT12ETM", stream);

  return 0;
}

