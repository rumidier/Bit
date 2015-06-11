#include <stdio.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <stdlib.h>

#define EPOLL_SIZE 5

int
main (int argc,
      char *argv[])
{
	int fd = open("myfifo", O_RDWR);
	char buff[1024];
	int i, ret;

	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	epfd = epoll_create(EPOLL_SIZE);

	ep_events = (struct epoll_event *)malloc (sizeof(struct epoll_event) *EPOLL_SIZE);
	event.events = EPOLLIN;
	event.data.fd = 0;

	epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);

	event.events = EPOLLIN;
	event.data.fd = fd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

	while (1)
	{
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if (event_cnt == -1)
		{
			puts("epoll_wait() error");
			break;
		}
		for (i = 0; i < event_cnt; i++)
		{
			if (ep_events[i].data.fd == 0)
			{
				ret = read(0, buff, sizeof buff);
				buff[ret - 1] = 0;
				printf("키보드 입력: %s\n", buff);
			}
			if (ep_events[i].data.fd == fd)
			{
				ret = read(fd, buff, sizeof buff);
				buff[ret - 1] = 0;
				printf("myfifo 입력: %s\n", buff);
			}
		}
	}

	return 0;
}
