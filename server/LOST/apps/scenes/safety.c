#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/ups.h"
#include "../../devices/power.h"
#include "../../devices/rack.h"
#include "../../devices/buzzer.h"
#include "../../devices/lbcomif.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "safety.h"

typedef struct _SAFETY_T
{ /* 0 if no error else error code */
  uint8_t http;
  uint8_t gsm;
  uint8_t ups_temp       :1;
  uint8_t ups_power      :1;
  uint8_t rack_temp      :1;
  uint8_t rack_alarm     :1;
} SAFETY_T;

typedef struct _SAFETY_VALUE_T
{
  uint8_t gsm_status;
  uint16_t ups_temp;
  uint16_t ups_temp_th;
  uint16_t rack_temp;
  uint16_t rack_temp_th;
} SAFETY_VALUE_T;

SAFETY_T safety_status;
SAFETY_T safety_control;
SAFETY_T safety_trig;
SAFETY_VALUE_T safety_value;

uint8_t safety_init(void)
{
  safety_status.http           = 0;
  safety_status.gsm            = 0;
  safety_status.ups_temp       = 0;
  safety_status.ups_power      = 0;
  safety_status.rack_temp      = 0;
  safety_status.rack_alarm     = 0;

  safety_control.http           = 1;
  safety_control.gsm            = 1;
  safety_control.ups_temp       = 1;
  safety_control.ups_power      = 1;
  safety_control.rack_temp      = 1;
  safety_control.rack_alarm     = 0; // Do not watch at the rack alarm when starting because the door is open !

  safety_trig.http           = 0;
  safety_trig.gsm            = 0;
  safety_trig.ups_temp       = 0;
  safety_trig.ups_power      = 0;
  safety_trig.rack_temp      = 0;
  safety_trig.rack_alarm     = 0;

  safety_value.gsm_status    = 0;
  safety_value.ups_temp          = 0;
  safety_value.ups_temp_th       = 213; /* 40C */
  safety_value.rack_temp         = 0;
  safety_value.rack_temp_th      = 213; /* 40C */

  NutThreadCreate("SafetyUnRD"  , SafetyUpsRackD  , 0, 512);
  NutThreadCreate("SafetyGsmD"  , SafetyGsmD  , 0, 512);
  NutThreadCreate("SafetyHttpD" , SafetyHttpD , 0, 512);
  NutRegisterCgi("safety.cgi", safety_form);

  return 0;
}

void safety_gsm_status_set(uint8_t gsm_status)
{
  safety_value.gsm_status = gsm_status;
}

uint16_t safety_ups_temp_value_get(void)
{
  return (safety_value.ups_temp);
}

uint16_t safety_rack_temp_value_get(void)
{
  return (safety_value.rack_temp);
}

/* This function is executed if a safety problem is detected */
uint8_t safety_action(char* msg)
{
  lbcomif_gsm_sms_send(msg);
  http_email_send(msg);

  return 0;
}

uint8_t safety_action_with_buzzer(char* msg)
{
  safety_action(msg);
  buzzer_start(1*60); /* 1 minute */

  return 0;
}

#define TEMP_NB 32
THREAD(SafetyUpsRackD, arg)
{
  uint16_t ups_temp[TEMP_NB] = { 139 }; /* 20C */
  uint16_t rack_temp[TEMP_NB] = { 139 }; /* 20C */

  uint8_t temp_index = 0;
  uint32_t temp_sum = 0;
  uint8_t i = 0;

  char msg[40];

  arg = arg;
  NutThreadSetPriority(100);

  while(1)
  {
    ups_temp[temp_index] = ups_temp_get();
    rack_temp[temp_index] = rack_temp_get();
    temp_index++; temp_index = temp_index % TEMP_NB;

    temp_sum = 0;
    for(i=0; i<TEMP_NB; i++) { temp_sum = temp_sum + ups_temp[i]; }
    if(!(safety_trig.ups_temp )) { safety_value.ups_temp = temp_sum / TEMP_NB; }
    if(!(safety_trig.ups_power)) { safety_status.ups_power = ups_power_status_get(); }

    if(safety_control.ups_temp )
    {
      if((!(safety_trig.ups_temp )) && (safety_value.ups_temp>=safety_value.ups_temp_th))
      {
        sprintf(msg, "Temperature-Alimentation-Elevee-%d", safety_value.ups_temp);
        safety_action_with_buzzer(msg);
        safety_trig.ups_temp  = 1;
      }
    }
    if(safety_control.ups_power)
    {
      if((!(safety_trig.ups_power)) && (safety_status.ups_power))
      {
        safety_action("Alerte-Coupure-Courant");
        safety_trig.ups_power = 1;
      }
    }

    temp_sum = 0;
    for(i=0; i<TEMP_NB; i++) { temp_sum = temp_sum + rack_temp[i]; }
    if(!(safety_trig.rack_temp )) { safety_value.rack_temp = temp_sum / TEMP_NB; }
    if(!(safety_trig.rack_alarm)) { safety_status.rack_alarm = rack_alarm_status_get(); }

    if(safety_control.rack_temp )
    {
      if((!(safety_trig.rack_temp )) && (safety_value.rack_temp>=safety_value.rack_temp_th))
      {
        sprintf(msg, "Temperature-Boitier-Elevee-%d", safety_value.rack_temp);
        safety_action_with_buzzer(msg);
        safety_trig.rack_temp = 1;
      }
    }
    if(safety_control.rack_alarm)
    {
      if((!(safety_trig.rack_alarm)) && (safety_status.rack_alarm))
      {
        safety_action_with_buzzer("Alerte-Boitier-Ouvert");
        safety_trig.rack_alarm = 1;
      }
    }

    buzzer_update();

    NutSleep(1000);
  }
}

THREAD(SafetyHttpD, arg)
{
  uint8_t http_nb = 0;
  uint8_t ret = 0;
  char msg[25];

  arg = arg;
  NutThreadSetPriority(103);

  while(1)
  {
    ret = http_status_get();
    if(0 != ret) { if(0xFF > http_nb) { http_nb++; } } else { http_nb = 0; }
    if(10 < http_nb) { safety_status.http = ret; } else { safety_status.http = 0; }
    if(safety_control.http)
    {
      if((!(safety_trig.http)) && (safety_status.http))
      {
        sprintf(msg, "Probleme-Internet-E%d", safety_status.http);
        safety_action(msg);
        safety_trig.http = 1;
      }
    }

    NutSleep(30000);
  }
}

int safety_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "ups_temp_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.ups_temp); }
      else { safety_trig.ups_temp = 0; buzzer_stop(); safety_control.ups_temp = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "ups_temp_th");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_value.ups_temp_th); }
      else { safety_value.ups_temp_th = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "ups_power_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.ups_power); }
      else { safety_trig.ups_power = 0; safety_control.ups_power = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_temp_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rack_temp); }
      else { safety_trig.rack_temp = 0; buzzer_stop(); safety_control.rack_temp = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_temp_th");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_value.rack_temp_th); }
      else { safety_value.rack_temp_th = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_alarm_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rack_alarm); }
      else { safety_trig.rack_alarm = 0; buzzer_stop(); safety_control.rack_alarm = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "http_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.http); }
      else { safety_trig.http = 0; safety_control.http = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "gsm_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.gsm); }
      else { safety_trig.gsm = 0; safety_control.gsm = strtoul(arg_s, NULL, 10); }
    }

    fflush(stream);
  }

  return 0;
}

int safety_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("Safety" , stream);
  fprintf_XML_elt_int("GSM_St"           , safety_value.gsm_status       , stream);
  fprintf_XML_elt_int("UPS_Temp"         , safety_value.ups_temp         , stream);
  fprintf_XML_elt_int("UPS_Temp_Th"      , safety_value.ups_temp_th      , stream);
  fprintf_XML_elt_int("UPS_Power"        , safety_status.ups_power       , stream);
  fprintf_XML_elt_int("Power0"           , power_get(POWER_0)            , stream);
  fprintf_XML_elt_int("Power1"           , power_get(POWER_1)            , stream);
  fprintf_XML_elt_int("Power2"           , power_get(POWER_2)            , stream);
  fprintf_XML_elt_int("Power3"           , power_get(POWER_3)            , stream);
  fprintf_XML_elt_int("RACK_Temp"        , safety_value.rack_temp        , stream);
  fprintf_XML_elt_int("RACK_Temp_Th"     , safety_value.rack_temp_th     , stream);
  fprintf_XML_elt_int("RACK_Alarm"       , safety_status.rack_alarm      , stream);
  fprintf_XML_elt_int("Buzzer"           , buzzer_state()                , stream);
  fprintf_XML_elt_int("HTTP"             , safety_status.http            , stream);
  fprintf_XML_elt_int("GSM"              , safety_status.gsm             , stream);

  fprintf_XML_elt_int("UPS_Temp_Ctrl"      , safety_control.ups_temp      , stream);
  fprintf_XML_elt_int("UPS_Power_Ctrl"     , safety_control.ups_power     , stream);
  fprintf_XML_elt_int("RACK_Temp_Ctrl"     , safety_control.rack_temp     , stream);
  fprintf_XML_elt_int("RACK_Alarm_Ctrl"    , safety_control.rack_alarm    , stream);
  fprintf_XML_elt_int("HTTP_Ctrl"          , safety_control.http          , stream);
  fprintf_XML_elt_int("GSM_Ctrl"           , safety_control.gsm           , stream);

  fprintf_XML_elt_int("UPS_Temp_Trig"      , safety_trig.ups_temp      , stream);
  fprintf_XML_elt_int("UPS_Power_Trig"     , safety_trig.ups_power     , stream);
  fprintf_XML_elt_int("RACK_Temp_Trig"     , safety_trig.rack_temp     , stream);
  fprintf_XML_elt_int("RACK_Alarm_Trig"    , safety_trig.rack_alarm    , stream);
  fprintf_XML_elt_int("HTTP_Trig"          , safety_trig.http          , stream);
  fprintf_XML_elt_int("GSM_Trig"           , safety_trig.gsm           , stream);
  fprintf_XML_elt_trailer("Safety" , stream);

  return 0;
}

