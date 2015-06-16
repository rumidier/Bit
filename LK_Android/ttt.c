#include <stdio.h>
#include <stdlib.h>

int ffs (int x)
{
  int r = 1;

  if (!x) return 0;

  if (!(x & 0xffff)) {
	  printf("ffff\n");
    x >>= 16;
    r += 16;
  }

  if (!(x & 0xff)) {
	  printf("ff\n");
    x >>= 8;
    r += 8;
  }

  if (!(x & 0xf)) {
	  printf("f\n");
    x >>= 4;
    r += 4;
  }

  if (!(x & 3)) {
	  printf("3\n");
    x >>=2;
    r += 2;
  }

  if (!(x & 1)) {
	  printf("1\n");
    x >>=1;
    r += 1;
  }

  return r;
}

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define BITS_PER_LONG 32

int sched_find_first_bit (const unsigned long *b)
{
#if BITS_PER_LONG == 64
	if (unlikely(b[0]))
		return ffs(b[0]);
	//if (likely(b[1]))
	if (b[1])
		return ffs(b[1])+64;
	return ffs(b[2]) + 128;
#elif BITS_PER_LONG == 32

	//if (unlikely(b[0]))
	if(b[0])
		return ffs(b[0]);
	//if (unlikely(b[1]))
	if(b[1])
		return ffs(b[1]) + 32;
	//if (unlikely(b[2]))
	if(b[2])
		return ffs(b[2]) + 64;
	if (b[3])
		return ffs(b[3]) + 96;
	return ffs(b[4]) + 128;
#else
#error BITS_PER_LONG not defined
#endif
}


int
main (int argc,
      char *argv[])
{
  unsigned long i = 0x10000000;

  int ret;
  ret = sched_find_first_bit(&i);
  printf("ret: %d\n", ret);

  return 0;
}
