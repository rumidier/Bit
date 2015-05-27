#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc,
	  char *argv[])
{
	int i = 0;

	for (i=0;  i<argc; i++)
	{
		printf("argv [%d] : %s\n", i, argv[i]);
	}
	printf("argc: %d\n", argc);

	return 0;
}
