#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int
main (int argc,
      char *argv[])
{
	pid_t pid;

	sleep(5);

	printf("\nProcess ID        = %d\n", pid = getpid());
	printf ("Parent process ID  = %d\n", getppid());
	printf ("RealUser ID        = %d\n", getuid());
	printf ("Effective User ID  = %d\n", geteuid());
	printf ("Real group ID ID   = %d\n", getgid());
	printf ("Effective group ID = %d\n", getegid());

	return 0;
}
