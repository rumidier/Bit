#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MYPORT 50000
#define MAXBUFLEN 100

int
main (int argc,
      char *argv[])
{
  int sockfd;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  int addr_len, numbytes;
  char buf[MAXBUFLEN];

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  my_addr.sim_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  bzero (&(my_addr.sin_zero), 8);

  if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  addr_len = sizeof(struct sockaddr);
  memset (buf, '\0', MAXBUFLEN);

  if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *)&their_addr, $addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
  printf("get packet from %s\n", inet_ntoa(theri_addr.sin_addr));
  printf("packet is %d bytes long\n", numbytes);
  printf("packet contains: %s\n", buf);

  close(sockfd);

  return 0;
}
