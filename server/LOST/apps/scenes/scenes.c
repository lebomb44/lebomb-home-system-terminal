#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pro/httpd.h>

#include "../../devices/lbcomif.h"

#include "events.h"
#include "scenes.h"

uint8_t scenes_init(void)
{
  lbcomif_registerSlaveCallBack(ID_LOST_SCENES_EXEC_TC, event_config);
  NutRegisterCgi("scenes.cgi", scenes_form);

  return 0;
}

void scenes_exec(uint8_t src, uint8_t dst, uint8_t cmd, uint8_t len, uint8_t * data)
{
  if(2 == len)
  {
    event_action(data[0], data[1]);
  }
}

int scenes_form(FILE * stream, REQUEST * req)
{
  char* scene_s = NULL;
  unsigned int scene = 0;
  char* status_s = NULL;
  unsigned int status = 0;

  NutHttpSendHeaderTop(stream, req, 200, "Ok");
  NutHttpSendHeaderBottom(stream, req, "text/html", -1);

  if(METHOD_GET == req->req_method)
  {
    scene_s = NutHttpGetParameter(req, "scene");
    status_s = NutHttpGetParameter(req, "status");
    if(scene_s && status_s)
    {
      scene = strtoul(scene_s, NULL, 10);
      status = strtoul(status_s, NULL, 10);
      if(EVENT_MAX > scene) { event_action(scene, status); }
    }
    fflush(stream);
  }

  return 0;
}

