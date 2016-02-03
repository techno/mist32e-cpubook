#include "io.h"

#define DISPLAY_COLOR_WHITE  0xffff
#define DISPLAY_COLOR_BLACK  0x0000
#define DISPLAY_COLOR_RED    0xf800
#define DISPLAY_COLOR_GREEN  0x07e0
#define DISPLAY_COLOR_BLUE   0x001f

void main(void)
{
  uart_init();
  uart_puts("Hello, keyboard_display.");
  display_clear(DISPLAY_COLOR_BLACK);

  while(1) {
    switch(keyboard_get_scancode()) {
    case 0xf01d: /* W */
      uart_puts("Change color: WHITE");
      display_rectangle(100, 100, 100, 100, DISPLAY_COLOR_WHITE);
      break;
    case 0xf01c: /* A */
      uart_puts("Change color: RED");
      display_rectangle(100, 100, 100, 100, DISPLAY_COLOR_RED);
      break;
    case 0xf01b: /* S */
      uart_puts("Change color: GREEN");
      display_rectangle(100, 100, 100, 100, DISPLAY_COLOR_GREEN);
      break;
    case 0xf023: /* D */
      uart_puts("Change color: BLUE");
      display_rectangle(100, 100, 100, 100, DISPLAY_COLOR_BLUE);
      break;
    default:
      break;
    }
  }
}
