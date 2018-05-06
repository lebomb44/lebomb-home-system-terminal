#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../config.h"
#include "../../devices/volume.h"
#include "../../devices/buzzer.h"
#include "../../services/http.h"
#include "../../services/web.h"

#include "../lbcom/lbcom_homeeasyTM.h"
#include "../lbcom/lbcom_gsmTC.h"

#include "alarm.h"

typedef struct _ALARM_T
{
  uint8_t status;
  ALARM_TYPE_T type;
  uint8_t control;
  time_t time;
  uint8_t trig;
} ALARM_T;

ALARM_T alarm_perimeter;
ALARM_T alarm_volume;
ALARM_T alarm_simulation;

uint8_t alarm_init(void)
{
  alarm_perimeter.status  = 0;
  alarm_perimeter.type    = ALARM_TYPE_OFF_AUTO;
  alarm_perimeter.control = 0; // TODO
  alarm_perimeter.time    = 0;
  alarm_perimeter.trig    = 0;

  alarm_volume.status  = 0;
  alarm_volume.type    = ALARM_TYPE_OFF_AUTO;
  alarm_volume.control = 0; // TODO
  alarm_volume.time    = 0;
  alarm_volume.trig    = 0;

  alarm_simulation.status  = 0;
  alarm_simulation.type    = ALARM_TYPE_OFF_AUTO;
  alarm_simulation.control = 0;
  alarm_simulation.time    = 0;
  alarm_simulation.trig    = 0;

  NutThreadCreate("AlarmD", AlarmD, 0, 512);
  NutRegisterCgi("alarm.cgi", alarm_form);

  /* Set alarm ON in case of spurious reset */
  /* alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); TODO */
  /* alarm_volume_set(ALARM_TYPE_ON_MANUAL); TODO */

  return 0;
}

/* This function is executed if an alarm is detected */
uint8_t alarm_action(char* msg)
{
  lbcom_gsmTC_sms_send(msg);
  http_email_send(msg);

  return 0;
}

/* This function is executed if an alarm is detected */
uint8_t alarm_action_with_buzzer(char* msg)
{
  alarm_action(msg);
  buzzer_start(60*60); /* 60 minutes */

  return 0;
}

void alarm_perimeter_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(ALARM_TYPE_MAX <= type) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(ALARM_TYPE_OFF_AUTO == type)   { if(ALARM_TYPE_ON_AUTO == alarm_perimeter.type) { alarm_perimeter.control = 0; alarm_perimeter.time = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(ALARM_TYPE_OFF_MANUAL == type) { alarm_perimeter.control = 0; alarm_perimeter.time = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(ALARM_TYPE_ON_AUTO == type)    { if(ALARM_TYPE_ON_MANUAL != alarm_perimeter.type) { alarm_perimeter.control = 1; alarm_perimeter.time = time(NULL) + alarm_perimeter.control; } else { return; } }
  /* In any case, user can force ON manually */
  if(ALARM_TYPE_ON_MANUAL == type)  { alarm_perimeter.control = 1; alarm_perimeter.time = time(NULL) + alarm_perimeter.control; }
  /* Save the new mode set */
  alarm_perimeter.type = type;
  /* Reset the trigger status */
  alarm_perimeter.trig = 0;
  /* Stop the buzzer */
  buzzer_stop();
}

void alarm_volume_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(ALARM_TYPE_MAX <= type) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(ALARM_TYPE_OFF_AUTO == type)   { if(ALARM_TYPE_ON_AUTO == alarm_volume.type) { alarm_volume.control = 0; alarm_volume.time = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(ALARM_TYPE_OFF_MANUAL == type) { alarm_volume.control = 0; alarm_volume.time = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(ALARM_TYPE_ON_AUTO == type)    { if(ALARM_TYPE_ON_MANUAL != alarm_volume.type) { alarm_volume.control = 1; alarm_volume.time = time(NULL) + alarm_volume.control; } else { return; } }
  /* In any case, user can force ON manually */
  if(ALARM_TYPE_ON_MANUAL == type)  { alarm_volume.control = 1; alarm_volume.time = time(NULL) + alarm_volume.control; }
  /* Save the new mode set */
  alarm_volume.type = type;
  /* Reset the trigger status */
  alarm_volume.trig = 0;
  /* Stop the buzzer */
  buzzer_stop();
}

void alarm_simulation_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(ALARM_TYPE_MAX <= type) { return; }

  /* Mode OFF in any case */
  if((ALARM_TYPE_OFF_MANUAL == type) || (ALARM_TYPE_OFF_AUTO == type)) { alarm_simulation.control = 0; }
  /* Mode ON in any case */
  if((ALARM_TYPE_ON_MANUAL == type ) || (ALARM_TYPE_ON_AUTO == type)) { alarm_simulation.control = 1; }
  /* Save the new mode set */
  alarm_simulation.type = type;
  /* Reset the trigger status */
  alarm_simulation.trig = 0;
}

THREAD(AlarmD, arg)
{
  char msg[60] = { 0 };
  uint32_t homeeasyTM_manufacturer = 0;
  uint8_t homeeasyTM_group = 0;
  uint8_t homeeasyTM_device = 0;
  uint8_t homeeasyTM_status = 0;

  arg = arg;
  NutThreadSetPriority(105);

  while(1)
  {
    homeeasyTM_manufacturer = lbcom_homeeasyTM_manufacturer_get();
    homeeasyTM_group = lbcom_homeeasyTM_group_get();
    homeeasyTM_device = lbcom_homeeasyTM_device_get();
    homeeasyTM_status = lbcom_homeeasyTM_status_get();

    /* Check the authorized codes */
    if(((0xFCE1CE == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)) \
    || ((0xFCBDD6 == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)) \
    || ((0xFCDAD2 == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)) \
    || ((0xFCBC2E == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)) \
    || ((0xD0A3B2 == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)) \
    || ((0xFCC302 == homeeasyTM_manufacturer) && (0x0 == homeeasyTM_group) && (0x2 == homeeasyTM_device)))
    {
      if(0 == homeeasyTM_status)
      {
        buzzer_stop();
        buzzer_on(); NutSleep(500); buzzer_off();
        alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); alarm_volume_set(ALARM_TYPE_OFF_MANUAL);
      }
      else if(1 == homeeasyTM_status)
      {
        buzzer_stop();
        buzzer_on(); NutSleep(500); buzzer_off(); NutSleep(500);
        buzzer_on(); NutSleep(500); buzzer_off(); NutSleep(500);
        buzzer_on(); NutSleep(500); buzzer_off();
        alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); alarm_volume_set(ALARM_TYPE_ON_MANUAL);
      }
      lbcom_homeeasyTM_code_reset();
    }

    /* Only update the status if the alarm did not trigger */
    if(0 == alarm_perimeter.trig)
    {
      /* Update status */
      alarm_perimeter.status = volume_status_group1_get();
      /* If alarm is enabled */
      if(1 == alarm_perimeter.control)
      {
        if(0 != alarm_perimeter.status)
        {
          sprintf(msg, "Alarme-Perimetre-%d", alarm_perimeter.status);
          alarm_action_with_buzzer(msg);
          alarm_perimeter.trig = 1;
        }
      }
    }
    if(0 == alarm_volume.trig)
    {
      /* Update status */
      alarm_volume.status = volume_status_group2_get();
      /* If alarm is enabled */
      if(1 == alarm_volume.control)
      {
        if(0 != alarm_volume.status)
        {
          sprintf(msg, "Alarme-Volume-%d", alarm_volume.status);
          alarm_action_with_buzzer(msg);
          alarm_volume.trig = 1;
        }
      }
    }
    if(0 == alarm_simulation.trig)
    {
      /* If alarm is enabled */
      if(1 == alarm_simulation.control)
      {
        if(0 != alarm_simulation.status)
        {
          sprintf(msg, "Alarme-Simulation-%d", alarm_simulation.status);
          alarm_action_with_buzzer(msg);
          alarm_simulation.trig = 1;
        }
      }
    }

    NutSleep(1000);
  }
}

int alarm_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;
  uint8_t password_ok = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "password");
    if(arg_s)
    {
      if(0 == strncmp(arg_s, LOST_PASSWORD, strnlen(LOST_PASSWORD, 10))) { password_ok = 1; }
      else { password_ok = 0; }
    }
    arg_s = NutHttpGetParameter(req, "perimeter_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_perimeter.control); }
      else 
      {
        if(1 == password_ok)
        {
          if(0 < strtoul(arg_s, NULL, 10))
          {
            alarm_perimeter_set(ALARM_TYPE_ON_MANUAL);
            fputs_P(PSTR("ALARM PERIMETER ON OK"), stream);
          }
          else
          {
            alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL);
            fputs_P(PSTR("ALARM PERIMETER OFF OK"), stream);
          }
        }
      }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_volume.control); }
      else
      {
        if(1 == password_ok)
        {
          if(0 < strtoul(arg_s, NULL, 10))
          {
            alarm_volume_set(ALARM_TYPE_ON_MANUAL);
            fputs_P(PSTR("ALARM VOLUME ON OK"), stream);
          }
          else
          {
            alarm_volume_set(ALARM_TYPE_OFF_MANUAL);
            fputs_P(PSTR("ALARM VOLUME OFF OK"), stream);
          }
        }
      }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_simulation.control); }
      else
      {
        if(1 == password_ok)
        {
          if(0 < strtoul(arg_s, NULL, 10))
          {
            alarm_simulation_set(ALARM_TYPE_ON_MANUAL);
            fputs_P(PSTR("ALARM SIMULATION ON OK"), stream);
          }
          else
          {
            alarm_simulation_set(ALARM_TYPE_OFF_MANUAL);
            fputs_P(PSTR("ALARM SIMULATION OFF OK"), stream);
          }
        }
      }
    }
    fflush(stream);
  }

  return 0;
}

int alarm_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("Alarm", stream);
  fprintf_XML_elt_int("Perimeter"      , alarm_perimeter.status , stream);
  fprintf_XML_elt_int("Perimeter_Ctrl" , alarm_perimeter.control , stream);
  fprintf_XML_elt_int("Perimeter_Trig" , alarm_perimeter.trig , stream);

  fprintf_XML_elt_int("Volume"         , alarm_volume.status    , stream);
  fprintf_XML_elt_int("Volume_Ctrl"    , alarm_volume.control    , stream);
  fprintf_XML_elt_int("Volume_Trig"    , alarm_volume.trig    , stream);

  fprintf_XML_elt_int("Simulation"     , alarm_simulation.status, stream);
  fprintf_XML_elt_int("Simulation_Ctrl", alarm_simulation.control, stream);
  fprintf_XML_elt_int("Simulation_Trig", alarm_simulation.trig, stream);
  fprintf_XML_elt_trailer("Alarm", stream);

  return 0;
}
