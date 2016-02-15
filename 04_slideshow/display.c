#include "io.h"

void display_clear(unsigned int color)
{
  *((volatile unsigned int *)OFFSET(DEVICE_DISPLAY_START, DISPLAY_CLR)) = color;
}

void display_set_pixel(unsigned int x, unsigned int y, unsigned int color)
{
  volatile unsigned int *pixel = OFFSET(DEVICE_DISPLAY_START, DISPLAY_PIXEL);

  if(x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
    pixel[x + (y * DISPLAY_WIDTH)] = color;
  }
}

void display_rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
  volatile unsigned int *pixel = OFFSET(DEVICE_DISPLAY_START, DISPLAY_PIXEL);
  unsigned int xx, yy;

  if(x + w >= DISPLAY_WIDTH || y + h >= DISPLAY_HEIGHT) {
    return;
  }

  for(xx = x; xx < x + w; xx++) {
    for(yy = y; yy < y + h; yy++) {
      pixel[xx + (yy * DISPLAY_WIDTH)] = color;
    }
  }
}
