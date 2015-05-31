#include <stdio.h>
#include <string.h>
#include <time.h>

int
main (int argc,
      char *argv[])
{
  int input_day;

  time_t current_time;
  time(&current_time);

  struct tm *local_time;
  local_time =  localtime(&current_time);
  local_time->tm_year += 1900;
  local_time->tm_mon   = 0;
  local_time->tm_mday  = 1;
  local_time->tm_hour  = 0;
  local_time->tm_min   = 0;
  local_time->tm_sec   = 0;
  
  printf("day: ");
  scanf("%d", &input_day);
  local_time->tm_mday += input_day;
  mktime(local_time);

  printf("1/1 + %d: %2d/%2d\n", input_day, local_time->tm_mon + 1, local_time->tm_mday);

  return 0;
}
