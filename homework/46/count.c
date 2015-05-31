#include <stdio.h>
#include <stdlib.h>

typedef struct _dic {
  int total;
  int big;
  int small;
  int vowel;
  int etc;
  int count[26];
} Dic;

int
main (int argc,
      char *argv[])
{

  FILE *fp;
  int i;
  char ch;
  Dic data;

  for (i = 0; i <= 25; i++)
    {
      data.count[i] = 0;
    }

  if ((fp = fopen ("./winter.txt", "r")))
    {
      while(EOF != (ch = fgetc(fp)))
        if ('a' <= ch && ch <= 'z')
          {
            if ('a' == ch || 'e' == ch || 'i' == ch || 'o' == ch || 'u' == ch)
              data.vowel++;

            if (97 <= ch && ch <= 122)
              data.count[ch - 97]++;

            data.total++;
            data.small++;
          }
        else if ('A' <= ch && ch <= 'Z') {
            if ('A' == ch || 'E' == ch || 'I' == ch || 'O' == ch || 'U' == ch)
              data.vowel++;

            if (65 <= ch && ch <= 90)
              data.count[ch - 65]++;

            data.total++;
            data.big++;
        }
        else if ('0' <= ch && ch <= '9') {
            data.total++;
            data.small++;
        }
        else {
          data.total++;
          data.etc++;
        }
    }
  else {
    printf("Open error\n");
    exit(-1);
  }

  printf("total = %d\n", data.total);
  printf("big   = %d\n", data.big);
  printf("small = %d\n", data.small);
  printf("vowel = %d\n", data.vowel);
  printf("etc   = %d\n", data.etc);

  int count = 0;

  for (i=0; i<=25; i++) {
    if (0 <= i && i <= 24) {
      printf("%c: %5d ",(65 + i), data.count[i]);
    }
    else {
      printf("%c: %5d\n",(65 + i), data.count[i]);
    }

    if (count == 4) {
      printf("\n");
      count = 0;
    }
    else count++;
  }
  printf("\n");
  fclose(fp);

  return 0;
}
