#include <stdio.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	char first, last, ch;
	int pid;

	if ((pid = fork()) > 0)
	{
		first = 'A';
		last  = 'Z';
	}
	else if (pid == 0)
	{
		first = 'a';
		last  = 'z';
		sleep(1);
	}

	for (ch = first; ch <= last; ch++)
	{
		write(1, &ch, 1);
	}

	return 0;
}
