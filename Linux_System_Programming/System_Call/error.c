#include <stdio.h>
#include <string.h>
#include <errno.h>

// /usr/include/asm-generic/errno-base.h

int
main (int argc,
	  char *argv[])
{
	char *err;
	char msg[10] = "err test";

//	err = strerror(EPERM);
//	printf("err: %s\n", err);
	err = strerror(ENOENT);
	printf("err: %s\n", err);
	errno = 3;
	perror(msg);

	return 0;
}
