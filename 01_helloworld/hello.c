#include "uart.h"

void main(void)
{
  uart_init();
  uart_puts("Hello, world!");
}
