#include <stdio.h>

#include <dev/gpio.h>

#include "power.h"

/* Wifi */
#define POWER0_PORT NUTGPIO_PORTB
#define POWER0_BIT 5
/* Ethernet */
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
  if(POWER_0 == power) { GpioPinSet(POWER0_PORT, POWER0_BIT, status); }
  if(POWER_1 == power) { GpioPinSet(POWER1_PORT, POWER1_BIT, status); }
  if(POWER_2 == power) { GpioPinSet(POWER2_PORT, POWER2_BIT, status); }
  if(POWER_3 == power) { GpioPinSet(POWER3_PORT, POWER3_BIT, status); }
}

uint8_t power_get(POWER_T power)
{
  if(POWER_0 == power) { return GpioPinGet(POWER0_PORT, POWER0_BIT); }
  if(POWER_1 == power) { return GpioPinGet(POWER1_PORT, POWER1_BIT); }
  if(POWER_2 == power) { return GpioPinGet(POWER2_PORT, POWER2_BIT); }
  if(POWER_3 == power) { return GpioPinGet(POWER3_PORT, POWER3_BIT); }
  return 0;
}
