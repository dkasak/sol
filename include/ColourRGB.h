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

#ifndef SOL_COLOURRGB_H
#define SOL_COLOURRGB_H

#include <iostream>

namespace Sol {

class ColourRGB {

public:
    double red, green, blue;

    ColourRGB(void);
    ColourRGB(double c);
    ColourRGB(double r, double g, double b);
    ColourRGB(const ColourRGB& c);

    ColourRGB
    operator+(const ColourRGB& c) const;

    ColourRGB
    operator*(const double r) const;

    ColourRGB
    operator*(const ColourRGB& c) const;

    ColourRGB
    operator/(const double r) const;

    ColourRGB&
    operator=(const ColourRGB& rhs);

    ColourRGB&
    operator+=(const ColourRGB& c);

    ColourRGB&
    operator*=(const double r);

    ColourRGB&
    operator/=(const double r);

    bool
    operator==(const ColourRGB& c) const;

    ColourRGB
    pow(double p) const;

    double
    average() const;

    void
    maximize();

    void
    clamp();

    ColourRGB
    clamped();
};

std::ostream&
operator<<(std::ostream& o, ColourRGB c);

inline ColourRGB
ColourRGB::operator+(const ColourRGB& c) const {
    return ColourRGB(this->red + c.red,
                     this->green + c.green,
                     this->blue + c.blue);
}

inline ColourRGB
ColourRGB::operator*(const double r) const {
    return ColourRGB(this->red * r,
                     this->green * r,
                     this->blue * r);
}

inline ColourRGB
ColourRGB::operator*(const ColourRGB& c) const {
    return ColourRGB(this->red * c.red,
                     this->green * c.green,
                     this->blue * c.blue);
}

inline ColourRGB
ColourRGB::operator/(const double r) const {
    return ColourRGB(this->red / r,
                     this->green / r,
                     this->blue / r);
}

inline ColourRGB&
ColourRGB::operator+=(const ColourRGB& c) {
    this->red += c.red;
    this->green += c.green;
    this->blue += c.blue;

    return *this;
}

inline ColourRGB&
ColourRGB::operator*=(const double r) {
    this->red *= r;
    this->green *= r;
    this->blue *= r;

    return *this;
}

inline ColourRGB&
ColourRGB::operator/=(const double r) {
    this->red /= r;
    this->green /= r;
    this->blue /= r;

    return *this;
}

inline bool
ColourRGB::operator==(const ColourRGB& c) const {
    return this->red == c.red &&
           this->green == c.green &&
           this->blue == c.blue;
}

inline double
ColourRGB::average(void) const {
    return (this->red +
            this->green +
            this->blue) / 3.0;
}

inline ColourRGB
operator*(const double r, const ColourRGB& c) {
    return ColourRGB(c.red * r,
                     c.green * r,
                     c.blue * r);
}

} // namespace Sol

#endif // SOL_COLOURRGB_H

