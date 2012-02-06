#include "global.h"

#include "devices/eeprom.h"
#include "devices/uart.h"

#include "apps/remote.h"

int main(void)
{
  remote_init();
  uart_init();
  eeprom_init();

  remote_cycle();

  while(1){}

  return 0;
}
