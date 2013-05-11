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

Scene::Scene() : 
    background(0.0, 0.0, 0.0),
    ambientLight(0.0)
{}

void
Scene::addShape(const Shape& s) {
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
Scene::setBackground(ColourRGB background) {
    this->background = background;
}

ColourRGB
Scene::getBackground() {
    return this->background;
}

} // namespace Sol
