#if 1
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>

//#define LED_ON 1
#define LED_ON			_IO('c', 1)
#define LED_RATIO		_IOW('c', 2, int)
#define LED_RATIO_READ	_IOR('c', 3, int)
int main(int argc, char ** argv)
{
	int fd;
	int ratio = 255;
	fd = open("/dev/mydev", O_RDWR);
//	ioctl(fd, LED_ON);
//	ioctl(fd, LED_RATIO,&ratio);
	ioctl(fd, LED_RATIO_READ, &ratio);
	printf("ratio: %d\n", ratio);
	close(fd);
	return 0;
}

#endif
