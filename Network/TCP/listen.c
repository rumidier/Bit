#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main (int argc,
      char *argv[],
      char **envp)
{
  int sck_inet, len_inet;
  struct sockaddr_in adr_inet;

  sck_inet = socket(AF_INET, SOCK_STREAM, 0);

  memset (&adr_inet, 0, sizeof adr_inet);
  adr_inet.sin_family = AF_INET;
  adr_inet.sin_port = htons(9000);

  inet_aton(argv[1], &adr_inet.sin_addr);
  len_inet = sizeof(adr_inet);

  if (bind(sck_inet, (struct sockaddr *)&adr_inet, len_inet) < 0)
    {
      printf("bind error\n");
      exit(0);
    }

  if (listen(sck_inet, 5) < 0)
    {
      printf("bind error\n");
      exit(0);
    }

  system("netstat -pa --tcp");
  close(sck_inet);

  return 0;
}
