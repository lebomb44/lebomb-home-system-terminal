#ifndef _UART_H_
#define _UART_H_

#include <stdio.h>

__BEGIN_DECLS

extern FILE * uart1_fd;
extern uint8_t uart_init(void);

__END_DECLS

#endif
