#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.56.101"
#define SERVER_PORT 9000

int
main (int argc,
		char *argv[])
{
	int sockfd;
	struct sockaddr_in dest_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(SERVER_PORT);
	dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
 	bzero(&(dest_addr.sin_zero), 8);
	connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));

	getchar();

	return 0;
}
