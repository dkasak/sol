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

#include "Scene.h"
#include "Debug.h"
#include <cstdio>
#include <cmath>
#include <limits>

namespace Sol {

Scene::Scene()
    : origin(Point(0, 0, 0)),
      screen(0, 0),
      background(0.0, 0.0, 0.0),
      ambientLight(0.0)
    {}

void 
Scene::setOrigin(const Point p) {
    this->origin = p;
}

void
Scene::setScreen(const Screen &s) {
    this->screen = s;
}

void
Scene::addShape(const Shape &s) {
    this->objects.push_back(&s);
}

void
Scene::addLight(const Light l) {
    this->lights.push_back(l);
}

void
Scene::setAmbient(double ambient) {
    this->ambientLight = ambient;
}

void
Scene::render() {
    const unsigned int sizeX = this->screen.sizeX;
    const unsigned int sizeY = this->screen.sizeY;
    const double pxSize = this->screen.pixelSize;

    // screen normal
    /* const Vector n(0, 0, 1); */

    for (int j = sizeY-1; j >= 0; --j) {
        for (int i = 0; i < sizeX; ++i) {
            DEBUG(2, "Pixel ->", i, j);
            const double dts = 900; // distance to screen
            Point p;
            p.x = origin.x + (((i - (sizeX / 2.0)) + 0.5) * pxSize);
            p.y = origin.y + (((j - (sizeY / 2.0)) + 0.5) * pxSize);
            p.z = origin.z;

            Ray r(Point(origin.x, origin.y, origin.z - dts), Vector(p.x - origin.x, p.y - origin.y, p.z + dts));
            /* Ray r(p, n); */
            ColourRGB c;
            Material m;
            double distance;
            double min = numeric_limits<double>::max();
            ShadeInfo si;
            ShadeInfo tmp;
            bool hit = false;

            for (int k = 0; k < this->objects.size(); ++k) {
                const Shape *s = this->objects[k];
                if (s->intersects(r, &distance, &tmp) &&
                    distance < min) {
                    min = distance;
                    si = tmp;
                    m = s->getMaterial();
                    c = m.getColour();
                    hit = true;
                }
            }
            if (hit) {
                ColourRGB colour;
                for (int k = 0; k < this->lights.size(); ++k) {
                    const Light &l = this->lights[k];
                    Vector path = l.position - si.hitpoint;
                    Vector normal = si.normal;
                    path.normalise();
                    double dot = normal.dot(path);
                    if (dot > 0) {
                        double diffuse = m.getDiffuse() * dot;
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
                this->image.push_back(this->background);
            }

        }
    }
}  

} // namespace Sol
