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

#include "World.h"
#include <cstdio>
#include <cmath>
#include <limits>

namespace Sol {

World::World() : 
    background(0.0, 0.0, 0.0),
    ambientLight(0.0)
{}

World::~World() {
    for (auto sp : this->shapes) {
        delete sp;
    }

    for (auto sp : this->lights) {
        delete sp;
    }
}

void
World::addShape(const Shape* s) {
    this->shapes.push_back(s);
}

void
World::addLight(const Light* l) {
    this->lights.push_back(l);
}

void
World::setAmbient(double ambient) {
    this->ambientLight = ambient;
}

void
World::setBackground(ColourRGB background) {
    this->background = background;
}

ColourRGB
World::getBackground() {
    return this->background;
}

bool
World::nearest_intersection(Ray ray, Intersection *intersection) {
    bool hit = false;

    for (const Shape* s : this->shapes) {
        Intersection i;

        if (intersection) {
            if (s->intersects(ray, &i) &&
                i.distance < intersection->distance) {
                *intersection = i;
                hit = true;
            }
        } else {
            if (s->intersects(ray)) {
                hit = true;
                break;
            }
        }
    }

    return hit;
}

} // namespace Sol
