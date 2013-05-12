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
class ShadeInfo;

class Shape {
protected:
    Point3D origin;
    const Material* material;

public:
    Shape();
    Shape(double x, double y, double z);
    Shape(Point3D p);
    virtual ~Shape();

    void
    move(double x, double y, double z);

    void
    move(Point3D p);

    void
    setMaterial(const Material*);

    const Material*
    getMaterial() const;

    void
    setOrigin(const Point3D &m);

    Point3D
    getOrigin() const;

    virtual bool
    intersects(const Ray &r, double *tmin, ShadeInfo *si) const = 0;
};

} // namespace Sol

#endif // SOL_SHAPE_H

