#include <stdio.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	getchar();
	printf("this is the original program\n");
	execl("./newpgm", "newpag", "parm1", "parm2", "parm3", (char *) 0);
	printf("This line should never get printed\n");

	return 0;
}
