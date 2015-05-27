#include <stdio.h>

int
main ()
{
	char buff[30] = "unbuffed";
	printf("hello \n");

	write(1, buff, sizeof buff);
	sleep(5);
	printf("\n");
}
