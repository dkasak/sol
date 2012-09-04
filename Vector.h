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

#ifndef SOL_VECTOR_H
#define SOL_VECTOR_H

#include <iostream>

namespace Sol {

class Vector {
public:
    double x, y, z;

    Vector();
    Vector(double x, double y, double z);

    Vector
    operator+(const Vector& v) const;

    Vector
    operator-(const Vector& v) const;

    Vector
    operator*(const double r) const;

    friend Vector
    operator*(const double r, const Vector& v);

    Vector
    operator/(const double r) const;

    double
    dot(const Vector& v) const;

    Vector
    cross(const Vector& v) const;

    double
    angle(const Vector& v) const;

    Vector&
    operator+=(const Vector& v);

    Vector&
    operator*=(const double r);

    Vector&
    operator/=(const double r);

    Vector&
    operator=(const Vector &v);

    void
    normalise();

    Vector
    normalised() const;

    double
    length() const;
};

std::ostream&
operator<<(std::ostream& o, const Sol::Vector& v);

} // namespace Sol

#endif // SOL_VECTOR_H

