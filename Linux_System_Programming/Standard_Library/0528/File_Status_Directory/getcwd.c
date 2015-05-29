#include <stdio.h>
#include <unistd.h>

#define PATH_MAX 1024

int
main (int argc,
      char *argv[])
{
	char path[PATH_MAX + 1];

	if (chdir("../") < 0)
		perror("error chdir");
	else
	{
		if (getcwd(path, PATH_MAX) == NULL)
			perror("error getcwd");
		else
			printf("Current working directory changed to %s \n", path);
	}

	return 0;
}
