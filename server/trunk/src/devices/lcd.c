#include <stdio.h>
#include <pro/httpd.h>

#include "lcd.h"

uint8_t lcd_init(void)
{
  return 0;
}

uint8_t lcd_puts(char * msg)
{
  printf(msg);
  return 0;
}
