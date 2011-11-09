#include <dev/gpio.h>

#include <stdio.h>
#include <pro/httpd.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include "adc.h"

uint8_t adc_init(void)
{
  uint8_t i = 0;
  /* Set the first 4 pins of PORTF as input */
  /* The 4 others pins are used by JTAG */
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
  /* Set the channel number in the hardware */
  ADMUX=(0x40+channel);
  NutSleep(100);
  /* Start the acquisition */
  ADCSRA=0xD7; //0b11010111
  /* Wait for the end of the acquisition */
  /* But do not block the complete system */
  while(!bit_is_set(ADCSRA,4)) { NutSleep(10); } //0b00010000
  /* Build the returned value with Low and High register */
  temp_ADC = (uint16_t) ADCL;
  temp_ADC += (((uint16_t) ADCH) << 8);

  return temp_ADC;
}
