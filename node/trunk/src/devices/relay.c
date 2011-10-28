#include "../global.h"
#include "relay.h"

#define RELAY_NB 2

u08 * relay_cmd_ddr[RELAY_NB] = { (u08*)&DDRD, (u08*)&DDRB };
u08 * relay_cmd_port[RELAY_NB] = { (u08*)&PORTD, (u08*)&PORTB };
u08 relay_cmd_bit[RELAY_NB] = { 7, 1 };

u08 * relay_st_ddr[RELAY_NB] = { (u08*)&DDRB, (u08*)&DDRD };
u08 * relay_st_port[RELAY_NB] = { (u08*)&PORTB, (u08*)&PORTD };
u08 * relay_st_pin[RELAY_NB] = { (u08*)&PINB, (u08*)&PIND };
u08 relay_st_bit[RELAY_NB] = { 0, 6 };

void relay_init(void)
{
  u08 i = 0;
  for(i=0; i<RELAY_NB; i++)
  {
    relay_set(i, RELAY_OFF); /* Set OFF */
    sbi((*relay_cmd_ddr[i]), relay_cmd_bit[i]); /* Set as OUTPUT */
    sbi((*relay_st_port[i]), relay_st_bit[i]); /* Enable pullup */
    cbi((*relay_st_ddr[i]), relay_st_bit[i]); /* Set as INPUT */
  }
}

u08 relay_get(u08 ch)
{
  if(ch>=RELAY_NB) { return RELAY_OFF; }
  if(bit_is_set((*relay_st_pin[ch]), relay_st_bit[ch])) { return RELAY_OFF; }
  else { return RELAY_ON; }
}

u08 relay_set(u08 ch, u08 val)
{
  u08 i = 0;
  u08 j = 0;
  if(ch>=RELAY_NB) { return RELAY_ERROR; }

  if(val==RELAY_ON)
  {
    sbi((*relay_cmd_port[ch]), relay_cmd_bit[ch]);
  }
  if(val==RELAY_OFF)
  {
    cbi((*relay_cmd_port[ch]), relay_cmd_bit[ch]);
  }
  i = 255;
  j = 0;
  while((i>0) && (relay_get(ch)!=val)) { for(j=0;j<100;j++) {nop();} i--; }
  if(i==0) { return RELAY_ERROR; }

  return RELAY_OK;
}
