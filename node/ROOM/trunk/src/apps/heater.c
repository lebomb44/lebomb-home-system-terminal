#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "heater.h"

#define HEATER_NB 3
#define HEATER_PUSH_NB 3

#define HEATER_OFF 0
#define HEATER_ON  1

u08 heater_but_state_old[HEATER_NB]  = { HEATER_OFF, HEATER_OFF, HEATER_OFF };

u08 heater_but[HEATER_NB]     = NODE_ROOM_CONFIG_HEATER_BUT;
u08 heater_relay[HEATER_NB]   = NODE_ROOM_CONFIG_HEATER_RELAY;

void heater_set(u08 heater, u08 pos)
{
  if(heater >= HEATER_NB) { return; }

  if(pos == HEATER_ON)
  {
    if(relay_set(heater_relay[heater], RELAY_ON) != RELAY_OK) { return; }
  }
  if(pos == HEATER_OFF)
  {
    if(relay_set(heater_relay[heater], RELAY_OFF) != RELAY_OK) { return; }
  }
}

u08 heater_get(u08 heater)
{
  if(heater >= HEATER_NB) { return HEATER_OFF; }

  if(relay_get(heater_relay[heater]) == RELAY_ON) { return HEATER_ON; }
  else { return HEATER_OFF; }
}

void heater_init(void)
{
}

void heater_cycle(void)
{
  u08 but_state_new = HEATER_OFF;
  u08 i = 0;

  for(i=0; i<HEATER_NB; i++)
  {
    but_state_new = button_get(heater_but[i]);
    if(but_state_new == BUTTON_ON) { but_state_new = HEATER_ON; } else { but_state_new = HEATER_OFF; }
    if(!alarm_control_heaters())
    {
      if(i < HEATER_PUSH_NB)
      {
        if((heater_but_state_old[i] == HEATER_ON) && (but_state_new == HEATER_OFF))
        {
          if(heater_get(i) == HEATER_OFF) { node[NODE_REG_HEATER+i] = HEATER_ON; } else { node[NODE_REG_HEATER+i] = HEATER_OFF; }
        }
      }
      else
      {
        if(but_state_new != heater_but_state_old[i])
        {
          node[NODE_REG_HEATER+i] = but_state_new;
        }
      }
    }
    else
    {
      node[NODE_REG_HEATER+i] = HEATER_OFF;
    }
    heater_set(i, node[NODE_REG_HEATER+i]);

    heater_but_state_old[i] = but_state_new;
  }
}
