#include "../global.h"
#include "../config.h"
#include "../devices/button.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "heater.h"

#define HEATER_NB 3

#define HEATER_ON  1
#define HEATER_OFF 0

u08 heater_but_cmd_old[HEATER_NB]  = { HEATER_OFF, HEATER_OFF, HEATER_OFF };
u08 heater_node_cmd_old[HEATER_NB] = { HEATER_OFF, HEATER_OFF, HEATER_OFF };

u08 heater_but[HEATER_NB]     = NODE_ROOM_CONFIG_HEATER_BUT;
u08 heater_relay[HEATER_NB]   = NODE_ROOM_CONFIG_HEATER_RELAY;

void heater_set(u08 heater, u08 pos)
{
  if(pos==HEATER_ON)
  {
    if(relay_set(heater_relay[heater], RELAY_ON)!=RELAY_OK) { return; }
  }
  if(pos==HEATER_OFF)
  {
    if(relay_set(heater_relay[heater], RELAY_OFF)!=RELAY_OK) { return; }
  }
}

void heater_set_all(u08 pos)
{
  u08 i = 0;
  for(i=0; i<HEATER_NB; i++)
  {
    heater_set(i, pos);
  }
}

void heaters_update(void)
{
  u08 but_cmd_new = HEATER_OFF;
  u08 i = 0;

  for(i=0; i<HEATER_NB; i++)
  {
    if(button_get(heater_but[i]) == BUTTON_ON)
    {
      but_cmd_new = HEATER_ON;
    }
    else
    {
      but_cmd_new = HEATER_OFF;
    }

    if(node[NODE_REG_HEATER+i] != heater_node_cmd_old[i])
    {
      heater_node_cmd_old[i] = node[NODE_REG_HEATER+i];
      heater_set(i, heater_node_cmd_old[i]);
    }
    else
    {
      if(but_cmd_new != heater_but_cmd_old[i])
      {
        heater_but_cmd_old[i] = but_cmd_new;
        heater_set(i, heater_but_cmd_old[i]);
      }
    }
  }
}

void heater_init(void)
{
}

void heater_cycle(void)
{
  u08 i = 0;
  if(!alarm_control_heaters())
  {
    heaters_update();
  }
  else
  {
    /* Only consider the remote control */
    for(i=0; i<HEATER_NB; i++)
    {
      if(node[NODE_REG_HEATER+i] != heater_node_cmd_old[i])
      {
        heater_node_cmd_old[i] = node[NODE_REG_HEATER+i];
        heater_set(i, heater_node_cmd_old[i]);
      }
    }
  }
}
