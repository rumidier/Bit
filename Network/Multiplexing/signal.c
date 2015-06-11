#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo)
{
	printf("sig_handler call \n");
}

int
main (int argc,
		char *argv[])
{
	int i = 0;
	signal (SIGINT, (void *) sig_handler);

	while (1)
	{
		printf(".\n");
		sleep(1);
	}

	return 0;
}
