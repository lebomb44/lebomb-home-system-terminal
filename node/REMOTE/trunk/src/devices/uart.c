#include "../global.h"
#include "uart.h"
#include <stdio.h>
#include <stdarg.h>

// UART
#define RXPORT PORTD
#define RXPIN PIND
#define RXBIT 0
#define TXPORT PORTD
#define TXPIN PIND
#define TXBIT 1

void uart_init(void)
{
  // Initialisation de la transmission
  UBRRH=0x00;    // Baud Rate
  UBRRL=207;     // Baud Rate 2400 bps
  UCSRC=0x86;    // Mode 8 bits
  cbi(UCSRB,2);  // Disable 8 bits mode
  sbi(UCSRB,3);  // Autorise transmition
  sbi(RXPORT,0); // Resistance de tirage sur RXD
  sbi(UCSRB,4);  // Autorise reception
}

void uart_putc(u08 data)
{
  while(!bit_is_set(UCSRA,5));
  UDR=data;
}

void uart_send(u08 *data, u08 nb)
{
  u16 i=0;
  for(i=0; i<nb; i++) { uart_putc(data[i]); }
}

void uart_puts(u08 *s)
{
  u08 c;
  while ( (c = *s++) ) 
    {
      uart_putc(c);
    }
}

#define BIN 2
#define CHAR 8
#define DEC 10
#define HEX 16
#define MOT 32

void uart_printf(const unsigned char *format, ...)
{
  static const unsigned char hex[] = "0123456789ABCDEF";
  unsigned int div_val, temp_arg;
  u08 i=8;
  va_list ap;

  va_start (ap, format);
  while(*format != '\0')
  {
	if(*format != '%')
	  { uart_putc (*format); }
	else
	  {
		temp_arg = va_arg(ap,unsigned int);
		format++;
        switch (*format)
	      {
			case 'b':
			  i=8;
			  do { i--; if(bit_is_set(temp_arg,i)) {uart_putc('1');} else {uart_putc('0');} } while(i);
			  break;
			case 'c':
			  uart_putc(temp_arg);
			  break;
			case 'd':
			  div_val = 10000;
			  if (temp_arg < 0) {temp_arg = - temp_arg; uart_putc('-');}
			  while (div_val > 1 && div_val > temp_arg) { div_val /= DEC; }
			  do { uart_putc(hex[temp_arg / div_val]); temp_arg %= div_val; div_val /= DEC; }
			  while (div_val);
			  break;
			case 'x':
			  div_val = 0x10;
			  do { uart_putc(hex[temp_arg / div_val]); temp_arg %= div_val; div_val /= HEX; }
			  while (div_val);
			  break;
			case 'm':
			  div_val = 0x1000;
			  do { uart_putc(hex[temp_arg / div_val]); temp_arg %= div_val; div_val /= HEX; }
			  while (div_val);
			  break;
			default:
			  uart_putc(*format);
			  break;
		  }
	  }
	format++;
  }
  va_end (ap);
}
