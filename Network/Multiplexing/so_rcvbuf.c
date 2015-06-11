#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

void DieWithError (char *errorMessage)
{
	perror(errorMessage);
	exit(0);
}

int
main (int argc,
		char *argv[])
{
	int sd     = -1;
	int sndbuf = 0;
	int rcvbuf = 0;
	socklen_t optlen;

	if ((sd = socket (PF_INET, SOCK_STREAM, 0)) < 0)
		DieWithError("socket");

	optlen = sizeof(sndbuf);
	if (getsockopt(sd, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen) < 0)
		DieWithError("getsockopt");
	optlen = sizeof (rcvbuf);
	if (getsockopt(sd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &optlen) < 0)
		DieWithError("getsockopt");

	printf("Socket Descriptor : %d\n", sd);
	printf(" Send buf: %d bytes\n", sndbuf);
	printf(" Recv buf: %d bytes\n", rcvbuf);
	close(sd);

	return 0;
}
