#include <stdio.h>
#include <fcntl.h>

int
main (int argc,
      char *argv[])
{
	char *fname = "test.txt";
	int fd;
	FILE *fp;

	if ( (fd = open(fname, O_RDONLY)) > 0)
		printf("Success!!\nFile descriptor: %d\n", fd);
	else
		printf("failed\n");

	if ( (fp = fdopen(fd,"r")) != NULL)
		printf("fdopen() Success!!\n");
	else
		printf("fdopen() failed\n");

	fclose(fp);
	return 0;
}
