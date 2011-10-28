#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <pro/httpd.h>

#include "../../services/web.h"

#include <time.h>

#include "scenes.h"

typedef enum _SCENE_STATUS_T
{
  SCENE_STATUS_OFF = 0,
  SCENE_STATUS_ON,
  SCENE_STATUS_IN_PROGRESS
} SCENE_STATUS_T;

typedef struct _Scene_T
{
  SCENE_STATUS_T status;
  uint8_t heure_start;
  uint8_t minute_start;
  uint8_t heure_end;
  uint8_t minute_end;
  uint8_t rec;
  void (*fcnt_start)(void);
  void (*fcnt_end)(void);
} Scene_T;

enum
{
  SCENE_REVEIL = 0,
  SCENE_COUCHE,
  SCENE_CHAUFFAGE_SDB,
  SCENE_CHAUFFAGE_CAFE,
  SCENE_LUMIERE_AUTO,
  SCENE_MUSIQUE_AUTO,
  SCENE_MAX
};

Scene_T scene_list[SCENE_MAX];

uint8_t scenes_init(void)
{
  uint8_t i=0;

  for(i=0; i<SCENE_MAX; i++)
  {
    scene_list[i].status       = SCENE_STATUS_OFF;
    scene_list[i].heure_start  = 0;
    scene_list[i].minute_start = 0;
    scene_list[i].heure_end    = 0;
    scene_list[i].minute_end   = 0;
    scene_list[i].rec          = 0;
    scene_list[i].fcnt_start   = NULL;
    scene_list[i].fcnt_end     = NULL;
  }
  scene_list[SCENE_REVEIL].fcnt_start = NULL; // set_led;
  scene_list[SCENE_REVEIL].fcnt_end = NULL; // clear_led;
  NutThreadCreate("ScenesD", ScenesD, 0, 512);
  NutRegisterCgi("scenes.cgi", scenes_form);

  return 0;
}

THREAD(ScenesD, arg)
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

    /* Process for each scene */
    for(i=0; i<SCENE_MAX; i++)
    {
      /* If the scene is enabled */
      if(scene_list[i].status == SCENE_STATUS_ON)
      {
        /* Check for a specific recurrence or for each days */
        if((scene_list[i].rec & (1<<time_now.tm_wday)) || (scene_list[i].rec == 0))
        {
          /* It the scene is programmed for now */
          if((scene_list[i].heure_start == time_now.tm_hour) && (scene_list[i].minute_start == time_now.tm_min))
          {
            /* Check the process action and execute it */
            if(scene_list[i].fcnt_start != NULL) { scene_list[i].fcnt_start(); }
            /* Now go to next step */
            scene_list[i].status = SCENE_STATUS_IN_PROGRESS;
          }
        }
      }
      
      /* If the scene has already started */
      if(scene_list[i].status == SCENE_STATUS_IN_PROGRESS)
      {
        /* Maybe, there is something to do if the end function is defined */
        if(scene_list[i].fcnt_end != NULL)
        {
          /* If the end is programmed for now */
          if((scene_list[i].heure_end == time_now.tm_hour) && (scene_list[i].minute_end == time_now.tm_min))
          {
            /* Execute the end function (this function has already been checked) */
            scene_list[i].fcnt_end();
            /* If theres is a recurrence, we should let the scene enabled. Else it is a one-shot scene */
            if(scene_list[i].rec) { scene_list[i].status = SCENE_STATUS_ON; }
            else { scene_list[i].status = SCENE_STATUS_OFF; }
          }
        }
        else /* Maybe there is no end function */
        {
          /* We must wait one minute before to re-enable the scene */
          if((scene_list[i].heure_end <= time_now.tm_hour) && (scene_list[i].minute_end < time_now.tm_min))
          {
            /* Only re-enable if there is a recurrence */
            if(scene_list[i].rec) { scene_list[i].status = SCENE_STATUS_ON; }
            else { scene_list[i].status = SCENE_STATUS_OFF; }
          }
        }
      }
    }
    NutSleep(10000);
  }
}

int scenes_form(FILE * stream, REQUEST * req)
{
  char* scene_s=NULL;
  unsigned int scene=0;
  char* arg_s=NULL;
  unsigned int rec=0;
  char* value_s=NULL;
  unsigned int value=0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    scene_s = NutHttpGetParameter(req, "scene");
    if(scene_s)
    {
      scene = strtoul(scene_s, NULL, 10);
      if((0 <= scene) && (scene < SCENE_MAX))
      {
        arg_s = NutHttpGetParameter(req, "status");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].status); }
          else { scene_list[scene].status = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "hs");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].heure_start); }
          else { scene_list[scene].heure_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "ms");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].minute_start); }
          else { scene_list[scene].minute_start = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "he");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].heure_end); }
          else { scene_list[scene].heure_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "me");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].minute_end); }
          else { scene_list[scene].minute_end = strtoul(arg_s, NULL, 10); }
        }
        arg_s = NutHttpGetParameter(req, "rec");
        if(arg_s)
        {
          if(arg_s[0] == '?') { fprintf(stream, "%d", scene_list[scene].rec); }
          else
          {
            value_s = NutHttpGetParameter(req, "value");
            if(value_s)
            {
              rec = strtoul(arg_s, NULL, 10);
              value = strtoul(value_s, NULL, 10);
              if(value) { scene_list[scene].rec |= 1<<rec; }
              else { scene_list[scene].rec &= ~(1<<rec); }
            }
          }
        }
      }
printf("EVENT=%d || %d | %d | %d %d | %d %d\n",scene,scene_list[scene].status,scene_list[scene].rec,scene_list[scene].heure_start,scene_list[scene].minute_start,scene_list[scene].heure_end,scene_list[scene].minute_end);
    }
    fflush(stream);
  }
    return 0;
}

int scenes_xml_get(FILE * stream)
{
  uint8_t i=0;
  char elt[7]="Event";
  elt[6]='\0';
  for(i=0; i<SCENE_MAX; i++)
  {
    elt[5]='0'+i;
    fprintf_XML_elt_header(elt, stream);
    fprintf_XML_elt_int("St", scene_list[i].status, stream);
    fprintf_XML_elt_int("rec1", (scene_list[i].rec & 0x02)>>1, stream);
    fprintf_XML_elt_int("rec2", (scene_list[i].rec & 0x04)>>2, stream);
    fprintf_XML_elt_int("rec3", (scene_list[i].rec & 0x08)>>3, stream);
    fprintf_XML_elt_int("rec4", (scene_list[i].rec & 0x10)>>4, stream);
    fprintf_XML_elt_int("rec5", (scene_list[i].rec & 0x20)>>5, stream);
    fprintf_XML_elt_int("rec6", (scene_list[i].rec & 0x40)>>6, stream);
    fprintf_XML_elt_int("rec0", (scene_list[i].rec & 0x01)>>0, stream);
    fprintf_XML_elt_int("HStart", scene_list[i].heure_start, stream);
    fprintf_XML_elt_int("MStart", scene_list[i].minute_start, stream);
    fprintf_XML_elt_int("HEnd", scene_list[i].heure_end, stream);
    fprintf_XML_elt_int("MEnd", scene_list[i].minute_end, stream);
    fprintf_XML_elt_trailer(elt, stream);
  }
  return 0;
}
