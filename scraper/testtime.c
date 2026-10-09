#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void get_recent_links()
{
  time_t *current_time = malloc(sizeof(time_t));
  struct tm *date = malloc(sizeof(struct tm));
  time(current_time);
  *current_time -= 10 * 60; // 10 minutes ago
  localtime_r(current_time, date);
  printf("Day: %d\n", date->tm_mday);
  printf("Month: %d\n", date->tm_mon + 1);
  printf("Year: %d\n", date->tm_year + 1900);
  printf("Hour: %d\n", date->tm_hour);
  printf("Min: %d\n", date->tm_min / 5 * 5); // lazy way to floor to nearest 5 
  printf("Second: %d\n", date->tm_sec);

  char *image_name =  "dpsri_70km_2025100815350000dBR.dpsri.png";
  char edited_name[100] = "dpsri_70km_";
  sprintf(edited_name, "dpsri_70km_%d%02d%02d%02d%02d0000dBR.dpsri.png",
    date->tm_year + 1900,
    date->tm_mon + 1,
    date->tm_mday,
    date->tm_hour,
    date->tm_min / 5 * 5); 
  printf(" Img name:%s\n", image_name);
  printf("Edit name:%s\n", edited_name);
}

int main()
{
  get_recent_links();
}
