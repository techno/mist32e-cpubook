#include <stdbool.h>
#include <limits.h>
#include "tetris.h"
#include "io.h"

#define putchar(c) (uart_putc(c))

char tiles[HEIGHT][WIDTH];

char current_block[BLOCK_HEIGHT][BLOCK_WIDTH];
int current_y, current_x;
enum tile current_tile;

bool block_init(void)
{
  unsigned int num = rand() % NUM_BLOCKS;

  memcpy(current_block, blocks[num], BLOCK_HEIGHT * BLOCK_WIDTH);
  current_y = 0;
  current_x = (WIDTH / 2) - (BLOCK_WIDTH / 2);
  current_tile = num + 1;

  if(block_move(0, 0)) {
    /* game over */
    return true;
  }

  return false;
}

bool block_move(int dy, int dx)
{
  int y, x;

  for(y = 0; y < BLOCK_HEIGHT && current_y + dy + y < HEIGHT; y++) {
    for(x = 0; x < BLOCK_WIDTH && current_x + dx + x < WIDTH; x++) {
      if(current_block[y][x]) {
	if(current_y + dy + y < 0 || current_x + dx + x < 0) {
	  return true;
	}
	else if(tiles[current_y + dy + y][current_x + dx + x]) {
	  /* conflict block */
	  return true;
	}
      }
    }
  }

  current_y += dy;
  current_x += dx;
  return false;
}

bool block_rotate(void)
{
  char tmp_block[BLOCK_HEIGHT][BLOCK_WIDTH];
  int y, x;

  /* rotate */
  for(y = 0; y < BLOCK_HEIGHT; y++) {
    for(x = 0; x < BLOCK_WIDTH; x++) {
      tmp_block[x][y] = current_block[BLOCK_HEIGHT - y - 1][x];
    }
  }

  /* conflict check */
  for(y = 0; y < BLOCK_HEIGHT && current_y + y < HEIGHT; y++) {
    for(x = 0; x < BLOCK_WIDTH && current_x + x < WIDTH; x++) {
      if(tmp_block[y][x]) {
	if(current_y + y < 0 || current_x + x < 0) {
	  return true;
	}
	else if(tiles[current_y + y][current_x + x]) {
	  /* conflict block */
	  return true;
	}
      }
    }
  }

  memcpy(current_block, tmp_block, BLOCK_HEIGHT * BLOCK_WIDTH);
  return false;
}

void block_copy(void)
{
  unsigned int y, x;

  for(y = 0; y < BLOCK_HEIGHT && current_y + y < HEIGHT; y++) {
    for(x = 0; x < BLOCK_WIDTH && current_x + x < WIDTH; x++) {
      if(current_block[y][x]) {
	tiles[current_y + y][current_x + x] = current_tile;
      }
    }
  }
}

void tiles_print_ch(void)
{
  unsigned int y, x;

  for(y = 0; y < HEIGHT; y++) {    
    for(x = 0; x < WIDTH; x++) {
      if(tiles[y][x]) {
	switch(tiles[y][x]) {
	case TILE_I:
	case TILE_O:
	case TILE_T:
	case TILE_J:
	case TILE_L:
	case TILE_S:
	case TILE_Z:
	  putchar('*');
	  break;
	case TILE_SIDE:
	  putchar('|');
	  break;
	case TILE_BOTTOM:
	  putchar('-');
	  break;
	default:
	  putchar(' ');
	  break;
	}
      }
      else if(current_y <= y && y - current_y < BLOCK_HEIGHT &&
	      current_x <= x && x - current_x < BLOCK_WIDTH &&
	      current_block[y - current_y][x - current_x]) {
	putchar('*');
      }
      else {
	putchar(' ');
      }
    }
    putchar('\n');
  }
}

void put_tile(unsigned int x, unsigned int y, unsigned int color)
{
  display_rectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
}

void tiles_print_display(void)
{
  unsigned int y, x;
  enum tile t;

  for(y = 0; y < HEIGHT; y++) {    
    for(x = 0; x < WIDTH; x++) {
      if(tiles[y][x]) {
	t = tiles[y][x];
      }
      else if(current_y <= y && y - current_y < BLOCK_HEIGHT &&
	      current_x <= x && x - current_x < BLOCK_WIDTH &&
	      current_block[y - current_y][x - current_x]) {
	t = current_tile;
      }
      else {
	t = TILE_NONE;
      }

      switch(t) {
      case TILE_I:
	put_tile(x, y, DISPLAY_COLOR_CYAN);
	break;
      case TILE_O:
	put_tile(x, y, DISPLAY_COLOR_YELLOW);
	break;
      case TILE_T:
	put_tile(x, y, DISPLAY_COLOR_PURPLE);
	break;
      case TILE_J:
	put_tile(x, y, DISPLAY_COLOR_BLUE);
	break;
      case TILE_L:
	put_tile(x, y, DISPLAY_COLOR_ORANGE);
	break;
      case TILE_S:
	put_tile(x, y, DISPLAY_COLOR_GREEN);
	break;
      case TILE_Z:
	put_tile(x, y, DISPLAY_COLOR_RED);
	break;
      case TILE_SIDE:
      case TILE_BOTTOM:
	put_tile(x, y, DISPLAY_COLOR_GRAY);
	break;
      default:
	put_tile(x, y, DISPLAY_COLOR_BLACK);
	break;
      }
    }
  }
}

unsigned int get_timestamp(void)
{
  unsigned int time;

  asm volatile ("srfrcr     \n\t"
		"srfrclr %0" : "=r"(time));
  return time;
}

unsigned int diff_timestamp(unsigned int prev, unsigned int now)
{
  if(now < prev) {
    return UINT_MAX - (prev - now) + 1;
  }
  return now - prev;
}

enum key get_key(void)
{
  unsigned int code;

  code = keyboard_get_scancode();
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

void init(void)
{
  int y, x;

  display_clear(DISPLAY_COLOR_BLACK);
  srand(get_timestamp());

  /* tiles init */
  for(x = 0; x < WIDTH; x++) {
    tiles[0][x] = TILE_TOP;
    tiles[HEIGHT - 1][x] = TILE_BOTTOM;
  }
  for(y = 1; y < HEIGHT - 1; y++) {
    tiles[y][0] = TILE_SIDE;
    for(x = 1; x < WIDTH - 1; x++) {
      tiles[y][x] = TILE_NONE;
    }
    tiles[y][WIDTH - 1] = TILE_SIDE;
  }

  /* generate block */
  block_init();
}

void main(void)
{
  unsigned int prev, now;
  bool move_fail;

  uart_init();
  uart_puts("Hello, TETRIS.");
  display_clear(DISPLAY_COLOR_WHITE);
  uart_puts("Press any key to start.");

  while(1) {
    if(keyboard_get_scancode()) {
      break;
    }
  }

  uart_puts("Start!");
  init();

  now = get_timestamp();

  while(1) {
    /* print tiles */
    tiles_print_display();
    tiles_print_ch();
    prev = now;

    while(diff_timestamp(prev, now) < CLOCK_HZ) {
      now = get_timestamp();

      switch(get_key()) {
      case KEY_LEFT:
	move_fail = block_move(0, -1);
	break;
      case KEY_RIGHT:
	move_fail = block_move(0, 1);
	break;
      case KEY_DOWN:
	move_fail = block_move(1, 0);
	break;
      case KEY_ROTATE:
	move_fail = block_rotate();
	break;
      default:
	move_fail = true;
	break;
      }
      if(!move_fail) {
	tiles_print_display();
	/*tiles_print_ch();*/
      }
    }

    /* move block down */
    if(block_move(1, 0)) {
      block_copy();
      if(block_init()) {
	/* GAME OVER */
	break;
      }
    }
  }
}
