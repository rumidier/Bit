#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	int nfds, ret;
	char buff[1024];

	struct pollfd fds;

	while (1) {
		fds.fd = 0;
		fds.events = POLLIN;
		nfds = poll(&fds, 1, 2500);

		if (nfds == 0)
		{
			printf("time out error\n");
		}
		if (fds.revents & POLLIN)
		{
			ret = read(0, buff, sizeof buff);
			buff[ret - 1] = 0;
			printf("[%s]\n", buff);
			if (strcmp (buff, "exit") == 0)
				break;
		}
	}

	return 0;
}
