/**
 * Copyright 2011, 2012 Denis Kasak <dkasak[at]termina.org.uk>
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


unsigned char*
read_bmp(const char* fname, bmp_meta_t* meta) {
    bmp_magic_t magic;
    bmp_header_t h1;
    dib_header_t h2;

    /* open file for reading */

    FILE *bmp = fopen(fname, "r");

    if (bmp == NULL) {
        return NULL;  
    }

    /* read headers/magic */
    fread(&magic, sizeof magic, 1, bmp);
    fread(&h1, sizeof h1, 1, bmp);
    fread(&h2, sizeof h2, 1, bmp);

    /* check if it's a BMP file (according to the magic) */
    if (magic.magic[0] != 'B' || magic.magic[1] != 'M') {
        return NULL;
    }

    /* allocate memory */
    size_t image_size = h2.width * h2.height * h2.bpp / CHAR_BIT;
    unsigned char* image = malloc(image_size);

    if (image == NULL) {
        return NULL;
    }

    unsigned char* ptr = image;

    /* read image */
    for (size_t row = 0; row < h2.height; ++row) {
        if (!fread((void *) ptr, h2.width * BYPP, 1, bmp)) {
            return NULL;
        }

        /* remove padding, if any */
        size_t tail = h2.width * BYPP % 4;
        size_t pad_len = tail ? 4-tail : 0;

        /* discard padding */
        while (pad_len--) {
            (void) fgetc(bmp);
        }

        ptr += h2.width * BYPP;
    }

    meta->width = h2.width;
    meta->height = h2.height;
    meta->bpp = h2.bpp;

    fclose(bmp);

    return image;
}

bool
write_bmp(const unsigned char* data, size_t width, size_t height, const char* fname) {
    bmp_magic_t magic;
    bmp_header_t h1;
    dib_header_t h2;

    /* open file for writing */
    FILE *bmp = fopen(fname, "w");

    if (bmp == NULL) {
        return false;  
    }

    /* initialise data structures */
    magic.magic[0] = 'B';
    magic.magic[1] = 'M';

    /* calculate padding so each row is alligned to 4 bytes */
    size_t tail = width * BYPP % 4;
    size_t pad_len = tail ? 4-tail : 0;

    h1.file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE + (width * height) * BYPP + pad_len * height;
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

    /* write image */
    unsigned char padding[] = "000";
    for (size_t row = 0; row < height; ++row) {
        if (!fwrite((void *) data, width * BYPP, 1, bmp)) {
            return NULL;
        }

        if (pad_len && !fwrite((void *) padding, pad_len, 1, bmp)) {
            return NULL;
        }

        data += width * BYPP;
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
 
