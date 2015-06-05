#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
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
  int server_fd, client_fd;
  int clilen, size, len;
  char sendline[MAXLINE], rbuf[MAXLINE];
  struct sockaddr_in client_addr, server_addr;
  struct sockaddr_in fd_ser, fd_cli;
  pid_t pid;

  if (argc < 2)
    {
      printf("Usage: %s TCP_PORT\n", argv[0]);
      return -1;
    }

  if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("Server: Can't open stream socket\n");
      return -1;
    }
  printf("SOCKET = %d\n", server_fd);

  bzero((char *)&server_addr, sizeof(server_addr));
  bzero((char *)&fd_ser, sizeof(server_addr));
  bzero((char *)&fd_cli, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
      printf("Server: Can't bind local address\n");
      return -1;
    }
  printf("Server started.\nWaiting for client..");

  listen(server_fd, 2);
  clilen = sizeof (client_addr);

  if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&clilen)) != -1)
    {
      printf("Server:  client connected\n");
      printf("Accept Socket = %d\n", client_fd);
      printf("Accept IP:%s, Port: %u\n", inet_ntoa(client_addr.sin_addr), (unsigned)ntohs(client_addr.sin_port));
      len = sizeof(fd_ser);

      if (getpeername(server_fd, (struct sockaddr *)&fd_ser, (socklen_t *)&len) == 0)
        {
          printf("fd_ser IP: %s, Port: %u\n", inet_ntoa(fd_ser.sin_addr), (unsigned)ntohs(fd_ser.sin_port));
        }
      len = sizeof(fd_cli);

      if (getpeername(client_fd, (struct sockaddr *)&fd_cli, (socklen_t *)&len) == 0)
        {
          printf("fd_cli IP:%s, Port:%u\n", inet_ntoa(fd_cli.sin_addr), (unsigned)ntohs(fd_cli.sin_port));
        }
    }
  else {
    printf("Server:failed in accepting.\n");
    return -1;
  }

  if ((pid = fork()) > 0) {
    while ((size = read(0, sendline, MAXLINE)) > 0)
      {
        sendline[size] = '\0';
        if (write(client_fd, sendline, size) != size)
          {
            printf("Server.fail in writing\n");
          }
        if (strncmp(sendline, escapechar, 4) == 0)
          {
            kill(pid, SIGQUIT);
            break;
          }
      }
  }
  else if (pid == 0)
    {
      while (1)
        {
          if ((size = read(client_fd, rbuf, MAXLINE)) > 0)
            {
              rbuf[size] = '\0';

              if (strncmp (rbuf, escapechar, 4) == 0)
                {
                  kill(getppid(), SIGQUIT);
                  break;
                }
              printf("%s", rbuf);
            }
        }
    }

  close(server_fd);
  close(client_fd);

  return 0;
}
