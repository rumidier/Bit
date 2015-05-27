#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	FILE *fp;

	if ( (fp = fopen("test.txt", "r")) != NULL )
	{
		printf("Success!\n");
		printf("Opening\"test.txt\" in \"r\" mode!\n");
	}
	else {
		perror("Error");
		exit(-1);
	}
	fclose(fp);

	return 0;
}
