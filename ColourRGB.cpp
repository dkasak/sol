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

#include "ColourRGB.h"

#include <cmath>    
#include <iostream>
#include <algorithm>

using std::min;

namespace Sol {

ColourRGB::ColourRGB() 
    : red(0.0),
      green(0.0),
      blue(0.0) 
    {}

ColourRGB::ColourRGB(double c) 
    : red(c),
      green(c),
      blue(c)
    {}

ColourRGB::ColourRGB(double r, double g, double b) 
    : red(r),
      green(g),
      blue(b)
    {}

ColourRGB::ColourRGB(const ColourRGB& c)
    : red(c.red),
      green(c.green),
      blue(c.blue) 
    {} 				 

ColourRGB& 											
ColourRGB::operator=(const ColourRGB& other) {
    if (this == &other)
        return *this;

    this->red = other.red;
    this->green = other.green;
    this->blue = other.blue;

    return *this;
}

ColourRGB
ColourRGB::pow(double e) const {
    const double pr = ::pow(this->red, e);
    const double pg = ::pow(this->green, e);
    const double pb = ::pow(this->blue, e);

    return ColourRGB(pr, pg, pb);
}

void
ColourRGB::clamp() {
    this->red = min(this->red, 1.0);
    this->green = min(this->green, 1.0);
    this->blue = min(this->blue, 1.0);
}

ColourRGB
ColourRGB::clamped() {
    double r, g, b;

    r = min(this->red, 1.0);
    g = min(this->green, 1.0);
    b = min(this->blue, 1.0);

    return ColourRGB(r, g, b);
}

void
ColourRGB::maximize() {
    double max = this->red;
    if (this->green > max) max = this->green;
    if (this->blue > max) max = this->blue;

    double ratio = 1.0 / max;
    this->red *= ratio;
    this->green *= ratio;
    this->blue *= ratio;
}

std::ostream&
operator<<(std::ostream& o, ColourRGB c) {
    std::cout << "Colour(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return o;
}

} // namespace Sol

