#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int
main (int argc,
		char *argv[])
{
	int i;
	signal (SIGINT, SIG_IGN);
	for ( i=0; i<5; i++)
	{
		printf("...sig: SIG_IGN\n");
		sleep(1);
	}
	signal(SIGINT, SIG_DFL);

	while (1) {
		printf("...sig: SIG_DFL\n");
		sleep(1);
	}

	return 0;
}
