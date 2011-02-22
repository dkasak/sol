#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "dbmp.h"

bool write_bmp(const char *data, unsigned int width, unsigned int height, const char *fname) {
    bmp_magic_t magic;
    bmp_header_t h1;
    dib_header_t h2;

    FILE *bmp;

    /* open file for writing */

    bmp = fopen(fname, "w");

    if (bmp == NULL) {
        return false;  
    }

    /* initialise data structures */

    magic.magic[0] = 'B';
    magic.magic[1] = 'M';

    h1.file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE + (width * height) * BPP;
    h1.reserved1 = 'D';
    h1.reserved2 = 'K';
    h1.bmp_offset = BMP_HEADER_SIZE + DIB_HEADER_SIZE;

    h2.header_size = DIB_HEADER_SIZE;
    h2.width = width;
    h2.height = height;
    h2.nplanes = 1;
    h2.bpp = BPP;
    h2.compress_type = 0;
    h2.data_size = 0;
    h2.hres = width;
    h2.vres = height;
    h2.ncolours = 0;
    h2.ncolours_important = 0;

    /* write BMP / DIB headers */

    fwrite((void *) &magic, sizeof magic, 1, bmp);
    fwrite((void *) &h1, sizeof h1, 1, bmp);
    fwrite((void *) &h2, sizeof h2, 1, bmp);

    int index;
    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            index = j * width + i;
            index *= BYPP;
            fprintf(bmp, "%c", data[index + 2]);
            fprintf(bmp, "%c", data[index + 1]);
            fprintf(bmp, "%c", data[index]);
        }
    }

    fclose(bmp);

    return true;
}

char *new_image_buffer(unsigned int width, unsigned int height) {
    return malloc(height * width * BYPP);
}

void destroy_image_buffer(char *image) {
    free(image);
}

