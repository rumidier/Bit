#include <stdio.h>
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
	int i   = 30;
	float f = 90.0;
	char *s = "abc";

	vpf("%d, %f, %s\n", i,f,s);

	return 0;
}
