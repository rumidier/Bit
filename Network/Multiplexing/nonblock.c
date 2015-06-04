#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc,
		char *argv[])
{
	int fd = open("myfifo", O_RDWR);
	char buff[1024];

	int ret;
	fcntl(0, F_SETFL, O_NONBLOCK);
	fcntl(fd, F_SETFL, O_NONBLOCK);

	while (1)
	{
		ret = read(0, buff, sizeof buff);

		if (ret >= 0)
		{
			buff[ret - 1] = 0;
			printf("키보드 입력 : %s\n", buff);
		}
		ret = read(fd, buff, sizeof buff);

		if (ret >= 0) {
			buff[ret - 1] = 0;
			printf("myfifo 입력 %s\n", buff);
		}
	}

	return 0;
}
