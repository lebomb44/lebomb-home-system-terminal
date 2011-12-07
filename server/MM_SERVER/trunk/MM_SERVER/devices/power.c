#include <stdio.h>

#include <dev/gpio.h>

#include "power.h"

/* WIFI */
#define POWER0_PORT NUTGPIO_PORTB
#define POWER0_BIT 5
/* POWER1 Not Used */
#define POWER1_PORT NUTGPIO_PORTB
#define POWER1_BIT 6
/* POWER2 Not Used */
#define POWER2_PORT NUTGPIO_PORTB
#define POWER2_BIT 7
/* Central Heater */
#define POWER3_PORT NUTGPIO_PORTE
#define POWER3_BIT 3

uint8_t power_init(void)
{
  GpioPinConfigSet(POWER0_PORT, POWER0_BIT, GPIO_CFG_OUTPUT);
  GpioPinConfigSet(POWER1_PORT, POWER1_BIT, GPIO_CFG_OUTPUT);
  GpioPinConfigSet(POWER2_PORT, POWER2_BIT, GPIO_CFG_OUTPUT);
  GpioPinConfigSet(POWER3_PORT, POWER3_BIT, GPIO_CFG_OUTPUT);

  return 0;
}

void power_set(POWER_T power, uint8_t status)
{
  if(power == POWER_0) { GpioPinSet(POWER0_PORT, POWER0_BIT, status); }
  if(power == POWER_1) { GpioPinSet(POWER1_PORT, POWER1_BIT, status); }
  if(power == POWER_2) { GpioPinSet(POWER2_PORT, POWER2_BIT, status); }
  if(power == POWER_3) { GpioPinSet(POWER3_PORT, POWER3_BIT, status); }
  printf("POWER %d %d\n", power, status);
}
