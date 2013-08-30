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

#ifndef SOL_SHAPE_H
#define SOL_SHAPE_H

#include "Material.h"
#include "Point.h"

namespace Sol {

class Ray;
struct Intersection;

class Shape {
protected:
    Point3D origin;
    Material* material;

public:
    Shape();
    Shape(Point3D p);
    virtual ~Shape();

    void
    set_material(Material* m);

    Material*
    get_material() const;

    void
    set_origin(const Point3D &m);

    Point3D
    get_origin() const;

    virtual bool
    intersects(const Ray &r, Intersection *si = nullptr) const = 0;
};

} // namespace Sol

#endif // SOL_SHAPE_H

