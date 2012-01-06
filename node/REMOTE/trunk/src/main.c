#include "global.h"

#include "devices/eeprom.h"
#include "devices/ir.h"
#include "devices/timer.h"
#include "devices/uart.h"

#include "apps/remote.h"

int main(void)
{
  uart_init();
  ir_init();
  eeprom_init();
  timer_init();

  remote_init();

  sleep_mode();
  sbi(SREG,7);
  //timer_start();

  remote_cycle();
  while(1)
  {
    sleep();
  }
  return 0;
}
