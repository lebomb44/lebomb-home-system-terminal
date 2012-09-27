#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "elec.h"

#define ELEC_NB 3
#define ELEC_PUSH_NB 3

#define ELEC_OFF 0
#define ELEC_ON  1

u08 elec_but_state_old[ELEC_NB]  = { ELEC_OFF, ELEC_OFF, ELEC_OFF };

u08 elec_but[ELEC_NB]     = NODE_ROOM_CONFIG_ELEC_BUT;
u08 elec_relay[ELEC_NB]   = NODE_ROOM_CONFIG_ELEC_RELAY;

void elec_set(u08 elec, u08 pos)
{
  if(elec >= ELEC_NB) { return; }

  if(pos == ELEC_ON)
  {
    if(relay_set(elec_relay[elec], RELAY_ON) != RELAY_OK) { return; }
  }
  if(pos == ELEC_OFF)
  {
    if(relay_set(elec_relay[elec], RELAY_OFF) != RELAY_OK) { return; }
  }
}

u08 elec_get(u08 elec)
{
  if(elec >= ELEC_NB) { return ELEC_OFF; }

  if(relay_get(elec_relay[elec]) == RELAY_ON) { return ELEC_ON; }
  else { return ELEC_OFF; }
}

void elec_init(void)
{
}

void elec_cycle(void)
{
  u08 but_state_new = ELEC_OFF;
  u08 i = 0;

  for(i=0; i<ELEC_NB; i++)
  {
    but_state_new = button_get(elec_but[i]);
    if(but_state_new == BUTTON_ON) { but_state_new = ELEC_ON; } else { but_state_new = ELEC_OFF; }
    if(!alarm_control_elecs())
    {
      if(i < ELEC_PUSH_NB)
      {
        if((elec_but_state_old[i] == ELEC_ON) && (but_state_new == ELEC_OFF))
        {
          if(elec_get(i) == ELEC_OFF) { node[NODE_REG_ELEC+i] = ELEC_ON; } else { node[NODE_REG_ELEC+i] = ELEC_OFF; }
        }
      }
      else
      {
        if(but_state_new != elec_but_state_old[i])
        {
          node[NODE_REG_ELEC+i] = but_state_new;
        }
      }
    }
    else
    {
      node[NODE_REG_ELEC+i] = ELEC_OFF;
    }
    elec_set(i, node[NODE_REG_ELEC+i]);

    elec_but_state_old[i] = but_state_new;
  }
}
