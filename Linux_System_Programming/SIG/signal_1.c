#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int
catchint(int signo)
{
	//Ctrl + c
	printf("SIGINT Receive\n");
}

int
main (int argc,
		char *argv[])
{
	signal(SIGINT, (void *) catchint);

	printf("sleep call #1\n"); sleep(1);
	printf("sleep call #2\n"); sleep(1);
	printf("sleep call #3\n"); sleep(1);
	printf("sleep call #4\n"); sleep(1);
	printf("Exiting");

	exit(0);

	return 0;
}
