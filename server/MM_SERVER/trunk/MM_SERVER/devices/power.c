#include <stdio.h>

#include <dev/gpio.h>

#include "power.h"

/* WIFI */
#define POWER0_PORT NUTGPIO_PORTE
#define POWER0_BIT 4
/* POWER1 Not Used */
#define POWER1_PORT NUTGPIO_PORTE
#define POWER1_BIT 4
/* POWER2 Not Used */
#define POWER2_PORT NUTGPIO_PORTE
#define POWER2_BIT 4
/* Central Heater */
#define POWER3_PORT NUTGPIO_PORTE
#define POWER3_BIT 4

uint8_t power_init(void)
{
  GpioPinConfigSet(POWER0_PORT, POWER0_BIT, 0);
  GpioPinConfigSet(POWER1_PORT, POWER1_BIT, 0);
  GpioPinConfigSet(POWER2_PORT, POWER2_BIT, 0);
  GpioPinConfigSet(POWER3_PORT, POWER3_BIT, 0);

  return 0;
}

void power_set(POWER_T power, uint8_t status)
{
  if(power == POWER_0) { GpioPinConfigSet(POWER0_PORT, POWER0_BIT, status); }
  if(power == POWER_1) { GpioPinConfigSet(POWER1_PORT, POWER1_BIT, status); }
  if(power == POWER_2) { GpioPinConfigSet(POWER2_PORT, POWER2_BIT, status); }
  if(power == POWER_3) { GpioPinConfigSet(POWER3_PORT, POWER3_BIT, status); }
}
