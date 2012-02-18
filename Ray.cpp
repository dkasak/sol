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

#ifndef SOL_RAY_H
#define SOL_RAY_H

namespace Sol {

// Default constructor
// Creates a ray from mathematical origin along the x axis
Ray::Ray() {
    this->point = Point();
    this->direction = Vector(1, 0, 0);
}

Ray(const Point &p, const Vector &d) {
    this->point = p;
    this->direction = d;
}

Ray(const Ray &r) {
    this->point = r->point;
    this->direction = r->direction;
}

virtual bool intersects(const Shape &s) const {
    return s.intersects(this);
};

} // namespace Sol

#endif // SOL_RAY_H

