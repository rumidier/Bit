#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc,
		char *argv[])
{
	if (argc != 3) {
		printf("usage: symlink_1 actualname symname\n");
		exit(1);
	}

	if (symlink(argv[1], argv[2]) < 0) {
		printf("symlink call error\n");
		exit (2);
	}
	else
		printf("symlink: %s -> %s\n", argv[2], argv[1]);

	return 0;
}
