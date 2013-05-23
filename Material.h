
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
#include "Constants.h"

namespace Sol {

class World;

class Material {
public:
    Material();

    virtual
    ~Material();

    virtual ColourRGB
    direct_illumination(Intersection i, World* w) = 0;

    virtual bool
    is_reflective() const;

    virtual ColourRGB
    reflectance() const;
};

class Matte : virtual public Material {
private:
    Lambertian lambertian;

public:
    Matte();
    Matte(double kd, ColourRGB cd);

    ColourRGB
    direct_illumination(Intersection i, World* w);
};

class Mirror : virtual public Material {
private:
    double ks;
    ColourRGB cs;

public:
    Mirror();
    Mirror(double ks, ColourRGB cs);

    bool
    is_reflective() const;

    ColourRGB
    reflectance() const;

    ColourRGB
    direct_illumination(Intersection i, World* w);
};

class MatteMirror : public Matte, public Mirror {
public:
    MatteMirror();
    MatteMirror(double kd, ColourRGB cd, double ks, ColourRGB cs);

    bool
    is_reflective() const;

    ColourRGB
    reflectance() const;

    ColourRGB
    direct_illumination(Intersection i, World* w);
};

} // namespace Sol

#endif // SOL_MATERIAL_H

