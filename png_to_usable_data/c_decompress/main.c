#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "decoder.h"

// Intensity of rain
int rain_intensity_arr[] = {   0, 255, 255,
                               0, 239, 239,
                               0, 209, 213,
                               0, 186, 191,
                               0, 151, 154,
                               0, 131, 125,
                               0, 128,  69,
                               0, 137,  56,
                               0, 162,  53,
                               0, 183,  41,
                               0, 202,  17,
                               0, 218,  13,
                               0, 245,   7,
                               0, 255,   0,
                              67, 255,  65,
                              72, 255,  70,
                             255, 255,  59,
                             255, 255,   0,
                             255, 240,   0,
                             255, 220,   0,
                             255, 198,   0,
                             255, 178,   0,
                             255, 165,   0,
                             255, 138,   0,
                             255, 114,   0,
                             255,  73,   0,
                             255,  31,   0,
                             229,   0,   0,
                             193,   0,   0,
                             182,   0, 106,
                             210,   0, 165,
                             212,   0, 170,
                             255,   0, 255};

int convert_image(char *filename, char *src_filepath);

int get_rain_intensity(int r, int g, int b, int a)
{
        if (a == 0) {
                return 0;
        }
        for (int i = 0; i < 33; i++) {
                int idx = i * 3;
                if (rain_intensity_arr[idx] == r
                    && rain_intensity_arr[idx + 1] == g
                    && rain_intensity_arr[idx + 2] == b) {
                        return i + 1;
                }
        }

        printf("Error, illegal color???\n");
        return -1;
}

int main(int argc, char *argv[])
{
        DIR *dir;
        struct dirent *ent;
        char filepath_prefix[] = "../../scraper/images/OLD/";
        // Loop through all images in directory
        if ((dir = opendir(filepath_prefix)) == NULL)
        {
                printf("File directory %s cannot be found\n", filepath_prefix);
                return -1;
        }

        printf("Scanning file directory %s\n", filepath_prefix);
        while ((ent = readdir(dir)) != NULL) {
                if (strcmp(ent->d_name, ".") == 0
                  || strcmp(ent->d_name, "..") == 0
                  || strcmp(ent->d_name, "OLD") == 0)
                {
                        printf("Not a file. Skipping...\n");
                        continue;
                }
                char source_file_path[255];
                sprintf(source_file_path, "%s%s", filepath_prefix, ent->d_name);
                convert_image(ent->d_name, source_file_path);
        }

        return 0;
}

int convert_image(char *filename, char *src_filepath)
{
        unsigned char *bytes = NULL;
        unsigned int width;
        unsigned int height;
        int result = decode_png_file(src_filepath, &bytes, &width, &height);
        if (result == -1) {
                // Invalid png
                return -1;
        }

        // converting namestring from .png to .dat to the correct folder
        char full_path_name[24] = "./data/";
        strcat(full_path_name, filename);
        full_path_name[20] = 'd';
        full_path_name[21] = 'a';
        full_path_name[22] = 't';
        printf("full_path_name: %s\n", full_path_name);
        printf("src_filepath: %s\n", src_filepath);
        FILE *outfile = fopen(full_path_name, "w");
        char pixel[18];

        for (int i = 0; i < height; i++) {
                for (int j = 0; j < width * 4; j+= 4) {
                        int idx = i * width * 4 + j;
                        sprintf(pixel, "%02d,", 
                                get_rain_intensity(bytes[idx],
                                                   bytes[idx + 1],
                                                   bytes[idx + 2],
                                                   bytes[idx + 3]));
                        fputs(pixel, outfile);
                }
                fputs("\n", outfile);
        }

        //fclose(outfile);

        free(bytes);

        return 0;
}
