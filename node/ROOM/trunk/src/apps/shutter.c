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

u08 shutter_but_state_old[SHUTTER_NB]  = { SHUTTER_STOP, SHUTTER_STOP, SHUTTER_STOP };

u08 shutter_but_up[SHUTTER_NB]     = NODE_ROOM_CONFIG_SHUTTER_BUT_UP;
u08 shutter_but_down[SHUTTER_NB]   = NODE_ROOM_CONFIG_SHUTTER_BUT_DOWN;

u08 shutter_relay_up[SHUTTER_NB]   = NODE_ROOM_CONFIG_SHUTTER_RELAY_UP;
u08 shutter_relay_down[SHUTTER_NB] = NODE_ROOM_CONFIG_SHUTTER_RELAY_DOWN;

void shutter_set(u08 shutter, u08 pos)
{
  if(shutter >= SHUTTER_NB) { return; }

  if((relay_get(shutter_relay_up[shutter]) == RELAY_ON) && (relay_get(shutter_relay_down[shutter]) == RELAY_ON))
  {
    relay_set(shutter_relay_down[shutter], RELAY_OFF);
    relay_set(shutter_relay_up[shutter], RELAY_OFF);
    return;
  }
  if(pos == SHUTTER_UP)
  {
    if(relay_set(shutter_relay_down[shutter], RELAY_OFF) != RELAY_OK) { return; }
    if(relay_set(shutter_relay_up[shutter], RELAY_ON) != RELAY_OK) { return; }
  }
  if(pos == SHUTTER_DOWN)
  {
    if(relay_set(shutter_relay_up[shutter], RELAY_OFF) != RELAY_OK) { return; }
    if(relay_set(shutter_relay_down[shutter], RELAY_ON) != RELAY_OK) { return; }
  }
  if(pos == SHUTTER_STOP)
  {
    if(relay_set(shutter_relay_down[shutter], RELAY_OFF) != RELAY_OK) { return; }
    if(relay_set(shutter_relay_up[shutter], RELAY_OFF) != RELAY_OK) { return; }
  }
}

u08 shutter_but_state_get(u08 shutter)
{
  if((button_get(shutter_but_up[i]) == BUTTON_ON ) && (button_get(shutter_but_down[i]) == BUTTON_OFF))
  {
    but_state_new = SHUTTER_UP;
  }
  else
  {
    if((button_get(shutter_but_up[i]) == BUTTON_OFF) && (button_get(shutter_but_down[i]) == BUTTON_ON ))
    {
      but_state_new = SHUTTER_DOWN;
    }
    else
    {
      but_state_new = SHUTTER_STOP;
    }
  }
}

void shutter_init(void)
{
  u08 i = 0;

  for(i=0; i<SHUTTER_NB; i++)
  {
    shutter_but_state_old[i] = shutter_but_state_get(i);
  }
}

void shutter_cycle(void)
{
  u08 but_state_new = SHUTTER_STOP;
  u08 i = 0;

  for(i=0; i<SHUTTER_NB; i++)
  {
    but_state_new = shutter_but_state_get(i);
    if(!alarm_control_shutters())
    {
      if(but_state_new != shutter_but_state_old[i])
      {
        node[NODE_REG_SHUTTER+i] = but_state_new;
      }
    }
    else
    {
      node[NODE_REG_SHUTTER+i] = SHUTTER_DOWN;
    }
    shutter_set(i, node[NODE_REG_SHUTTER+i]);

    shutter_but_state_old[i] = but_state_new;
  }
}
