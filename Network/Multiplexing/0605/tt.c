#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
  int nfds, ret;
  int fd;
  fd_set readfds;
  char buff[1024];

  fd = open("myfifo", O_RDWR);
  while(1)
    {
      FD_ZERO(&readfds);
      FD_SET(0, &readfds);
      FD_SET(fd, &readfds);

      select (fd+1, &readfds, 0, 0, 0);

      if(FD_ISSET(0, &readfds))
        {
          ret = read(0, buff, sizeof buff);
          if (ret > 0)
            {
              buff[ret - 1] = 0;
              printf("keyboard: %s\n", buff);
            }
        }

      if (FD_ISSET(fd, &readfds))
        {
          ret = read(fd, buff, sizeof buff);
          if (ret > 0)
            {
              buff[ret - 1] = 0;
              printf("myfifo: %s\n", buff);
            }
        }
    }

  return 0;
}
