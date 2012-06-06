#include "../global.h"
#include "../devices/eeprom.h"
#include "alarm.h"
#include "node.h"

#define ALARM_SHUTTER1 0
#define ALARM_SHUTTER2 1
#define ALARM_SHUTTER3 2

#define ALARM_SHUTTER1_DDR  DDRD
#define ALARM_SHUTTER1_PORT PORTD
#define ALARM_SHUTTER1_PIN  PIND
#define ALARM_SHUTTER1_BIT  3

#define ALARM_SHUTTER2_DDR  DDRD
#define ALARM_SHUTTER2_PORT PORTD
#define ALARM_SHUTTER2_PIN  PIND
#define ALARM_SHUTTER2_BIT  4

#define ALARM_SHUTTER3_DDR  DDRB
#define ALARM_SHUTTER3_PORT PORTB
#define ALARM_SHUTTER3_PIN  PINB
#define ALARM_SHUTTER3_BIT  6

void alarm_init(void)
{
  sbi(ALARM_SHUTTER1_PORT, ALARM_SHUTTER1_BIT);
  cbi(ALARM_SHUTTER1_DDR , ALARM_SHUTTER1_BIT);

  sbi(ALARM_SHUTTER2_PORT, ALARM_SHUTTER2_BIT);
  cbi(ALARM_SHUTTER2_DDR , ALARM_SHUTTER2_BIT);

  sbi(ALARM_SHUTTER3_PORT, ALARM_SHUTTER3_BIT);
  cbi(ALARM_SHUTTER3_DDR , ALARM_SHUTTER3_BIT);
}

void alarm_cycle(void)
{
  u08 i =0;

  if(bit_is_set(ALARM_SHUTTER1_PIN, ALARM_SHUTTER1_BIT)) { sbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER1); } else { cbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER1); }
  if(bit_is_set(ALARM_SHUTTER2_PIN, ALARM_SHUTTER2_BIT)) { sbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER2); } else { cbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER2); }
  if(bit_is_set(ALARM_SHUTTER3_PIN, ALARM_SHUTTER3_BIT)) { sbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER3); } else { cbi(node[NODE_REG_PERI_STATUS], ALARM_SHUTTER3); }

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
  if(node[NODE_REG_PERI_CONTROL] > 0) { return 1; }
  else { return 0; }
}

u08 alarm_status_shutters(void)
{
  if(node[NODE_REG_PERI_STATUS] > 0) { return 1; }
  else { return 0; }
}

u08 alarm_control_lights(void)
{
  if(node[NODE_REG_VOL_CONTROL] > 0) { return 1; }
  else { return 0; }
}

u08 alarm_control_heaters(void)
{
  if(node[NODE_REG_VOL_CONTROL] > 0) { return 1; }
  else { return 0; }
}

u08 alarm_control_elecs(void)
{
  if(node[NODE_REG_VOL_CONTROL] > 0) { return 1; }
  else { return 0; }
}
