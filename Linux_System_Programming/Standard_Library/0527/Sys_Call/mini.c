#include <stdio.h>
#include <stdarg.h>

void
miniprintf( char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	double dval;
	int ival;

	va_start (ap, fmt);

	for (p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}
		switch(*++p)
		{
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char*); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}

int
main (int argc,
      char *argv[])
{
	int n      = 20;
	double d   = 24.23;
	char msg[] = "hello";
	miniprintf("miniprintf: %d %f %s\n", n, d, msg);

	return 0;
}
