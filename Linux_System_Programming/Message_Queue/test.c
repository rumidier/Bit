#include <stdio.h>
#include <stdlib.h>

struct AAA {
	int mtype;
	char mtext[1];
};

int
main (int argc,
      char *argv[])
{
	struct AAA * p;
	int i;

	p = (struct AAA *) malloc (sizeof(struct AAA));

	for (i = 0; i <= 10; i++)
	{
		p->mtext[i] = i+1;
	}

	for (i=0; i<=10; i++)
	{
		printf("mtext[%d]: %d\n", i, p->mtext[i]);
	}

	return 0;
}
