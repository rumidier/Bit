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

	while (1) {
		ret = read(0, buff, sizeof buff);
		buff[ret - 1] = 0;
		printf("키보드 입력 : %s\n", buff);
		ret = read(fd, buff, sizeof buff);
		buff[ret - 1] = 0;
		printf("myfifo 입력: %s\n", buff);
	}

	return 0;
}
