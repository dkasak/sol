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

#include <time.h>
#include <math.h>
#include "dbmp.h"

int
main(void) {

    srand(time(NULL));

    char *img = new_image_buffer(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    char colour;
    int index;
    for (int j = 0; j < DEFAULT_HEIGHT; ++j) {
        for (int i = 0; i < DEFAULT_WIDTH; ++i) {
            colour = 127 - 127 * cos(0.1 * sqrt(i * i + j * j));
            index = j * DEFAULT_WIDTH + i;
            index *= BYPP;
            img[index] = colour;
            img[index + 1] = colour;
            img[index + 2] = colour;
        }
    }

    write_bmp(img, DEFAULT_WIDTH, DEFAULT_HEIGHT, "test.bmp");
    destroy_image_buffer(img);

    return 0;
}

