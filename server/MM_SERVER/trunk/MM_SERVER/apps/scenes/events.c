#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../services/web.h"

#include <time.h>

#include "events.h"

typedef enum _EVENT_STATUS_T
{
  EVENT_STATUS_OFF = 0,
  EVENT_STATUS_ON,
  EVENT_STATUS_IN_PROGRESS
} EVENT_STATUS_T;

typedef struct _Event_T
{
  EVENT_STATUS_T status;
  uint8_t hour_start;
  uint8_t minute_start;
  uint8_t hour_end;
  uint8_t minute_end;
  uint8_t rec;
  void (*fcnt_start)(void);
  void (*fcnt_end)(void);
} Event_T;

enum
{
  EVENT_REVEIL = 0,
  EVENT_COUCHE,
  EVENT_CHAUFFAGE_SDB,
  EVENT_CHAUFFAGE_CAFE,
  EVENT_LUMIERE_AUTO,
  EVENT_MUSIQUE_AUTO,
  EVENT_MAX
};

Event_T event_list[EVENT_MAX];

uint8_t events_init(void)
{
  uint8_t i=0;

  for(i=0; i<EVENT_MAX; i++)
  {
    event_list[i].status       = EVENT_STATUS_OFF;
    event_list[i].hour_start  = 0;
    event_list[i].minute_start = 0;
    event_list[i].hour_end    = 0;
    event_list[i].minute_end   = 0;
    event_list[i].rec          = 0;
    event_list[i].fcnt_start   = NULL;
    event_list[i].fcnt_end     = NULL;
  }
  event_list[EVENT_REVEIL].fcnt_start = NULL; // set_led;
  event_list[EVENT_REVEIL].fcnt_end = NULL; // clear_led;
  NutThreadCreate("EventsD", EventsD, 0, 512);
  NutRegisterCgi("events.cgi", events_form);

  return 0;
}

THREAD(EventsD, arg)
{
  uint8_t i=0;
  time_t tt;
  tm time_now;

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
      if(event_list[i].status == EVENT_STATUS_ON)
      {
        /* Check for a specific recurrence or for a one-shot event */
        if((event_list[i].rec & (1<<time_now.tm_wday)) || (event_list[i].rec == 0))
        {
          /* If the event is programmed for now */
          if((event_list[i].hour_start == time_now.tm_hour) && (event_list[i].minute_start == time_now.tm_min))
          {
            /* Check the process action and execute it */
            if(event_list[i].fcnt_start != NULL) { event_list[i].fcnt_start(); }
            /* Now go to next step */
            event_list[i].status = EVENT_STATUS_IN_PROGRESS;
          }
        }
      }

      /* If the event has already started */
      if(event_list[i].status == EVENT_STATUS_IN_PROGRESS)
      {
        /* Maybe, there is something to do if the end function is defined */
        if(event_list[i].fcnt_end != NULL)
        {
          /* If the end is programmed for now */
          if((event_list[i].hour_end == time_now.tm_hour) && (event_list[i].minute_end == time_now.tm_min))
          {
            /* Execute the end function (this function has already been checked) */
            event_list[i].fcnt_end();
            /* If there is a recurrence, we should let the event enabled. Else it is a one-shot event */
            if(event_list[i].rec) { event_list[i].status = EVENT_STATUS_ON; }
            else { event_list[i].status = EVENT_STATUS_OFF; }
          }
        }
        else /* Maybe there is no end function */
        {
          /* We must wait one minute before to re-enable the event */
          /* FIXME : ERROR with 23:59 */
          if((event_list[i].hour_end <= time_now.tm_hour) && (event_list[i].minute_end < time_now.tm_min))
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
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    event_s = NutHttpGetParameter(req, "event");
    if(event_s)
    {
      event = strtoul(event_s, NULL, 10);
      if((0 <= event) && (event < EVENT_MAX))
      {
        arg_s = NutHttpGetParameter(req, "status");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].status); }
          else { event_list[event].status = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "hs");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].hour_start); }
          else { event_list[event].hour_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "ms");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].minute_start); }
          else { event_list[event].minute_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "he");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].hour_end); }
          else { event_list[event].hour_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "me");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].minute_end); }
          else { event_list[event].minute_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "rec");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", event_list[event].rec); }
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
  uint8_t i=0;
  char elt[7]="Event";
  elt[6]='\0';
  for(i=0; i<EVENT_MAX; i++)
  {
    elt[5]='0'+i;
    fprintf_XML_elt_header(elt, stream);
    fprintf_XML_elt_int("St", event_list[i].status, stream);
    fprintf_XML_elt_int("rec1", (event_list[i].rec & 0x02)>>1, stream);
    fprintf_XML_elt_int("rec2", (event_list[i].rec & 0x04)>>2, stream);
    fprintf_XML_elt_int("rec3", (event_list[i].rec & 0x08)>>3, stream);
    fprintf_XML_elt_int("rec4", (event_list[i].rec & 0x10)>>4, stream);
    fprintf_XML_elt_int("rec5", (event_list[i].rec & 0x20)>>5, stream);
    fprintf_XML_elt_int("rec6", (event_list[i].rec & 0x40)>>6, stream);
    fprintf_XML_elt_int("rec0", (event_list[i].rec & 0x01)>>0, stream);
    fprintf_XML_elt_int("HStart", event_list[i].hour_start, stream);
    fprintf_XML_elt_int("MStart", event_list[i].minute_start, stream);
    fprintf_XML_elt_int("HEnd", event_list[i].hour_end, stream);
    fprintf_XML_elt_int("MEnd", event_list[i].minute_end, stream);
    fprintf_XML_elt_trailer(elt, stream);
  }
  return 0;
}
