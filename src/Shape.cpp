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

#include "Shape.h"

namespace Sol {

Shape::Shape()
    : material(nullptr)
{}

Shape::Shape(Point3D p)
    : origin(p.x, p.y, p.x),
      material(nullptr)
{}

Shape::~Shape() {
    if (this->material) {
        delete this->material;
        this->material = nullptr;
    }
}

void
Shape::set_material(Material* m) {
    this->material = m;
}

Material*
Shape::get_material() const {
    return this->material;
}

void
Shape::set_origin(const Point3D& m) {
    this->origin = m;
}

Point3D
Shape::get_origin() const {
    return this->origin;
}

} // namespace Sol

