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
#include "Point.h"
#include "Ray.h"
#include "World.h"
#include "Sampler.h"
#include "Screen.h"

namespace Sol {

class Camera {
private:
    Point3D position;
    Screen screen; 

public:
    Camera(Point3D p);
    Camera(double x, double y, double z);

    Point3D
    get_position();

    void
    set_position(Point3D p);

    void
    set_position(double x, double y, double z);

    void
    set_screen(Screen s);

    Screen
    get_screen();

    virtual Ray
    shoot_ray(Point3D p) = 0;

    void
    render(World world);

    vector<ColourRGB> image;
};

class OrtographicCamera : public Camera {
public:
    OrtographicCamera(Point3D p);
    OrtographicCamera(double x, double y, double z);

    virtual Ray
    shoot_ray(Point3D p);
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Point3D p);
    PerspectiveCamera(double x, double y, double z);

    virtual Ray
    shoot_ray(Point3D p);
};

} // namespace Sol

#endif // SOL_CAMERA_H

