#include <stdio.h>

#include <dev/gpio.h>

#include "adc.h"
#include "rack.h"

#define RACK_ADC_CHANNEL 0
#define RACK_ALARM_PORT NUTGPIO_PORTE
#define RACK_ALARM_BIT 4

uint8_t rack_init(void)
{
  GpioPinConfigSet(RACK_ALARM_PORT, RACK_ALARM_BIT, 0);

  return 0;
}

uint8_t rack_temp_status_get(uint16_t temp_th)
{
  if(rack_temp_get() < temp_th) { return 0; }
  else { return 1; }
}

uint16_t rack_temp_get(void)
{
  /* 10mV / °F */
  /* ADC 10 bits */

  /* 0 -> 1023 */
  /* 0V -> 5V */
  /* 0°F -> 500°F */
  /* -17.777°C -> 260°C */

  /* a = 271 m°C / u */
  /* b = -17777 m°C */

  return adc_get(RACK_ADC_CHANNEL);
}

uint8_t rack_alarm_status_get(void)
{
  if(GpioPinGet(RACK_ALARM_PORT, RACK_ALARM_BIT) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
