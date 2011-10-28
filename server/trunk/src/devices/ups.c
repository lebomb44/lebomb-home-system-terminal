#include <stdio.h>

#include <dev/gpio.h>

#include <pro/httpd.h>

#include "adc.h"
#include "ups.h"

#define UPS_ADC_CHANNEL 1
#define UPS_POWER_PORT NUTGPIO_PORTE
#define UPS_POWER_BIT 4

uint8_t ups_init(void)
{
  GpioPinConfigSet(UPS_POWER_PORT, UPS_POWER_BIT, 0);

  return 0;
}

uint8_t ups_temp_status_get(uint16_t temp_th)
{
  if(ups_temp_get() < temp_th) { return 0; }
  else { return 1; }
}

uint16_t ups_temp_get(void)
{
  /* 10mV / °F */
  /* ADC 10 bits */

  /* 0 -> 1023 */
  /* 0V -> 5V */
  /* 0°F -> 500°F */
  /* -17.777°C -> 260°C */

  /* a = 271 m°C / u */
  /* b = -17777 m°C */

  return adc_get(UPS_ADC_CHANNEL);
}

uint8_t ups_power_status_get(void)
{
  if(GpioPinGet(UPS_POWER_PORT, UPS_POWER_BIT) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
