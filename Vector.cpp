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

Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D& v) {
    this->x = v.x;
    this->y = v.y;
}

Vector2D
Vector2D::operator+(const Vector2D &v) const {
    double i, j;

    i = this->x + v.x;
    j = this->y + v.y;

    return Vector2D(i, j);
}

Vector2D
Vector2D::operator-(const Vector2D &v) const {
    double i, j;

    i = this->x - v.x;
    j = this->y - v.y;

    return Vector2D(i, j);
}

Vector2D
Vector2D::operator-() const {
    return Vector2D(-this->x, -this->y);
}

Vector2D
Vector2D::operator*(const double r) const {
    double i, j;

    i = this->x * r;
    j = this->y * r;

    return Vector2D(i, j);
}

Vector2D
operator*(const double r, const Vector2D &v) {
    double i, j;

    i = v.x * r;
    j = v.y * r;

    return Vector2D(i, j);
}

Vector2D
Vector2D::operator/(const double r) const {
    double i, j;

    i = this->x / r;
    j = this->y / r;

    return Vector2D(i, j);
}

double
Vector2D::dot(const Vector2D &v) const {
    return this->x * v.x +
           this->y * v.y;
}

Vector2D&
Vector2D::operator+=(const Vector2D &v) {
    this->x += v.x;
    this->y += v.y;

    return *this;
}

Vector2D&
Vector2D::operator*=(const double r) {
    this->x *= r;
    this->y *= r;

    return *this;
}

Vector2D&
Vector2D::operator/=(const double r) {
    this->x /= r;
    this->y /= r;

    return *this;
}

Vector2D&
Vector2D::operator=(const Vector2D &v) {
    this->x = v.x;
    this->y = v.y;

    return *this;
}

double
Vector2D::angle(const Vector2D &v) const {
    double cosine = this->dot(v) / (this->length() * v.length());

    if (cosine > 1.0) {
        cosine = 1.0;
    } else if (cosine < -1.0) {
        cosine = -1.0;
    }

    return acos(cosine);
}

double
Vector2D::length() const {
    return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0));
}

double
Vector2D::length_squared() const {
    return pow(this->x, 2.0) + pow(this->y, 2.0);
}

Vector2D
Vector2D::normalised() const {
    Vector2D tmp = (*this);

    tmp /= tmp.length();

    return tmp;
}

void
Vector2D::normalise() {
    (*this) /= this->length();
}

Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const Vector3D& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

Vector3D
Vector3D::operator+(const Vector3D &v) const {
    double i, j, k;

    i = this->x + v.x;
    j = this->y + v.y;
    k = this->z + v.z;

    return Vector3D(i, j, k);
}

Vector3D
Vector3D::operator-(const Vector3D &v) const {
    double i, j, k;

    i = this->x - v.x;
    j = this->y - v.y;
    k = this->z - v.z;

    return Vector3D(i, j, k);
}

Vector3D
Vector3D::operator-() const {
    return Vector3D(-this->x, -this->y, -this->z);
}

Vector3D
Vector3D::operator*(const double r) const {
    double i, j, k;

    i = this->x * r;
    j = this->y * r;
    k = this->z * r;

    return Vector3D(i, j, k);
}

Vector3D
operator*(const double r, const Vector3D &v) {
    double i, j, k;

    i = v.x * r;
    j = v.y * r;
    k = v.z * r;

    return Vector3D(i, j, k);
}

Vector3D
Vector3D::operator/(const double r) const {
    double i, j, k;

    i = this->x / r;
    j = this->y / r;
    k = this->z / r;

    return Vector3D(i, j, k);
}

double
Vector3D::dot(const Vector3D &v) const {
    return this->x * v.x +
           this->y * v.y +
           this->z * v.z;
}

Vector3D
Vector3D::cross(const Vector3D &v) const {
    double i, j, k;

    i = this->y * v.z - this->z * v.y;
    j = this->z * v.x - this->x * v.z;
    k = this->x * v.y - this->y * v.x;

    return Vector3D(i, j, k);
}

Vector3D&
Vector3D::operator+=(const Vector3D &v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;

    return *this;
}

Vector3D&
Vector3D::operator*=(const double r) {
    this->x *= r;
    this->y *= r;
    this->z *= r;

    return *this;
}

Vector3D&
Vector3D::operator/=(const double r) {
    this->x /= r;
    this->y /= r;
    this->z /= r;

    return *this;
}

Vector3D&
Vector3D::operator=(const Vector3D &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

double
Vector3D::angle(const Vector3D &v) const {
    double cosine = this->dot(v) / (this->length() * v.length());

    if (cosine > 1.0) {
        cosine = 1.0;
    } else if (cosine < -1.0) {
        cosine = -1.0;
    }

    return acos(cosine);
}

double
Vector3D::length() const {
    return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0));
}

double
Vector3D::length_squared() const {
    return pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0);
}

Vector3D
Vector3D::normalised() const {
    Vector3D tmp = (*this);

    tmp /= tmp.length();

    return tmp;
}

void
Vector3D::normalise() {
    (*this) /= this->length();
}

std::ostream&
operator<<(std::ostream& o, const Sol::Vector2D& v) {
    o << v.x;
    o << "i + ";
    o << v.y;
    o << "j";

    return o;
}

std::ostream&
operator<<(std::ostream& o, const Sol::Vector3D& v) {
    o << v.x;
    o << "i + ";
    o << v.y;
    o << "j + ";
    o << v.z;
    o << "k";

    return o;
}

} // namespace Sol

