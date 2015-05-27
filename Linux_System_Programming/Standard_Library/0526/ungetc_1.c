#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main (int argc,
		char *argv[])
{
	int c, number = 0;
	char op;
	FILE *fp;

	if ( (fp = fopen("test.txt", "r")) == NULL )
	{
		perror("File open error");
		exit(-1);
	}

	while (!feof(fp))
	{
		while ((c = fgetc(fp)) != EOF && isdigit(c))
			number = 10 * number + c - '0';

		if (c == '\n')
			continue;

		fprintf(stdout, "Operand => %d\n", number);
		number = 0;

		if (c != EOF)
		{
			ungetc(c, fp);
			op = fgetc(fp);
			fprintf(stdout, "Operator => %c\n", op);
		}
	}
	fclose(fp);

	return 0;
}
