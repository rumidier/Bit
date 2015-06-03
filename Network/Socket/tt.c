#include <stdio.h>
#include <arpa/inet.h>

int
main (int argc,
      char *argv[])
{
  unsigned short h_port = 0x1234;
  unsigned short n_port;
  unsigned long h_addr = 0x12345678;
  unsigned long n_addr;

  n_port = htons (h_port);
  n_addr = htonl (h_addr);

  printf("Host ordered port: %#x\n", h_port);
  printf("Network ordred port: %#x\n", n_port);
  printf("Host ordered address: %#x\n", h_addr);
  printf("Network ordred address: %#x\n", n_addr);

  return 0;
}
