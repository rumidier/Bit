#include <sys/types.h>
#include <sys/stat.h>

int
main (int argc,
		char *argv[])
{
	struct stat stabuf;

	if (lchown("aaa", 1001, 1001) < 0 ) {
		perror("chmod error for aaa");
		exit(-1);
	}
}
