#include <stdio.h>
#include <arpa/inet.h>

int
main (int argc,
      char *argv[])
{
  struct sockaddr_in ip_addr;
  char *ip;

  ip_addr.sin_addr.s_addr = inet_addr(argv[1]);
  printf("inet_addr(): dotted decimal(%s) => hexa(%x)\n", argv[1], ip_addr.sin_addr.s_addr);

  ip = inet_ntoa(ip_addr.sin_addr);
  printf("inet_aton(): hexa(%x) => dotted decimal(%s)\n", ip_addr.sin_addr.s_addr, ip);

  return 0;
}
