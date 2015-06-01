#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sig(int sig) {
	printf("child die(%d)\n", getpid());
}

int
main (int argc,
      char *argv[])
{
	signal(SIGINT, sig);
	pause();

	return 0;
}
