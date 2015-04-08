
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

#ifndef SOL_INTERSECTION_H
#define SOL_INTERSECTION_H

#include "Vector.h"
#include "Point.h"
#include "Ray.h"

namespace Sol {

class Shape;

struct Intersection {
    Vector3D normal;
    Point3D hit_point;
    double distance;
    const Shape* shape;
    Ray ray;

    Intersection();
};

} // namespace Sol

#endif // SOL_INTERSECTION_H

