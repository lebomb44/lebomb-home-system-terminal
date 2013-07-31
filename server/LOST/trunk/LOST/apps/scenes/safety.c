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
#include "../../devices/gsm.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "../rooms/rooms.h"
#include "safety.h"

typedef struct _SAFETY_T
{ /* 0 if no error else error code */
  uint8_t http;
  uint8_t gsm;
  uint8_t rooms_error;
  uint8_t rooms_hum;
  uint8_t rooms_smoke;
  uint8_t rooms_temp_max :1;
  uint8_t rooms_temp_min :1;
  uint8_t ups_temp       :1;
  uint8_t ups_power      :1;
  uint8_t rack_temp      :1;
  uint8_t rack_alarm     :1;
} SAFETY_T;

typedef struct _SAFETY_VALUE_T
{
  ROOM_N_T room_error_nb;
  ROOM_N_T room_hum_nb;
  ROOM_N_T room_smoke_nb;
  uint16_t rooms_temp_max;
  uint16_t rooms_temp_max_th;
  ROOM_N_T room_temp_max_nb;
  uint16_t rooms_temp_min;
  uint16_t rooms_temp_min_th;
  ROOM_N_T room_temp_min_nb;
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
  safety_status.rooms_error    = 0;
  safety_status.rooms_hum      = 0;
  safety_status.rooms_smoke    = 0;
  safety_status.rooms_temp_max = 0;
  safety_status.rooms_temp_min = 0;
  safety_status.ups_temp       = 0;
  safety_status.ups_power      = 0;
  safety_status.rack_temp      = 0;
  safety_status.rack_alarm     = 0;

  safety_control.http           = 1;
  safety_control.gsm            = 1;
  safety_control.rooms_error    = 0; // TODO
  safety_control.rooms_hum      = 0; // TODO
  safety_control.rooms_smoke    = 0; // TODO
  safety_control.rooms_temp_max = 0; // TODO
  safety_control.rooms_temp_min = 0; // TODO
  safety_control.ups_temp       = 1;
  safety_control.ups_power      = 1;
  safety_control.rack_temp      = 1;
  safety_control.rack_alarm     = 0; // Do not watch at the rack alarm when starting because the door is open !

  safety_trig.http           = 0;
  safety_trig.gsm            = 0;
  safety_trig.rooms_error    = 0;
  safety_trig.rooms_hum      = 0;
  safety_trig.rooms_smoke    = 0;
  safety_trig.rooms_temp_max = 0;
  safety_trig.rooms_temp_min = 0;
  safety_trig.ups_temp       = 0;
  safety_trig.ups_power      = 0;
  safety_trig.rack_temp      = 0;
  safety_trig.rack_alarm     = 0;

  safety_value.room_error_nb     = ROOM_MAX;
  safety_value.room_hum_nb       = ROOM_MAX;
  safety_value.room_smoke_nb     = ROOM_MAX;
  safety_value.rooms_temp_max    = 213;
  safety_value.rooms_temp_max_th = 213;
  safety_value.room_temp_max_nb  = ROOM_MAX;
  safety_value.rooms_temp_min    = 213;
  safety_value.rooms_temp_min_th = 213;
  safety_value.room_temp_min_nb  = ROOM_MAX;
  safety_value.ups_temp          = 0;
  safety_value.ups_temp_th       = 213; /* 40°C */
  safety_value.rack_temp         = 0;
  safety_value.rack_temp_th      = 213; /* 40°C */

  NutThreadCreate("SafetyUnRD"  , SafetyUpsRackD  , 0, 512);
  NutThreadCreate("SafetyRoomsD", SafetyRoomsD, 0, 512);
  NutThreadCreate("SafetyGsmD"  , SafetyGsmD  , 0, 512);
  NutThreadCreate("SafetyHttpD" , SafetyHttpD , 0, 512);
  NutRegisterCgi("safety.cgi", safety_form);

  return 0;
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
  gsm_sms_send(msg);
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
  uint16_t ups_temp[TEMP_NB] = {0}; /* FIXME Should be set to a correct value : 20 C */
  uint16_t rack_temp[TEMP_NB] = {0}; /* FIXME Should be set to a correct value : 20 C */

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

THREAD(SafetyRoomsD, arg)
{
  char msg[40];

  arg = arg;
  NutThreadSetPriority(101);

  while(1)
  {
    if(!(safety_trig.rooms_error   )) { safety_status.rooms_error   = rooms_error_status_get  (&(safety_value.room_error_nb));    }
    if(!(safety_trig.rooms_hum     )) { safety_status.rooms_hum     = rooms_hum_status_get    (&(safety_value.room_hum_nb));      }
    if(!(safety_trig.rooms_smoke   )) { safety_status.rooms_smoke   = rooms_smoke_status_get  (&(safety_value.room_smoke_nb));    }
    if(!(safety_trig.rooms_temp_max)) { safety_value.rooms_temp_max = rooms_temp_max_value_get(&(safety_value.room_temp_max_nb)); }
    if(!(safety_trig.rooms_temp_min)) { safety_value.rooms_temp_min = rooms_temp_min_value_get(&(safety_value.room_temp_min_nb)); }

    if(safety_control.rooms_error)
    {
      if((!(safety_trig.rooms_error)) && (safety_status.rooms_error))
      {
        sprintf(msg, "Probleme-Acces-Module-%d-E%d", safety_value.room_error_nb, safety_status.rooms_error);
        safety_action(msg);
        safety_trig.rooms_error = 1;
      }
    }
    if(safety_control.rooms_hum)
    {
      if((!(safety_trig.rooms_hum)) && (rooms_hum_trig_get(&(safety_value.room_hum_nb))))
      {
        sprintf(msg, "Humidite-Piece-%d", safety_value.room_hum_nb);
        safety_action(msg);
        safety_trig.rooms_hum = 1;
      }
    }
    if(safety_control.rooms_smoke)
    {
      if((!(safety_trig.rooms_smoke)) && (rooms_smoke_trig_get(&(safety_value.room_smoke_nb))))
      {
        sprintf(msg, "Fumee-Piece-%d", safety_value.room_smoke_nb);
        safety_action_with_buzzer(msg);
        safety_trig.rooms_smoke = 1;
      }
    }
    if(safety_control.rooms_temp_max)
    {
      if((!(safety_trig.rooms_temp_max)) && (rooms_temp_max_trig_get(&(safety_value.room_temp_max_nb))))
      {
        sprintf(msg, "Temperature-Piece-%d-Elevee-%d", safety_value.room_temp_max_nb, safety_value.rooms_temp_max);
        safety_action_with_buzzer(msg);
        safety_trig.rooms_temp_max = 1;
      }
    }
    if(safety_control.rooms_temp_min)
    {
      if((!(safety_trig.rooms_temp_min)) && (rooms_temp_min_trig_get(&(safety_value.room_temp_min_nb))))
      {
        sprintf(msg, "Temperature-Piece-%d-Basse-%d" , safety_value.room_temp_min_nb, safety_value.rooms_temp_min);
        safety_action(msg);
        safety_trig.rooms_temp_min = 1;
      }
    }

    NutSleep(1000);
  }
}

THREAD(SafetyGsmD, arg)
{
  uint8_t gsm_nb = 0;
  uint8_t ret = 0;
  char msg[20];

  arg = arg;
  NutThreadSetPriority(102);

  NutSleep(3000);

  while(1)
  {
    ret = gsm_status_get();
    if(0 != ret) { if(0xFF > gsm_nb) { gsm_nb++; } } else { gsm_nb = 0; }
    if(10 < gsm_nb) { safety_status.gsm = ret; } else { safety_status.gsm = 0; }
    if(safety_control.gsm)
    {
      if((!(safety_trig.gsm)) && (safety_status.gsm))
      {
        sprintf(msg, "Probleme-GSM-E%d", safety_status.gsm);
        safety_action(msg);
        safety_trig.gsm = 1;
      }
    }

    NutSleep(30000);
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
    arg_s = NutHttpGetParameter(req, "rooms_error_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rooms_error); }
      else { safety_trig.rooms_error = 0; safety_control.rooms_error = strtoul(arg_s, NULL, 10); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_max_ctrl");
    if(arg_s)
    {  
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rooms_temp_max); }
      else { safety_trig.rooms_temp_max = 0; buzzer_stop(); safety_control.rooms_temp_max = strtoul(arg_s, NULL, 10); rooms_temp_max_control_set(safety_control.rooms_temp_max); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_max_th");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_value.rooms_temp_max_th); }
      else { safety_value.rooms_temp_max_th = strtoul(arg_s, NULL, 10); rooms_temp_max_th_set(safety_value.rooms_temp_max_th); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_min_ctrl");
    if(arg_s)
    {  
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rooms_temp_min); }
      else { safety_trig.rooms_temp_min = 0; safety_control.rooms_temp_min = strtoul(arg_s, NULL, 10); rooms_temp_min_control_set(safety_control.rooms_temp_min); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_temp_min_th");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_value.rooms_temp_min_th); }
      else { safety_value.rooms_temp_min_th = strtoul(arg_s, NULL, 10); rooms_temp_min_th_set(safety_value.rooms_temp_min_th); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_hum_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rooms_hum); }
      else { safety_trig.rooms_hum = 0; safety_control.rooms_hum = strtoul(arg_s, NULL, 10); rooms_hum_control_set(safety_control.rooms_hum); }
    }
    arg_s = NutHttpGetParameter(req, "rooms_smoke_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", safety_control.rooms_smoke); }
      else { safety_trig.rooms_smoke = 0; buzzer_stop(); safety_control.rooms_smoke = strtoul(arg_s, NULL, 10); rooms_smoke_control_set(safety_control.rooms_smoke); }
    }
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
  fprintf_XML_elt_int("Rooms_Error"      , safety_status.rooms_error     , stream);
  fprintf_XML_elt_int("Rooms_Error_Nb"   , safety_value.room_error_nb    , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max"   , safety_value.rooms_temp_max   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Max_Th", safety_value.rooms_temp_max_th, stream);
  fprintf_XML_elt_int("Rooms_Temp_Max_Nb", safety_value.room_temp_max_nb , stream);
  fprintf_XML_elt_int("Rooms_Temp_Min"   , safety_value.rooms_temp_min   , stream);
  fprintf_XML_elt_int("Rooms_Temp_Min_Th", safety_value.rooms_temp_min_th, stream);
  fprintf_XML_elt_int("Rooms_Temp_Min_Nb", safety_value.room_temp_min_nb , stream);
  fprintf_XML_elt_int("Rooms_Hum"        , safety_status.rooms_hum       , stream);
  fprintf_XML_elt_int("Rooms_Hum_Nb"     , safety_value.room_hum_nb      , stream);
  fprintf_XML_elt_int("Rooms_Smoke"      , safety_status.rooms_smoke     , stream);
  fprintf_XML_elt_int("Rooms_Smoke_Nb"   , safety_value.room_smoke_nb    , stream);
  fprintf_XML_elt_int("UPS_Temp"         , safety_value.ups_temp         , stream);
  fprintf_XML_elt_int("UPS_Temp_Th"      , safety_value.ups_temp_th      , stream);
  fprintf_XML_elt_int("UPS_Power"        , safety_status.ups_power       , stream);
  fprintf_XML_elt_int("Power0"           , power_get(POWER_0)            , stream);
  fprintf_XML_elt_int("Power1"           , power_get(POWER_1)            , stream);
  fprintf_XML_elt_int("Power2"           , power_get(POWER_2)            , stream);
  fprintf_XML_elt_int("RACK_Temp"        , safety_value.rack_temp        , stream);
  fprintf_XML_elt_int("RACK_Temp_Th"     , safety_value.rack_temp_th     , stream);
  fprintf_XML_elt_int("RACK_Alarm"       , safety_status.rack_alarm      , stream);
  fprintf_XML_elt_int("Heater"           , power_get(POWER_3)            , stream);
  fprintf_XML_elt_int("Buzzer"           , buzzer_state()                , stream);
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
