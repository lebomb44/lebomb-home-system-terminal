#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../rooms/rooms.h"
#include "events.h"
#include "../../devices/power.h"
#include "scenes.h"

uint8_t scenes_init(void)
{
  NutRegisterCgi("scenes.cgi", scenes_form);

  return 0;
}

int scenes_form(FILE * stream, REQUEST * req)
{
  char* scene_s=NULL;
  unsigned int scene = 0;
  char* status_s=NULL;
  unsigned int status = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBot(stream, "text/html", -1);

  if (req->req_method == METHOD_GET)
  {
    scene_s = NutHttpGetParameter(req, "scene");
    status_s = NutHttpGetParameter(req, "status");
    if(scene_s && status_s)
    {
      scene = strtoul(scene_s, NULL, 10);
      status = strtoul(status_s, NULL, 10);
      if(scene < EVENT_MAX) { event_action(scene, status); }
      if((EVENT_MAX <= scene) && (scene < (EVENT_MAX + POWER_MAX))) { power_set(scene - EVENT_MAX, status); }
    }
    fflush(stream);
  }

  return 0;
}
