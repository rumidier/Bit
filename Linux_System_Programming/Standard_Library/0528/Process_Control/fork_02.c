#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

static int global = 6;
char *filename = "temp1";
char buf[40];

int
main (int argc,
      char *argv[])
{
	int fd, pid;
	int local;

	local = 88;

	if((fd = open(filename, O_RDWR | O_CREAT, 0777)) < 0) {
		fprintf(stderr, "Error, cannot create file\n");
		exit(0);
	}
	sprintf(buf, "a stdout by write function\n");
	write (STDOUT_FILENO, buf, strlen(buf));

	printf("before fork\n");

	if ((pid = fork()) < 0) {
		printf("fork error");
	}
	else if (pid == 0)
	{
		global++;
		local++;
	}
	else
		sleep(2);

	sprintf(buf, "pid = %d, global = %d, local = %d\n", getpid(), global, local);
	write(fd, buf, strlen(buf));

	return 0;
}
