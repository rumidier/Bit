#include <poll.h>

int
main (int argc,
      char *argv[])
{
	poll(0, 0, 3000);

	return 0;
}
