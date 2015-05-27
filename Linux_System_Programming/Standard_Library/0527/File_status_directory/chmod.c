#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

int
main (int argc,
      char *argv[])
{
	struct stat statbuf;

	if ( stat("before.test", &statbuf) < 0 ) {
		perror("stat error for before.test");
		exit(-1);
	}

	if ( chmod("before.txt", (statbuf.st_mode & S_IXGRP) | S_ISGID ) < 0 ) {
		perror("chmod error for before.test");
		exit(-1);
	}

	if (chmod("after.text", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
		perror("chmod error for after.test");
		exit(-1);
	}

	return 0;
}
