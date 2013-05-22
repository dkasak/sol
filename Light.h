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

#ifndef SOL_LIGHT_H
#define SOL_LIGHT_H

#include "ColourRGB.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

namespace Sol {

class World;

class Light {
protected:
    Point3D position;

public:
    ColourRGB colour;

    Light(Point3D position);
    Light(Point3D position, ColourRGB colour);

    virtual
    ~Light();

    virtual double
    attenuation(Point3D p) const = 0;

    virtual Vector3D
    get_path(Point3D p) const;

    virtual Vector3D
    get_direction(Point3D p) const;

    virtual bool
    occluded(Ray r, const World* w) const = 0;
};

class PointLight : public Light {
public:
    PointLight(Point3D position);
    PointLight(Point3D position, ColourRGB colour);

    double
    attenuation(Point3D p) const;

    bool
    occluded(Ray r, const World* w) const;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(Vector3D direction, ColourRGB colour);

    double
    attenuation(Point3D p) const;

    Vector3D
    get_path(Point3D p) const;

    bool
    occluded(Ray r, const World* w) const;
};

} // namespace Sol

#endif // SOL_LIGHT_H
