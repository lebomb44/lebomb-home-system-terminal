#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/lbcomif.h"
#include "../../services/web.h"

#include "lbcom.h"
#include "lbcom_homeeasyTM.h"
#include "lbcom_gsmTM.h"
#include "lbcom_bourdilot_freezerTM.h"

uint8_t lbcom_init(void)
{
  NutThreadCreate("LbComD" , LbComD , 0, 512);
  NutRegisterCgi("lbcom.cgi", lbcom_form);
  NutRegisterCgi("lbcom_homeeasy.cgi", lbcom_homeeasy_form);
  NutRegisterCgi("lbcom_gsm.cgi", lbcom_gsm_form);
  NutRegisterCgi("lbcom_bourdilot_freezer.cgi", lbcom_bourdilot_freezer_form);

  return 0;
}

THREAD(LbComD, arg)
{
  arg = arg;
  NutThreadSetPriority(100);

  while(1)
  {
    lbcomif_run();
    /* Is there something received ? */
    if(1 == lbcomif_rxIsReady())
    {
      if(ID_LOST_MASTER == lbcomif_rxGetDst())
      {
             if(ID_HOME_EASY_SLAVE        == lbcomif_rxGetDst()) { lbcom_homeeasyTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_GSM_SLAVE              == lbcomif_rxGetDst()) { lbcom_gsmTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
        else if(ID_BOURDILOT_FRIDGE_SLAVE == lbcomif_rxGetDst()) { lbcom_bourdilot_freezerTM_receive(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData()); }
      }
      else if(ID_LOST_SLAVE == lbcomif_rxGetDst())
      {
        lbcomif_execSlaveCallBack(lbcomif_rxGetSrc(), lbcomif_rxGetDst(), lbcomif_rxGetCmd(), lbcomif_rxGetLen(), lbcomif_rxGetData());
      }
      lbcomif_rxRelease();
    }
    else
    {
      NutSleep(1000);
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

    data = malloc(len);
    if(NULL != data)
    {
      for(i=0; i<len; i++)
      {
        argData[4] = i/100; argData[5] = (i/10) % 10; argData[6] = i%10; argData[7] = 0;
        arg_s = NutHttpGetParameter(req, argData);
        if(arg_s) { data[i] = strtoul(arg_s, NULL, 10); } else { free(data); return 5; }
      }
      free(data);
    }
    fflush(stream);
  }

  return 0;
}

int lbcom_homeeasy_form(FILE * stream, REQUEST * req)
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
    arg_s = NutHttpGetParameter(req, "codeReset");
    if(arg_s) { lbcom_homeeasyTM_code_reset(); }

    arg_s = NutHttpGetParameter(req, "manufacturer");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n", lbcom_homeeasyTM_manufacturer_get()); }
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
    arg_s = NutHttpGetParameter(req, "send");
    if(arg_s) { lbcom_homeeasyTC_send(manufactuer, group, device, status); }

    fflush(stream);
  }

  return 0;
}

int lbcom_gsm_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "init");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_init_status_get()); }
      else { lbcom_gsmTM_init_status_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "checkpowerup");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_checkpowerup_status_get()); }
      else { lbcom_gsmTM_checkpowerup_status_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "signalstrenght");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d\n%d\n", lbcom_gsmTM_signalstrenght_status_get(), lbcom_gsmTM_signalstrenght_value_get()); }
      else { lbcom_gsmTM_signalstrenght_set(strtoul(arg_s, NULL, 10)); }
    }

    arg_s = NutHttpGetParameter(req, "sendsms");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", lbcom_gsmTM_sendsms_status_get()); }
      else { lbcom_gsmTM_sendsms_status_set(strtoul(arg_s, NULL, 10)); }
    }
    fflush(stream);
  }

  return 0;
}

int lbcom_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("LbCom" , stream);
  fprintf_XML_elt_int("HomeEasy_Manufacturer", lbcom_homeeasyTM_manufacturer_get(), stream);
  fprintf_XML_elt_int("HomeEasy_Group"       , lbcom_homeeasyTM_group_get()       , stream);
  fprintf_XML_elt_int("HomeEasy_Device"      , lbcom_homeeasyTM_device_get()      , stream);
  fprintf_XML_elt_int("HomeEasy_Status"      , lbcom_homeeasyTM_status_get()      , stream);
  fprintf_XML_elt_trailer("LbCom" , stream);

  return 0;
}

