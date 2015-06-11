#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 512
#define MAX_SOCK 64

char *escapechar = "exit";
int maxfdp1;
int num_chat = 0;
int client_s[MAX_SOCK];

void removeClient(int i)
{
  close (client_s[i]);
  if (i != num_chat -1)
    client_s[i] = client_s[num_chat - 1];
  num_chat--;
  printf("채팅 참가자 1명 탈퇴. 현재 참가자 수 = %d\n", num_chat);
}

int getmax(int k)
{
  int max = k;
  int r;

  for (r=0; r<num_chat; r++)
    {
      if (client_s[r] > max)
        max = client_s[r];
    }

  return max;
}

int
main (int argc,
      char *argv[])
{
  char rline[MAXLINE], my_msg[MAXLINE];
  char *start = "Connected to chat_server \n";
  int i, j, n;
  int s, client_fd, clilen;

  fd_set read_fds;
  struct sockaddr_in client_addr, server_addr;

  if (argc != 2)
    {
      printf("사용법: %s port\n", argv[0]);
      exit(0);
    }

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("Server: Can't open stream socket.");
      exit(0);
    }
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  if (bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
      printf("Server: Can't bind local address.\n");
      exit(0);
    }
  listen(s, 5);

  maxfdp1 = s + 1;

  while (1)
    {
      FD_ZERO(&read_fds);
      FD_SET(s, &read_fds);
      for(i=0; i<num_chat; i++)
        FD_SET(client_s[i], &read_fds);
      maxfdp1 = getmax(s) + 1;

      if (select(maxfdp1, &read_fds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0)
        {
          printf("select error <= 0\n");
          exit(0);
        }

      if(FD_ISSET(s, &read_fds))
        {
          clilen = sizeof(client_addr);
          client_fd = accept(s, (struct sockaddr *)&client_addr, (socklen_t *)&clilen);

          if(client_fd == -1)
            {
              printf("accept error\n");
              exit(0);
            }
          client_s[num_chat] = client_fd;
          num_chat++;
          send(client_fd, start, strlen(start), 0);
          printf("%d번째 사용자 추가.\n", num_chat);
        }
      for(i=0; i<num_chat; i++)
        {
          memset(rline,'\0', MAXLINE);
          if (FD_ISSET(client_s[i], &read_fds))
            {
              if ((n=recv(client_s[i], rline, MAXLINE, 0)) <= 0)
                {
                  removeClient(i);
                  continue;
                }
              if (strstr(rline, escapechar) != NULL)
                {
                  removeClient(i);
                  continue;
                }
              rline[n] = '\0';
              for (j=0; j < num_chat; j++)
                send(client_s[j], rline, n, 0);
              printf("%s\n", rline);
            }
        }
    }
}
