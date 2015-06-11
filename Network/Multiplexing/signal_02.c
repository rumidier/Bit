#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void sig_handler(int signo)
{
	printf("sig_handler call\n");
}

int
main (int argc,
      char *argv[])
{
	char buff[1024];
	int ret;
	int i = 0;
	int value;

	int fd = open("myfifo", O_RDWR);

	signal(SIGIO, (void *)sig_handler);

	value = fcntl(fd, F_GETFL, 0);
	value |= O_ASYNC;
	fcntl (fd, F_SETFL, value);
	fcntl(fd, F_SETOWN, getpid());

	while (1)
	{
		printf(".\n");
		sleep(1);
	}

	return 0;
}
