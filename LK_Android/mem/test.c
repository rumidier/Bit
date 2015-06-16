#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>

int global = 0x7777777;
int bss;

int
main (int argc,
      char *argv[])
{
	int local;
	int *p;
	void * handle;
	double (*fp)(double);

	handle = dlopen("libm.so", RTLD_LAZY);
	fp = dlsym(handle, "sin");

	p = (int *)malloc(4);
	printf("main   : %p\n", main);
	printf("global : %p\n", &global);
	printf("bss    : %p\n", &bss);
	printf("p      : %p\n", p);
	printf("printf : %p\n", printf);
	printf("fp     : %p\n", fp);
	printf("local  : %p\n",&local);
	printf("sin    : %lf\n", sin(M_PI_2));
	printf("fp     : %lf\n", fp(M_PI_2));

	dlclose(handle);
	return 0;
}
