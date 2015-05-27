#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <asm-generic/errno-base.h>

int
main (int argc,
		char *argv[])
{
	char *fname = "test.txt";
	int fd;
	off_t fsize;

	if ((fd = open (fname, O_RDONLY)) < 0)
	{
		perror("open()");
		exit(-1);
	}

	fsize = lseek(fd, 5, SEEK_SET);
	printf("The size of 0 <%s> is %lu byts.\n", fname, fsize);


	fsize = lseek(fd, 0, SEEK_CUR);
	printf("The size of 5 <%s> is %lu byts.\n", fname, fsize);

	fsize = lseek(fd, 10, SEEK_CUR);
	printf("The size of 10 <%s> is %lu byts.\n", fname, fsize);

	fsize = lseek(fd, -5, SEEK_END);
	printf("The size of -10 <%s> is %lu byts.\n", fname, fsize);

	exit(0);
	return 0;
}
