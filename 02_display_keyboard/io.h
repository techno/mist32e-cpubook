#define OFFSET(ptr, offset) ((void *)((char *)ptr + offset))
#define WORD_ADDR(addr) (addr << 2) 

/* KEYBOARD */
#define DEVICE_KEYBOARD_START WORD_ADDR(0x04000000)
#define DEVICE_KEYBOARD_END   WORD_ADDR(0x04000002)

#define KEYBOARD_DATA WORD_ADDR(0)
#define KEYBOARD_FLAGR WORD_ADDR(1)

unsigned int keyboard_get(void);

/* SCI */
#define DEVICE_SCI_START WORD_ADDR(0x04000040)
#define DEVICE_SCI_END   WORD_ADDR(0x04000044)

#define SCI_TXD  WORD_ADDR(0)
#define SCI_RXD  WORD_ADDR(1)
#define SCI_CFG  WORD_ADDR(2)
#define SCI_FLAG WORD_ADDR(3)

#define SCI_TEN 1
#define SCI_REN 2

void uart_init(void);
void uart_putc(int c);
void uart_puts(char *str);

/* DISPLAY */
#define DEVICE_DISPLAY_START WORD_ADDR(0x040000c0)
#define DEVICE_DISPLAY_END   WORD_ADDR(0x0404b1c0)

#define DISPLAY_CLR   WORD_ADDR(0x00000000)
#define DISPLAY_PIXCEL WORD_ADDR(0x00000100)

#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480

void display_clear(unsigned int color);
void display_set_pixcel(unsigned int x, unsigned int y, unsigned int color);
void display_rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
