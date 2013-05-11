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

#include "Point.h"
#include "Ray.h"
#include "Screen.h"

namespace Sol {

class Camera {
public:
    Camera(Point p);
    Camera(double x, double y, double z);

    Point position;
};

class OrtographicCamera : public Camera {
public:
    OrtographicCamera(Point p);
    OrtographicCamera(double x, double y, double z);
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Point p);
    PerspectiveCamera(double x, double y, double z);
};

} // namespace Sol

#endif // SOL_CAMERA_H

