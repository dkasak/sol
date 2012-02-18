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

#ifndef DBMP_H
#define DBMP_H

#define DEFAULT_WIDTH      640
#define DEFAULT_HEIGHT     480
#define BPP                24
#define BYPP               BPP / CHAR_BIT 

#define BMP_HEADER_SIZE    sizeof (bmp_magic_t) + sizeof (bmp_header_t)
#define DIB_HEADER_SIZE    sizeof (dib_header_t)

typedef struct {
    unsigned char magic[2];
} bmp_magic_t;

typedef struct {
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bmp_offset;
} bmp_header_t;

typedef struct {
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t nplanes;
    uint16_t bpp;
    uint32_t compress_type;
    uint32_t data_size;
    uint32_t hres;
    uint32_t vres;
    uint32_t ncolours;
    uint32_t ncolours_important;
} dib_header_t;

bool write_bmp(const char *data, unsigned int width, unsigned int height, const char *fname);
char *new_image_buffer(unsigned int width, unsigned int height);
void destroy_image_buffer(char *image);

#endif // DBMP_H

