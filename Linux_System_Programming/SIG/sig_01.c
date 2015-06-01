#include <stdio.h>
#include <signal.h>

void foo (int signo)
{
	printf("foo: signo: %d\n", signo);
}

void goo (int i)
{
	printf("goo called : %d\n", i);
}

int
main (int argc,
		char *argv[])
{
	void (*p)(int);

	p = signal(SIGINT, foo);
	printf("%p\n", p);

	p = signal(SIGINT, goo);
	printf("%p\n", p);

	p(3);

	return 0;
}
