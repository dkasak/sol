/**
 * Copyright 2011, 2012 Denis Kasak <denis.kasak@gmail.com>
 * 
 * This file is part of Sol.
 * 
 * Sol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Sol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Sol. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "dbmp.h"

bool
write_bmp(const unsigned char* data, size_t width, size_t height, const char* fname) {
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

    h1.file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE + (width * height) * BYPP;
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

    size_t index;
    for (size_t j = height-1; j != (size_t) -1; --j) {
        for (size_t i = 0; i < width; ++i) {
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

unsigned char* new_image_buffer(size_t width, size_t height) {
    return malloc(height * width * BYPP);
}

void destroy_image_buffer(unsigned char* image) {
    free(image);
}
 
