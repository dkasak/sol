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

#include "Shape.h"

namespace Sol {

Shape::Shape() {}

Shape::Shape(double x, double y, double z) : origin(x, y, z) {}

Shape::Shape(Point p) : origin(p.x, p.y, p.x) {}

Shape::~Shape() {}

void
Shape::move(double x, double y, double z) {
    this->origin.x = x;
    this->origin.y = y;
    this->origin.z = z;
}

void
Shape::move(Point p) {
    this->origin.x = p.x;
    this->origin.y = p.y;
    this->origin.z = p.z;
}

void
Shape::setMaterial(const Material* m) {
    this->material = m;
}

const Material*
Shape::getMaterial() const {
    return this->material;
}

void
Shape::setOrigin(const Point& m) {
    this->origin = m;
}

Point
Shape::getOrigin() const {
    return this->origin;
}

} // namespace Sol

