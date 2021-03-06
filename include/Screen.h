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

#ifndef SOL_SCREEN_H
#define SOL_SCREEN_H

#include "Point.h"

namespace Sol {

class Screen {
private:
    unsigned int hres, vres;
    double pixel_size;

public:
    Screen();
    Screen(unsigned int hres,
           unsigned int vres);

    unsigned int
    get_hres() const;

    void
    set_hres(unsigned int hres);

    unsigned int
    get_vres() const;

    void
    set_vres(unsigned int vres);

    double
    get_pixel_size() const;

    void
    set_pixel_size(double pixel_size);
};

} // namespace Sol

#endif // SOL_SCREEN_H
