#include <stdio.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	char buf[BUFSIZ];

	setbuf(stdout, buf);
	printf("Hello,");
	sleep(2);
	printf("UNIX!");
	sleep(2);
	printf("\n");
	sleep(3);

	setbuf(stdout, buf);
	sleep(3);

	printf("How"); sleep(1);
	printf("are"); sleep(1);
	printf("you"); sleep(1);
	printf("\n"); sleep(1);

	return 0;
}
