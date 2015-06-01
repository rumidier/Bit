#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void
handler (int sig) {
	printf("signal no(%d) Received\n", sig);
}

int
main (int argc,
      char *argv[])
{
	if (signal(SIGUSR1, handler) == SIG_ERR) {
		fprintf(stderr, "cannot set USR1\n");
		exit(1);
	}

	if (signal(SIGUSR2, handler) == SIG_ERR) {
		fprintf(stderr, "cannot set USR2\n");
		exit(1);
	}

	for(;;) pause();
}
