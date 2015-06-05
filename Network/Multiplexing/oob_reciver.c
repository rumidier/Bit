#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define MYPORT 50000
#define BACKLOG 10
#define MAXSIZE 100

int
main (int argc,
		char *argv[])
{
	int sockfd, new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size, n;
	char buff[MAXSIZE];
	fd_set rset, xset;
	int justreadoob = 0;

	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("sock");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	if(bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size)) == -1) {
		perror("accept");
		exit(0);
	}

	FD_ZERO(&rset);
	FD_ZERO(&xset);

	for(;;) {
		FD_SET(new_fd, &rset);

		if (justreadoob == 0)
			FD_SET (new_fd, &xset);

		select (new_fd + 1, &rset, NULL, &xset, NULL);

		if(FD_ISSET(new_fd, &xset))
		{
			n = recv(new_fd, buff, sizeof(buff) - 1, MSG_OOB);
			buff[n] = '\0';
			printf("read %d OOB byte: %s\n", n, buff);

			justreadoob = 1;
			FD_CLR(new_fd, &xset);
		}
		if (FD_ISSET(new_fd, &rset))
		{
			if ((n = recv(new_fd, buff, sizeof(buff) - 1, 0)) == 0)
			{
				printf("recvied EOF\n");
				exit(0);
			}
			buff[n] = '\0';
			printf("read %d byte: %s\n", n, buff);
			justreadoob = 0;
		}
	}

	close(new_fd);
	close(sockfd);

	return 0;
}
