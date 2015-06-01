#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

client(int readfd, int writefd)
{
	char buff[MAXBUFF];
	int n;

	if (fets(buff, MAXBUFF, stdin) == NULL)
		printf("client: filename read error");

	n=strlen(buff);
	if (buff[n-1] == '\n')
		n--;

	if (write(writefd, buff, n) != n)
		printf("client: filename write error");

	while ((n = read(readfd, buff, MAXBUFF)) > 0)
		if (write(1, buff, n) != n)
			printf("client: data write error");

	if (n < 0)
		printf("client: data read error");

}

server (
int
main (int argc,
      char *argv[])
{
	int childpid, pipe1[2], pipe2[2];

	if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
		printf("pipe error");
	if ((childpid = fork()) < 0)
		printf("fork error");
	else if (childpid > 0) {
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		while (wait((int *) 0) != childpid);

		close(pipe1[1]);
		close(pipe2[0]);
		exit(0);
	}
	else {
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);

		close(pipe1[0]);
		close(pipe2[1]);
		exit(0);
	}
}
