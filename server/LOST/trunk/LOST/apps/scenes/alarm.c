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

typedef struct _ALARM_T
{
  uint8_t status;
  ALARM_TYPE_T type;
  uint8_t control;
  uint8_t trig;
  ROOM_N_T room;
} ALARM_T;

ALARM_T alarm_perimeter;
ALARM_T alarm_volume;
ALARM_T alarm_simulation;

uint8_t alarm_init(void)
{
  alarm_perimeter.status  = 0;
  alarm_perimeter.type    = ALARM_TYPE_OFF_AUTO;
  alarm_perimeter.control = 0; // TODO
  alarm_perimeter.trig    = 0;
  alarm_perimeter.room    = ROOM_MAX;

  alarm_volume.status  = 0;
  alarm_volume.type    = ALARM_TYPE_OFF_AUTO;
  alarm_volume.control = 0; // TODO
  alarm_volume.trig    = 0;
  alarm_volume.room    = ROOM_MAX;

  alarm_simulation.status  = 0;
  alarm_simulation.type    = ALARM_TYPE_OFF_AUTO;
  alarm_simulation.control = 0;
  alarm_simulation.trig    = 0;
  alarm_simulation.room    = ROOM_MAX;

  /* Clear Green and Red LEDs */
  room_light_set(ROOM_COULOIR, 0, 0); room_light_set(ROOM_COULOIR, 1, 0);

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
  if(type == ALARM_TYPE_OFF_AUTO)   { if(alarm_perimeter.type == ALARM_TYPE_ON_AUTO) { alarm_perimeter.control = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(type == ALARM_TYPE_OFF_MANUAL) { alarm_perimeter.control = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(type == ALARM_TYPE_ON_AUTO)    { if(alarm_perimeter.type != ALARM_TYPE_ON_MANUAL) { alarm_perimeter.control = 60; } else { return; } }
  /* In any case, user can force ON manually */
  if(type == ALARM_TYPE_ON_MANUAL)  { alarm_perimeter.control = 60; }
  /* Save the new mode set */
  alarm_perimeter.type = type;
  /* Reset the trigger status */
  alarm_perimeter.trig = 0;
  /* Stop the buzzer */
  buzzer_stop();
  /* Stop the alarm monitoring in every rooms */
  rooms_perimeter_control_set(0);
  NutSleep(100);
  /* Reset the alarm trigger status in every rooms */
  rooms_perimeter_trig_set(0);
  /* Clear Green and Red LEDs */
  room_light_set(ROOM_COULOIR, 0, 0); room_light_set(ROOM_COULOIR, 1, 0);
  if(type == ALARM_TYPE_OFF_MANUAL) { room_elec_set(ROOM_COULOIR, 0, 1); NutSleep(100); room_elec_set(ROOM_COULOIR, 0, 0); }
  if(type == ALARM_TYPE_ON_MANUAL )
  {
    room_elec_set(ROOM_COULOIR, 0, 1); NutSleep(100); room_elec_set(ROOM_COULOIR, 0, 0); NutSleep(100); 
	room_elec_set(ROOM_COULOIR, 0, 1); NutSleep(100); room_elec_set(ROOM_COULOIR, 0, 0); NutSleep(100); 
	room_elec_set(ROOM_COULOIR, 0, 1); NutSleep(100); room_elec_set(ROOM_COULOIR, 0, 0);
  }
  /* Set bipper OFF again ! */
  NutSleep(1); room_elec_set(ROOM_COULOIR, 0, 0);
  /* ... and again ! */
  NutSleep(1); room_elec_set(ROOM_COULOIR, 0, 0);
}

void alarm_volume_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(type >= ALARM_TYPE_MAX) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(type == ALARM_TYPE_OFF_AUTO)   { if(alarm_volume.type == ALARM_TYPE_ON_AUTO) { alarm_volume.control = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(type == ALARM_TYPE_OFF_MANUAL) { alarm_volume.control = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(type == ALARM_TYPE_ON_AUTO)    { if(alarm_volume.type != ALARM_TYPE_ON_MANUAL) { alarm_volume.control = 60; } else { return; } }
  /* In any case, user can force ON manually */
  if(type == ALARM_TYPE_ON_MANUAL)  { alarm_volume.control = 60; }
  /* Save the new mode set */
  alarm_volume.type = type;
  /* Reset the trigger status */
  alarm_volume.trig = 0;
  /* Stop the buzzer */
  buzzer_stop();
  /* Stop the alarm monitoring in every rooms */
  rooms_volume_control_set(0);
  NutSleep(100);
  /* Reset the alarm trigger status in every rooms */
  rooms_volume_trig_set(0);
  /* Clear Green and Red LEDs */
  room_light_set(ROOM_COULOIR, 0, 0); room_light_set(ROOM_COULOIR, 1, 0);
}

void alarm_simulation_set(ALARM_TYPE_T type)
{
  /* Check the argument */
  if(type >= ALARM_TYPE_MAX) { return; }

  /* Mode OFF in any case */
  if((type == ALARM_TYPE_OFF_MANUAL) || (type == ALARM_TYPE_OFF_AUTO)) { alarm_simulation.control = 0; }
  /* Mode ON in any case */
  if((type == ALARM_TYPE_ON_MANUAL ) || (type == ALARM_TYPE_ON_AUTO )) { alarm_simulation.control = 1; }
  /* Save the new mode set */
  alarm_simulation.type = type;
  /* Reset the trigger status */
  alarm_simulation.trig = 0;
  /* Stop the simulation in every rooms */
  rooms_simulation_control_set(alarm_simulation.control);
}

THREAD(AlarmD, arg)
{
  char msg[60];
  arg = arg;
  NutThreadSetPriority(105);

  while(1)
  {
    /* Only update the status if the alarm did not trigger */
    if(alarm_perimeter.trig == 0)
    {
      /* If alarm is enabled */
      if(alarm_perimeter.control == 1) { alarm_perimeter.status = rooms_perimeter_trig_get(&(alarm_perimeter.room)); }
      /* If alarm is NOT enabled */
      else { alarm_perimeter.status  = rooms_perimeter_status_get(&(alarm_perimeter.room)); }
    }
    if(alarm_volume.trig == 0)
    {
      /* If alarm is enabled */
      if(alarm_volume.control == 1) { alarm_volume.status = /* FIXME rooms_volume_trig_get(&(alarm_volume.room)) |*/ volume_status_get(); }
      /* If alarm is NOT enabled */
      else { alarm_volume.status  = /* FIXME rooms_volume_status_get(&(alarm_volume.room)) |*/ volume_status_get(); }
    }
    if(alarm_simulation.trig == 0)
    {
      /* If alarm is enabled */
      if(alarm_simulation.control == 1) { alarm_simulation.status = rooms_simulation_status_get(&(alarm_simulation.room)); }
      /* If alarm is NOT enabled */
      else { alarm_simulation.status  = rooms_simulation_status_get(&(alarm_simulation.room)); }
    }

    /* ************************************************************ */
    /* Manage the watchdog ENABLE / DISABLE for the alarm PERIMETER */
    /* ************************************************************ */
    /* Step : Alarm enabled */
    if(alarm_perimeter.control == 1)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(alarm_perimeter.trig == 2)
      {
        sprintf(msg, "Alarme-Perimetre-%d-%s", alarm_perimeter.status, room_name_get(alarm_perimeter.room));
        alarm_action_with_buzzer(msg);
      }
      /* Step : Alarm trig watchdog finished : Set Red LED */
      if(alarm_perimeter.trig == 1) { room_light_set(ROOM_COULOIR, 1, 1); }
      /* Step : Alarm trig during watchdog */
      if(alarm_perimeter.trig > 1)
      {
        alarm_perimeter.trig--;
        /* Toggle Red LED */
        room_light_set(ROOM_COULOIR, 1, (alarm_perimeter.trig) & 0x01);
      }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_perimeter.trig == 0)
      {
        /* Detection */
        if(alarm_perimeter.status)
        {
          /* Start timer */
          alarm_perimeter.trig = 30;
          /* Clear Green LED */
          room_light_set(ROOM_COULOIR, 0, 0);
        }
      }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_perimeter.control == 2)
    {
      /* Only activate the alarm if all the shutters are closed */
      if(rooms_perimeter_status_get(NULL) == 0)
      {
        alarm_perimeter.control--;
        rooms_perimeter_control_set(0x01); /* FIXME Perimeter control only available on the first input in ROOM Nodes */
        room_perimeter_control_set(ROOM_SALON, 0x07); /* FIXME But we have the 3 shutters of the SALON available */
        room_perimeter_control_set(ROOM_BUREAU, 0x07); /* FIXME But we have the 1 shutter and 2 doors of the BUREAU available */
        /* Set Green LED */
        room_light_set(ROOM_COULOIR, 0, 1);
      }
      /* If the shutters are not closed try to close them */
      else
      {
        rooms_shutters_set(ROOM_SHUTTER_DOWN);
      }
    }
    /* Step before enabling the alarm */
    if(alarm_perimeter.control == 3)
    {
      /* Check if all the shutters are closed else send alert message */
      if(alarm_perimeter.status != 0)
      {
        sprintf(msg, "Impossible-d-activer-Alarme-Perimetre-%d-%s", alarm_perimeter.status, room_name_get(alarm_perimeter.room));
        alarm_action(msg);
      }
    }
    /* Force all shutters down when enabling alarm perimeter */
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_perimeter.control >  2)
    {
      alarm_perimeter.control--;
      /* Toggle Green LED */
      room_light_set(ROOM_COULOIR, 0, (alarm_perimeter.control+1) & 0x01);
      /* Close all shutters */
      rooms_shutters_set(ROOM_SHUTTER_DOWN);
    }

    /* ********************************************************* */
    /* Manage the watchdog ENABLE / DISABLE for the alarm VOLUME */
    /* ********************************************************* */
    /* Step : Alarm enabled */
    if(alarm_volume.control == 1)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(alarm_volume.trig == 2)
      {
        sprintf(msg, "Alarme-Volume-%d-%s", alarm_volume.status, room_name_get(alarm_volume.room));
        alarm_action_with_buzzer(msg);
      }
      /* Step : Alarm trig watchdog finished : Set Red LED */
      if(alarm_volume.trig == 1) { room_light_set(ROOM_COULOIR, 1, 1); }
      /* Step : Alarm trig during watchdog */
      if(alarm_volume.trig > 1)
      {
        alarm_volume.trig--;
        /* Toggle Red LED */
        room_light_set(ROOM_COULOIR, 1, (alarm_volume.trig) & 0x01);
      }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_volume.trig == 0)
      {
        if(alarm_volume.status)
        {
          alarm_volume.trig = 30;
          /* Clear Green LED */
          room_light_set(ROOM_COULOIR, 0, 0);
        }
      }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_volume.control == 2)
    {
      /* Only activate the alarm if nothing is moving */
      if(/* FIXME (rooms_volume_status_get(NULL) == 0) &&*/ (!volume_status_get()))
      {
        alarm_volume.control--;
        /* FIXME rooms_volume_control_set(0x00); Volume not yet available in ROOM Nodes */
        /* Set Green LED */
        room_light_set(ROOM_COULOIR, 0, 1);
      }
    }
    /* Step before enabling the alarm */
    if(alarm_volume.control == 3)
    {
      /* Check if nothing is moving else send alert message */
      if((alarm_volume.status != 0) || volume_status_get())
      {
        sprintf(msg, "Impossible-d-activer-Alarme-Volume-%d-%s", alarm_volume.status, room_name_get(alarm_volume.room));
        alarm_action(msg);
      }
    }
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_volume.control >  2)
    {
      alarm_volume.control--;
      /* Toggle Green LED */
      room_light_set(ROOM_COULOIR, 0, (alarm_volume.control+1) & 0x01);
    }

    NutSleep(500);
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
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_perimeter.control); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); } else { alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_volume.control); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_volume_set(ALARM_TYPE_ON_MANUAL); } else { alarm_volume_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_simulation.control); }
      else { if(strtoul(arg_s, NULL, 10) > 0) { alarm_simulation_set(ALARM_TYPE_ON_MANUAL); } else { alarm_simulation_set(ALARM_TYPE_OFF_MANUAL); } }
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
  fprintf_XML_elt_int("Perimeter_Room" , alarm_perimeter.room , stream);

  fprintf_XML_elt_int("Volume"         , alarm_volume.status    , stream);
  fprintf_XML_elt_int("Volume_Ctrl"    , alarm_volume.control    , stream);
  fprintf_XML_elt_int("Volume_Trig"    , alarm_volume.trig    , stream);
  fprintf_XML_elt_int("Volume_Room"    , alarm_volume.room    , stream);

  fprintf_XML_elt_int("Simulation"     , alarm_simulation.status, stream);
  fprintf_XML_elt_int("Simulation_Ctrl", alarm_simulation.control, stream);
  fprintf_XML_elt_int("Simulation_Trig", alarm_simulation.trig, stream);
  fprintf_XML_elt_int("Simulation_Room", alarm_simulation.room, stream);
  fprintf_XML_elt_trailer("Alarm", stream);

  return 0;
}
