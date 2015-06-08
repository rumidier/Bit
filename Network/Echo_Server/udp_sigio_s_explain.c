#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>

#define ECHOMAX 255

void DieWithError (char *errorMessage);
void UseldleTime();
void SIGIOHandler(int signalType);

int sock;

int
main (int argc,
      char *argv[])
{

  struct sockaddr_in echoServAddr;
  unsigned short echoServPort;
  struct sigaction handler;

  if (argc != 2)
    {
      fprintf(stderr, "Usage: %s<SERVER PORT>\n", argv[0]);
      exit(0);
    }
  echoServPort = atoi(argv[1]);
  //10진 정수 문자열을 정수로 변환합니다.

  if ((sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    DieWithError("socket() failed");

  //IPv4의 인터넷 프로토콜 UDP socket 을 엽니다.

  memset (&echoServAddr, 0, sizeof(echoServAddr));
  // sockaddr_in 정보를 리셋합니다.

  echoServAddr.sin_family = AF_INET;
  //주소체계에 저장하는 AF_INET
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //주소를 지정해 주는것으로 `inet_addr("내 시스템의 IP")`로도 지정할 수 있지만 프로그램이 실행되는 시스템마다
  //IP가 다르므로 고정 IP로 하지않고 `htonl(INADDR_ANY)`로 사용합니다.
  echoServAddr.sin_port=htons(echoServPort);
  //host 시스템에서 network로 short형 데이터를 보낼 때 바이트 오더를 바꾸어 주는 함수
  //sockaddr_in 에 서버 정보를 저장합니다.

  if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    DieWithError("bind() faild");
  handler.sa_handler = SIGIOHandler;

  if (sigfillset(&handler.sa_mask) < 0)
    DieWithError("sigfillset() failed");

  handler.sa_flags = 0;

  if (sigaction(SIGIO, &handler, 0) < 0)
    DieWithError("sigaction() failed for SIGIO");

  if (fcntl(sock, F_SETOWN, getpid ()) < 0)
    DieWithError("Unable to set process owner to us");

  if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
    DieWithError("Unable to put client sock into nonblocking/async mode");

  for (;;)
    UseldleTime();

  return 0;
}

void UseldleTime()
{
  printf(".\n");
  sleep(3);
}

void SIGIOHandler (int signalType)
{
  struct sockaddr_in echoClntAddr;
  unsigned int clntLen;
  int recvMsgSize;
  char echoBuffer[ECHOMAX];

  do
    {
      clntLen = sizeof (echoClntAddr);
      if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
        {
          if (errno != EWOULDBLOCK)
            DieWithError("recvfrom() failed");
        }
      else 
        {
          printf("Handler client %s\n", inet_ntoa(echoClntAddr.sin_addr));
          echoBuffer[recvMsgSize] = '\0';
          printf("buf = %s\n", echoBuffer);

          if (sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *)&echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
            DieWithError("sendto() failed");
        }
    }
  while (recvMsgSize >= 0);
}

void DieWithError (char *errorMessage)
{
  perror(errorMessage);
  exit(0);
}
