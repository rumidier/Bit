#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	int fd = open("myfifo", O_RDWR);
	char buff[1024];

	struct pollfd pollfd[2];
	int ret;

	setvbuf(stdin, NULL, _IONBF, 0);
	fcntl(0, F_SETFL, O_NONBLOCK);
	fcntl(fd, F_SETFL, O_NONBLOCK);

	while(1) {
		pollfd[0].fd = 0;
		pollfd[0].events = POLLIN;

		pollfd[1].fd = fd;
		pollfd[1].events = POLLIN;
		poll(pollfd, 2, -1);
		if (pollfd[0].revents & POLLIN)
		{
			ret = read(0, buff, sizeof buff);
			buff[ret - 1] = 0;
			printf("키보드 입력 : %s\n", buff);
		}
		if (pollfd[1].revents & POLLIN)
		{
			ret = read(fd, buff, sizeof buff);
			buff[ret - 1] = 0;
			printf("myfifo 입력: %s\n", buff);
		}
	}

	return 0;
}
