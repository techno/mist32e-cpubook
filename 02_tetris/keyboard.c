#include "io.h"
#include "tetris.h"

unsigned int keyboard_get(void)
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

enum key keyboard_get_timeout(void)
{
  unsigned int i;
  unsigned int code;

  for (i = 0; i < 500000; i++) {
    asm volatile("nop");
  }

  code = keyboard_get();
  switch(code) {
  case 0xE0F074: // move right
    return KEY_RIGHT;
    break;
  case 0xE0F06B: // move left
    return KEY_LEFT;
    break;
  case 0xE0F072: // move down
    return KEY_DOWN;
    break;
  case 0xE0F075: // rotate
    return KEY_ROTATE;
    break;
  default:
    break;
  }

  return KEY_NONE;
}
