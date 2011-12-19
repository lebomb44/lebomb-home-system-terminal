#include "../global.h"
#include "ir.h"

#define IR_LED_DDR  DDRB
#define IR_LED_PORT PORTB
#define IR_LED_BIT  2

void ir_init(void)
{
  cbi(IR_LED_PORT, IR_LED_BIT);
  sbi(IR_LED_DDR , IR_LED_BIT);
}

u08 ir_set(u08 channel)
{
  return 0;
}
