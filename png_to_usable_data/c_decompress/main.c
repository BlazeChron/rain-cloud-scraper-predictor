#include <stdio.h>
#include <stdlib.h>

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
        if (argc < 2) {
                printf("Usage: [filepath]\n");
                return -1;
        }

        char *filename = argv[1];
        unsigned char *bytes = NULL;
        unsigned int width;
        unsigned int height;
        decode_png_file(filename, &bytes, &width, &height);
        printf("width: %u height: %u\n", width, height);

        FILE *outfile = fopen("thingy.txt", "w");
        char pixel[18];
        //for (int i = 0; i < height; i++) {
        //        for (int j = 0; j < width * 4; j+= 4) {
        //                int idx = i * width * 4 + j;
        //                sprintf(pixel, "[%hhu,%hhu,%hhu,%hhu]", 
        //                        bytes[idx],
        //                        bytes[idx + 1],
        //                        bytes[idx + 2],
        //                        bytes[idx + 3]);
        //                fputs(pixel, outfile);
        //        }
        //        fputs("\n", outfile);
        //}

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

        fclose(outfile);

        free(bytes);
}
