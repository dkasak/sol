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

#include "Ray.h"

namespace Sol {

// Default constructor
// Creates a ray from mathematical origin along the x axis
Ray::Ray() {
    this->origin = Point3D();
    this->direction = Vector3D(1, 0, 0);
}

Ray::Ray(const Point3D& p, const Vector3D& d) {
    this->origin = p;
    this->direction = d;
}

Ray::Ray(const Ray& r) {
    this->origin = r.origin;
    this->direction = r.direction;
}

} // namespace Sol

