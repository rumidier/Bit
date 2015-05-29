#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
char glob_var[] = "HOBBY=swimming";

void
addone()
{
	char auto_var[10];
	strcpy(auto_var, "LOVER=wk");
	putenv(auto_var);
}

int
main (int argc,
      char *argv[])
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("environ[%d]: %s\n", i, environ[i]);
	}

	putenv (glob_var);
	addone();
	printf("My hobby is %s\n", getenv("HOBBY"));
	printf("My lover is %s\n", getenv("LOVER"));
	strcpy (glob_var+6, "fishing");

	for ( i = 0; environ[i] != NULL; i++)
	{
		printf("environ[%d]: %s\n", i, environ[i]);
	}

	return 0;
}
