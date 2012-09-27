#include "../global.h"
#include "../config.h"
#include "ir.h"

#ifndef QUARTZ_USED
#ifdef IR_USED
#error "Impossible configuration : IR without Quartz"
#endif
#endif

#define IR_LED_DDR  DDRB
#define IR_LED_PORT PORTB
#define IR_LED_BIT  2

void ir_init(void)
{
#ifdef IR_USED
  cbi(IR_LED_PORT, IR_LED_BIT);
  sbi(IR_LED_DDR , IR_LED_BIT);
#endif
}

u08 ir_set(u08 channel)
{
#ifdef IR_USED

#endif

  return 0;
}
