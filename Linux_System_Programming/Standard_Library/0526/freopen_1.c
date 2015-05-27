#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	char *fname = "test.txt";
	FILE *fp;

	printf("First printf is on the screen.\n");
	if ( (fp = freopen(fname, "w", stdout)) == NULL )
	{
		perror("freopen");
		exit(-1);
	}
	printf("Second printf is in this file\n");

	return 0;
}
