#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#include <dev/board.h>
#include <dev/gpio.h>

#include <sys/thread.h>
#include <sys/timer.h>

#include <arpa/inet.h>

#include "uart.h"

FILE * uart1_fd;

uint8_t uart_init(void)
{
  u_long uart_data = 0;

  GpioPinConfigSet(NUTGPIO_PORTE, 0, GPIO_CFG_PULLUP);
  GpioPinSetHigh(NUTGPIO_PORTE, 0);
  GpioPinConfigSet(NUTGPIO_PORTE, 1, GPIO_CFG_OUTPUT);
  GpioPinSetLow(NUTGPIO_PORTE, 1);

  NutRegisterDevice(&DEV_UART0, 0, 0);
  freopen(DEV_UART0_NAME, "r+b", stdout);

  uart_data = 2400;
  _ioctl(_fileno(stdout), UART_SETSPEED, &uart_data);
  freopen(DEV_UART0_NAME, "r+b", stdin);
  uart_data = 2400;
  _ioctl(_fileno(stdout), UART_SETSPEED   , &uart_data);
  uart_data = 8;
  _ioctl(_fileno(stdout), UART_SETDATABITS, &uart_data);
  uart_data = 0;
  _ioctl(_fileno(stdout), UART_SETPARITY  , &uart_data);
  uart_data = 1;
  _ioctl(_fileno(stdout), UART_SETSTOPBITS, &uart_data);
  uart_data=1000;
  _ioctl(_fileno(stdin), UART_SETREADTIMEOUT, &uart_data);

  GpioPinConfigSet(NUTGPIO_PORTD, 2, GPIO_CFG_PULLUP);
  GpioPinSetHigh(NUTGPIO_PORTD, 2);
  GpioPinConfigSet(NUTGPIO_PORTD, 3, GPIO_CFG_OUTPUT);
  GpioPinSetLow(NUTGPIO_PORTD, 3);

  NutRegisterDevice(&DEV_UART1, 0, 0);
  uart1_fd = fopen(DEV_UART1_NAME, "r+b");

  uart_data = 115200;
  _ioctl(_fileno(uart1_fd), UART_SETSPEED   , &uart_data);
  uart_data = 8;
  _ioctl(_fileno(uart1_fd), UART_SETDATABITS, &uart_data);
  uart_data = 0;
  _ioctl(_fileno(uart1_fd), UART_SETPARITY  , &uart_data);
  uart_data = 1;
  _ioctl(_fileno(uart1_fd), UART_SETSTOPBITS, &uart_data);
  uart_data=2000;
  _ioctl(_fileno(uart1_fd), UART_SETREADTIMEOUT, &uart_data);
/*
  uart_data = 2048;
  _ioctl(_fileno(uart1_fd), UART_SETRXBUFSIZ, &uart_data);
  uart_data = 1228;
  _ioctl(_fileno(uart1_fd), UART_SETRXBUFLWMARK, &uart_data);
  uart_data = 2048;
  _ioctl(_fileno(uart1_fd), UART_SETTXBUFSIZ, &uart_data);
  uart_data = 1228;
  _ioctl(_fileno(uart1_fd), UART_SETTXBUFLWMARK, &uart_data);
*/

  return 0;
}
