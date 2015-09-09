#include <cstdint>
#include <iostream>
#include <algorithm>
#include <unistd.h>

#define PORTAL_FULL_SLOT (PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT + PORTAL_SLOW_SLOT)
#define PORTAL_SLOW_SLOT 3000
#define PORTAL_CRUISE_SLOT 6000

#define PORTAL_CMD_CLOSE 0
#define PORTAL_CMD_OPEN  1

#define MOTOR_MAX_CURRENT 70
#define MOTOR_MAX_SLOW_CURRENT 15
#define delay usleep

int portal_last_cmd = PORTAL_CMD_CLOSE;
int portal_cmd = PORTAL_CMD_CLOSE;
bool portal_cmd_accepted = false;
uint16_t portal_start_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
uint16_t portal_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
uint16_t portal_force = 0;
int motor_max_current = MOTOR_MAX_SLOW_CURRENT;

uint16_t get_force(uint16_t _begin_position, uint16_t _position) {
  uint16_t _begin_force = 0;
  uint16_t _end_force = 0;

  if(PORTAL_SLOW_SLOT > (_position - _begin_position)) {
    _begin_force = _position - _begin_position;
  }
  else {
    _begin_force = PORTAL_SLOW_SLOT;
  }

  if(PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT > _position) {
    _end_force = PORTAL_SLOW_SLOT;
  }
  else {
    if((PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT) < _position) {
      _position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
    }
    if((PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT) <= _position) {
      _end_force = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT - _position;
      if(PORTAL_SLOW_SLOT/5 > _end_force) {
        _end_force = PORTAL_SLOW_SLOT/5;
      }
    }
  }
  return std::min(_begin_force, _end_force);
}

int main (int argc, char *argv[])
{
int new_cmd = PORTAL_CMD_CLOSE;
portal_start_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
portal_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT+600;
portal_cmd_accepted = true;

/*
      if(PORTAL_CMD_CLOSE == new_cmd) {
        portal_last_cmd = portal_cmd;
        portal_cmd = PORTAL_CMD_CLOSE;
        if((PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT) < portal_position) {
          portal_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
        }
        if(PORTAL_CMD_CLOSE == portal_last_cmd) {
          portal_start_position = portal_position;
        }
        if(PORTAL_CMD_OPEN == portal_last_cmd) {
          portal_start_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT - portal_position;
          portal_position = portal_start_position;
        }
        portal_cmd_accepted = true;
      }
      if(PORTAL_CMD_OPEN == new_cmd) {
        portal_last_cmd = portal_cmd;
        portal_cmd = PORTAL_CMD_OPEN;
        if((PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT) < portal_position) {
          portal_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT;
        }
        if(PORTAL_CMD_OPEN == portal_last_cmd) {
          portal_start_position = portal_position;
        }
        if(PORTAL_CMD_CLOSE == portal_last_cmd) {
          portal_start_position = PORTAL_SLOW_SLOT + PORTAL_CRUISE_SLOT + PORTAL_SLOW_SLOT - portal_position;
          portal_position = portal_start_position;
        }
        portal_cmd_accepted = true;
      }
*/

  if(true == portal_cmd_accepted) {
    delay(1);
    portal_position++;
    if(PORTAL_FULL_SLOT < portal_position) {
      portal_position = PORTAL_FULL_SLOT;
    }
    portal_force = get_force(portal_start_position, portal_position);
  }

  /* Back to idle mode : everything OFF */
/*
  if(motor_max_current < analogRead(MOTOR_SENSE_pin)) {
    portal_cmd_accepted = false;
    portal_force = 0;
  }
*/
std::cout << "portal_force=" << portal_force << std::endl;
}

