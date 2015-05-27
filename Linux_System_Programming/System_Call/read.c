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
	int fd, linecnt = 0;
	char c;

	char *fname = "test.txt";

	if((fd = open (fname, O_RDONLY)) < 0) {
		perror("open()");
		exit (-1);
	}

	for (;;) {
		if (read(fd, &c, 1) > 0) {
			if (c=='\n') linecnt++;
		}
		else {
			break;
		}
	}

	printf("Total line: %d\n", linecnt);
	return 0;
}
