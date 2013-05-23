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

#include "Constants.h"
#include "Camera.h"
#include "ColourRGB.h"
#include "Debug.h"
#include "Light.h"
#include "Material.h"
#include "Plane.h"
#include "Ray.h"
#include "World.h"
#include "Screen.h"
#include "Shape.h"
#include "Sphere.h"
#include "Options.h"

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <random>

extern "C" {
#include "dbmp.h"
}

using namespace Sol;

World* build_world() {
    World* world = new World;

    world->set_background(ColourRGB(0.1, 0.2, 0.3));

    auto m1 = new Mirror(0.7, white);
    auto m2 = new Mirror(0.7, cyan);
    auto m3 = new Mirror(0.7, red);
    auto m4 = new Matte(1.0, yellow);
    auto mp = new Matte(0.8, white);

    auto s1 = new Sphere(Point3D( 0.0, 0.2, 6.0), 1.0);
    s1->set_material(m1);
    auto s2 = new Sphere(Point3D(-3.0, 0.2,  0.0), 1.0);
    s2->set_material(m2);
    auto s3 = new Sphere(Point3D( 3.0, 0.2,  0.0), 1.0);
    s3->set_material(m3);
    auto s4 = new Sphere(Point3D( 0.0, 0.5, -0.5), 0.3);
    s4->set_material(m4);

    auto p = new Plane(Point3D(0, -1.0, 0), Vector3D(0.0, 1.0, 0.0));
    p->set_material(mp);

    world->add_shape(s1);
    world->add_shape(s2);
    world->add_shape(s3);
    world->add_shape(s4);
    world->add_shape(p);

    auto l1 = new PointLight(Point3D( 0.0, 2.0, -2.0), white, 25.0);
    auto l2 = new PointLight(Point3D(-2.5, 2.0,  0.0), white, 50.0);
    auto l3 = new PointLight(Point3D( 2.5, 2.0,  0.0), green, 12.0);
    auto l4 = new DirectionalLight(Vector3D( -2.5, -2.0,  0.0), yellow, 0.4);

    world->add_light(l1);
    world->add_light(l2);
    world->add_light(l3);
    world->add_light(l4);

    return world;
}

void output_image(Camera& camera, Options opt) {
    unsigned char *image = new_image_buffer(camera.get_screen().get_hres(),
                                            camera.get_screen().get_vres());

    assert(camera.image.size() ==
           camera.get_screen().get_hres() * camera.get_screen().get_vres());

    // Cyan pixel as the first pixel of the rendered image, for orientation
    camera.image[0] = ColourRGB(0.0, 1.0, 1.0);

    for (size_t i = 0; i < camera.image.size(); ++i) {
        image[3*i]     = camera.image[i].blue * 255;
        image[3*i + 1] = camera.image[i].green * 255;
        image[3*i + 2] = camera.image[i].red * 255;
    }

    // Red pixel in top-left corner for testing, to be removed eventually
    image[0] = 255;
    image[1] = 0;
    image[2] = 0;

    DEBUG(1, "Writing BMP...");
    write_bmp(image,
              camera.get_screen().get_hres(),
              camera.get_screen().get_vres(),
              opt.output_filename.c_str());
    destroy_image_buffer(image);
}

int
main(int argc, char **argv) {
    Options opt;
    try {
        opt = parse_options(argc, argv);
    } catch (const InvalidOption &e) {
        std::cout << "Invalid option: " << e.name << std::endl;
        exit(EXIT_SUCCESS);
    } catch (const InvalidOptionValue &e) {
        std::cout << "Invalid value \"" << e.value 
                  << "\" for option " << e.name << std::endl;
        exit(EXIT_SUCCESS);
    } catch (const MissingOptionValue &e) {
        std::cout << "Missing argument for option " << e.name 
                  << std::endl;
        exit(EXIT_SUCCESS);
    }

    debug_level = opt.debug_level;

    Sampler *sampler;
    if (opt.sampler == STOCHASTIC) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<double> distribution(0, 1);
        auto generator = [rng, distribution] () mutable { return distribution(rng); };
        sampler = new StochasticSampler(opt.supersamples, generator);
    } else if (opt.sampler == REGULAR) {
        sampler = new RegularSampler(opt.supersamples);
    }

    Screen screen = Screen(opt.hres, opt.vres);
    screen.set_pixel_size(opt.pixel_size);

    PerspectiveCamera camera(Point3D(0.0, 0.0, -5.0), sampler);
    camera.set_screen(screen);
    camera.screen_distance = 3.5;

    World* world = build_world();

    DEBUG(1, "Began rendering");
    camera.render(world);
    DEBUG(1, "Finished rendering");

    output_image(camera, opt);

    delete world;
    delete sampler;

    return EXIT_SUCCESS;
}
