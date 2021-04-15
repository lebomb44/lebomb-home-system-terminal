#include <stdio.h>

#include <dev/gpio.h>

#include "volume.h"

#define VOLUME0_PORT NUTGPIO_PORTE
#define VOLUME0_BIT 7
#define VOLUME1_PORT NUTGPIO_PORTB
#define VOLUME1_BIT 0

#define VOLUME2_PORT NUTGPIO_PORTD
#define VOLUME2_BIT 4
#define VOLUME3_PORT NUTGPIO_PORTD
#define VOLUME3_BIT 6

#define VOLUME4_PORT NUTGPIO_PORTD
#define VOLUME4_BIT 7
#define VOLUME5_PORT NUTGPIO_PORTD
#define VOLUME5_BIT 5

uint8_t volume_init(void)
{
  GpioPinConfigSet(VOLUME0_PORT, VOLUME0_BIT, GPIO_CFG_PULLUP);
  GpioPinConfigSet(VOLUME1_PORT, VOLUME1_BIT, GPIO_CFG_PULLUP);
  GpioPinConfigSet(VOLUME2_PORT, VOLUME2_BIT, GPIO_CFG_PULLUP);
  GpioPinConfigSet(VOLUME3_PORT, VOLUME3_BIT, GPIO_CFG_PULLUP);
  GpioPinConfigSet(VOLUME4_PORT, VOLUME4_BIT, GPIO_CFG_PULLUP);
  GpioPinConfigSet(VOLUME5_PORT, VOLUME5_BIT, GPIO_CFG_PULLUP);

  return 0;
}

uint8_t volume_status_get(void)
{
  return ((GpioPinGet(VOLUME0_PORT, VOLUME0_BIT) << 0 ) | \
          (GpioPinGet(VOLUME1_PORT, VOLUME1_BIT) << 1 ) | \
          (GpioPinGet(VOLUME2_PORT, VOLUME2_BIT) << 2 ) | \
          (GpioPinGet(VOLUME3_PORT, VOLUME3_BIT) << 3 ) | \
          (GpioPinGet(VOLUME4_PORT, VOLUME4_BIT) << 4 ) | \
          (GpioPinGet(VOLUME5_PORT, VOLUME5_BIT) << 5 ));
}

uint8_t volume_status_group1_get(void)
{
  return ((GpioPinGet(VOLUME0_PORT, VOLUME0_BIT) << 0 ) | \
          (GpioPinGet(VOLUME1_PORT, VOLUME1_BIT) << 1 ) | \
          (GpioPinGet(VOLUME4_PORT, VOLUME4_BIT) << 4 ) | \
          (GpioPinGet(VOLUME5_PORT, VOLUME5_BIT) << 5 ));
}

uint8_t volume_status_group2_get(void)
{
  return ((GpioPinGet(VOLUME2_PORT, VOLUME2_BIT) << 2 ) | \
          /* FIXME (GpioPinGet(VOLUME3_PORT, VOLUME3_BIT) << 3 ) */);
}

