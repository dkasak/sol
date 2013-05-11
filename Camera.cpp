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

#include "Camera.h"

namespace Sol {

Camera::Camera(Point p) :
    position(p),
    screen()
{}

Camera::Camera(double x, double y, double z) :
    position(Point(x, y, z)),
    screen()
{}

Point
Camera::get_position() {
    return this->position;
}

void
Camera::set_position(Point p) {
    this->position = p;
}

void
Camera::set_position(double x, double y, double z) {
    this->position = Point(x, y, z);
}

void
Camera::set_screen(Screen s) {
    this->screen = screen;
}

Screen
Camera::get_screen() {
    return this->screen;
}


OrtographicCamera::OrtographicCamera(Point p) :
    Camera(p)
{}

OrtographicCamera::OrtographicCamera(double x, double y, double z) :
    Camera(Point(x, y, z))
{}

PerspectiveCamera::PerspectiveCamera(Point p) :
    Camera(p)
{}

PerspectiveCamera::PerspectiveCamera(double x, double y, double z) :
    Camera(Point(x, y, z))
{}

} // namespace Sol



