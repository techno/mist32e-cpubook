#define OFFSET(ptr, offset) ((void *)((char *)ptr + offset))
#define WORD_ADDR(addr) (addr << 2) 

/* KEYBOARD */
#define DEVICE_KEYBOARD_START WORD_ADDR(0x04000000)
#define DEVICE_KEYBOARD_END   WORD_ADDR(0x04000002)

#define KEYBOARD_DATA WORD_ADDR(0)
#define KEYBOARD_FLAGR WORD_ADDR(1)

unsigned int keyboard_get_scancode(void);

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
#define DISPLAY_PIXEL WORD_ADDR(0x00000100)

#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480

#define DISPLAY_COLOR_WHITE  0xffff
#define DISPLAY_COLOR_BLACK  0x0000
#define DISPLAY_COLOR_RED    0xf800
#define DISPLAY_COLOR_GREEN  0x07e0
#define DISPLAY_COLOR_BLUE   0x001f
#define DISPLAY_COLOR_YELLOW 0xffe0
#define DISPLAY_COLOR_CYAN   0x07ff
#define DISPLAY_COLOR_ORANGE 0xfd20
#define DISPLAY_COLOR_PURPLE 0x8010
#define DISPLAY_COLOR_GRAY   0xce79

void display_clear(unsigned int color);
void display_set_pixel(unsigned int x, unsigned int y, unsigned int color);
void display_rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);

/* MMC */
#define DEVICE_MMC_START WORD_ADDR(0x0404b200)

#define MMC_SDINIT  WORD_ADDR(0)
#define MMC_SDREAD  WORD_ADDR(1)
#define MMC_SDWRITE WORD_ADDR(2)
#define MMC_SDCFG   WORD_ADDR(3)
#define MMC_SDFLAG  WORD_ADDR(0xf)
#define MMC_SDBUF   WORD_ADDR(0x10)

#define MMC_SECTOR_SIZE 512
#define MMC_SECTOR_SIZE 512

int mmc_init(void);
unsigned int mmc_read(unsigned int sector, void *buf);
unsigned int mmc_write(unsigned int sector, const void *buf);
