#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int
main (int argc,
      char *argv[])
{
	int fd;

	if (argc != 3) {
		printf("usage: rename_1 oldname newname\n");
		exit(1);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("first open error\n");
		exit(2);
	}
	else
		close(fd);

	if (rename(argv[1], argv[2]) < 0) {
		printf("rename call error\n");
		exit(3);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("second open error\n");
		exit(4);
	}

	if ((fd = open(argv[2], O_RDONLY)) < 0) {
		printf("third open error\n");
		exit(5);
	}

	exit(0);
	return 0;
}
