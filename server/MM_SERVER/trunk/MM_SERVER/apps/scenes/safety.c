#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/ups.h"
#include "../../devices/rack.h"
#include "../../devices/buzzer.h"
#include "../../devices/gsm.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "../rooms/rooms.h"
#include "safety.h"

typedef struct _SAFETY_T
{ /* 0 if no error else error code */
  uint8_t rooms_error;
  uint8_t rooms_temp_max;
  uint8_t rooms_temp_min;
  uint8_t rooms_hum;
  uint8_t rooms_smoke;
  uint8_t http;
  uint8_t gsm;
  uint8_t ups_temp       :1;
  uint8_t ups_power      :1;
  uint8_t rack_temp      :1;
  uint8_t rack_alarm     :1;
} SAFETY_T;

typedef struct _SAFETY_VALUE_T
{
  uint16_t rooms_temp_max;
  uint16_t rooms_temp_max_th;
  uint16_t rooms_temp_min;
  uint16_t rooms_temp_min_th;
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
  safety_status.rooms_error    = 0;
  safety_status.rooms_temp_max = 0;
  safety_status.rooms_temp_min = 0;
  safety_status.rooms_hum      = 0;
  safety_status.rooms_smoke    = 0;
  safety_status.ups_temp       = 0;
  safety_status.ups_power      = 0;
  safety_status.rack_temp      = 0;
  safety_status.rack_alarm     = 0;
  safety_status.http           = 0;
  safety_status.gsm            = 0;

  safety_control.rooms_error    = 0; // TODO
  safety_control.rooms_temp_max = 0; // TODO
  safety_control.rooms_temp_min = 0; // TODO
  safety_control.rooms_hum      = 0; // TODO
  safety_control.rooms_smoke    = 0; // TODO
  safety_control.ups_temp       = 0; // TODO
  safety_control.ups_power      = 0; // TODO
  safety_control.rack_temp      = 0; // TODO
  safety_control.rack_alarm     = 0; // Do not watch at the rack alarm when stating because the door is open !
  safety_control.http           = 0; // TODO
  safety_control.gsm            = 0; // TODO

  safety_trig.rooms_error    = 0;
  safety_trig.rooms_temp_max = 0;
  safety_trig.rooms_temp_min = 0;
  safety_trig.rooms_hum      = 0;
  safety_trig.rooms_smoke    = 0;
  safety_trig.ups_temp       = 0;
  safety_trig.ups_power      = 0;
  safety_trig.rack_temp      = 0;
  safety_trig.rack_alarm     = 0;
  safety_trig.http           = 0;
  safety_trig.gsm            = 0;

  safety_value.rooms_temp_max    = 213;
  safety_value.rooms_temp_max_th = 213;
  safety_value.rooms_temp_min    = 213;
  safety_value.rooms_temp_min_th = 213;
  safety_value.ups_temp = 0;
  safety_value.ups_temp_th = 213; /* 40°C */
  safety_value.rack_temp = 0;
  safety_value.rack_temp_th = 213; /* 40°C */

  NutThreadCreate("SafetyUnRD"  , SafetyUpsRackD  , 0, 512);
  NutThreadCreate("SafetyRoomsD", SafetyRoomsD, 0, 512);
  NutThreadCreate("SafetyGsmD"  , SafetyGsmD  , 0, 512);
  NutThreadCreate("SafetyHttpD" , SafetyHttpD , 0, 512);
  NutRegisterCgi("safety.cgi", safety_form);

  return 0;
}

/* This function is executed if a safety problem is detected */
uint8_t safety_action(char* msg)
{
  gsm_sms_send(gsm1, msg);
  gsm_sms_send(gsm2, msg);
  http_email_send(msg);

  return 0;
}

uint8_t safety_action_with_buzzer(char* msg)
{
  safety_action(msg);
  buzzer_set();

  return 0;
}

#define TEMP_NB 32
THREAD(SafetyUpsRackD, arg)
{
  uint16_t ups_temp[TEMP_NB] = {0};
  uint16_t rack_temp[TEMP_NB] = {0};

  uint8_t temp_index = 0;
  uint32_t temp_sum = 0;
  uint8_t i = 0;

  NutThreadSetPriority(20);

  while(1)
  {
    ups_temp[temp_index] = ups_temp_get();
    rack_temp[temp_index] = rack_temp_get();
    temp_index++; temp_index = temp_index % TEMP_NB;

    temp_sum = 0;
    for(i=0; i<TEMP_NB; i++) { temp_sum = temp_sum + ups_temp[i]; }
    safety_value.ups_temp = temp_sum / TEMP_NB;
    safety_status.ups_power = ups_power_status_get();
    if(safety_control.ups_temp ) { if((!(safety_trig.ups_temp )) && (safety_value.ups_temp>=safety_value.ups_temp_th)) { safety_action_with_buzzer("UPS-Temp" ); safety_trig.ups_temp  = 1; } }
    if(safety_control.ups_power) { if((!(safety_trig.ups_power)) && (safety_status.ups_power                        )) { safety_action("UPS-Power"); safety_trig.ups_power = 1; } }

    temp_sum = 0;
    for(i=0; i<TEMP_NB; i++) { temp_sum = temp_sum + rack_temp[i]; }
    safety_value.rack_temp = temp_sum / TEMP_NB;
    safety_status.rack_alarm = rack_alarm_status_get();
    if(safety_control.rack_temp ) { if((!(safety_trig.rack_temp )) && (safety_value.rack_temp>=safety_value.rack_temp_th)) { safety_action_with_buzzer("RACK-Temp" ); safety_trig.rack_temp  = 1; } }
    if(safety_control.rack_alarm) { if((!(safety_trig.rack_alarm)) && (safety_status.rack_alarm                         )) { safety_action_with_buzzer("RACK-Alarm"); safety_trig.rack_alarm = 1; } }

    NutSleep(1000);
  }
}

THREAD(SafetyRoomsD, arg)
{
  NutThreadSetPriority(21);

  while(1)
  {
    safety_status.rooms_error   = rooms_error_status_get();
    safety_value.rooms_temp_max = rooms_temp_max_value_get();
    safety_value.rooms_temp_min = rooms_temp_min_value_get();
    safety_status.rooms_hum     = rooms_hum_status_get();
    safety_status.rooms_smoke   = rooms_smoke_status_get();
    if(safety_control.rooms_error   ) { if((!(safety_trig.rooms_error   )) && (safety_status.rooms_error)) { safety_action("ROOM-Error"    ); safety_trig.rooms_error    = 1; } }
    if(safety_control.rooms_temp_max) { if((!(safety_trig.rooms_temp_max)) && (rooms_temp_max_trig_get())) { safety_action_with_buzzer("ROOM-Temp-Max" ); safety_trig.rooms_temp_max = 1; } }
    if(safety_control.rooms_temp_min) { if((!(safety_trig.rooms_temp_min)) && (rooms_temp_min_trig_get())) { safety_action("ROOM-Temp-Min" ); safety_trig.rooms_temp_min = 1; } }
    if(safety_control.rooms_hum     ) { if((!(safety_trig.rooms_hum     )) && (rooms_hum_trig_get()     )) { safety_action("ROOM-Hum"      ); safety_trig.rooms_hum      = 1; } }
    if(safety_control.rooms_smoke   ) { if((!(safety_trig.rooms_smoke   )) && (rooms_smoke_trig_get()   )) { safety_action_with_buzzer("ROOM-Smoke"    ); safety_trig.rooms_smoke    = 1; } }

    NutSleep(1000);
  }
}

THREAD(SafetyGsmD, arg)
{
  uint8_t gsm_nb = 0;
  uint8_t ret = 0;
  char msg[10];

  NutThreadSetPriority(22);

  NutSleep(3000);

  while(1)
  {
    ret = gsm_status_get();
    if(ret != 0) { if(gsm_nb < 0xFF) { gsm_nb++; } } else { gsm_nb = 0; }
    if(gsm_nb > 10) { safety_status.gsm = ret; } else { safety_status.gsm = 0; }
    if(safety_control.gsm) { if((!(safety_trig.gsm)) && (safety_status.gsm)) { sprintf(msg, "GSM-%d", safety_control.gsm); safety_action(msg); safety_trig.gsm = 1; } }

    NutSleep(30000);
  }
}

THREAD(SafetyHttpD, arg)
{
  uint8_t http_nb = 0;
  uint8_t ret = 0;
  char msg[10];

  NutThreadSetPriority(23);

  while(1)
  {
    ret = http_status_get();
    if(ret != 0) { if(http_nb < 0xFF) { http_nb++; } } else { http_nb = 0; }
    if(http_nb > 10) { safety_status.http = ret; } else { safety_status.http = 0; }
    if(safety_control.http) { if((!(safety_trig.http)) && (safety_status.http)) { sprintf(msg, "HTTP-%d", safety_control.http); safety_action(msg); safety_trig.http = 1; } }

    NutSleep(30000);
  }
}

int safety_form(FILE * stream, REQUEST * req)
{
  char* arg_s=NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    arg_s = NutHttpGetParameter(req, "rooms_error_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rooms_error); }
      else { safety_trig.rooms_error = 0; safety_control.rooms_error = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_max_ctrl");
    if(arg_s)
    {  
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rooms_temp_max); }
      else { safety_trig.rooms_temp_max = 0; safety_control.rooms_temp_max = strtoul(arg_s, NULL, 10); rooms_temp_max_control_set(safety_control.rooms_temp_max); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_max_th");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_value.rooms_temp_max_th); }
      else { safety_value.rooms_temp_max_th = strtoul(arg_s, NULL, 10); rooms_temp_max_th_set(safety_value.rooms_temp_max_th); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_min_ctrl");
    if(arg_s)
    {  
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rooms_temp_min); }
      else { safety_trig.rooms_temp_min = 0; safety_control.rooms_temp_min = strtoul(arg_s, NULL, 10); rooms_temp_min_control_set(safety_control.rooms_temp_min); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_min_th");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_value.rooms_temp_min_th); }
      else { safety_value.rooms_temp_min_th = strtoul(arg_s, NULL, 10); rooms_temp_min_th_set(safety_value.rooms_temp_min_th); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_hum_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rooms_hum); }
      else { safety_trig.rooms_hum = 0; safety_control.rooms_hum = strtoul(arg_s, NULL, 10); rooms_hum_control_set(safety_control.rooms_hum); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_smoke_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rooms_smoke); }
      else { safety_trig.rooms_smoke = 0; safety_control.rooms_smoke = strtoul(arg_s, NULL, 10); rooms_smoke_control_set(safety_control.rooms_smoke); }
    }
    arg_s = NutHttpGetParameter(req, "ups_temp_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.ups_temp); }
      else { safety_trig.ups_temp = 0; safety_control.ups_temp = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "ups_temp_th");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_value.ups_temp_th); }
      else { safety_value.ups_temp_th = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "ups_power_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.ups_power); }
      else { safety_trig.ups_power = 0; safety_control.ups_power = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_temp_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rack_temp); }
      else { safety_trig.rack_temp = 0; safety_control.rack_temp = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_temp_th");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_value.rack_temp_th); }
      else { safety_value.rack_temp_th = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rack_alarm_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.rack_alarm); }
      else { safety_trig.rack_alarm = 0; safety_control.rack_alarm = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "http_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.http); }
      else { safety_trig.http = 0; safety_control.http = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "gsm_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", safety_control.gsm); }
      else { safety_trig.gsm = 0; safety_control.gsm = strtoul(arg_s, NULL, 10); }
    }

    fflush(stream);
  }

  return 0;
}

int safety_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("Safety" , stream);
  fprintf_XML_elt_int("Rooms_Error"      , safety_status.rooms_error     , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max"   , safety_value.rooms_temp_max   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max_Th", safety_value.rooms_temp_max_th, stream);
  fprintf_XML_elt_int("Rooms_Temp_Min"   , safety_value.rooms_temp_min   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Min_Th", safety_value.rooms_temp_min_th, stream);
  fprintf_XML_elt_int("Rooms_Hum"        , safety_status.rooms_hum       , stream);
  fprintf_XML_elt_int("Rooms_Smoke"      , safety_status.rooms_smoke     , stream);
  fprintf_XML_elt_int("UPS_Temp"         , safety_value.ups_temp         , stream);
  fprintf_XML_elt_int("UPS_Temp_Th"      , safety_value.ups_temp_th      , stream);
  fprintf_XML_elt_int("UPS_Power"        , safety_status.ups_power       , stream);
  fprintf_XML_elt_int("RACK_Temp"        , safety_value.rack_temp        , stream);
  fprintf_XML_elt_int("RACK_Temp_Th"     , safety_value.rack_temp_th     , stream);
  fprintf_XML_elt_int("RACK_Alarm"       , safety_status.rack_alarm      , stream);
  fprintf_XML_elt_int("HTTP"             , safety_status.http            , stream);
  fprintf_XML_elt_int("GSM"              , safety_status.gsm             , stream);

  fprintf_XML_elt_int("Rooms_Error_Ctrl"   , safety_control.rooms_error   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max_Ctrl", safety_control.rooms_temp_max, stream);
  fprintf_XML_elt_int("Rooms_Temp_Min_Ctrl", safety_control.rooms_temp_min, stream);
  fprintf_XML_elt_int("Rooms_Hum_Ctrl"     , safety_control.rooms_hum     , stream);
  fprintf_XML_elt_int("Rooms_Smoke_Ctrl"   , safety_control.rooms_smoke   , stream);
  fprintf_XML_elt_int("UPS_Temp_Ctrl"      , safety_control.ups_temp      , stream);
  fprintf_XML_elt_int("UPS_Power_Ctrl"     , safety_control.ups_power     , stream);
  fprintf_XML_elt_int("RACK_Temp_Ctrl"     , safety_control.rack_temp     , stream);
  fprintf_XML_elt_int("RACK_Alarm_Ctrl"    , safety_control.rack_alarm    , stream);
  fprintf_XML_elt_int("HTTP_Ctrl"          , safety_control.http          , stream);
  fprintf_XML_elt_int("GSM_Ctrl"           , safety_control.gsm           , stream);

  fprintf_XML_elt_int("Rooms_Error_Trig"   , safety_trig.rooms_error   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max_Trig", safety_trig.rooms_temp_max, stream);
  fprintf_XML_elt_int("Rooms_Temp_Min_Trig", safety_trig.rooms_temp_min, stream);
  fprintf_XML_elt_int("Rooms_Hum_Trig"     , safety_trig.rooms_hum     , stream);
  fprintf_XML_elt_int("Rooms_Smoke_Trig"   , safety_trig.rooms_smoke   , stream);
  fprintf_XML_elt_int("UPS_Temp_Trig"      , safety_trig.ups_temp      , stream);
  fprintf_XML_elt_int("UPS_Power_Trig"     , safety_trig.ups_power     , stream);
  fprintf_XML_elt_int("RACK_Temp_Trig"     , safety_trig.rack_temp     , stream);
  fprintf_XML_elt_int("RACK_Alarm_Trig"    , safety_trig.rack_alarm    , stream);
  fprintf_XML_elt_int("HTTP_Trig"          , safety_trig.http          , stream);
  fprintf_XML_elt_int("GSM_Trig"           , safety_trig.gsm           , stream);
  fprintf_XML_elt_trailer("Safety" , stream);

  return 0;
}
