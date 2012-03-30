#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "shutter.h"

#define SHUTTER_NB 3

#define SHUTTER_UP 255
#define SHUTTER_STOP 0
#define SHUTTER_DOWN 1

u08 shutter_but_cmd_old[SHUTTER_NB]  = { SHUTTER_STOP, SHUTTER_STOP, SHUTTER_STOP };
u08 shutter_node_cmd_old[SHUTTER_NB] = { SHUTTER_STOP, SHUTTER_STOP, SHUTTER_STOP };

u08 shutter_but_up[SHUTTER_NB]     = NODE_ROOM_CONFIG_SHUTTER_BUT_UP;
u08 shutter_but_down[SHUTTER_NB]   = NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN;

u08 shutter_relay_up[SHUTTER_NB]   = NODE_ROOM_CONFIG_SHUTTER_RELAY_UP;
u08 shutter_relay_down[SHUTTER_NB] = NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN;

void shutter_set(u08 shutter, u08 pos)
{
  if((relay_get(shutter_relay_up[shutter])==RELAY_ON) && (relay_get(shutter_relay_down[shutter])==RELAY_ON))
  {
    relay_set(shutter_relay_down[shutter], RELAY_OFF);
    relay_set(shutter_relay_up[shutter], RELAY_OFF);
    return;
  }
  if(pos==SHUTTER_UP)
  {
    if(relay_set(shutter_relay_down[shutter], RELAY_OFF)!=RELAY_OK) { return; }
    if(relay_set(shutter_relay_up[shutter], RELAY_ON)!=RELAY_OK) { return; }
  }
  if(pos==SHUTTER_DOWN)
  {
    if(relay_set(shutter_relay_up[shutter], RELAY_OFF)!=RELAY_OK) { return; }
    if(relay_set(shutter_relay_down[shutter], RELAY_ON)!=RELAY_OK) { return; }
  }
  if(pos==SHUTTER_STOP)
  {
    if(relay_set(shutter_relay_down[shutter], RELAY_OFF)!=RELAY_OK) { return; }
    if(relay_set(shutter_relay_up[shutter], RELAY_OFF)!=RELAY_OK) { return; }
  }
}

void shutter_set_all(u08 pos)
{
  u08 i = 0;
  for(i=0; i<SHUTTER_NB; i++)
  {
    shutter_set(i, pos);
  }
}

void shutters_update(void)
{
  u08 but_cmd_new = SHUTTER_STOP;
  u08 i = 0;

  for(i=0; i<SHUTTER_NB; i++)
  {
    if(button_get(shutter_but_up[i]) && !button_get(shutter_but_down[i]))
    {
      but_cmd_new = SHUTTER_UP;
    }
    else
    {
      if(!button_get(shutter_but_up[i]) && button_get(shutter_but_down[i]))
      {
        but_cmd_new = SHUTTER_DOWN;
      }
      else
      {
        but_cmd_new = SHUTTER_STOP;
      }
    }

    if(node[NODE_REG_SHUTTER+i] != shutter_node_cmd_old[i])
    {
      shutter_node_cmd_old[i] = node[NODE_REG_SHUTTER+i];
      shutter_set(i, shutter_node_cmd_old[i]);
    }
    else
    {
      if(but_cmd_new != shutter_but_cmd_old[i])
      {
        shutter_but_cmd_old[i] = but_cmd_new;
        shutter_set(i, shutter_but_cmd_old[i]);
      }
    }
  }
}

void shutter_init(void)
{
}

void shutter_cycle(void)
{
  if(!alarm_control_shutters())
  {
    shutters_update();
  }
  else
  {
    if(!alarm_status_shutters())
    {
      shutter_set_all(SHUTTER_DOWN);
    }
    else
    {
      shutter_set_all(SHUTTER_STOP);
    }
  }
}
