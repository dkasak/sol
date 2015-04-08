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

#ifndef SOL_TRACER_H
#define SOL_TRACER_H

#include "ColourRGB.h"
#include "Ray.h"
#include "World.h"

namespace Sol {

class Tracer {
public:
    virtual ColourRGB ray_trace(Ray r, World* w, long depth = 0) = 0;
};

class RayCaster : public Tracer {
public:
    ColourRGB ray_trace(Ray r, World* w);
};

class RayTracer : public Tracer {
public:
    ColourRGB ray_trace(Ray r, World* w, long depth = 0);
};

} // namespace Sol

#endif // SOL_TRACER_H
