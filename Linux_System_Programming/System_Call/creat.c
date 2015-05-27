#include <fcntl.h>

int
main (int argc,
		char *argv[])
{
	char *fname = "test.txt";
	int fd;

	fd = creat(fname, 0666);
	if (fd < 0)
		perror("creat()");
	else
	{
		printf("Success!\n Filename:%s,fd:%d\n", fname, fd);
		close(fd);
	}

	return 0;
}
