/**
 * Copyright 2011-2015 Denis Kasak <dkasak[at]termina.org.uk>
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

#include "Film.h"

namespace Sol {

Film::Film() {}

void
Film::commit(ColourRGB pixel) {
   this->storage.push_back(pixel);
}

size_t
Film::size() const {
    return this->storage.size();
}

unsigned char*
Film::BGR24() const {
    unsigned char* data = new unsigned char[this->storage.size() * 3];

    for (size_t i = 0; i < this->storage.size(); ++i) {
        data[3*i]     = this->storage[i].blue * 255;
        data[3*i + 1] = this->storage[i].green * 255;
        data[3*i + 2] = this->storage[i].red * 255;
    }

    return data;
}

} // namespace Sol
