#include <stdio.h>

int
main (int   argc,
      char *argv[])
{
	int a[7] = {1,2,3,4,5,6,7};
	int *p;
	int index;
	p = &a[5];
	//(120 -100) /sizeof(a[0])

	index = p - a;
	//&a[5] - &a[0] = index
	//&*(a+5) - &*(a+0)
	// a + 5 - a
	// 5

	printf("index: %d\n", index);

	return 0;
}
