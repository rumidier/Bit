#include <stdio.h>

int
main (int argc,
      char *argv[])
{
	FILE *pipein_fp, *pipeout_fp;
	char readbuf[80];

	pipein_fp = popen("ls" "r");

	pipeout_fp = popen("sort", "w");

	while (fgets(readbuf, 80, pipein_fp))
		fputs(readbuf, pipeout_fp);
}
