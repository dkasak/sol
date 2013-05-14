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

#include "Screen.h"

namespace Sol {

Screen::Screen() :
    hres(0),
    vres(0),
    pixel_size(1.0)
{}

Screen::Screen(unsigned int x, unsigned int y) :
    hres(x),
    vres(y),
    pixel_size(1.0)
{}

unsigned int
Screen::get_hres() const {
    return this->hres;
}

void
Screen::set_hres(unsigned int hres) {
    this->hres = hres;
}

unsigned int
Screen::get_vres() const {
    return this->vres;
}

void
Screen::set_vres(unsigned int vres) {
    this->vres = vres;
}

double
Screen::get_pixel_size() const {
    return this->pixel_size;
}

void
Screen::set_pixel_size(double pixel_size) {
    this->pixel_size = pixel_size;
}

} // namespace Sol
