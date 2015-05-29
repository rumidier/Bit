#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (int argc,
      char *argv[])
{
	int status;

	if (fork() == 0)
	{
		exit(7);
	}

	wait(&status);
	if (WIFEXITED(status))
		printf("noma= %d\n", WEXITSTATUS(status));

    if (WIFSIGNALED(status))
		printf("abnormal: %d\n", WTERMSIG(status));

	return 0;

}
