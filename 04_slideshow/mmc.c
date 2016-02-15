#include "io.h"

int mmc_init(void)
{
  volatile unsigned int *flag = OFFSET(DEVICE_MMC_START, MMC_SDFLAG);

  if(!(*flag & 1)) {
    /* error: card is not detected */
    //return 1;
  }

  /* initlalize */
  *(volatile unsigned int *)OFFSET(DEVICE_MMC_START, MMC_SDINIT) = 0;
  return 0;
}

unsigned int mmc_read(unsigned int sector, void *buf)
{
  unsigned int i;
  unsigned int *dest = buf;
  volatile unsigned int *read_sector = OFFSET(DEVICE_MMC_START, MMC_SDREAD);
  volatile unsigned int *hard_buf = OFFSET(DEVICE_MMC_START, MMC_SDBUF);

  *read_sector = sector;
  for(i = 0; i < MMC_SECTOR_SIZE >> 2; i++) {
    *dest++ = *hard_buf++;
  }

  return *(volatile unsigned int *)OFFSET(DEVICE_MMC_START, MMC_SDFLAG);
}

unsigned int mmc_write(unsigned int sector, const void *buf)
{
  unsigned int i;
  const unsigned int *src = buf;
  volatile unsigned int *write_sector = OFFSET(DEVICE_MMC_START, MMC_SDWRITE);
  volatile unsigned int *hard_buf = OFFSET(DEVICE_MMC_START, MMC_SDBUF);

  for(i = 0; i < MMC_SECTOR_SIZE >> 2; i++) {
    *hard_buf++ = *src++;
  }
  *write_sector = sector;

  return *(volatile unsigned int *)OFFSET(DEVICE_MMC_START, MMC_SDFLAG);
}
