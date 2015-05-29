#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	printf("_exit() test\n");
	_exit(0);
}
