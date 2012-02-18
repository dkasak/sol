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

#include <cmath>
#include <ostream>

#include "Vector.h"

namespace Sol {

Vector::Vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::Vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vector::getX() const {
    return this->x;
}

double Vector::getY() const {
    return this->y;
}

double Vector::getZ() const {
    return this->z;
}

void Vector::setX(double x) {
    this->x = x;
}

void Vector::setY(double y) {
    this->y = y;
}

void Vector::setZ(double Z) {
    this->z = z;
}

Vector Vector::operator+(const Vector &v) const {
    double i, j, k;

    i = this->x + v.x;
    j = this->y + v.y;
    k = this->z + v.z;

    return Vector(i, j, k);
}

Vector Vector::operator*(const double r) const {
    double i, j, k;

    i = this->x * r;
    j = this->y * r;
    k = this->z * r;

    return Vector(i, j, k);
}

Vector Vector::operator/(const double r) const {
    double i, j, k;

    i = this->x / r;
    j = this->y / r;
    k = this->z / r;

    return Vector(i, j, k);
}

double Vector::dot(const Vector &v) const {
    return this->x * v.x +
           this->y * v.y +
           this->z * v.z;
}

Vector Vector::cross(const Vector &v) const {
    double i, j, k;

    i = this->y * v.z - this->z * v.y;
    j = this->z * v.x - this->x * v.z;
    k = this->x * v.y - this->y * v.x;

    return Vector(i, j, k);
}

Vector& Vector::operator+=(const Vector &v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;

    return *this;
}

Vector& Vector::operator*=(const double r) {
    this->x *= r;
    this->y *= r;
    this->z *= r;

    return *this;
}

Vector& Vector::operator/=(const double r) {
    this->x /= r;
    this->y /= r;
    this->z /= r;

    return *this;
}

Vector& Vector::operator=(const Vector &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

double Vector::angle(const Vector &v) const {
    double cosine = this->dot(v) / (this->length() * v.length());

    if (cosine > 1.0) {
        cosine = 1.0;
    } else if (cosine < -1.0) {
        cosine = -1.0;
    }

    return acos(cosine);
}

double Vector::length() const {
    return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0));
}

Vector Vector::normalised() const {
    Vector tmp = (*this);

    tmp /= tmp.length();

    return tmp;
}

void Vector::normalise() {
    (*this) /= this->length();
}

} // namespace Sol

std::ostream& operator<<(std::ostream& o, const Sol::Vector &v) {
    o << v.getX();
    o << "i + ";
    o << v.getY();
    o << "j + ";
    o << v.getZ();
    o << "k";

    return o;
}

