#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

#define MYPORT 50000
#define MAXLEN 1000

int
main (int argc,
      char *argv[])
{
  int sockfd;
  struct sockaddr_in their_addr;
  struct hostent *he;
  int numbytes;
  char buf[MAXLEN];

  if (argc != 2) {
    fprintf(stderr, "usage: %s IP\n", argv[0]);
    exit(1);
  }

  if ((he=gethosbyname(argv[1])) == NULL) {
    herror("gethostbyname");
    exit(1);
  }

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(MYPORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(their_addr.sin_zero), 8);
  memset(buf, '\0', MAXLEN);

  printf("Input Message: ");
  fflush(stdin);
  fgets(buf, MAXLEN, stdin);

  if ((numbytes = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
  close(sockfd);

  return 0;
}
