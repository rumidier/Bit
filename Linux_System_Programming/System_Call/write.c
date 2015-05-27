#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int
main (int argc,
		char * argv[])
{
	int fd, linecnt = 0;
	char c;
	char buf[20] = "hello";

	char *fname = "test.txt";

	if ((fd = open (fname, O_RDWR)) < 0) {
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

	write(fd,buf,strlen(buf));
	printf("Total line: %d\n", linecnt);


	return 0;
}
