#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

#include "lbcom_ht12eTM.h"

void lbcom_ht12eTC_send(uint16_t address, uint8_t data)
{
  uint8_t _data[3] = {0};

  _data[0] = 0x00FF & (address>>8);
  _data[1] = 0x00FF & (address);
  _data[2] = data;

  lbcomif_send(ID_LOST_MASTER, ID_HT12E_SLAVE, ID_HT12E_SEND_TC, sizeof(_data), _data);
}

int lbcom_ht12eTC_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  uint16_t address = 0;
  uint8_t data = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "address");
    if(arg_s) { address = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "data");
    if(arg_s) { data = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "send");
    if(arg_s) { lbcom_ht12eTC_send(address, data); }

    fflush(stream);
  }

  return 0;
}

