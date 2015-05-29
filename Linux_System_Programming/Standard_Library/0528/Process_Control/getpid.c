#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int
main (int argc,
      char *argv[])
{
	pid_t pid;
	FILE *fp;

	if ((fp = fopen(argv[1], "r")) == NULL ) {
		printf("file oepn error\n");
		exit(-1);
	}

	printf("\nProcess ID        = %d\n", pid = getpid());
	printf ("Parent process ID  = %d\n", getppid());
	printf ("RealUser ID        = %d\n", getuid());
	printf ("Effective User ID  = %d\n", geteuid());
	printf ("Real group ID ID   = %d\n", getgid());
	printf ("Effective group ID = %d\n", getegid());

	return 0;
}
