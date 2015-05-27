#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	char name[L_tmpnam], line[80];
	FILE *fp;

	printf("%s\n", tmpnam(NULL));

	tmpnam(name);
	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL) {
		perror("tmpfile error");
		exit(-1);
	}

	fputs("one line of output\n", fp);
	rewind(fp);

	if (fgets(line, sizeof(line), fp) == NULL) {
		perror("fgets error");
		exit(-1);
	}

	fputs(line,stdout);
	exit(0);

	return 0;
}
