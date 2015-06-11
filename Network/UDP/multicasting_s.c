#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MULTI_PORT 12345
#define MULTI_GROUP "225.0.0.37"
#define MSGBUFSIZE 256

int
main (int argc,
      char *argv[])
{
  struct sockaddr_in addr;
  int fd, nbytes, addrlen;
  struct ip_mreq mreq;
  char msgbuf[MSGBUFSIZE];

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror("socket");
      exit(1);
    }
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(MULTI_PORT);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("bind");
      exit(1);
    }

  mreq.imr_multiaddr.s_addr = inet_addr(MULTI_GROUP);
  mreq.imr_interface.s_addr=htonl(INADDR_ANY);

  if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
      perror("setsockopt");
      exit(1);
    }

  while(1) {
    addrlen = sizeof(addr);
    memset(msgbuf, '\0', strlen(msgbuf));

    if ((nbytes = recvfrom(fd, msgbuf, MSGBUFFSIZE, 0, (struct sockaddr *)&addr, &addrlen)) < 0)
      {
        perror("recvfrom");
        exit(1);
      }
    puts(msgbuf);
  }
}
