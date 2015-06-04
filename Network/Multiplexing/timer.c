#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 500000;
	select(0, 0, 0, 0, &timeout);

	return 0;
}
