#include <string.h>
#include <stdio.h>

int
main (int argc,
      char *argv[])
{
  int i;
  char str1[] = "hello world";
  char str2[] = "hello test";

  printf ("bcmp : %d\n", memcmp(str1, str2, 5));
  printf ("bcmp : %d\n", memcmp(str1, str2, 7));

  memset(str1, 0, 5);
  for (i=0; i<11; i++)
    {
      if (str1[i] == 0)
        printf("%d", i);
      else {
        putchar(str1[i]);
      }
    }
  printf("\n");

  memcpy(str1, str2, 5);
  printf("str1: %s\n", str1);

  return 0;
}
