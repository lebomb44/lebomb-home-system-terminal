#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "light.h"

#define LIGHT_NB 3
#define LIGHT_PUSH_NB 3

#define LIGHT_ON  1
#define LIGHT_OFF 0

u08 light_but_state_old[LIGHT_NB] = { LIGHT_OFF, LIGHT_OFF, LIGHT_OFF };

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

void light_init(void)
{
}

void light_cycle(void)
{
  u08 but_state_new = LIGHT_OFF;
  u08 i = 0;

  for(i=0; i<LIGHT_NB; i++)
  {
    but_state_new = button_get(light_but[i]);
    if(!alarm_control_lights())
    {
      if(i < LIGHT_PUSH_NB)
      {
        if((light_but_state_old[i] == LIGHT_ON) && (but_state_new == LIGHT_OFF))
        {
          if(light_get(i) == LIGHT_OFF) { node[NODE_REG_LIGHT+i] = LIGHT_ON; } else { node[NODE_REG_LIGHT+i] = LIGHT_OFF; }
        }
      }
      else
      {
        if(but_state_new != light_but_state_old[i])
        {
          node[NODE_REG_LIGHT+i] = but_state_new;
        }
      }
      light_set(i, node[NODE_REG_LIGHT+i]);
    }
    light_but_state_old[i] = but_state_new;
  }
}
