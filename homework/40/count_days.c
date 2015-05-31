#include <stdio.h>
#include <string.h>
#include <time.h>

int
main(int argc,
     char *argv[])
{
   int start_year, start_mon, start_day;
   int end_year, end_mon, end_day;
   int diff_day;
   double diff_sec;
   struct tm user_time;
   time_t start_time;
   time_t end_time;

   memset(&user_time, 0, sizeof(user_time));
   printf("start year: ");
   scanf("%d", &start_year);
   printf("start month: ");
   scanf("%d", &start_mon);
   printf("start day: ");
   scanf("%d", &start_day);
   user_time.tm_year   = start_year - 1900;
   user_time.tm_mon    = start_mon - 1;
   user_time.tm_mday   = start_day;

   start_time   = mktime( &user_time);

   memset(&user_time, 0, sizeof(user_time));
   printf("end year: ");
   scanf("%d", &end_year);
   printf("end mon: ");
   scanf("%d", &end_mon);
   printf("end day: ");
   scanf("%d", &end_day);
   user_time.tm_year   = end_year - 1900;
   user_time.tm_mon    = end_mon - 1;
   user_time.tm_mday   = end_day;

   end_time   = mktime( &user_time);

   diff_sec = difftime(end_time, start_time);
   diff_day = diff_sec / (60 * 60 * 24);

   printf("%4d/%2d/%2d ~ %4d/%2d/%2d: %d day(s)\n", start_year, start_mon, start_day, end_year, end_mon, end_day, diff_day);

   return 0;
}

