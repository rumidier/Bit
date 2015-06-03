#include <stdio.h>
#include <unistd.h>

int
main (int argc,
      char *argv[])
{
  char name[20];


  gethostname(name, 20);
  printf("name: %s\n", name);

  return 0;
}
