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

#include "Constants.h"
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
protected:
    Point3D look_from_point, look_at_point;
    Vector3D view_dir, view_up_dir;
    Screen screen; 
    Sampler* sampler;
    double fov;

public:
    Film film;

    Camera(Point3D lf, Point3D la, Vector3D vu, double fov);

    virtual
    ~Camera();

    void
    look_from(Point3D p);

    void
    look_at(Point3D p);

    void
    view_up(Vector3D vu);

    Vector3D
    view_direction() const;

    Vector3D
    w() const;

    Vector3D
    u() const;

    Vector3D 
    v() const;

    void
    field_of_view(double fov, bool in_degrees = false);

    void
    zoom(double zoom_factor);

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
    OrtographicCamera(Point3D lf = Point3D(0, 0, 0), 
                      Point3D la = Point3D(0, 0, 1),
                      Vector3D vu = Vector3D(0, 1, 0),
                      double fov = pi/3);

    virtual Ray
    shoot_ray(Point3D p) const;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Point3D lf = Point3D(0, 0, 0), 
                      Point3D la = Point3D(0, 0, 1),
                      Vector3D vu = Vector3D(0, 1, 0),
                      double fov = pi/3);

    virtual Ray
    shoot_ray(Point3D p) const;
};

} // namespace Sol

#endif // SOL_CAMERA_H

