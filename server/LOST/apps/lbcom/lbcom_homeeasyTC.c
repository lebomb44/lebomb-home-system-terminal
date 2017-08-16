#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

#include "lbcom_homeeasyTM.h"

void lbcom_homeeasyTC_send(uint32_t manufacturer, uint8_t group, uint8_t device, uint8_t status)
{
  uint8_t data[7] = {0};

  data[0] = 0x000000FF & (manufacturer>>24);
  data[1] = 0x000000FF & (manufacturer>>16);
  data[2] = 0x000000FF & (manufacturer>>8);
  data[3] = 0x000000FF & (manufacturer);

  data[4] = group;
  data[5] = device;
  data[6] = status;

  lbcomif_send(ID_LOST_MASTER, ID_HOME_EASY_SLAVE, ID_HOME_EASY_SEND_TC, sizeof(data), data);
}

int lbcom_homeeasyTC_form(FILE * stream, REQUEST * req)
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
    arg_s = NutHttpGetParameter(req, "manufacturer");
    if(arg_s) { manufacturer = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "group");
    if(arg_s) { group = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "device");
    if(arg_s) { device = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "status");
    if(arg_s) { status = strtoul(arg_s, NULL, 10); }

    arg_s = NutHttpGetParameter(req, "send");
    if(arg_s) { lbcom_homeeasyTC_send(manufacturer, group, device, status); }

    fflush(stream);
  }

  return 0;
}

