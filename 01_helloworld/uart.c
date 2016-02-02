#include "uart.h"

void uart_init(void)
{
  *(volatile unsigned int *)OFFSET(DEVICE_SCI_START, SCI_CFG) = SCI_TEN | SCI_REN;
}

void uart_putc(int c)
{
  *(volatile unsigned int *)OFFSET(DEVICE_SCI_START, SCI_TXD) = c;
}

void uart_puts(char *str)
{
  while(*str) {
    uart_putc(*(str++));
  }
  uart_putc('\n');
}
