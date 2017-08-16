#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

#include "lbcom_bourdilot_freezerTC.h"

void lbcom_bourdilot_freezerTC_network(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_BOURDILOT_FREEZER_SLAVE, ID_BOURDILOT_FREEZER_NETWORK_TC, 0, NULL);
}

void lbcom_bourdilot_freezerTC_temp(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_BOURDILOT_FREEZER_SLAVE, ID_BOURDILOT_FREEZER_TEMP_TC, 0, NULL);
}

int lbcom_bourdilot_freezerTC_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "network");
    if(arg_s) { lbcom_bourdilot_freezerTC_network(); }

    arg_s = NutHttpGetParameter(req, "temp");
    if(arg_s) { lbcom_bourdilot_freezerTC_temp(); }

    fflush(stream);
  }

  return 0;
}

