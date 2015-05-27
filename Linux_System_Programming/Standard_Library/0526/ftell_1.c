#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	char *fname = "test.txt";
	long fsize;
	FILE *fp;

	if ( (fp = fopen(fname, "r")) == NULL ) 
	{
		printf("File Open Error\n");
		exit(-1);
	}
	fseek(fp, 0L, SEEK_END);
	fsize = ftell(fp);

	printf("The size of <%s> is %ld byte.\n", fname, fsize);
	exit(0);

	return 0;
}
