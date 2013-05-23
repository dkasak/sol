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

#ifndef SOL_CAMERA_H
#define SOL_CAMERA_H

#include <limits>

#include "ColourRGB.h"
#include "Debug.h"
#include "Film.h"
#include "Point.h"
#include "Ray.h"
#include "Sampler.h"
#include "Screen.h"
#include "Tracer.h"
#include "World.h"

namespace Sol {

class Camera {
private:
    Point3D position;
    Screen screen; 
    Sampler* sampler;

public:
    Film film;

    Camera(Point3D p, Sampler* s);
    Camera(double x, double y, double z, Sampler* s);

    Point3D
    get_position() const;

    void
    set_position(Point3D p);

    void
    set_position(double x, double y, double z);

    void
    set_screen(Screen s);

    Screen
    get_screen() const;

    void
    set_sampler(Sampler* s);

    Sampler*
    get_sampler() const;

    virtual Ray
    shoot_ray(Point3D p) const = 0;

    void
    render(World* world);
};

class OrtographicCamera : public Camera {
public:
    OrtographicCamera(Point3D p, Sampler* s);
    OrtographicCamera(double x, double y, double z, Sampler* s);

    virtual Ray
    shoot_ray(Point3D p) const;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Point3D p, Sampler* s);
    PerspectiveCamera(double x, double y, double z, Sampler* s);

    virtual Ray
    shoot_ray(Point3D p) const;

    unsigned int screen_distance;
};

} // namespace Sol

#endif // SOL_CAMERA_H

