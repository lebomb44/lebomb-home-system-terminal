#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../devices/ID.h"

#include "../../services/web.h"

#include "lbcom_alarmTM.h"

uint8_t _lbcom_alarmTM_status = 0;

void lbcom_alarmTM_receive(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  _lbcom_alarmTM_status = cmd;
}

uint8_t lbcom_alarmTM_status_get(void) { return _lbcom_alarmTM_status; }
void lbcom_alarmTM_status_set(uint8_t status) { _lbcom_alarmTM_status = status; }
void lbcom_alarmTM_status_reset(void) { _lbcom_alarmTM_status = 0; }

int lbcom_alarmTM_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "network");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_alarmTM_status_get()); }
      else { lbcom_alarmTM_status_set(strtoul(arg_s, NULL, 10)); }
    }

    fflush(stream);
  }

  return 0;
}

int lbcom_alarmTM_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom_AlarmTM" , stream);
  fprintf_XML_elt_int("Status", lbcom_alarmTM_status_get(), stream);
  fprintf_XML_elt_trailer("LbCom_AlarmTM" , stream);

  return 0;
}

