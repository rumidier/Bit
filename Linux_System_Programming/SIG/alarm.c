#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int alm(signo)
{
	printf("SIGALRM Receive");
}

int
main (int argc,
    char *argv[])
{
	signal(SIGALRM, (void *)alm);
	alarm(10);
	printf("process id pause\n");
	pause();
	printf("process is wakeup\n");

	return 0;
}
