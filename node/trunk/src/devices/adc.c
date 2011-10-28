#include "../global.h"
#include "adc.h"

void adc_init(void)
{
}

u08 adc_get(u08 channel)
{
  uint16_t temp_ADC = 0;

  if(channel>7) { return 0; }
  ADMUX=(0x40+channel);
  ADCSRA=0xD7; /* 0b11010111 */
  while(!bit_is_set(ADCSRA,4)); /* 0b00010000 */
  temp_ADC = (uint16_t) ADCL;
  temp_ADC += (((uint16_t) ADCH) << 8);

  return temp_ADC;
}
