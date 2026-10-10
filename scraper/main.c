#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "weather_images_handler.h"

#define LOOKBACK_LIMIT 10

struct image
{
  char image_name[17]; //YYYYMMDDTTTT.png
  char url_name[94];
  int is_present;
};

int main()
{
  int total_cycles = 0;

  time_t *start_time = malloc(sizeof(time_t));
  time_t *loop_time = malloc(sizeof(time_t));
  struct tm *date = malloc(sizeof(struct tm));
  struct image imgs[LOOKBACK_LIMIT];

  // randomisation
  srand(time(NULL));

  char *folder_prefix = "images/";
  char *url_prefix = "https://www.nea.gov.sg/docs/default-source/rain-area/";

  // Directory scanning
  DIR *dir;
  struct dirent *ent;
  
  while(1)
  {
    printf("------------------------------\n");
    printf("Cycle %d\n", total_cycles);
    printf("------------------------------\n");
    time(start_time);
    *start_time -= 20 * 60; // 20 minutes ago, since 10min ago is earliest
    //memcpy(loop_time, start_time, sizeof(time_t));
    loop_time = start_time;

    if ((dir = opendir("./images/")) == NULL)
    {
      printf("File directory ./images/ cannot be found\n");
      return 1;
    }

    for (int i = 0; i < LOOKBACK_LIMIT; i++)
    {
      date = localtime(loop_time);
      sprintf(imgs[i].image_name, "%04d%02d%02d%02d%02d.png",
        date->tm_year + 1900,
        date->tm_mon + 1,
        date->tm_mday,
        date->tm_hour,
        date->tm_min / 5 * 5); 

      sprintf(imgs[i].url_name, "%sdpsri_70km_%d%02d%02d%02d%02d0000dBR.dpsri.png",
        url_prefix,
        date->tm_year + 1900,
        date->tm_mon + 1,
        date->tm_mday,
        date->tm_hour,
        date->tm_min / 5 * 5); 

      *loop_time -= 5 * 60;
      imgs[i].is_present = 0;
    }

    int file_count = 0;
    // check file directory
    printf("Scanning file directory...\n");
    while ((ent = readdir(dir)) != NULL)
    {
      printf("Found %s ", ent->d_name);
      if (strcmp(ent->d_name, ".") == 0
        || strcmp(ent->d_name, "..") == 0
        || strcmp(ent->d_name, "OLD") == 0)
      {
        printf("Not a file. Skipping...\n");
        continue;
      }

      // Images
      // TODO Probably include regex to eliminate other random images
      // or probably not cus im lazy
      int is_recent_image = 0;
      for (int i = 0; i < LOOKBACK_LIMIT; i++)
      {
        if (strcmp(ent->d_name, imgs[i].image_name) == 0)
        {
          imgs[i].is_present = 1;
          printf("Present %d / %d\n", ++file_count, LOOKBACK_LIMIT);
          is_recent_image = 1;
        }
      }

      if (!is_recent_image)
      {
        // some older file, move to OLD folder
        printf("Older file, moving to OLD folder...\n");
        char old_file_location[17 + 9] = "./images/";
        char new_file_location[17 + 13] = "./images/OLD/";
        strcat(old_file_location, ent->d_name);
        strcat(new_file_location, ent->d_name);
        printf("New file location from %s -> %s \n", old_file_location, new_file_location);
        rename(old_file_location, new_file_location);
      }
    }

    printf("%d / %d recent files found. %s\n", file_count, LOOKBACK_LIMIT,
      file_count == LOOKBACK_LIMIT ? "" : "Downloading missing files...");

    // start from the back
    for (int i = LOOKBACK_LIMIT - 1; i >= 0; i--)
    {
      // if not present, download
      if (!imgs[i].is_present)
      {
        char file_location[17 + 9] = "./images/";
        strcat(file_location, imgs[i].image_name);
        printf("Accesssing url: %s\n", imgs[i].url_name);

        download_image(imgs[i].url_name, file_location);

        if (i != 0)
        {
          int random_time_interval = rand() % 30 + 45;
          printf("Sleeping for %d seconds to avoid IP ban\n", random_time_interval);
          sleep(random_time_interval);
        }
      }
    }
    printf("Cycle %d completed\n", ++total_cycles);
    closedir(dir);

    int random_time_interval = rand() % 180 + 300;
    printf("Sleeping for %d seconds to wait for an update\n", random_time_interval);
    sleep(random_time_interval);
  }
  return 0;
}
