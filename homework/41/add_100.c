#include <stdio.h>
#include <string.h>
#include <time.h>

int
main(int argc,
     char *argv[])
{
   int input_year, input_mon, input_day;
   struct tm user_time;

   memset(&user_time, 0, sizeof(user_time));

   printf("year: ");
   scanf("%d", &input_year);
   printf("month: ");
   scanf("%d", &input_mon);
   printf("start day: ");
   scanf("%d", &input_day);

   user_time.tm_year   = input_year - 1900;
   user_time.tm_mon    = input_mon - 1;
   user_time.tm_mday   = input_day;

   user_time.tm_mday += 100;
   mktime(&user_time);

   printf("%4d/%2d/%2d + 100 = %4d/%2d/%2d\n",
          input_year,
          input_mon,
          input_day, 
          user_time.tm_year + 1900,
          user_time.tm_mon + 1,
          user_time.tm_mday
          );

   return 0;
}
