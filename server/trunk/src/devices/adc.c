#include <dev/gpio.h>

#include <stdio.h>
#include <pro/httpd.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include "adc.h"

uint8_t adc_init(void)
{
  uint8_t i = 0;
  for(i=0; i<4; i++)
  {
    cbi(DDRF,i);
  }

  return 0;
}

uint16_t adc_get(uint8_t channel)
{
  uint16_t temp_ADC = 0;

  if(channel > 3) { return 0; }
  ADMUX=(0x40+channel);
  NutSleep(100);
  ADCSRA=0xD7; //0b11010111
  while(!bit_is_set(ADCSRA,4)) { NutSleep(10); } //0b00010000
  temp_ADC = (uint16_t) ADCL;
  temp_ADC += (((uint16_t) ADCH) << 8);

  return temp_ADC;
}
