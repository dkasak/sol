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

#ifndef SOL_SPHERE_H
#define SOL_SPHERE_H

#include "Shape.h"
#include "ShadeInfo.h"
#include "Ray.h"

namespace Sol {

class Sphere : public Shape {

private:
    double radius;

public:
    Sphere();
    Sphere(double r);
    Sphere(Point p, double r);
    void setRadius(double r);
    double getRadius() const;

    virtual bool intersects(const Ray &r, double *distance, ShadeInfo *si) const;
};

} // namespace Sol

#endif // SOL_SPHERE_H

