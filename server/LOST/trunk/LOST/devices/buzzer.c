#include <stdio.h>

#include <dev/gpio.h>

#include "buzzer.h"

#define BUZZER_PORT NUTGPIO_PORTE
#define BUZZER_BIT 2

uint8_t buzzer_init(void)
{
  GpioPinConfigSet(BUZZER_PORT, BUZZER_BIT, GPIO_CFG_OUTPUT);

  return 0;
}

void buzzer_set(void)
{
  GpioPinSetHigh(BUZZER_PORT, BUZZER_BIT);
}

uint8_t buzzer_get(void)
{
  return GpioPinGet(BUZZER_PORT, BUZZER_BIT);
}
