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
#include "Shape.h"
#include "Screen.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "ColourRGB.h"
#include <assert.h>

extern "C" {
#include "dbmp.h"
}

#define SIZE_X 640
#define SIZE_Y 480

using namespace Sol;

int main() {
    Scene scene;

    scene.setOrigin(Point(0, 0, -100));

    Screen screen(SIZE_X, SIZE_Y);
    scene.setScreen(screen);

    Material m1;
    m1.setColour(ColourRGB(1.0, 0.9, 0));
    Material m2;
    m2.setColour(ColourRGB(0.0, 0.9, 0));

    Sphere s1(Point(0, 0, 100), 150);
    s1.setMaterial(m1);
    Sphere s2(Point(0, -100, -30), 120);
    s2.setMaterial(m2);
    scene.addShape(s1);
    scene.addShape(s2);

    /* Light l1; */
    /* l1.setBrightness(); */
    /* l1.setColour(); */
    /* l1.setPosition(); */
    /* scene.addLight(l1); */

    scene.render();

    char *image = new_image_buffer(scene.screen.sizeX, scene.screen.sizeY);
                        
    assert(scene.image.size() == scene.screen.sizeX * scene.screen.sizeY);
    for (int i = 0; i < scene.image.size(); ++i) {
        image[3*i] = scene.image[i].red * 255;
        image[3*i + 1] = scene.image[i].green * 255;
        image[3*i + 2] = scene.image[i].blue * 255;
    }

    write_bmp(image, scene.screen.sizeX, scene.screen.sizeY, "output.bmp");
    destroy_image_buffer(image);

    return 0;
}
