#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../devices/lbcomif.h"
#include "../../services/web.h"

#include <time.h>

#include "events_proc.h"
#include "events.h"

typedef struct _Event_T
{
  EVENT_STATUS_T status;
  EVENT_STATUS_T status_start;
  uint8_t hour_start;
  uint8_t minute_start;
  EVENT_STATUS_T status_end;
  uint8_t hour_end;
  uint8_t minute_end;
  uint8_t rec;
  void (*fcnt_start)(void);
  void (*fcnt_end)(void);
} Event_T;

Event_T event_list[EVENT_MAX];

uint8_t events_init(void)
{
  EVENT_T i = 0;

  for(i=0; i<EVENT_MAX; i++)
  {
    event_list[i].status       = EVENT_STATUS_OFF;
    event_list[i].status_start = EVENT_STATUS_ON;
    event_list[i].hour_start   = 0;
    event_list[i].minute_start = 0;
    event_list[i].status_end   = EVENT_STATUS_ON;
    event_list[i].hour_end     = 0;
    event_list[i].minute_end   = 0;
    event_list[i].rec          = 0;
    event_list[i].fcnt_start   = NULL;
    event_list[i].fcnt_end     = NULL;
  }
  events_proc_init();

  /* Set the default configuration for the Alarm Perimeter */
  /* Force the Alarm ON everyday in the night and OFF in the morning */
  event_list[EVENT_ALARM_PERIMETER_CHECK].status       = EVENT_STATUS_ON;
  event_list[EVENT_ALARM_PERIMETER_CHECK].status_start = EVENT_STATUS_ON; event_list[EVENT_ALARM_PERIMETER_CHECK].hour_start = 0; event_list[EVENT_ALARM_PERIMETER_CHECK].minute_start = 5;
  event_list[EVENT_ALARM_PERIMETER_CHECK].status_end   = EVENT_STATUS_ON; event_list[EVENT_ALARM_PERIMETER_CHECK].hour_end   = 6; event_list[EVENT_ALARM_PERIMETER_CHECK].minute_end   = 0;
  event_list[EVENT_ALARM_PERIMETER_CHECK].rec          = 0xFF;

  /* Set the default configuration for the Ethernet power line */
  /* Force the poweroff everyday in the night */
  event_list[EVENT_POWER_1].status       = EVENT_STATUS_ON;
  event_list[EVENT_POWER_1].status_start = EVENT_STATUS_OFF; event_list[EVENT_POWER_1].hour_start = 0; event_list[EVENT_POWER_1].minute_start = 0;
  event_list[EVENT_POWER_1].status_end   = EVENT_STATUS_ON;  event_list[EVENT_POWER_1].hour_end   = 1; event_list[EVENT_POWER_1].minute_end   = 0;
  event_list[EVENT_POWER_1].rec          = 0xFF;

  NutThreadCreate("EventsD", EventsD, 0, 512);
  lbcomif_registerSlaveCallBack(ID_LOST_EVENTS_CONFIG_TC, event_config);
  NutRegisterCgi("events.cgi", events_form);

  return 0;
}

void event_set(EVENT_T event, void (*fcnt_start)(void), void (*fcnt_end)(void))
{
  if(EVENT_MAX > event)
  {
    event_list[event].fcnt_start = fcnt_start;
    event_list[event].fcnt_end   = fcnt_end;
  }
}

void event_config(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  uint8_t event = 0;

  if(10 == len)
  {
    event = data[0];
    if(EVENT_MAX > event)
    {
      event_list[event].status       = data[1];
      event_list[event].status_start = data[2];
      event_list[event].hour_start   = data[3];
      event_list[event].minute_start = data[4];
      event_list[event].status_end   = data[5];
      event_list[event].hour_end     = data[6];
      event_list[event].minute_end   = data[7];
      if(data[9]) { event_list[event].rec |= 1<<data[8]; }
      else { event_list[event].rec &= ~(1<<data[8]); }
    }
  }
}

void event_action(EVENT_T event, EVENT_STATUS_T status)
{
  if(EVENT_MAX > event)
  {
    if(EVENT_STATUS_ON  == status) { if(NULL != event_list[event].fcnt_start) { (*(event_list[event].fcnt_start))(); } }
    if(EVENT_STATUS_OFF == status) { if(NULL != event_list[event].fcnt_end  ) { (*(event_list[event].fcnt_end))()  ; } }
  }
}

THREAD(EventsD, arg)
{
  EVENT_T i = 0;
  time_t tt;
  tm time_now;

  arg = arg;
  NutThreadSetPriority(240);

  while(1)
  {
    /* Get the current time */
    tt = time(NULL);
    /* Convert the time in a human readable form */
    localtime_r(&tt, &time_now); time_now.tm_mon++;
    /* Process for each event */
    for(i=0; i<EVENT_MAX; i++)
    {
      /* If the event is enabled */
      if(EVENT_STATUS_ON == event_list[i].status)
      {
        /* Check for a specific recurrence or for a one-shot event */
        if((event_list[i].rec & (1<<time_now.tm_wday)) || (0 == event_list[i].rec))
        {
          /* If the event is programmed for now */
          if((event_list[i].hour_start == time_now.tm_hour) && (event_list[i].minute_start == time_now.tm_min) && (30 > time_now.tm_sec))
          {
            /* Check the process action and execute it */
        	if(EVENT_STATUS_ON == event_list[i].status_start) { event_action(i, EVENT_STATUS_ON); }
            /* Now go to next step */
            event_list[i].status = EVENT_STATUS_IN_PROGRESS;
          }
        }
      }

      /* If the event has already started */
      if(EVENT_STATUS_IN_PROGRESS == event_list[i].status)
      {
        /* Maybe, there is something to do if the end function is defined */
        if(NULL != event_list[i].fcnt_end)
        {
          /* If the end is programmed for now */
          if((event_list[i].hour_end == time_now.tm_hour) && (event_list[i].minute_end == time_now.tm_min) && (30 < time_now.tm_sec))
          {
            /* Execute the end function (this function has already been checked) */
        	if(EVENT_STATUS_ON == event_list[i].status_end) { event_action(i, EVENT_STATUS_OFF); }
            /* If there is a recurrence, we should let the event enabled. Else it is a one-shot event */
            if(event_list[i].rec) { event_list[i].status = EVENT_STATUS_ON; }
            else { event_list[i].status = EVENT_STATUS_OFF; }
          }
        }
        else /* Maybe there is no end function */
        {
          /* We must wait the end of the START minute before to re-enable the event */
          if((event_list[i].hour_start == time_now.tm_hour) && (event_list[i].minute_start == time_now.tm_min) && (30 < time_now.tm_sec))
          {
            /* Only re-enable if there is a recurrence */
            if(event_list[i].rec) { event_list[i].status = EVENT_STATUS_ON; }
            else { event_list[i].status = EVENT_STATUS_OFF; }
          }
        }
      }
    }
    NutSleep(10000);
  }
}

int events_form(FILE * stream, REQUEST * req)
{
  char* event_s=NULL;
  unsigned int event=0;
  char* arg_s=NULL;
  unsigned int rec=0;
  char* value_s=NULL;
  unsigned int value=0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    event_s = NutHttpGetParameter(req, "event");
    if(event_s)
    {
      event = strtoul(event_s, NULL, 10);
      if(EVENT_MAX > event)
      {
        arg_s = NutHttpGetParameter(req, "status");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].status); }
          else { event_list[event].status = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "ss");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].status_start); }
          else { event_list[event].status_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "hs");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].hour_start); }
          else { event_list[event].hour_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "ms");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].minute_start); }
          else { event_list[event].minute_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "se");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].status_end); }
          else { event_list[event].status_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "he");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].hour_end); }
          else { event_list[event].hour_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "me");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].minute_end); }
          else { event_list[event].minute_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "rec");
        if(arg_s)
        {
          if('?' == arg_s[0]) { fprintf(stream, "%d", event_list[event].rec); }
          else
          {
            value_s = NutHttpGetParameter(req, "value");
            if(value_s)
            {
              rec = strtoul(arg_s, NULL, 10);
              value = strtoul(value_s, NULL, 10);
              if(value) { event_list[event].rec |= 1<<rec; }
              else { event_list[event].rec &= ~(1<<rec); }
            }
          }
        }
      }
    }
    fflush(stream);
  }

  return 0;
}

int events_xml_get(FILE * stream)
{
  uint8_t i = 0;
  char elt[10];
  for(i=0; i<EVENT_MAX; i++)
  {
    sprintf(elt, "Event%d", i);
    fprintf_XML_elt_header(elt, stream);
    fprintf_XML_elt_int("St", event_list[i].status, stream);
    fprintf_XML_elt_int("rec1", (event_list[i].rec & 0x02)>>1, stream);
    fprintf_XML_elt_int("rec2", (event_list[i].rec & 0x04)>>2, stream);
    fprintf_XML_elt_int("rec3", (event_list[i].rec & 0x08)>>3, stream);
    fprintf_XML_elt_int("rec4", (event_list[i].rec & 0x10)>>4, stream);
    fprintf_XML_elt_int("rec5", (event_list[i].rec & 0x20)>>5, stream);
    fprintf_XML_elt_int("rec6", (event_list[i].rec & 0x40)>>6, stream);
    fprintf_XML_elt_int("rec0", (event_list[i].rec & 0x01)>>0, stream);
    fprintf_XML_elt_int("StStart", event_list[i].status_start, stream);
    fprintf_XML_elt_int("HStart" , event_list[i].hour_start  , stream);
    fprintf_XML_elt_int("MStart" , event_list[i].minute_start, stream);
    fprintf_XML_elt_int("StEnd"  , event_list[i].status_end  , stream);
    fprintf_XML_elt_int("HEnd"   , event_list[i].hour_end    , stream);
    fprintf_XML_elt_int("MEnd"   , event_list[i].minute_end  , stream);
    fprintf_XML_elt_trailer(elt, stream);
  }
  return 0;
}
