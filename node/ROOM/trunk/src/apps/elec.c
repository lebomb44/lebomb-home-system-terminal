#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "elec.h"

#define ELEC_NB 3

#define ELEC_ON  1
#define ELEC_OFF 0

u08 elec_but_cmd_old[ELEC_NB]  = { ELEC_OFF, ELEC_OFF, ELEC_OFF };
u08 elec_node_cmd_old[ELEC_NB] = { ELEC_OFF, ELEC_OFF, ELEC_OFF };

u08 elec_but[ELEC_NB]     = NODE_ROOM_CONFIG_ELEC_BUT;
u08 elec_relay[ELEC_NB]   = NODE_ROOM_CONFIG_ELEC_RELAY;

void elec_set(u08 elec, u08 pos)
{
  if(elec >= ELEC_NB) { return; }

  if(pos==ELEC_ON)
  {
    if(relay_set(elec_relay[elec], RELAY_ON)!=RELAY_OK) { return; }
  }
  if(pos==ELEC_OFF)
  {
    if(relay_set(elec_relay[elec], RELAY_OFF)!=RELAY_OK) { return; }
  }
}

void elec_set_all(u08 pos)
{
  u08 i = 0;
  for(i=0; i<ELEC_NB; i++)
  {
    elec_set(i, pos);
  }
}

void elecs_update(void)
{
  u08 but_cmd_new = ELEC_OFF;
  u08 i = 0;

  for(i=0; i<ELEC_NB; i++)
  {
    if(button_get(elec_but[i]) == BUTTON_ON)
    {
      but_cmd_new = ELEC_ON;
    }
    else
    {
      but_cmd_new = ELEC_OFF;
    }

    if(node[NODE_REG_ELEC+i] != elec_node_cmd_old[i])
    {
      elec_node_cmd_old[i] = node[NODE_REG_ELEC+i];
      elec_set(i, elec_node_cmd_old[i]);
    }
    else
    {
      if(but_cmd_new != elec_but_cmd_old[i])
      {
        elec_but_cmd_old[i] = but_cmd_new;
        elec_set(i, elec_but_cmd_old[i]);
      }
    }
  }
}

void elec_init(void)
{
}

void elec_cycle(void)
{
  u08 i = 0;
  if(!alarm_control_elecs())
  {
    elecs_update();
  }
  else
  {
    /* Only consider the remote control */
    for(i=0; i<ELEC_NB; i++)
    {
      if(node[NODE_REG_ELEC+i] != elec_node_cmd_old[i])
      {
        elec_node_cmd_old[i] = node[NODE_REG_ELEC+i];
        elec_set(i, elec_node_cmd_old[i]);
      }
    }
  }
}
