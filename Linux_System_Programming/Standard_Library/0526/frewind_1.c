#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	char *fname = "test.txt";
	long position;
	FILE *fp;

	if ( (fp = fopen(fname,"r")) == NULL ) {
		printf("File Open Erro\n");
		exit(-1);
	}

	fseek(fp, 10L, SEEK_CUR);
	position = ftell(fp);
	printf("Current position = %ld\n", position);

	rewind(fp);
	position = ftell(fp);
	printf("After rewind() position = %ld\n", position);

	exit(0);

	return 0;
}
