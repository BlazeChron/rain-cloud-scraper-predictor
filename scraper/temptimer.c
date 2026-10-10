#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  time_t *current_time = malloc(sizeof(time_t));
  struct tm *date = malloc(sizeof(struct tm));
  while (1)
  {
    time(current_time);
    localtime_r(current_time, date);

    printf("%02d:%02d:%02d\n",
      date->tm_hour,
      date->tm_min,
      date->tm_sec); 

    sleep(300);
  }
}

