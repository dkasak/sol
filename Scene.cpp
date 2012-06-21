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
#include <cstdio>
#include <cmath>
#include <limits>

namespace Sol {

Scene::Scene()
    : origin(Point(0, 0, 0)),
      screen(0, 0),
      background(0.0, 0.0, 0.0)
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
    Vector n(0, 0, 1);

    for (int j = sizeY-1; j >= 0; --j) {
        for (int i = 0; i < sizeX; ++i) {
            Point p;
            p.x = ((i - (sizeX / 2.0)) + 0.5) * pxSize;
            p.y = ((j - (sizeY / 2.0)) + 0.5) * pxSize;
            p.z = 0;

            Ray r(p, n);
            ColourRGB c;
            Material m;
            double distance;
            double min = numeric_limits<double>::max();
            ShadeInfo si;
            bool hit = false;

            for (int k = 0; k < this->objects.size(); ++k) {
                const Shape *s = this->objects[k];
                if (s->intersects(r, &distance, &si) &&
                    distance < min) {
                    min = distance;
                    m = s->getMaterial();
                    c = m.getColour();
                    hit = true;
                }
            }

            if (hit) {
                double angle = n.angle(si.normal);
                double factor = cos(abs(angle));
                c *= factor;
                this->image.push_back(c);
            } else {
                this->image.push_back(this->background);
            }

        }
    }
}  

} // namespace Sol
