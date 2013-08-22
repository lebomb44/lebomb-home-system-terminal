#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
  time_t time;
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
  alarm_perimeter.time    = 0;
  alarm_perimeter.trig    = 0;
  alarm_perimeter.room    = ROOM_MAX;

  alarm_volume.status  = 0;
  alarm_volume.type    = ALARM_TYPE_OFF_AUTO;
  alarm_volume.control = 0; // TODO
  alarm_volume.time    = 0;
  alarm_volume.trig    = 0;
  alarm_volume.room    = ROOM_MAX;

  alarm_simulation.status  = 0;
  alarm_simulation.type    = ALARM_TYPE_OFF_AUTO;
  alarm_simulation.control = 0;
  alarm_simulation.time    = 0;
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

/* LED list */
typedef enum _ALARM_LED_T
{
  ALARM_LED_GREEN = 0,
  ALARM_LED_RED,
  ALARM_LED_MAX
} ALARM_LED_T;

/* LED states list */
typedef enum _ALARM_LED_STATE_T
{
  ALARM_LED_STATE_OFF = 0,
  ALARM_LED_STATE_ON,
  ALARM_LED_STATE_TOGGLE,
  ALARM_LED_STATE_MAX
} ALARM_LED_STATE_T;

/* LED management function */
void alarm_led_set(ALARM_LED_T led, ALARM_LED_STATE_T state)
{
  static ALARM_LED_STATE_T alarm_led_state[ALARM_LED_MAX] = { ALARM_LED_STATE_OFF, ALARM_LED_STATE_OFF };

  if(ALARM_LED_MAX > led)
  {
    if(ALARM_LED_STATE_OFF    == state) { room_light_set(ROOM_COULOIR, led, 0); }
    if(ALARM_LED_STATE_ON     == state) { room_light_set(ROOM_COULOIR, led, 1); }
    if(ALARM_LED_STATE_TOGGLE == state)
    {
      if(ALARM_LED_STATE_OFF == alarm_led_state[led]) { room_light_set(ROOM_COULOIR, led, 1); alarm_led_state[led] = ALARM_LED_STATE_ON ; }
      else                                            { room_light_set(ROOM_COULOIR, led, 0); alarm_led_state[led] = ALARM_LED_STATE_OFF; }
    }
  }
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
  if(ALARM_TYPE_ON_AUTO == type)    { if(ALARM_TYPE_ON_MANUAL != alarm_perimeter.type) { alarm_perimeter.control = 60; alarm_perimeter.time = time(NULL) + alarm_perimeter.control; } else { return; } }
  /* In any case, user can force ON manually */
  if(ALARM_TYPE_ON_MANUAL == type)  { alarm_perimeter.control = 60; alarm_perimeter.time = time(NULL) + alarm_perimeter.control; }
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
  if(ALARM_TYPE_OFF_MANUAL == type) { room_elec_set(ROOM_COULOIR, 0, 1); NutSleep(100); room_elec_set(ROOM_COULOIR, 0, 0); }
  if(ALARM_TYPE_ON_MANUAL == type)
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
  if(ALARM_TYPE_MAX <= type) { return; }

  /* Mode OFF AUTO can only be done if alarm was already in mode ON AUTO */
  if(ALARM_TYPE_OFF_AUTO == type)   { if(ALARM_TYPE_ON_AUTO == alarm_volume.type) { alarm_volume.control = 0; alarm_volume.time = 0; } else { return; } }
  /* In any case, user can force OFF manually */
  if(ALARM_TYPE_OFF_MANUAL == type) { alarm_volume.control = 0; alarm_volume.time = 0; }
  /* Mode ON AUTO can only be done if alarm was NOT already set ON manually */
  if(ALARM_TYPE_ON_AUTO == type)    { if(ALARM_TYPE_ON_MANUAL != alarm_volume.type) { alarm_volume.control = 60; alarm_volume.time = time(NULL) + alarm_volume.control; } else { return; } }
  /* In any case, user can force ON manually */
  if(ALARM_TYPE_ON_MANUAL == type)  { alarm_volume.control = 60; alarm_volume.time = time(NULL) + alarm_volume.control; }
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
  /* Stop the simulation in every rooms */
  rooms_simulation_control_set(alarm_simulation.control);
}

THREAD(AlarmD, arg)
{
  char msg[60];
  time_t now = 0;
  arg = arg;
  NutThreadSetPriority(105);

  while(1)
  {
    /* Only update the status if the alarm did not trigger */
    if(0 == alarm_perimeter.trig)
    {
      /* If alarm is enabled */
      if(1 == alarm_perimeter.control) { alarm_perimeter.status = rooms_perimeter_trig_get(&(alarm_perimeter.room)); }
      /* If alarm is NOT enabled */
      else { alarm_perimeter.status  = rooms_perimeter_status_get(&(alarm_perimeter.room)); }
    }
    if(0 == alarm_volume.trig)
    {
      /* If alarm is enabled */
      if(1 == alarm_volume.control) { alarm_volume.status = /* FIXME rooms_volume_trig_get(&(alarm_volume.room)) |*/ volume_status_get(); }
      /* If alarm is NOT enabled */
      else { alarm_volume.status  = /* FIXME rooms_volume_status_get(&(alarm_volume.room)) |*/ volume_status_get(); }
    }
    if(0 == alarm_simulation.trig)
    {
      /* If alarm is enabled */
      if(1 == alarm_simulation.control) { alarm_simulation.status = rooms_simulation_status_get(&(alarm_simulation.room)); }
      /* If alarm is NOT enabled */
      else { alarm_simulation.status  = rooms_simulation_status_get(&(alarm_simulation.room)); }
    }

    /* ********** Update Green LED state ********** */
    /* At least one alarm is enabled -> Green LED ON */
    if((1 == alarm_perimeter.control) || (1 == alarm_volume.control)) { alarm_led_set(ALARM_LED_GREEN, ALARM_LED_STATE_ON); }
    /* At least one alarm is going to be enabled -> Toggle Green LED */
    else if((1 < alarm_perimeter.control) || (1 < alarm_volume.control)) { alarm_led_set(ALARM_LED_GREEN, ALARM_LED_STATE_TOGGLE); }
    /* All alarms are off -> Green LED OFF */
    if((0 == alarm_perimeter.control) && (0 == alarm_volume.control)) { alarm_led_set(ALARM_LED_GREEN, ALARM_LED_STATE_OFF); }
    /* ********** Update Red LED state ********** */
    /* At least one alarm is triggered -> Red LED ON */
    if((1 == alarm_perimeter.trig) || (1 == alarm_volume.trig)) { alarm_led_set(ALARM_LED_RED, ALARM_LED_STATE_ON); }
    /* At least one alarm is going to trigger -> Toggle Red LED */
    else if((1 < alarm_perimeter.trig) || (1 < alarm_volume.trig)) { alarm_led_set(ALARM_LED_RED, ALARM_LED_STATE_TOGGLE); }
    /* All triggers are off -> Red LED OFF */
    if((0 == alarm_perimeter.trig) && (0 == alarm_volume.trig)) { alarm_led_set(ALARM_LED_RED, ALARM_LED_STATE_OFF); }
    /* Both alarm triggered -> Green LED OFF */
    if((1 == alarm_perimeter.trig) && (1 == alarm_volume.trig)) { alarm_led_set(ALARM_LED_GREEN, ALARM_LED_STATE_OFF); }

    /* ************************************************************ */
    /* Manage the watchdog ENABLE / DISABLE for the alarm PERIMETER */
    /* ************************************************************ */
    /* Step : Alarm enabled */
    if(1 == alarm_perimeter.control)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(2 == alarm_perimeter.trig)
      {
        sprintf(msg, "Alarme-Perimetre-%d-%s", alarm_perimeter.status, room_name_get(alarm_perimeter.room));
        alarm_action_with_buzzer(msg);
        alarm_perimeter.trig = 1;
      }
      /* Step : Alarm trig during watchdog */
      if(2 < alarm_perimeter.trig)
      {
        now = time(NULL);
        if(2 < (alarm_perimeter.time - now)) { alarm_perimeter.trig = alarm_perimeter.time - now; }
        else { alarm_perimeter.trig = 2; }
      }
      /* Step : Alarm did not triggered. Check the status */
      if(0 == alarm_perimeter.trig)
      {
        /* Detection */
        if(alarm_perimeter.status)
        {
          /* Start timer */
          alarm_perimeter.trig = 30; alarm_perimeter.time = time(NULL) + alarm_perimeter.trig;
        }
      }
    }
    /* Step : Alarm control is going to be enabled */
    if(2 == alarm_perimeter.control)
    {
      /* Only activate the alarm if all the shutters are closed */
      if(0 == alarm_perimeter.status)
      {
        rooms_perimeter_control_set(0x01); /* FIXME Perimeter control only available on the first input in ROOM Nodes */
        room_perimeter_control_set(ROOM_SALON, 0x07); /* FIXME But we have the 3 shutters of the SALON available */
        room_perimeter_control_set(ROOM_BUREAU, 0x07); /* FIXME But we have the 1 shutter and 2 doors of the BUREAU available */
        alarm_perimeter.control = 1;
      }
      /* If the shutters are not closed try to close them */
      else
      {
    	  rooms_shutters_set(ROOM_SHUTTER_STOP); rooms_shutters_set(ROOM_SHUTTER_DOWN);
      }
    }
    /* Step before enabling the alarm */
    if(3 == alarm_perimeter.control)
    {
      /* Check if all the shutters are closed else send alert message */
      if(alarm_perimeter.status)
      {
        sprintf(msg, "Impossible-d-activer-Alarme-Perimetre-%d-%s", alarm_perimeter.status, room_name_get(alarm_perimeter.room));
        alarm_action(msg);
      }
      alarm_perimeter.control = 2;
    }
    /* Force all shutters down when enabling alarm perimeter */
    /* Step : Alarm control during watchdog for being enabled */
    if(3 < alarm_perimeter.control)
    {
      now = time(NULL);
      if(3 < (alarm_perimeter.time - now)) { alarm_perimeter.control = alarm_perimeter.time - now; }
      else { alarm_perimeter.control = 3; }
      /* Close all shutters */
      rooms_shutters_set(ROOM_SHUTTER_DOWN);
    }

    /* ********************************************************* */
    /* Manage the watchdog ENABLE / DISABLE for the alarm VOLUME */
    /* ********************************************************* */
    /* Step : Alarm enabled */
    if(1 == alarm_volume.control)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(2 == alarm_volume.trig)
      {
        sprintf(msg, "Alarme-Volume-%d-%s", alarm_volume.status, room_name_get(alarm_volume.room));
        alarm_action_with_buzzer(msg);
        alarm_volume.trig = 1;
      }
      /* Step : Alarm trig during watchdog */
      if(2 < alarm_volume.trig)
      {
        now = time(NULL);
        if(2 < (alarm_volume.time - now)) { alarm_volume.trig = alarm_volume.time - now; }
        else { alarm_volume.trig = 2; }
      }
      /* Step : Alarm did not triggered. Check the status */
      if(0 == alarm_volume.trig)
      {
        /* Detection */
        if(alarm_volume.status)
        {
          /* Start timer */
          alarm_volume.trig = 30; alarm_volume.time = time(NULL) + alarm_volume.trig;
        }
      }
    }
    /* Step : Alarm control is going to be enabled */
    if(2 == alarm_volume.control)
    {
      /* Only activate the alarm if nothing is moving */
      if(0 == alarm_volume.status)
      {
        /* FIXME rooms_volume_control_set(0x00); Volume not yet available in ROOM Nodes */
        alarm_volume.control = 1;
      }
    }
    /* Step before enabling the alarm */
    if(3 == alarm_volume.control)
    {
      /* Check if nothing is moving else send alert message */
      if(alarm_volume.status)
      {
        sprintf(msg, "Impossible-d-activer-Alarme-Volume-%d-%s", alarm_volume.status, room_name_get(alarm_volume.room));
        alarm_action(msg);
      }
      alarm_volume.control = 2;
    }
    /* Step : Alarm control during watchdog for being enabled */
    if(3 < alarm_volume.control)
    {
      now = time(NULL);
      if(3 < (alarm_volume.time - now)) { alarm_volume.control = alarm_volume.time - now; }
      else { alarm_volume.control = 3; }
    }

    NutSleep(1000);
  }
}

int alarm_form(FILE * stream, REQUEST * req)
{
  char* arg_s = NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    arg_s = NutHttpGetParameter(req, "perimeter_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_perimeter.control); }
      else { if(0 < strtoul(arg_s, NULL, 10)) { alarm_perimeter_set(ALARM_TYPE_ON_MANUAL); } else { alarm_perimeter_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_volume.control); }
      else { if(0 < strtoul(arg_s, NULL, 10)) { alarm_volume_set(ALARM_TYPE_ON_MANUAL); } else { alarm_volume_set(ALARM_TYPE_OFF_MANUAL); } }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if('?' == arg_s[0]) { fprintf(stream, "%d", alarm_simulation.control); }
      else { if(0 < strtoul(arg_s, NULL, 10)) { alarm_simulation_set(ALARM_TYPE_ON_MANUAL); } else { alarm_simulation_set(ALARM_TYPE_OFF_MANUAL); } }
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
