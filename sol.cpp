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
#include "Plane.h"
#include "Material.h"
#include "ColourRGB.h"
#include "Debug.h"
#include "Options.h"

#include <cassert>
#include <cstring>
#include <cstdlib>

extern "C" {
#include "dbmp.h"
}

using namespace Sol;

int
main(int argc, char **argv) {
    Options opt;
    try {
        opt = parse_options(argc, argv);
    } catch (const InvalidOption &e) {
        std::cout << "Invalid option: " << e.option_name << std::endl;
        exit(EXIT_SUCCESS);
    } catch (const InvalidOptionValue &e) {
        std::cout << "Invalid option value \"" << e.option_value <<  
            "\" for option " << e.option_name << std::endl;
        exit(EXIT_SUCCESS);
    }

    debug_level = opt.debug_level;

    Scene scene;
    scene.setScreen(new Screen(opt.hres, opt.vres));
    scene.setBackground(ColourRGB(0.1, 0.2, 0.3));

    Material *m1 = new Material();
    m1->setDiffuse(1.0);
    m1->setColour(ColourRGB(1.0, 1.0, 1.0));

    Material *m2 = new Material();
    m2->setDiffuse(1.0);
    m2->setColour(ColourRGB(0.0, 0.9, 0.1));

    Material *m3 = new Material();
    m3->setDiffuse(1.0);
    m3->setColour(ColourRGB(1.0, 0.1, 0.1));

    Sphere s1(Point(0, 60, 160), 150.0);
    Sphere s2(Point(300, 200, 400), 150.0);
    s1.setMaterial(m1);
    s2.setMaterial(m2);
    scene.addShape(s1);
    scene.addShape(s2);

    Plane p(Point(0, -100, 0), Vector(0.0, 1.0, 0.0)); 
    p.setMaterial(m3);
    scene.addShape(p);

    Light l1(Point(160, 160, 0), ColourRGB(0.5, 0.1, 0.3)*1.6);
    Light l2(Point(100, 20, 20), ColourRGB(0.5, 0.5, 0.5)*1.6);
    scene.addLight(l1);
    scene.addLight(l2);

    DEBUG(1, "Began rendering");
    scene.render();
    DEBUG(1, "Finished rendering");

    unsigned char *image = new_image_buffer(scene.getScreen()->sizeX, scene.getScreen()->sizeY);
    assert(scene.image.size() == scene.getScreen()->sizeX * scene.getScreen()->sizeY);

    // Cyan pixel as the first pixel of the rendered image, for orientation
    scene.image[0] = ColourRGB(0.0, 1.0, 1.0);

    for (size_t i = 0; i < scene.image.size(); ++i) {
        image[3*i] = scene.image[i].red * 255;
        image[3*i + 1] = scene.image[i].green * 255;
        image[3*i + 2] = scene.image[i].blue * 255;
    }

    // Red pixel in top-left corner for testing, to be removed eventually
    image[0] = 255;
    image[1] = 0;
    image[2] = 0;

    DEBUG(1, "Write BMP");
    write_bmp(image, scene.getScreen()->sizeX, scene.getScreen()->sizeY, opt.output_filename.c_str());
    destroy_image_buffer(image);

    delete m1;
    delete m2;
    delete m3;

    return 0;
}
