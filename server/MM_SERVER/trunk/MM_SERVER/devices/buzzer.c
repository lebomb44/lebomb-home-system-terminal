#include <stdio.h>

#include <dev/gpio.h>

#include "buzzer.h"

#define BUZZER_PORT NUTGPIO_PORTE
#define BUZZER_BIT 4

uint8_t buzzer_init(void)
{
  GpioPinConfigSet(BUZZER_PORT, BUZZER_BIT, 0);

  return 0;
}

void buzzer_set(void)
{
  GpioPinConfigSet(BUZZER_PORT, BUZZER_BIT, 0);
}
