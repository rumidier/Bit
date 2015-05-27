#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	int fd;
	char c;

	if ( (fd = open("test.txt", O_RDONLY)) < 0 )
	{
		perror("open");
		exit(0);
	}

	for (;;)
	{
		if (read(fd, &c, 1) > 0)
			putchar(c);
		else
			break;
	}
	return 0;
}
