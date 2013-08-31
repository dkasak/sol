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

#ifndef SOL_BOX_H
#define SOL_BOX_H

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

namespace Sol {

enum Face { Negative_X, Positive_X, Negative_Y, Positive_Y, Negative_Z, Positive_Z };

class Box : public Shape {
private:
    Point3D a, b;

public:
    Box(Point3D a, Point3D b);

    virtual bool
    intersects(const Ray &r, Intersection *si = nullptr) const;

    Vector3D
    get_normal(Face face) const;
};

} // namespace Sol

#endif // SOL_BOX_H

