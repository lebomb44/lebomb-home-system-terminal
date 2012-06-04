#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "light.h"

#define LIGHT_NB 3

#define LIGHT_ON  1
#define LIGHT_OFF 0

u08 light_but_state_old[LIGHT_NB] = { LIGHT_OFF, LIGHT_OFF, LIGHT_OFF };
u08 light_but_cmd_old[LIGHT_NB]   = { LIGHT_OFF, LIGHT_OFF, LIGHT_OFF };
u08 light_node_cmd_old[LIGHT_NB]  = { LIGHT_OFF, LIGHT_OFF, LIGHT_OFF };

u08 light_but[LIGHT_NB]     = NODE_ROOM_CONFIG_LIGHT_BUT;
u08 light_relay[LIGHT_NB]   = NODE_ROOM_CONFIG_LIGHT_RELAY;

void light_set(u08 light, u08 pos)
{
  if(light >= LIGHT_NB) { return; }

  if(pos==LIGHT_ON)
  {
    if(relay_set(light_relay[light], RELAY_ON)!=RELAY_OK) { return; }
  }
  if(pos==LIGHT_OFF)
  {
    if(relay_set(light_relay[light], RELAY_OFF)!=RELAY_OK) { return; }
  }
}

u08 light_get(u08 light)
{
  if(relay_get(light_relay[light]) == RELAY_ON) { return LIGHT_ON; }
  else { return LIGHT_OFF; }
}

void light_set_all(u08 pos)
{
  u08 i = 0;
  for(i=0; i<LIGHT_NB; i++)
  {
    light_set(i, pos);
  }
}

void lights_update(void)
{
  u08 but_state_new = LIGHT_OFF;
  u08 but_cmd_new   = LIGHT_OFF;
  u08 i = 0;

  for(i=0; i<LIGHT_NB; i++)
  {
    but_state_new = button_get(light_but[i]);
    if((light_but_state_old[i] == LIGHT_ON) && (but_state_new == LIGHT_OFF))
    {
      if(light_get(i) == LIGHT_OFF) { light_set(i, LIGHT_ON ); } else { light_set(i, LIGHT_OFF); }
    }
    light_but_state_old[i] = but_state_new;

// if(button_get(light_but[i]) == BUTTON_ON) { but_cmd_new = LIGHT_ON; } else { but_cmd_new = LIGHT_OFF; }

    if(node[NODE_REG_LIGHT+i] != light_node_cmd_old[i])
    {
      light_node_cmd_old[i] = node[NODE_REG_LIGHT+i];
      light_set(i, light_node_cmd_old[i]);
    }
    else
    {
      if(but_cmd_new != light_but_cmd_old[i])
      {
        light_but_cmd_old[i] = but_cmd_new;
        light_set(i, light_but_cmd_old[i]);
      }
    }
  }
}

void light_init(void)
{
}

void light_cycle(void)
{
  u08 i = 0;
  if(!alarm_control_lights())
  {
    lights_update();
  }
  else
  {
    /* Only consider the remote control */
    for(i=0; i<LIGHT_NB; i++)
    {
      if(node[NODE_REG_LIGHT+i] != light_node_cmd_old[i])
      {
        light_node_cmd_old[i] = node[NODE_REG_LIGHT+i];
        light_set(i, light_node_cmd_old[i]);
      }
    }
  }
}
