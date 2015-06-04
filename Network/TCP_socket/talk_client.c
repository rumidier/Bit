#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024

char *escapechar = "exit\n";

int
main (int argc,
      char *argv[])
{
	char sendline[MAXLINE];
	char *haddr;
	int size, port;
	pid_t pid;
	static int s;
	static struct sockaddr_in server_addr;
	int len;
	static struct sockaddr_in fd_ser;

	if (argc < 3)
	{
		printf("Usage: %s SERVER_ADDRESS TCP_POR\n", argv[0]);
		return -1;
	}
	else {
		haddr = argv[1];
		port = atoi(argv[2]);
	}

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Client: CAn't open stream socket.\n");
		return -1;
	}
	bzero((char *)&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(haddr);
	server_addr.sin_port = htons(port);

	if (connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Client: can't connect to server.\n");
		return -1;
	}
	len = sizeof (fd_ser);

	if (getpeername(s, (struct sockaddr *)&fd_ser, (socklen_t *)&len) == 0)
	{
		printf("fd_ser IP: %s, Port: %u\n", inet_ntoa(fd_ser.sin_addr), (unsigned)ntohs(fd_ser.sin_port));
	}

	if ((pid = fork()) > 0)
	{
		while ((size = read(0, sendline, MAXLINE)) > 0)
		{
			sendline[size] = '\0';
			if (write(s, sendline, strlen(sendline)) != size)
			{
				printf("client: can't write to server.\n");
				return -1;
			}
			if (strncmp(sendline, escapechar, 4) == 0)
			{
				kill(pid, SIGQUIT);
				break;
			}
		}
	}

	return 0;
}
