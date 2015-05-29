#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;


//export 환경변수 확인하기
int
main (int argc,
      char *argv[])
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("environ[%d]: %s\n", i, environ[i]);
	}

	return 0;
}
