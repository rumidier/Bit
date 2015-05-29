#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
main (int argc,
		char *argv[])
{
	printf("pid = %d, ppid = %d\n", getpid(), getppid());

	fork();

	printf("after pid = %d, ppid = %d\n", getpid(), getppid());

	return 0;
}
