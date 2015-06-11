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

  if ((echoStringLen = strlen(echoString)) > ECHOMAX)
	  DieWithError("Echo word too long");

  if ((sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	  DieWithError("socket() failed");
  memset (&echoServAddr, 0, sizeof(echoServAddr));
  echoServAddr.sin_family = AF_INET;
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);
  echoServAddr.sin_port = htons(echoServPort);

  if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
	  DieWithError("sendto() sent a different number of types than expected");

  fromSize = sizeof(fromAddr);
  memset(echoBuffer, '\0', ECHOMAX + 1);

  if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *)&fromAddr, &fromSize)) != echoStringLen)
	  DieWithError("recvfron() failed");

  if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
  {
	  fprintf(stderr, "Error: received a packet from unknown source.\n");
	  exit(1);
  }
  echoBuffer[respStringLen]='\0';
  printf("Received: %s(%d)\n", echoBuffer, (int)strlen(echoBuffer));
  close(sock);

  exit(1);
  return 0;
}
