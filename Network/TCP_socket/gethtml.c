#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_STRING_LENGTH 100

int
main (int argc,
      char *argv[])
{

  int sockfd;
  struct sockaddr_in cliaddr;
  char sendmsg[MAX_STRING_LENGTH];
  char recvmsg[MAX_STRING_LENGTH];

  if (argc != 2)
    {
      printf("usage: gethtm IP\n");
      exit(0);
    }
  sockfd = socket(PF_INET, SOCK_STREAM, 0);

  bzero(&cliaddr, sizeof(cliaddr));
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(80);
  cliaddr.sin_addr.s_addr = inet_addr(argv[1]);

  connect (sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

  bzero(sendmsg, MAX_STRING_LENGTH);
  strcpy(sendmsg, "GET /index.html\n");
  send(sockfd, sendmsg, sizeof(sendmsg), 0);

  while (1)
    {
      bzero(recvmsg, MAX_STRING_LENGTH);
      if (recv(sockfd, recvmsg, sizeof(recvmsg) - 1, 0) <= 0) {
        break;
      }
      printf("%s", (char *)recvmsg);
    }
  close (sockfd);
  return 0;
}
