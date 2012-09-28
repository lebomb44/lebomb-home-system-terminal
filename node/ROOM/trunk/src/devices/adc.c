#include "../global.h"
#include "adc.h"

void adc_init(void)
{
}

u08 adc_get(u08 channel)
{
  u16 temp_ADC = 0;
  u08 ret = 0;

  if(channel>5) { return 0; }
  ADMUX=(0x40+channel);
  ADCSRA=0xD7; /* 0b11010111 */
  while(!bit_is_set(ADCSRA,4)); /* 0b00010000 */
  temp_ADC = (u16) ADCL;
  temp_ADC += (((u16) ADCH) << 8);
  ADCSRA = 0;

  if(temp_ADC > 255) { ret = 255; }
  else { ret = temp_ADC; }
  return ret;
}
