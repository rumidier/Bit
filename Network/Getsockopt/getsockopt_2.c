#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

void DieWithError (char * errorMessage)
{
  perror (errorMessage);
  exit(0);
}

int
main (int argc,
      char *argv[])
{
  int sd = -1;
  int so_type = -1;
  socklen_t optlen;

  if ((sd = socket (PF_INET, SOCK_STREAM, 0)) < 0)
    DieWithError("socket(2)");

  optlen = sizeof(so_type);
  if (getsockopt (sd, SOL_SOCKET, SO_TYPE, &so_type, &optlen) < 0)
    DieWithError("getsockopt");

  printf("Sock Descriptor: %d\n", sd);
  printf(" SO_TYPE : %d\n", so_type);
  printf(" SOCK_STREAM = %d\n", SOCK_STREAM);

  close(sd);

  return 0;
}
