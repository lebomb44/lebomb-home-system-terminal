#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/lbcomif.h"
#include "../../services/web.h"

#include "lbcom.h"
#include "lbcom_homeeasyTC.h"
#include "lbcom_homeeasyTM.h"
#include "lbcom_ht12eTC.h"
#include "lbcom_ht12eTM.h"
#include "lbcom_gsmTC.h"
#include "lbcom_gsmTM.h"
#include "lbcom_bourdilot_freezerTC.h"
#include "lbcom_bourdilot_freezerTM.h"
#include "lbcom_alarmTC.h"
#include "lbcom_alarmTM.h"

uint8_t lbcom_init(void)
{
  NutThreadCreate("LbComD" , LbComD , 0, 512);
  NutRegisterCgi("lbcom.cgi", lbcom_form);
  NutRegisterCgi("lbcom_homeeasyTC.cgi", lbcom_homeeasyTC_form);
  NutRegisterCgi("lbcom_homeeasyTM.cgi", lbcom_homeeasyTM_form);
  NutRegisterCgi("lbcom_ht12eTC.cgi", lbcom_ht12eTC_form);
  NutRegisterCgi("lbcom_ht12eTM.cgi", lbcom_ht12eTM_form);
  NutRegisterCgi("lbcom_gsmTC.cgi", lbcom_gsmTC_form);
  NutRegisterCgi("lbcom_gsmTM.cgi", lbcom_gsmTM_form);
  NutRegisterCgi("lbcom_bourdilot_freezerTC.cgi", lbcom_bourdilot_freezerTC_form);
  NutRegisterCgi("lbcom_bourdilot_freezerTM.cgi", lbcom_bourdilot_freezerTM_form);
  NutRegisterCgi("lbcom_alarmTC.cgi", lbcom_alarmTC_form);
  NutRegisterCgi("lbcom_alarmTM.cgi", lbcom_alarmTM_form);

  return 0;
}

THREAD(LbComD, arg)
{
  arg = arg;
  NutThreadSetPriority(100);

  while(1)
  {
    while(lbcomif_run());
    /* Is there something received ? */
    if(1 == lbcomif_rxIsReady())
    {
      if(ID_LOST_MASTER == lbcomif_rxGetDst())
      {
             if(ID_HOME_EASY_SLAVE         == lbcomif_rxGetSrc()) { lbcom_homeeasyTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_HT12E_SLAVE             == lbcomif_rxGetSrc()) { lbcom_ht12eTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_GSM_SLAVE               == lbcomif_rxGetSrc()) { lbcom_gsmTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_BOURDILOT_FREEZER_SLAVE == lbcomif_rxGetSrc()) { lbcom_bourdilot_freezerTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_ALARM_SLAVE             == lbcomif_rxGetSrc()) { lbcom_alarmTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
      }
      else if(ID_LOST_SLAVE == lbcomif_rxGetDst())
      {
        lbcomif_execSlaveCallBack(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData());
      }
      lbcomif_rxRelease();
    }
    else
    {
      NutSleep(1);
    }
  }
}

int lbcom_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  uint8_t src = 0;
  uint8_t dst = 0;
  uint8_t cmd = 0;
  uint16_t len = 0;
  uint8_t * data = NULL;
  uint16_t i = 0;
  char argData[8] = "data000";

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "src");
    if(arg_s) { src = strtoul(arg_s, NULL, 10); } else { return 1; }

    arg_s = NutHttpGetParameter(req, "dst");
    if(arg_s) { dst = strtoul(arg_s, NULL, 10); } else { return 2; }

    arg_s = NutHttpGetParameter(req, "cmd");
    if(arg_s) { cmd = strtoul(arg_s, NULL, 10); } else { return 3; }

    arg_s = NutHttpGetParameter(req, "len");
    if(arg_s) { len = strtoul(arg_s, NULL, 10); } else { return 4; }

    if(0 < len)
    {
      data = malloc(len);
      if(NULL != data)
      {
        for(i=0; i<len; i++)
        {
          argData[4] = '0'+ (i/100); argData[5] = '0' + ((i/10) % 10); argData[6] = '0' + (i%10); argData[7] = 0;
          arg_s = NutHttpGetParameter(req, argData);
          if(arg_s) { data[i] = strtoul(arg_s, NULL, 10); } else { free(data); return 5; }
        }
      }
    }
    lbcomif_send(src, dst, cmd, len, data);
    if(NULL != data) { free(data); data = NULL; }

    fflush(stream);
  }

  return 0;
}

int lbcom_xml_get(FILE * stream)
{
  lbcom_homeeasyTM_xml_get(stream);
  lbcom_ht12eTM_xml_get(stream);
  lbcom_gsmTM_xml_get(stream);
  lbcom_bourdilot_freezerTM_xml_get(stream);
  lbcom_alarmTM_xml_get(stream);

  return 0;
}

