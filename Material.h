
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

#ifndef SOL_MATERIAL_H
#define SOL_MATERIAL_H

#include "ColourRGB.h"
#include "BRDF.h"
#include "Intersection.h"

namespace Sol {

class World;

class Material {
public:
    Material();

    virtual
    ~Material();

    virtual ColourRGB
    shade(Intersection i, World* w) = 0;
};

class Matte : public Material {
private:
    Lambertian lambertian;

public:
    Matte();
    Matte(double kd, ColourRGB cd);

    ColourRGB
    diffuse(Point3D p, Vector3D wi, Vector3D wo) const;

    void
    set_diffuse_coefficient(double kd);

    void
    set_diffuse_reflectance(ColourRGB cd);

    ColourRGB
    shade(Intersection i, World* w);
};

} // namespace Sol

#endif // SOL_MATERIAL_H

