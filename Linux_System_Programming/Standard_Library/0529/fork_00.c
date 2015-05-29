#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
	wait(0);
}

int
main (int argc,
      char *argv[])
{
	pid_t pid;

	int i;
	signal(SIGCHLD, my_sig);
/*
  SIGCHLD 확인은 kill -l
http://jangpd007.tistory.com/90
*/
	pid = fork();

	if (pid == 0)
	{
		for ( i=0; i<3; i++)
		{
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	}
	while(1)
	{
		sleep(1);
		printf("parent\n");
	}

	return 0;
}
