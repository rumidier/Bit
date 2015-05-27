#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h> //umask
#include <sys/stat.h> //umask

int
main (int argc,
	  char *argv[])
{
	if ( open("before.test", O_WRONLY | O_CREAT | O_TRUNC, 0777) < 0 ) {
		printf("1st open call error\n");
		exit(1);
	}

	umask(0777);

	if ( open("after.test", O_WRONLY | O_CREAT | O_TRUNC, 0777) < 0) {
		printf("1st open call error\n");
		exit(2);
	}

	return 0;
}
