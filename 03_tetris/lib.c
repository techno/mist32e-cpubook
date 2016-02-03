static unsigned int rand_seed;

void *memcpy(void *dest, const void *src, unsigned int n)
{
  for(; n > 0; n--) {
    *(char *)dest++ = *(char *)src++;
  }
  return dest;
}

unsigned int srand(unsigned int s)
{
  return (rand_seed = s);
}

/*
unsigned int rand(void)
{
  asm volatile("rand %0, %1" : "=r"(rand_seed) : "r"(rand_seed));
  return rand_seed;
}
*/
unsigned int rand(void)
{
  static unsigned int x = 123456789;
  static unsigned int y = 362436069;
  static unsigned int z = 521288629;
  unsigned int w = rand_seed;
  unsigned int t;

  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return rand_seed = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
