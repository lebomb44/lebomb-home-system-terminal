#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/volume.h"
#include "../../devices/buzzer.h"
#include "../../devices/gsm.h"
#include "../../services/http.h"
#include "../../services/web.h"
#include "../rooms/rooms.h"
#include "alarm.h"

typedef struct ALARM_T
{
  uint8_t perimeter;
  uint8_t volume;
  uint8_t simulation;
} ALARM_T;

ALARM_T alarm_status;
ALARM_T alarm_type;
ALARM_T alarm_control;
ALARM_T alarm_trig;

uint8_t alarm_init(void)
{
  alarm_status.perimeter  = 0;
  alarm_status.volume     = 0;
  alarm_status.simulation = 0;

  alarm_type.perimeter  = ALARM_TYPE_OFF_AUTO;
  alarm_type.volume     = ALARM_TYPE_OFF_AUTO;
  alarm_type.simulation = ALARM_TYPE_OFF_AUTO;

  alarm_control.perimeter  = 0; // TODO
  alarm_control.volume     = 0; // TODO
  alarm_control.simulation = 0;

  alarm_trig.perimeter  = 0;
  alarm_trig.volume     = 0;
  alarm_trig.simulation = 0;

  NutThreadCreate("AlarmD", AlarmD, 0, 512);
  NutRegisterCgi("alarm.cgi", alarm_form);

  /* Set alarm ON in case of reset */
  /* alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); TODO */
  /* alarm_volume_set(ALARM_TYPE_ON_MANUAL); TODO */

  return 0;
}

/* This function is executed if an alarm is detected */
uint8_t alarm_action(char* msg)
{
  gsm_sms_send(msg);
  http_email_send(msg);

  return 0;
}

/* This function is executed if an alarm is detected */
uint8_t alarm_action_with_buzzer(char* msg)
{
  alarm_action(msg);
  buzzer_start(5*60); /* 5 minutes */

  return 0;
}

void alarm_perimeter_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(type >= ALARM_TYPE_MAX) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(type == ALARM_TYPE_OFF_AUTO)   { if(alarm_type.perimeter == ALARM_TYPE_ON_AUTO) { alarm_control.perimeter = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(type == ALARM_TYPE_OFF_MANUAL) { alarm_control.perimeter = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(type == ALARM_TYPE_ON_AUTO)    { if(alarm_type.perimeter != ALARM_TYPE_ON_MANUAL) { alarm_control.perimeter = 30; } else { return; } }
  /* In any case, user can force ON manually */
  if(type == ALARM_TYPE_ON_MANUAL)  { alarm_control.perimeter = 30; }
  /* Save the new mode set */
  alarm_type.perimeter = type;
  /* Reset the trigger status */
  alarm_trig.perimeter = 0;
  /* Stop the buzzer */
  buzzer_stop();
  /* Stop the alarm monitoring in every rooms */
  rooms_perimeter_control_set(0);
  NutSleep(100);
  /* Reset the alarm trigger status in every rooms */
  rooms_perimeter_trig_set(0);
}

void alarm_volume_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(type >= ALARM_TYPE_MAX) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(type == ALARM_TYPE_OFF_AUTO)   { if(alarm_type.volume == ALARM_TYPE_ON_AUTO) { alarm_control.volume = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(type == ALARM_TYPE_OFF_MANUAL) { alarm_control.volume = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(type == ALARM_TYPE_ON_AUTO)    { if(alarm_type.volume != ALARM_TYPE_ON_MANUAL) { alarm_control.volume = 30; } else { return; } }
  /* In any case, user can force ON manually */
  if(type == ALARM_TYPE_ON_MANUAL)  { alarm_control.volume = 30; }
  /* Save the new mode set */
  alarm_type.volume = type;
  /* Reset the trigger status */
  alarm_trig.volume = 0;
  /* Stop the buzzer */
  buzzer_stop();
  /* Stop the alarm monitoring in every rooms */
  rooms_volume_control_set(0);
  NutSleep(100);
  /* Reset the alarm trigger status in every rooms */
  rooms_volume_trig_set(0);
}

void alarm_simulation_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(type >= ALARM_TYPE_MAX) { return; }

  /* Mode OFF in any case */
  if((type == ALARM_TYPE_OFF_MANUAL) || (type == ALARM_TYPE_OFF_AUTO)) { alarm_control.simulation = 0; }
  /* Mode ON in any case */
  if((type == ALARM_TYPE_ON_MANUAL ) || (type == ALARM_TYPE_ON_AUTO )) { alarm_control.simulation = 1; }
  /* Save the new mode set */
  alarm_type.simulation = type;
  /* Reset the trigger status */
  alarm_trig.simulation = 0;
  /* Stop the simulation in every rooms */
  rooms_simulation_control_set(alarm_control.simulation);
}

THREAD(AlarmD, arg)
{
  arg = arg;
  NutThreadSetPriority(105);

  while(1)
  {
    alarm_status.perimeter  = rooms_perimeter_trig_get();
    alarm_status.volume     = rooms_volume_trig_get() | volume_status_get();
    alarm_status.simulation = rooms_simulation_status_get();

    /* Manage the watchdog ENABLE / DISABLE for the alarm PERIMETER */
    /* Step : Alarm enabled */
    if(alarm_control.perimeter == 1)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(alarm_trig.perimeter == 2) { alarm_action_with_buzzer("Alarme-Perimetre"); }
      /* Step : Alarm trig during watchdog */
      if(alarm_trig.perimeter > 1)  { alarm_trig.perimeter--; }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_trig.perimeter == 0) { if(alarm_status.perimeter) { alarm_trig.perimeter = 30; } }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_control.perimeter == 2)
    {
      /* Only activate the alarm if all the shutters are closed */
      if(!rooms_perimeter_status_get())
      {
        rooms_perimeter_control_set(0x01); /* FIXME Perimeter control only available on the first input in ROOM Nodes */
        room_perimeter_control_set(ROOM_SALON, 0x07); /* FIXME But we have the 3 shutters of the SALON available */
        room_perimeter_control_set(ROOM_BUREAU, 0x07); /* FIXME But we have the 1 shutter and 2 doors of the BUREAU available */
        alarm_control.perimeter--;
      }
      /* If the shutters are not closed try to close them */
      else
      {
        rooms_shutters_set(ROOM_SHUTTER_DOWN);
      }
    }
    /* Step before enabling the alarm */
    if(alarm_control.perimeter == 3)
    {
      /* Check if all the shutters are closed else send alert message */
      if(rooms_perimeter_status_get())
      {
        alarm_action("Impossible-d-activer-Alarme-Perimetre");
      }
    }
    /* Force all shutters down when enabling alarm perimeter */
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_control.perimeter >  2) { alarm_control.perimeter--; /*rooms_shutters_set(ROOM_SHUTTER_DOWN);*/ }

    /* Manage the watchdog ENABLE / DISABLE for the alarm VOLUME */
    /* Step : Alarm enabled */
    if(alarm_control.volume == 1)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(alarm_trig.volume == 2) { alarm_action_with_buzzer("Alarme-Volume"); }
      /* Step : Alarm trig during watchdog */
      if(alarm_trig.volume > 1)  { alarm_trig.volume--; }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_trig.volume == 0) { if(alarm_status.volume) { alarm_trig.volume = 30; } }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_control.volume == 2)
    {
      /* Only activate the alarm if nothing is moving */
      if((!rooms_volume_status_get()) && (!volume_status_get()))
      {
        rooms_volume_control_set(0x00); /* FIXME Volume not yet available in ROOM Nodes */
        alarm_control.volume--;
      }
    }
    /* Step before enabling the alarm */
    if(alarm_control.volume == 3)
    {
      /* Check if all the shutters are closed else send alert message */
      if(rooms_volume_status_get() || volume_status_get())
      {
        alarm_action("Impossible-d-activer-Alarme-Volume");
      }
    }
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_control.volume >  2) { alarm_control.volume--; }

    NutSleep(1000);
  }
}

int alarm_form(FILE * stream, REQUEST * req)
{
  char* arg_s=NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    arg_s = NutHttpGetParameter(req, "perimeter_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.perimeter); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); } else { alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.volume); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_volume_set(ALARM_TYPE_ON_MANUAL); } else { alarm_volume_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.simulation); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_simulation_set(ALARM_TYPE_ON_MANUAL); } else { alarm_simulation_set(ALARM_TYPE_OFF_MANUAL); } }
    }

    fflush(stream);
  }

  return 0;
}

int alarm_xml_get(FILE * stream)
{
  fprintf_XML_elt_header("Alarm", stream);
  fprintf_XML_elt_int("Perimeter" , alarm_status.perimeter , stream);
  fprintf_XML_elt_int("Volume"    , alarm_status.volume    , stream);
  fprintf_XML_elt_int("Simulation", alarm_status.simulation, stream);

  fprintf_XML_elt_int("Perimeter_Ctrl" , alarm_control.perimeter , stream);
  fprintf_XML_elt_int("Volume_Ctrl"    , alarm_control.volume    , stream);
  fprintf_XML_elt_int("Simulation_Ctrl", alarm_control.simulation, stream);

  fprintf_XML_elt_int("Perimeter_Trig" , alarm_trig.perimeter , stream);
  fprintf_XML_elt_int("Volume_Trig"    , alarm_trig.volume    , stream);
  fprintf_XML_elt_int("Simulation_Trig", alarm_trig.simulation, stream);
  fprintf_XML_elt_trailer("Alarm", stream);

  return 0;
}
