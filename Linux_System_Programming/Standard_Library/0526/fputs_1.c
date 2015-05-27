#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	FILE *fp;
	char buf[256];

	if ( (fp = fopen(argv[1], "w+")) == NULL )
	{
		perror("fopen error");
		exit(-1);
	}

	fputs("Input String >> ", stdout);
	gets(buf);
	fputs(buf,fp);
	puts(buf);
	rewind(fp);
	fgets(buf, sizeof(buf),fp);
	fputs(buf,fp);
	printf("[");
	puts(buf);
	printf("]");

	fclose(fp);

	return 0;
}
