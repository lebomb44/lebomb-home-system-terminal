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
  uint8_t perimeter :1;
  uint8_t volume    :1;
  uint8_t simulation:1;
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
  buzzer_set();

  return 0;
}

THREAD(AlarmD, arg)
{
  NutThreadSetPriority(25);

  while(1)
  {
    alarm_status.perimeter  = rooms_perimeter_status_get();
    alarm_status.volume     = rooms_volume_status_get() || volume_status_get(); // TODO
    alarm_status.simulation = rooms_simulation_status_get();
    /* Check all the status but we don t know from which room */
    if(alarm_control.perimeter) { if((!(alarm_trig.perimeter)) && rooms_perimeter_trig_get()) { alarm_action_with_buzzer("Alarm-Perimeter"); alarm_trig.perimeter = 1; } }
    if(alarm_control.volume   ) { if((!(alarm_trig.volume   )) && rooms_volume_trig_get()   ) { alarm_action_with_buzzer("Alarm-Volume"   ); alarm_trig.volume    = 1; } }
    NutSleep(1000);
  }
}

int alarm_form(FILE * stream, REQUEST * req)
{
  char* arg_s=NULL;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    arg_s = NutHttpGetParameter(req, "perimeter_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.perimeter); }
      else { alarm_trig.perimeter = 0; alarm_control.perimeter = strtoul(arg_s, NULL, 10); rooms_perimeter_control_set(alarm_control.perimeter); }
    }
    arg_s = NutHttpGetParameter(req, "volume_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.volume); }
      else { alarm_trig.volume = 0; alarm_control.volume = strtoul(arg_s, NULL, 10); rooms_volume_control_set(alarm_control.volume); }
    }
    arg_s = NutHttpGetParameter(req, "simulation_ctrl");
    if(arg_s)
    {
      if(arg_s[0] == '?') { fprintf(stream, "%d", alarm_control.simulation); }
      else { alarm_trig.simulation = 0; alarm_control.simulation = strtoul(arg_s, NULL, 10); rooms_simulation_control_set(alarm_control.simulation); }
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
