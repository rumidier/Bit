#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define PORT 9989

int CreateSvrSock()
{
  int nSvrSock = 0;
  int nRet = 0;
  auto int one = 1;
  struct sockaddr_in svrAddr;

  nSvrSock = socket(AF_INET, SOCK_STREAM, 0);
  if (nSvrSock < 0) {
    printf("Socket Create Error : %s\n", strerror(errno));
    return -1;
  }

  if (setsockopt(nSvrSock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one) == -1)
    {
      printf("Error setting SO_REUSEADDR for socket: %s", strerror (errno));
      return -1;
    }

  memset (&svrAddr, 0, sizeof(svrAddr));
  svrAddr.sin_family = AF_INET;
  svrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  svrAddr.sin_port =  htons(PORT);

  nRet = bind(nSvrSock, (struct sockaddr *) &svrAddr, sizeof(svrAddr));
  if (nRet < 0)
    {
      printf("bind error : %s\n", strerror(errno));
      return -1;
    }

  nRet = listen(nSvrSock, 20);
  if (nRet < 0)
    {
      printf("Listen Error : %s\n", strerror(errno));
      return -1;
    }

  return nSvrSock;
}

void Process (int nSvrSockFD)
{
  int nCliSockFD = 0;
  char szBuf[1024];
  struct sockaddr_in addr;
  socklen_t nAddr = sizeof (struct sockaddr_in);

  printf("start pre fork[%d]\n", (int)getpid());
  while(1)
    {
      nCliSockFD = accept(nSvrSockFD, (struct sockaddr *) &addr, &nAddr);
      printf("[%d] accept client [%d]\n", (int)getpid(), nCliSockFD);
      memset(szBuf, 0, sizeof(szBuf));
      recv(nCliSockFD, szBuf, 1024, 0);
      send(nCliSockFD, szBuf, 1024, 0);
      close(nCliSockFD);
    }
}

void PreFork (int nSvrSockFD)
{
  pid_t pid = 0;

  if ( (pid = fork()) > 0)
    return;
  Process(nSvrSockFD);
}

int
main (int argc,
      char *argv[])
{
  int i = 0, n = 4, nSvrSockFD = CreateSvrSock();
  printf("start server %d\n", PORT);

  for (i = 0; i < n; i++)
    PreFork(nSvrSockFD);

  getchar();

  return 0;
}
