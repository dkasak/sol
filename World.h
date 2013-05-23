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

#ifndef SOL_WORLD_H
#define SOL_WORLD_H

#include <vector>

#include "Material.h"
#include "Screen.h"
#include "Intersection.h"
#include "Shape.h"
#include "Sphere.h"
#include "Ray.h"
#include "Point.h"
#include "ColourRGB.h"
#include "Light.h"
#include "Vector.h"

using namespace std;

namespace Sol {

class World {
private:
    ColourRGB ambientLight;
    ColourRGB background;

public:
    vector<const Shape *> shapes;
    vector<const Light *> lights;

    World();
    ~World();

    void
    add_shape(const Shape* s);

    void
    add_light(const Light* l);

    void
    set_ambient(ColourRGB ambient);

    ColourRGB
    get_ambient();

    void
    set_background(ColourRGB background);

    ColourRGB
    get_background();

    bool
    nearest_intersection(Ray ray, Intersection *i = nullptr);
};

} // namespace Sol

#endif // SOL_WORLD_H

