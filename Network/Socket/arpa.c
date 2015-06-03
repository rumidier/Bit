#include <stdio.h>
#include <arpa/inet.h>

int
main (int argc,
      char *argv[])
{
  struct sockaddr_in ip_addr1;
  struct sockaddr_in ip_addr2;

  ip_addr1.sin_addr.s_addr = inet_addr(argv[1]);

  printf("inet_addr(): dotted decimal(%s) => hexa(%x)\n", argv[1], ip_addr1.sin_addr.s_addr);
  inet_aton(argv[1], &ip_addr2.sin_addr);

  printf("inet_aton(): dotted decimal(%s) => hexa(%x)\n", argv[1], ip_addr2.sin_addr.s_addr);

  return 0;
}
