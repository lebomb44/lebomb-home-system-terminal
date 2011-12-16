#include "global.h"

#include "devices/adc.h"
#include "devices/eeprom.h"
#include "devices/i2c.h"
#include "devices/ir.h"
#include "devices/relay.h"
#include "devices/timer.h"
#include "devices/uart.h"

#include "apps/room.h"
#include "apps/node.h"
#include "apps/safety.h"
#include "apps/alarm.h"

int main(void)
{
  relay_init();
  uart_init();
  i2c_init();
  ir_init();
  adc_init();
  eeprom_init();
  timer_init();

  node_init();
  safety_init();
  alarm_init();
  room_init();

  sleep_mode();
  sbi(SREG,7);
  timer_start();
  while(1)
  {
    safety_cycle();
    alarm_cycle();
    room_cycle();
    sleep();
/*  uart_putc((u08)'.'); */
  }
  return 0;
}
