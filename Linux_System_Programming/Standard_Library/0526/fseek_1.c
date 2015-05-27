#include <stdio.h>
#include <stdlib.h>

int
main (int argc,
      char *argv[])
{
	char *fname = "test.txt";
	long position;
	int ch;
	FILE *fp;

	if ( (fp = fopen(fname, "r")) == NULL) {
		printf("File Open Erro\n");
		exit(-1);
	}

	printf("Input nubmer >> ");
	scanf("%ld", &position);

	fseek(fp, position-1L, SEEK_SET);
	ch = getc(fp);
	printf("%ldth character => %c\n", position, ch);

	//test code
	fseek(fp, 0L, SEEK_END);
	position = ftell(fp);
	printf("file size: %ld\n", position);

	exit(0);
	return 0;
}
