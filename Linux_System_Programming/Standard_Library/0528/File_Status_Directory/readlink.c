#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	int nbyte;
	char buf[50];

	if (argc != 2) {
		printf("usage: readlink_1 symname\n");
		exit(1);
	}

	if ((nbyte = readlink(argv[1], buf, 50)) < 0) {
		printf("readlink call error\n");
		exit(2);
	}
	else
	{
		buf[nbyte] = '\0';
		printf("buf: %s \n", buf);
	}

	return 0;
}
