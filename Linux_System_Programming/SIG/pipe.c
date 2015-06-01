#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

int
main (int argc,
      char *argv[])
{
	char inbuf[MSGSIZE];
	int p[2],j;

	if (pipe(p) < 0) {
		perror("pipe call");
		exit(1);
	}

	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	for (j=0; j<3; j++) {
		read(p[0], inbuf, MSGSIZE);
		printf("%s\n", inbuf);
	}

	exit(0);
	return 0;
}
