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

#include "Shape.h"
#include "Vector.h"

namespace Sol {

class Ray {

public:
    Point  origin;
    Vector direction;

    Ray();
    Ray(const Point& p, const Vector& d);
    Ray(const Ray& r);

    virtual bool
    intersects(const Shape& s, double *tmin, ShadeInfo *si) const;
};

} // namespace Sol

#endif // SOL_RAY_H

