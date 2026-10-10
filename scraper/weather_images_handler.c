// https://linux.die.net/man/3/libcurl-tutorial
//char *image_name = "dpsri_70km_2025100815350000dBR.dpsri.png";
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

// Would love to put something like "ur mudder" but too identifiable
#define USER_AGENT_STRING "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36"

FILE *file = NULL;

//void get_recent_link(char *ptr);

int download_image(char *url, char *save_location)
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
    curl_global_cleanup();
    return 1;
  }
  printf("Initialised handle\n");

  /*
  char image_name[40];
  get_recent_link(image_name);
  char *url_prefix = "https://www.nea.gov.sg/docs/default-source/rain-area/";
  char *folder_prefix = "images/";
  
  char url[93]; //prefix + image = 53 + 40 = 93
  char file_location[47];
  sprintf(url, "%s%s", url_prefix, image_name);
  sprintf(file_location, "%s%s", folder_prefix, image_name);
  printf("Accessing %s\n", url);
  printf("Saving to %s\n", file_location);


  */
  printf("Opening file\n");
  // set up file to write
  file = fopen(save_location, "w+");

  // Handle options
  curl_easy_setopt(easy_handle, CURLOPT_URL, url);
  // Use the default CURLOPT_WRITEDATA
  curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, NULL);
  curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, file);
  curl_easy_setopt(easy_handle, CURLOPT_USERAGENT, USER_AGENT_STRING);


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

/*
#include <stdlib.h>

// put the ptr to the string here
// ptr must have minimum size of 40
void get_recent_link(char *ptr)
{
    sprintf(ptr, "dpsri_70km_%d%02d%02d%02d%02d0000dBR.dpsri.png",
      date->tm_year + 1900,
      date->tm_mon + 1,
      date->tm_mday,
      date->tm_hour,
      date->tm_min / 5 * 5); 
}

//https://www.nea.gov.sg/docs/default-source/rain-area/ 53 chars
//images/ 7 chars
*/
