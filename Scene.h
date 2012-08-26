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

#ifndef SOL_SCENE_H
#define SOL_SCENE_H

#include <vector>

#include "Material.h"
#include "Screen.h"
#include "ShadeInfo.h"
#include "Shape.h"
#include "Sphere.h"
#include "Ray.h"
#include "Point.h"
#include "ColourRGB.h"
#include "Light.h"
#include "Vector.h"

using namespace std;

namespace Sol {

class Scene {
private:
    Point origin;
    Screen *screen;
    vector<const Shape *> objects;
    vector<Light> lights;
    double ambientLight;
    ColourRGB background;

public:
    // TODO: handle properly with getters
    vector<ColourRGB> image;

    Scene();
    ~Scene();

    void
    setOrigin(const Point p);

    void
    setScreen(Screen* s);

    Screen*
    getScreen();

    void
    addShape(const Shape& s);

    void
    addLight(const Light l);

    void
    setAmbient(double ambient);

    void
    setBackground(ColourRGB background);

    ColourRGB
    getBackground();

    void
    render();
};

} // namespace Sol

#endif // SOL_SCENE_H

