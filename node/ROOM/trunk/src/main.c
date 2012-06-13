#include "global.h"

#include "devices/adc.h"
#include "devices/button.h"
#include "devices/eeprom.h"
#include "devices/i2c.h"
#include "devices/ir.h"
#include "devices/relay.h"
#include "devices/timer.h"
#include "devices/uart.h"

#include "apps/light.h"
#include "apps/shutter.h"
#include "apps/heater.h"
#include "apps/elec.h"
#include "apps/node.h"
#include "apps/safety.h"
#include "apps/alarm.h"
#include "apps/remote.h"

int main(void)
{
  button_init();
  relay_init();
  /* uart_init(); UART pins used as output for relay */
  i2c_init();
  ir_init();
  adc_init();
  eeprom_init();
  timer_init();

  node_init();
  safety_init();
  alarm_init();
  light_init();
  shutter_init();
  heater_init();
  elec_init();
  /* remote_init();  UART pins used as output for relay */

  sleep_mode();
  sbi(SREG,7);
  timer_start();
  while(1)
  {
    safety_cycle();
    alarm_cycle();
    light_cycle();
    shutter_cycle();
    heater_cycle();
    elec_cycle();
    /* remote_cycle(); UART pins used as output for relay */
    sleep();
    /* uart_putc((u08)'.'); UART pins used as output for relay */
  }
  return 0;
}
