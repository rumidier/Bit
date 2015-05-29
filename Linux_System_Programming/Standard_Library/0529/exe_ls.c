#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main ()
{
	char *argv[] = {"ls", "-l", (char *)0};

	/*
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		execve("/bin/ls", argv, 0);
	}
	wait(0);
	printf("after\n");
	*/

	return 0;
}
