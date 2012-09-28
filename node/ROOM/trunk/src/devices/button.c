#include "../global.h"
#include "../config.h"
#include "button.h"

#define BUTTON_NB 6

#ifdef PB2_BUTTON_USED
#define BUT_DDR_5 ((u08*)&DDRB)
#else
#define BUT_DDR_5 (NULL)
#endif
//u08 * but_ddr[BUTTON_NB] = { (u08*)&DDRD, (u08*)&DDRB, (u08*)&DDRC, (u08*)&DDRC, (u08*)&DDRC, BUT_DDR_5 };
//u08 * but_port[BUTTON_NB] = { (u08*)&PORTD, (u08*)&PORTB, (u08*)&PORTC, (u08*)&PORTC, (u08*)&PORTC, (u08*)&PORTB };
//u08 * but_pin[BUTTON_NB] = { (u08*)&PIND, (u08*)&PINB, (u08*)&PINC, (u08*)&PINC, (u08*)&PINC, (u08*)&PINB };
//u08 but_bit[BUTTON_NB] = { 5, 7, 1, 2, 3, 2 };

u08 * but_ddr[BUTTON_NB] = { (u08*)&DDRD, (u08*)&DDRD, (u08*)&DDRC, (u08*)&DDRC, (u08*)&DDRC, BUT_DDR_5 };
u08 * but_port[BUTTON_NB] = { (u08*)&PORTD, (u08*)&PORTD, (u08*)&PORTC, (u08*)&PORTC, (u08*)&PORTC, (u08*)&PORTB };
u08 * but_pin[BUTTON_NB] = { (u08*)&PIND, (u08*)&PIND, (u08*)&PINC, (u08*)&PINC, (u08*)&PINC, (u08*)&PINB };
u08 but_bit[BUTTON_NB] = { 7, 6, 1, 2, 3, 2 };

void button_init(void)
{
  u08 i = 0;
  for(i=0; i<BUTTON_NB; i++)
  {
    if((but_ddr[i] != NULL) && (but_port[i] != NULL) && (but_pin[i] != NULL))
    {
      sbi((*but_port[i]), but_bit[i]);
      cbi((*but_ddr[i]), but_bit[i]);
    }
  }
}

u08 button_get(u08 ch)
{
  if(ch >= BUTTON_NB) { return BUTTON_OFF; }
  if((but_ddr[ch] != NULL) && (but_port[ch] != NULL) && (but_pin[ch] != NULL))
  {
    if(!bit_is_set((*but_pin[ch]), but_bit[ch])) { return BUTTON_ON; }
    else { return BUTTON_OFF; }
  }
  else
  {
    return BUTTON_OFF;
  }
}
