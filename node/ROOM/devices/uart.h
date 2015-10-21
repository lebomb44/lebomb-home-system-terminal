#ifndef _UART_
#define _UART_

#include "../global.h"

extern void uart_init(void);
extern void uart_putc(u08 data);
extern void uart_send(u08 *data, u08 nb);
extern void uart_puts(u08 *s);
extern void uart_printf(const unsigned char *, ...);

#endif

