#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int
vpf(char *fmt,...)
{
	va_list argptr;
	int cnt;

	va_start(argptr, fmt);
	cnt = vprintf(fmt, argptr);
	va_end(argptr);

	return cnt;
}

int
main (int argc,
      char *argv[])
{
	int i   = 20;
	float f = 24.23;
	char *s = "hello";

	vpf("miniprintf: %d, %f, %s\n", i,f,s);

	return 0;
}
