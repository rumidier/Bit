#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main (int argc,
		char *argv[])
{
	struct stat statbuf;

	if (truncate("trun.txt", 10) < 0) {
		perror("truncate error");
		exit(-1);
	}

	return 0;
}
