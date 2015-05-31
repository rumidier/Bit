#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

void
reverse_change (char *str)
{
  int i;
  int str_len = strlen(str);

  puts("<after reverse..>");
  printf("Output string: ");

  for (i=(str_len - 1); i>=0; i--) {
    //printf("[%c]", str[i]); //DEBUG
    printf("%c", str[i]);
  }
  puts("");

}

int
main (int argc,
      char *argv[])
{
  char buf[BUF_SIZE];
  printf("input string: ");
  scanf("%s", buf);

  reverse_change(buf);

  return 0;
}
