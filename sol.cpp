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
#include "Film.h"
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

#include "Worlds/four_spheres.cpp"

void output_image(const Film& film, size_t width, size_t height, const char* filename) {
    DEBUG(1, "Writing BMP...");
    unsigned char* image = film.BGR24();
    write_bmp(image, width, height, filename);
    delete[] image;
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

    PerspectiveCamera camera;
    camera.look_from(Point3D(0, 30, -70));
    camera.look_at(Point3D(0, 0, 0));
    camera.set_screen(screen);
    camera.set_sampler(sampler);
    camera.zoom(0.2);

    World* world = build_world();

    DEBUG(1, "Began rendering");
    camera.render(world);
    DEBUG(1, "Finished rendering");

    assert(camera.film.size() ==
           screen.get_hres() * screen.get_vres());

    output_image(camera.film, screen.get_hres(),
                 screen.get_vres(), opt.output_filename.c_str());

    delete world;

    return EXIT_SUCCESS;
}
