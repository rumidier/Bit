#include <stdio.h>
#include <signal.h>

void shoe_mask()
{
	sigset_t sigset;

	if (sigprocmask(0, NULL, &sigset) < 0)
		printf("sigprocmask error");

	if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");

	printf("\n");
}

int
main (int argc,
		char *argv[])
