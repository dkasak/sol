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
    position(p)
{}

Camera::Camera(double x, double y, double z) :
    position(Point(x, y, z))
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
    this->screen = s;
}

Screen
Camera::get_screen() {
    return this->screen;
}

void
Camera::render(World world) {
    const unsigned int sizeX = this->screen.sizeX;
    const unsigned int sizeY = this->screen.sizeY;
    const double pxSize = this->screen.pixelSize;

    // screen normal
    /* const Vector n(0, 0, 1); */

    for (unsigned int j = sizeY-1; j != (unsigned int) -1; --j) {
        for (unsigned int i = 0; i < sizeX; ++i) {
            DEBUG(2, "Pixel ->", i, j);

            Point p;
            p.x = (((i - (sizeX / 2.0)) + 0.5) * pxSize);
            p.y = (((j - (sizeY / 2.0)) + 0.5) * pxSize);
            p.z = 0.0;

            Ray r = shoot_ray(p);

            /* Ray r(p, n); */
            ColourRGB c;
            const Material *m;
            double distance;
            double min = numeric_limits<double>::max();
            ShadeInfo shade;
            ShadeInfo tmp;
            bool hit = false;

            for (unsigned int k = 0; k < world.objects.size(); ++k) {
                const Shape *s = world.objects[k];
                if (s->intersects(r, &distance, &tmp) &&
                    distance < min) {
                    min = distance;
                    shade = tmp;
                    hit = true;
                }
            }
            
            if (hit) {
                ColourRGB colour;

                m = shade.material;
                c = m->getColour();

                for (unsigned int k = 0; k < world.lights.size(); ++k) {
                    const Light &l = world.lights[k];
                    Vector path = l.position - shade.hitpoint;
                    Vector normal = shade.normal;
                    Vector normalised_path = path.normalised();
                    min = numeric_limits<double>::max();
                    r.direction = normalised_path;
                    r.origin = shade.hitpoint;

                    hit = false;
                    for (int o = 0; o < world.objects.size(); ++o) {
                        const Shape *s = world.objects[o];
                        if (s->intersects(r, &distance, &tmp) && (distance < path.length())) {
                            hit = true;
                            break;
                        }
                    }
                    if (hit) continue;

                    double dot = normal.dot(normalised_path);
                    if (dot > 0) {
                        double diffuse = m->getDiffuse() * dot;
                        colour += diffuse * c * l.colour;
                        DEBUG(4, "Diffuse factor:", diffuse);
                        DEBUG(4, "Light colour:", l.colour);
                        DEBUG(4, "Object colour:", c);
                        DEBUG(3, "Final colour:", colour);
                    }
                } 

                colour.clamp();
                this->image.push_back(colour);
            } else {
                this->image.push_back(world.getBackground());
            }

        }
    }
}


OrtographicCamera::OrtographicCamera(Point p) :
    Camera(p)
{}

OrtographicCamera::OrtographicCamera(double x, double y, double z) :
    Camera(Point(x, y, z))
{}

Ray
OrtographicCamera::shoot_ray(Point p) {
    Vector normal(0, 0, 1);
    return Ray(p, normal);
}

Ray
PerspectiveCamera::shoot_ray(Point p) {
    // FIXME: hardcoded, shouldn't be 
    int dts = 800; 
    return Ray(get_position(), Vector(p.x, p.y, p.z + dts));
}

PerspectiveCamera::PerspectiveCamera(Point p) :
    Camera(p)
{}

PerspectiveCamera::PerspectiveCamera(double x, double y, double z) :
    Camera(Point(x, y, z))
{}

} // namespace Sol



