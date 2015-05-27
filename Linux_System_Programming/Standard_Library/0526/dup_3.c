#include <stdio.h>
#include <fcntl.h>

int
main (int argc,
	  char *argv[])
{
	int fd;
	int ret;
	char buff[10];

	if (argc == 2)
	{
		fd = open (argv[1], O_RDONLY);
		close(0);
		dup(fd);
	}

	while (ret = read(0, buff, sizeof buff))
		write (1, buff, ret);

	if (argc == 2)
	{
		close(fd);
		close(0);
	}

	return 0;
}
