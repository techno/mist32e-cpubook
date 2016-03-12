#include "io.h"

unsigned int keyboard_get_scancode(void)
{
  unsigned int scancode, k;
  volatile unsigned int flag __attribute__ ((unused));
  unsigned int result = 0;

  while(1) {
    flag = *(volatile unsigned int *)OFFSET(DEVICE_KEYBOARD_START, KEYBOARD_FLAGR);
    scancode = *(volatile unsigned int *)OFFSET(DEVICE_KEYBOARD_START, KEYBOARD_DATA);

    if(scancode & 0x100) {
      k = scancode & 0xff;
      result = (result << 8) | k;

      if(k == 0xe0 || k == 0xf0) {	
	continue;
      }
      return result;
    }
    else if(!result) {
      return result;
    }
  }
}
