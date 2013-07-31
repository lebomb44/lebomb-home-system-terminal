#include <stdio.h>

#include <dev/gpio.h>

#include "buzzer.h"

#define BUZZER_PORT NUTGPIO_PORTE
#define BUZZER_BIT 2

uint16_t buzzer_time = 0;

uint8_t buzzer_init(void)
{
  GpioPinConfigSet(BUZZER_PORT, BUZZER_BIT, GPIO_CFG_OUTPUT);
  buzzer_stop();

  return 0;
}

void buzzer_start(uint16_t duration)
{
  if(0 == buzzer_time)
  {
    /* FIXME GpioPinSetHigh(BUZZER_PORT, BUZZER_BIT); */
    buzzer_time = duration;
  }
}

void buzzer_stop(void)
{
  buzzer_time = 0;
  GpioPinSetLow(BUZZER_PORT, BUZZER_BIT);
}

void buzzer_update(void)
{
  if(0 < buzzer_time) { buzzer_time--; }
  else { buzzer_stop(); }
}

uint16_t buzzer_state(void)
{
  return buzzer_time;
}
