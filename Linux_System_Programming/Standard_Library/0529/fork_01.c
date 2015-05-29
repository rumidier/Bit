#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void my_sig(int signo)
{
	while(wait(0) > 0) {
		printf("my_sig(%d)\n", signo);
	}
}

/*
   defunct 확인을 위해
   ps -ef | grep fork_01
 */

int
main (int argc,
      char *argv[])
{
	pid_t pid;

	int i, j;
	signal(SIGCHLD, my_sig);

	for (j=0; j<7; j++) 
	{
		pid = fork();
		if (pid == 0)
		{
			for (i=0; i<3; i++)
			{
				sleep(i);
				printf("\t\tchild\n");
			}

			exit(3);
		}
	}

	while(1)
	{
		sleep(1);
		printf("parent\n");
	}

	return 0;
}
