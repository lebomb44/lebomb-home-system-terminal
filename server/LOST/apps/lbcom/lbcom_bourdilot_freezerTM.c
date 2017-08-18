#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

#include "../../services/web.h"

#include "lbcom_bourdilot_freezerTM.h"

uint8_t _lbcom_bourdilot_freezerTM_network = 0;
int16_t _lbcom_bourdilot_freezerTM_temp = -20;

void lbcom_bourdilot_freezerTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
       if(ID_BOURDILOT_FREEZER_NETWORK_TM == cmd) { if(0 == len) { _lbcom_bourdilot_freezerTM_network = 1; } }
  else if(ID_BOURDILOT_FREEZER_TEMP_TM    == cmd) { if(2 == len) { _lbcom_bourdilot_freezerTM_temp = (0xFF00 & (((int16_t)data[0])<<8)) | (0x00FF & ((int16_t)data[1])); } }
}

uint8_t lbcom_bourdilot_freezerTM_network_get(void) { return _lbcom_bourdilot_freezerTM_network; }
void lbcom_bourdilot_freezerTM_network_set(uint8_t network) { _lbcom_bourdilot_freezerTM_network = network; }
int16_t lbcom_bourdilot_freezerTM_temp_get(void) { return _lbcom_bourdilot_freezerTM_temp; }
void lbcom_bourdilot_freezerTM_temp_set(int16_t temp) { _lbcom_bourdilot_freezerTM_temp = temp; }

int lbcom_bourdilot_freezerTM_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "network");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_bourdilot_freezerTM_network_get()); }
      else { lbcom_bourdilot_freezerTM_network_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "temp");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_bourdilot_freezerTM_temp_get()); }
      else { lbcom_bourdilot_freezerTM_temp_set(strtol(arg_s, NULL, 10)); }
    }

    fflush(stream);
  }

  return 0;
}

int lbcom_bourdilot_freezerTM_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom_Bourdilot_FreezerTM" , stream);
  fprintf_XML_elt_int("Network", lbcom_bourdilot_freezerTM_network_get(), stream);
  fprintf_XML_elt_int("Temp"   , lbcom_bourdilot_freezerTM_temp_get()   , stream);
  fprintf_XML_elt_trailer("LbCom_Bourdilot_FreezerTM" , stream);

  return 0;
}

