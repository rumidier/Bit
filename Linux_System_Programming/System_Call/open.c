#include <stdio.h>
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

	fd = open(fname, O_RDONLY);

	if (fd > 0)
	{
		printf("Success\n FileName : %s, fd: %d\n", fname, fd);
		close(fd);
	}
	else
	{
	    printf ("fd: %d\n", errno);
		perror("open faild\n");
	}

	return 0;
}
