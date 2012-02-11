#include "../global.h"
#include "../devices/relay.h"
#include "alarm.h"
#include "node.h"
#include "room.h"

#define ROOM_SHUTTER_NB 1

#define SHUTTER_UP 255
#define SHUTTER_STOP 0
#define SHUTTER_DOWN 1

u08 room_shutter_but_cmd_old[ROOM_SHUTTER_NB]  = { SHUTTER_STOP };
u08 room_shutter_node_cmd_old[ROOM_SHUTTER_NB] = { SHUTTER_STOP };

u08 * shutter_but_up_ddr[ROOM_SHUTTER_NB] = { (u08*)&DDRD };
u08 * shutter_but_up_port[ROOM_SHUTTER_NB] = { (u08*)&PORTD };
u08 * shutter_but_up_pin[ROOM_SHUTTER_NB] = { (u08*)&PIND };
u08 shutter_but_up_bit[ROOM_SHUTTER_NB] = { 5  };

u08 * shutter_but_down_ddr[ROOM_SHUTTER_NB] = { (u08*)&DDRB };
u08 * shutter_but_down_port[ROOM_SHUTTER_NB] = { (u08*)&PORTB };
u08 * shutter_but_down_pin[ROOM_SHUTTER_NB] = { (u08*)&PINB };
u08 shutter_but_down_bit[ROOM_SHUTTER_NB] = { 7 };

u08 shutter_relay_up[ROOM_SHUTTER_NB] = { 0 };
u08 shutter_relay_down[ROOM_SHUTTER_NB] = { 1 };

void room_shutter_set(u08 shutter, u08 pos)
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

void room_shutter_set_all(u08 pos)
{
  u08 i = 0;
  for(i=0; i<ROOM_SHUTTER_NB; i++)
  {
    room_shutter_set(i, pos);
  }
}

u08 room_shutter_but_up_get(u08 shutter)
{
  return !bit_is_set((*shutter_but_up_pin[shutter]), shutter_but_up_bit[shutter]);
}

u08 room_shutter_but_down_get(u08 shutter)
{
  return !bit_is_set((*shutter_but_down_pin[shutter]), shutter_but_down_bit[shutter]);
}

void room_shutters_update(void)
{
  u08 but_cmd_new = SHUTTER_STOP;
  u08 i = 0;

  for(i=0; i<ROOM_SHUTTER_NB; i++)
  {
    if(room_shutter_but_up_get(i) && !room_shutter_but_down_get(i))
    {
      but_cmd_new = SHUTTER_UP;
    }
    else
    {
      if(!room_shutter_but_up_get(i) && room_shutter_but_down_get(i))
      {
        but_cmd_new = SHUTTER_DOWN;
      }
      else
      {
        but_cmd_new = SHUTTER_STOP;
      }
    }

    if(node[NODE_REG_SHUTTER+i] != room_shutter_node_cmd_old[i])
    {
      room_shutter_node_cmd_old[i] = node[NODE_REG_SHUTTER+i];
      room_shutter_set(i, room_shutter_node_cmd_old[i]);
    }
    else
    {
      if(but_cmd_new != room_shutter_but_cmd_old[i])
      {
        room_shutter_but_cmd_old[i] = but_cmd_new;
        room_shutter_set(i, room_shutter_but_cmd_old[i]);
      }
    }
  }
}

void room_init(void)
{
  u08 i = 0;
  for(i=0; i<ROOM_SHUTTER_NB; i++)
  {
    sbi((*shutter_but_up_port[i]), shutter_but_up_bit[i]);
    cbi((*shutter_but_up_ddr[i]), shutter_but_up_bit[i]);
    sbi((*shutter_but_down_port[i]), shutter_but_down_bit[i]);
    cbi((*shutter_but_down_ddr[i]), shutter_but_down_bit[i]);
  }
}

void room_cycle(void)
{
  if(!alarm_control_shutters())
  {
    room_shutters_update();
  }
  else
  {
    if(!alarm_status_shutters())
    {
      room_shutter_set_all(SHUTTER_DOWN);
    }
    else
    {
      room_shutter_set_all(SHUTTER_STOP);
    }
  }
}
