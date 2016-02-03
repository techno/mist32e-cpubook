#include <stdbool.h>

#define WIDTH (10 + 2)
#define HEIGHT (20 + 2)

#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4
#define NUM_BLOCKS 7

#define TILE_SIZE 20

enum tile {
  TILE_NONE,
  TILE_I,
  TILE_O,
  TILE_T,
  TILE_J,
  TILE_L,
  TILE_S,
  TILE_Z,
  TILE_SIDE,
  TILE_TOP,
  TILE_BOTTOM,
};

enum key {
  KEY_NONE,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_DOWN,
  KEY_ROTATE,
};

bool block_init(void);
bool block_move(int dy, int dx);
bool block_rotate(void);
void block_copy(void);
void tiles_print_ch(void);
void tiles_print_display(void);

enum key keyboard_get_timeout(void);

unsigned int srand(unsigned int s);
unsigned int rand(void);
void *memcpy(void *dest, const void *src, unsigned int n);

static const char blocks[NUM_BLOCKS][BLOCK_HEIGHT][BLOCK_WIDTH] = {
  {
    {0,0,0,0},
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {1,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {1,1,1,0},
    {1,0,0,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
  },
};
