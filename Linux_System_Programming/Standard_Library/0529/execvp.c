#include <stdio.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	static char *nargv[] = {"newpgm", "parm1", "parm2", "parm3", (char *) 0};
	printf("this is the original program\n");
	execvp("newpgm",  nargv);
	/* execlp("newpgm", "newpg", "parm1",  "parm2", "parm3", (char *) 0); */
	printf("This line should never get printed\n");

	return 0;
}
