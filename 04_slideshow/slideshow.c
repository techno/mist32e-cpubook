#include "io.h"
#include "interrupt.h"

#define IMAGE_MAX 5
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define IMAGE_DEPTH 16
#define IMAGE_SIZE ((IMAGE_DEPTH / 8) * IMAGE_WIDTH * IMAGE_HEIGHT)

volatile unsigned int nimg, prev_nimg;

void __attribute__((interrupt)) int_keyboard(void)
{
  unsigned int c;
  while((c = keyboard_get_scancode()) && c < 0xf000)
    nimg++;
}

void main(void)
{
  idt_entry *idt;
  unsigned int sector;
  char buf[MMC_SECTOR_SIZE];
  unsigned int i, j, x, y, p, p1, p2;

  nimg = 0;
  prev_nimg = 999999;

  /* idt initialize */
  idt = idt_setup();
  idt_entry_setup(idt, IDT_KEYBOARD_NUM, &int_keyboard);
  idt_entry_enable(idt, IDT_KEYBOARD_NUM);

  /* load idt */
  idt_set(idt);
  idt_load();

  /* enable interrupt */
  interrupt_enable();

  uart_init();
  if(mmc_init()) {
    uart_puts("MMC initialization failed.");
    return;
  }

  display_clear(DISPLAY_COLOR_BLACK);

  while(1) {
    if(prev_nimg != nimg) {
      nimg %= IMAGE_MAX;
      prev_nimg = nimg;

      sector = nimg * IMAGE_SIZE / MMC_SECTOR_SIZE;

      x = 0;
      y = 0;
      
      for(i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i += (MMC_SECTOR_SIZE / 2)) {
	mmc_read(sector++, buf);

	for(j = 0; j < MMC_SECTOR_SIZE; j += 4) {
	  p = *(unsigned int *)(buf + j);
	  p2 = p & 0xffff;
	  p1 = (p >> 16) & 0xffff;

	  display_set_pixel(x++, y, p2);
	  display_set_pixel(x++, y, p1);

	  if(x >= IMAGE_WIDTH) {
	    x = 0;
	    y++;
	  }
	}
      }
    }
  }
}
