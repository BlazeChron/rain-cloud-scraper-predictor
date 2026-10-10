#include <stdio.h>
#include <dirent.h>

int main()
{
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir("./images/")) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      printf("%s\n", ent->d_name);
    }
    closedir(dir);
  } else {
    printf("failure\n");
  }
  return 0;
}
