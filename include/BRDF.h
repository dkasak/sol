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

#ifndef SOL_BRDF_H
#define SOL_BRDF_H

#include "Point.h"
#include "ColourRGB.h"

namespace Sol {

class Material;

class BRDF {
    virtual ColourRGB
    operator()(Point3D p, Vector3D wi, Vector3D wo) const = 0;
};

class Lambertian : public BRDF {
public:
    double kd;
    ColourRGB cd;

    Lambertian(double kd, ColourRGB cd);

    ColourRGB
    operator()(Point3D p, Vector3D wi, Vector3D wo) const;
};

} // namespace Sol

#endif // SOL_BRDF_H

