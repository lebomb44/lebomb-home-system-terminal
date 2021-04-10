#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/lbcomif.h"

#include "lbcom_alarmTC.h"

void lbcom_alarmTC_status(void)
{
  lbcomif_send(ID_LOST_MASTER, ID_ALARM_SLAVE, ID_ALARM_STATUS_TC, 0, NULL);
}

int lbcom_alarmTC_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "status");
    if(arg_s) { lbcom_alarmTC_status(); }

    fflush(stream);
  }

  return 0;
}

