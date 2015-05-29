#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int my_system (char *cmd) {
	char *argv[] = {cmd, (char *)0};
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == 0) {
		execve("/bin/ls", argv, 0);
		_exit(127);
	} else if (pid < 0) {
		status = -1;
	} else {
		waitpid (pid, &status, 0);
	}

	return status;
}

int
main ()
{
	my_system("ls -l");

	return 0;
}
