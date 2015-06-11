#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 50000
#define MAXDATASIZE 1000

void
iband (int s, char *buf)
{
	int z;

	if ((z = send(s, buf, strlen(buf), 0)) == -1) {
		perror("send");
		close(s);
		exit(0);
	}
	printf("ib: '%s' (%d)\n", buf, z);
}

void
oband (int s, char *buf)
{
	int z;
	if ((z = send(s, buf, strlen(buf), MSG_OOB )) == -1) {
		perror("send");
		close(s);
		exit(0);
	}
	printf("ob: '%s' (%d)\n", buf, z);
}

int
main (int argc,
		char *argv[])
{
	int sockfd;
	struct hostent *he;
	struct sockaddr_in their_addr;

	if (argc != 2) {
		fprintf(stderr, "usage: %s IP\n", argv[0]);
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL)
	{
		herror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	iband(sockfd, "123");
	sleep(1);

	oband(sockfd, "abcdef");
	sleep(1);

	iband(sockfd, "56");
	sleep(1);

	oband(sockfd, "789");
	sleep(1);

	iband(sockfd, "89");
	sleep(1);

	close(sockfd);

	return 0;
}
