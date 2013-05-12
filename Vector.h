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

class Vector3D {
public:
    double x, y, z;

    Vector3D();
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& v);

    Vector3D
    operator+(const Vector3D& v) const;

    Vector3D
    operator-(const Vector3D& v) const;

    Vector3D
    operator*(const double r) const;

    friend Vector3D
    operator*(const double r, const Vector3D& v);

    Vector3D
    operator/(const double r) const;

    double
    dot(const Vector3D& v) const;

    Vector3D
    cross(const Vector3D& v) const;

    double
    angle(const Vector3D& v) const;

    Vector3D&
    operator+=(const Vector3D& v);

    Vector3D&
    operator*=(const double r);

    Vector3D&
    operator/=(const double r);

    Vector3D&
    operator=(const Vector3D &v);

    void
    normalise();

    Vector3D
    normalised() const;

    double
    length() const;
};

std::ostream&
operator<<(std::ostream& o, const Sol::Vector3D& v);

} // namespace Sol

#endif // SOL_VECTOR_H

