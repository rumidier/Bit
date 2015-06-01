#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	pid_t pid = getpid();
	sleep(3);
	kill(pid,3);
	while(1);

	return 0;
}
