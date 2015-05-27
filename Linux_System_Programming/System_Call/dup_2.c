#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int
main (int argc,
		char *argv[])
{
	char *fname = "test.txt";
	int fd;

	if((fd = creat(fname, 0666)) < 0) {
		perror("create()");
		exit (-1);
	}
	printf ("First printf is on the screen.\n");
	dup2 (fd, 1);
	printf("Second printf is in this file.\n");


	return 0;
}
