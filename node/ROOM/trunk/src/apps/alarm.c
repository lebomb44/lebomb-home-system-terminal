#include "../global.h"
#include "../devices/eeprom.h"
#include "alarm.h"
#include "node.h"

#define ALARM_SHUTTERS 0
#define ALARM_WINDOWS  1
#define ALARM_MOVE1    0

#define ALARM_SHUTTERS_DDR  DDRD
#define ALARM_SHUTTERS_PORT PORTD
#define ALARM_SHUTTERS_PIN  PIND
#define ALARM_SHUTTERS_BIT  3

#define ALARM_WINDOWS_DDR  DDRD
#define ALARM_WINDOWS_PORT PORTD
#define ALARM_WINDOWS_PIN  PIND
#define ALARM_WINDOWS_BIT  4

#define ALARM_MOVE1_DDR  DDRB
#define ALARM_MOVE1_PORT PORTB
#define ALARM_MOVE1_PIN  PINB
#define ALARM_MOVE1_BIT  6

void alarm_init(void)
{
  sbi(ALARM_SHUTTERS_PORT, ALARM_SHUTTERS_BIT);
  cbi(ALARM_SHUTTERS_DDR , ALARM_SHUTTERS_BIT);

  sbi(ALARM_WINDOWS_PORT, ALARM_WINDOWS_BIT);
  cbi(ALARM_WINDOWS_DDR , ALARM_WINDOWS_BIT);

  sbi(ALARM_MOVE1_PORT, ALARM_MOVE1_BIT);
  cbi(ALARM_MOVE1_DDR , ALARM_MOVE1_BIT);
}

void alarm_cycle(void)
{
  u08 i =0;

  if(bit_is_set(ALARM_SHUTTERS_PIN, ALARM_SHUTTERS_BIT)) { sbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTERS); } else { cbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTERS); }
  if(bit_is_set(ALARM_WINDOWS_PIN , ALARM_WINDOWS_BIT )) { sbi(node[NODE_REG_PERI_STATUS], ALARM_WINDOWS ); } else { cbi(node[NODE_REG_PERI_STATUS], ALARM_WINDOWS ); }
  if(bit_is_set(ALARM_MOVE1_PIN   , ALARM_MOVE1_BIT   )) { sbi(node[NODE_REG_VOL_STATUS ], ALARM_MOVE1   ); } else { cbi(node[NODE_REG_VOL_STATUS ], ALARM_MOVE1   ); }

  for(i=0; i<8; i++)
  {
    if(bit_is_set(node[NODE_REG_PERI_CONTROL], i))
    {
      if(!(bit_is_set(node[NODE_REG_PERI_TRIG],i)))
      {
        if(bit_is_set(node[NODE_REG_PERI_STATUS],i))
        {
          sbi(node[NODE_REG_PERI_TRIG],i);
          // FIXME eeprom_write((u16)NODE_REG_PERI_TRIG, node[NODE_REG_PERI_TRIG]);
        }
      }
    }
    else
    {
      cbi(node[NODE_REG_PERI_TRIG],i);
    }
  }
  for(i=0; i<8; i++)
  {
    if(bit_is_set(node[NODE_REG_VOL_CONTROL], i))
    {
      if(!(bit_is_set(node[NODE_REG_VOL_TRIG],i)))
      {
        if(bit_is_set(node[NODE_REG_VOL_STATUS],i))
        {
          sbi(node[NODE_REG_VOL_TRIG],i);
          // FIXME eeprom_write((u16)NODE_REG_VOL_TRIG, node[NODE_REG_VOL_TRIG]);
        }
      }
    }
    else
    {
      cbi(node[NODE_REG_VOL_TRIG],i);
    }
  }
}

u08 alarm_control_shutters(void)
{
  return bit_is_set(node[NODE_REG_PERI_CONTROL], ALARM_SHUTTERS);
}

u08 alarm_status_shutters(void)
{
  return bit_is_set(node[NODE_REG_PERI_STATUS], ALARM_SHUTTERS);
}

u08 alarm_trig_shutters(void)
{
  return bit_is_set(node[NODE_REG_PERI_TRIG], ALARM_SHUTTERS);
}
