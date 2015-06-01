#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int
main (int argc,
      char *argv[])
{
	pid_t pid = getpid();
	sleep(3);
	//kill(pid,3);
	raise(2);
	while(1);

	return 0;
}
