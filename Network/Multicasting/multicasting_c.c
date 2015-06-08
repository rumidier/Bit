#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MULTI_PORT 12345
#define MULTI_GROUP "225.0.0.37"

int
main (int argc,
      char *argv[])
{
  struct sockaddr_in addr;
  int fd, cnt;
  struct ip_mreq mreq;
  char *message = "Hello, World!";

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) <0)
    {
      perror("socket");
      exit(1);
    }

  memset (&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(MULTI_GROUP);
  addr.sin_port = htons(MULTI_PORT);

  while (1)
    {
      if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
          perror("sendto");
          exit(1);
        }
      sleep(1);
    }
}
