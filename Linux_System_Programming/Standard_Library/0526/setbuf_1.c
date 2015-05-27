#include <stdio.h>

int
main (int argc,
      char *argv[])
{
	char buf[BUFSIZ];
	printf("Hello,"); sleep(1);
	printf("UNIX!"); sleep(1);
	printf("\n"); sleep(1);

	setbuf(stdout, NULL);
	printf("How"); sleep(1);
	printf("are"); sleep(1);
	printf("you"); sleep(1);
	printf("\n"); sleep(1);

	return 0;
}
