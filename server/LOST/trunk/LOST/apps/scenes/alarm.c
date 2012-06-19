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
ALARM_T alarm_control;
ALARM_T alarm_trig;

uint8_t alarm_init(void)
{
  alarm_status.perimeter  = 0;
  alarm_status.volume     = 0;
  alarm_status.simulation = 0;

  alarm_control.perimeter  = 0; // TODO
  alarm_control.volume     = 0; // TODO
  alarm_control.simulation = 0;

  alarm_trig.perimeter  = 0;
  alarm_trig.volume     = 0;
  alarm_trig.simulation = 0;

  NutThreadCreate("AlarmD", AlarmD, 0, 512);
  NutRegisterCgi("alarm.cgi", alarm_form);

  return 0;
}

/* This function is executed if an alarm is detected */
uint8_t alarm_action_with_buzzer(char* msg)
{
  gsm_sms_send(gsm1, msg);
  gsm_sms_send(gsm2, msg);
  http_email_send(msg);
  buzzer_start(5*60); /* 5 minutes */

  return 0;
}

void alarm_perimeter_set(uint8_t control)
{
  if(control > 0) { alarm_control.perimeter = 30; } else { alarm_control.perimeter = 0; }
  alarm_trig.perimeter = 0;
  buzzer_stop();
  rooms_perimeter_control_set(0);
  NutSleep(100);
  rooms_perimeter_trig_set(0);
}

void alarm_volume_set(uint8_t control)
{
  if(control > 0) { alarm_control.volume = 30; } else { alarm_control.volume = 0; }
  alarm_trig.volume = 0;
  buzzer_stop();
  rooms_volume_control_set(0);
  NutSleep(100);
  rooms_volume_trig_set(0);
}

void alarm_simulation_set(uint8_t control)
{
  alarm_trig.simulation = 0;
  alarm_control.simulation = control;
  rooms_simulation_control_set(alarm_control.simulation);
}

THREAD(AlarmD, arg)
{
  arg = arg;
  NutThreadSetPriority(25);

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
      if(alarm_trig.perimeter == 2) { alarm_action_with_buzzer("Alarm-Perimeter"); }
      /* Step : Alarm trig during watchdog */
      if(alarm_trig.perimeter > 1)  { alarm_trig.perimeter--; }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_trig.perimeter == 0) { if(alarm_status.perimeter) { alarm_trig.perimeter = 30; } }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_control.perimeter == 2)
    {
      rooms_perimeter_control_set(0x01); /* FIXME Perimeter control only available on the first input in ROOM Nodes */
      room_perimeter_control_set(ROOM_SALON, 0x07); /* FIXME But we have the 3 shutters of the SALON available */
      room_perimeter_control_set(ROOM_BUREAU, 0x07); /* FIXME But we have the 1 shutter and 2 doors of the BUREAU available */
    }
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_control.perimeter >  1) { alarm_control.perimeter--; }

    /* Manage the watchdog ENABLE / DISABLE for the alarm VOLUME */
    /* Step : Alarm enabled */
    if(alarm_control.volume == 1)
    {
      /* Step : Alarm trig watchdog is going to finish */
      if(alarm_trig.volume == 2) { alarm_action_with_buzzer("Alarm-Volume"); }
      /* Step : Alarm trig during watchdog */
      if(alarm_trig.volume > 1)  { alarm_trig.volume--; }
      /* Step : Alarm did not triggered. Check to status */
      if(alarm_trig.volume == 0) { if(alarm_status.volume) { alarm_trig.volume = 30; } }
    }
    /* Step : Alarm control is going to be enabled */
    if(alarm_control.volume == 2) { rooms_volume_control_set(0x00); } /* FIXME Volume not yet available in ROOM Nodes */
    /* Step : Alarm control during watchdog for being enabled */
    if(alarm_control.volume >  1) { alarm_control.volume--; }

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
      else { alarm_perimeter_set(strtoul(arg_s, NULL, 10)); }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.volume); }
      else { alarm_volume_set(strtoul(arg_s, NULL, 10)); }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.simulation); }
      else { alarm_simulation_set(strtoul(arg_s, NULL, 10)); }
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
