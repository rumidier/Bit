#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

void DieWithError (char *errorMessage)
{
  perror(errorMessage);
  exit(0);
}

int
main (int argc,
      char *argv[])
{
  int sock;
  struct sockaddr_in echoServAddr;
  struct sockaddr_in fromAddr;
  unsigned short echoServPort;
  unsigned int fromSize;
  char *servIP;
  char *echoString;
  char echoBuffer[ECHOMAX + 1];
  int echoStringLen;
  int respStringLen;

  if (argc != 4)
  {
	  fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
	  exit(1);
  }
  servIP       = argv[1];
  echoString   = argv[2];
  echoServPort = atoi(argv[3]);

}
