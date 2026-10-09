// https://linux.die.net/man/3/libcurl-tutorial
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>


FILE *file = NULL;

void get_recent_link(char *ptr);

int main()
{
  // Global prep, called once before program start
  curl_global_init(CURL_GLOBAL_ALL);
  printf("Initialised libcurl\n");
  
  // Handle set up
  CURL *easy_handle;
  easy_handle = curl_easy_init();
  if (easy_handle == NULL)
  {
    printf("Error: easy_handle not initialised\n");
    curl_global_cleanup(); //TODO There's no way I'm writing this for each error?
    return 1;
  }
  printf("Initialised handle\n");

  //char *image_name = "dpsri_70km_2025100815350000dBR.dpsri.png";
  char image_name[100];
  get_recent_link(image_name);
  char *url_prefix = "https://www.nea.gov.sg/docs/default-source/rain-area/";
  char *folder_prefix = "images/";
  
  char url[100];
  char file_location[100];
  strcpy(url, url_prefix);
  strcat(url, image_name);
  strcpy(file_location, folder_prefix);
  strcat(file_location, image_name);
  printf("Accessing %s\n", url);
  printf("Saving to %s\n", file_location);

  // Would love to put something like "ur mudder" but that's too identifiable or something
  char *user_agent_string = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36";

  printf("opening file\n");
  // set up file to write
  file = fopen(file_location, "w+");
  //file = fopen("yuuka.png", "w+");

  // Handle options
  curl_easy_setopt(easy_handle, CURLOPT_URL, url);
  // Use the default CURLOPT_WRITEDATA
  curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, NULL);
  curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, file);
  curl_easy_setopt(easy_handle, CURLOPT_USERAGENT, user_agent_string);


  // Execute
  CURLcode execute_curl_code = curl_easy_perform(easy_handle);
  if (execute_curl_code == 0)
  {
    printf("Curl successful\n");
  } else {
    printf("Curl unsuccessful\n");
  }

  // Cleanup operations
  fclose(file);
  curl_easy_cleanup(easy_handle);
  curl_global_cleanup();
  
  printf("Finished cleanup, exiting...\n");
  return 0;
}

#include <stdlib.h>
#include <time.h>

// put the ptr to the string here
void get_recent_link(char *ptr)
{
  time_t *current_time = malloc(sizeof(time_t));
  struct tm *date = malloc(sizeof(struct tm));
  time(current_time);
  *current_time -= 20 * 60; // 20 minutes ago, since 10min ago is earliest
  localtime_r(current_time, date);

  char edited_name[100] = "dpsri_70km_";
  sprintf(edited_name, "dpsri_70km_%d%02d%02d%02d%02d0000dBR.dpsri.png",
    date->tm_year + 1900,
    date->tm_mon + 1,
    date->tm_mday,
    date->tm_hour,
    date->tm_min / 5 * 5); 
  strcpy(ptr, edited_name);
}
