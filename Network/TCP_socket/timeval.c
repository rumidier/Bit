#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
  int nfds, ret;
  char buff[1024];
  struct timeval timeout;
  fd_set readfds;

  while(1)
    {
      timeout.tv_sec = 2;
      timeout.tv_usec = 500000;
      FD_ZERO(&readfds);
      FD_SET(0, &readfds);
      nfds = select(1, &readfds, 0, 0, &timeout);

      if (nfds == 0)
        {
          printf("time out error\n");
        }
      if (FD_ISSET(0, &readfds))
        {
          ret = read (0, buff, sizeof buff);
          buff[ret - 1] = 0;
          printf("[%s]\n", buff);
          if (strcmp(buff, "exit") == 0)
            break;
        }
    }

  return 0;
}
