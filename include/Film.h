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

#ifndef SOL_FILM_H
#define SOL_FILM_H

#include <vector>
#include <cstdlib>

#include "ColourRGB.h"

namespace Sol {

class Film {
private:
    std::vector<ColourRGB> storage;

public:
    Film();

    size_t
    size() const;

    void
    commit(ColourRGB pixel);

    unsigned char*
    BGR24() const;
};

} // namespace Sol

#endif // SOL_FILM_H

