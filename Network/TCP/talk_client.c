#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024

char *escapechar = "exit\n";

int
main (int argc,
      char *argv[])
{
  char sendline[MAXLINE];
  char *haddr;
  int size, port, len;
  static int s;
  static struct sockaddr_in server_addr;
  static struct sockaddr_in fd_ser;
/*
struct saockaddr_in  {
  sin_family_t   sin_family;
  unist16_t      sin_port;
  struct in_addr sin_addr;
  char           sin_zero[8];
}
*/
  pid_t pid;

  if ( argc < 3 )
    {
      printf("Usage: %s SERVER_ADDRESS TCP_POR\n", argv[0]);
      return -1;
    }
  else {
    haddr = argv[1];
    port  = atoi(argv[2]);
  }

  //PF_INET : IPv4 인터넷 프로토콜
  if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("Client: Can't open stream socket.\n");
      return -1;
    }
  bzero((char *)&server_addr, sizeof(server_addr));

  server_addr.sin_family      = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(haddr);
  // http://forum.falinux.com/zbxe/index.php?document_srl=433968&mid=C_LIB
  // inet_addr() 함수는 숫자와 점으로 이루어진 IP 문자열을 long형의 숫자 IP 주소로 바꾸어 줍니다. struct sockaddr_in 에서 .sin_addr.s_add 값을 long형의 숫자 IP값을 넣어 주어야 하는데 이 때 사용됩니다.
  // haddr의 값은 두번째 인자로 전달되는 192.168.56.101(Bit 입력 IP) 입니다.
  server_addr.sin_port        = htons(port);
  printf("[%d]\n", htons(port));
  // htons is host-to-network short
  // 호스트로부터 빅엔디안인 TCP/IP 네트워크 바이트 순서로u_short 타입의 값을 변환합니다.
  // - 리턴 : TCP/IP  네트워크 바이트 순서로된 값
  // hostshort : 호스트(시스템) 바이트 순서로된 16비트 숫자.

  if ( connect( s, (struct sockaddr *)&server_addr, sizeof(server_addr) ) < 0 )
    {
      printf("Client: can't connect to server.\n");
      return -1;
    }
  len = sizeof (fd_ser);

  if (getpeername(s, (struct sockaddr *)&fd_ser, (socklen_t *)&len) == 0)
    {
      printf("fd_ser IP: %s, Port: %u\n", inet_ntoa(fd_ser.sin_addr), (unsigned)ntohs(fd_ser.sin_port));
    }

  if ((pid = fork()) > 0)
    {
      while ((size = read(0, sendline, MAXLINE)) > 0)
        {
          sendline[size] = '\0';
          if (write(s, sendline, strlen(sendline)) != size)
            {
              printf("client: can't write to server.\n");
              return -1;
            }
          if (strncmp(sendline, escapechar, 4) == 0)
            {
              kill(pid, SIGQUIT);
              break;
            }
        }
    }

  return 0;
}
