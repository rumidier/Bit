#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	FILE *fp;
	fpos_t position;
	int i;

	fp = fopen("sample.txt", "wt");

	for (i=0; i<100; i++)
	{
		putc('A', fp);
	}

	fgetpos(fp, &position);
	printf("position: %ld\n", position);

//	rewind(fp);
//	fsetpos(fp, &position);
//	printf("position: %ld\n", position);
//rewind(fp);
	fsetpos(fp, &position);
	printf("position: %ld\n", position);

	fclose(fp);

	return 0;
}
