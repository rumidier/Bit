#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main (int argc,
      char **argv[])
{
  int sck_inet;
  struct sockaddr_in addr_inet, get_addr;
  int len_inet;

  sck_inet = socket(AF_INET, SOCK_STREAM, 0);

  memset(&addr_inet, 0, sizeof(addr_inet));
  addr_inet.sin_family = AF_INET;
  addr_inet.sin_port = htons(9000);
  inet_aton(argv[1], &addr_inet.sin_addr);
  len_inet = sizeof(addr_inet);

  if (bind(sck_inet, (struct sockaddr *)&addr_inet, len_inet) < 0) {
    printf("bind erron\n");
    exit(1);
  }

  if (getsockname(sck_inet, (struct sockaddr *) &get_addr, &len_inet) < 0) {
    printf("getsockname error\n");
    exit(1);
  }
  printf("IP: %s, PORT: %u\n",
         inet_ntoa(get_addr.sin_addr),
         (unsigned)ntohs(get_addr.sin_port));

  close(sck_inet);

  return 0;
}
