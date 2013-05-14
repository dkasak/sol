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

#include "Camera.h"

namespace Sol {

Camera::Camera(Point3D p) :
    position(p)
{}

Camera::Camera(double x, double y, double z) :
    position(Point3D(x, y, z))
{}

Point3D
Camera::get_position() {
    return this->position;
}

void
Camera::set_position(Point3D p) {
    this->position = p;
}

void
Camera::set_position(double x, double y, double z) {
    this->position = Point3D(x, y, z);
}

void
Camera::set_screen(Screen s) {
    this->screen = s;
}

Screen
Camera::get_screen() {
    return this->screen;
}

void
Camera::render(World world) {
    const unsigned int hres = this->screen.get_hres();
    const unsigned int vres = this->screen.get_vres();
    const double pixel_size = this->screen.get_pixel_size();

    // screen normal
    /* const Vector3D n(0, 0, 1); */

    for (unsigned int j = vres-1; j != (unsigned int) -1; --j) {
        for (unsigned int i = 0; i < hres; ++i) {
            DEBUG(2, "Pixel ->", i, j);

            // Calculate lower left corner of pixel
            Point3D p;
            p.x = (i - (hres / 2.0)) * pixel_size;
            p.y = (j - (vres / 2.0)) * pixel_size;
            p.z = 0.0;

            unsigned int supersamples = 2;
            RegularSampler sampler(supersamples);
            unsigned int num_samples = sampler.num_samples();
            ColourRGB colour;

            for (auto sample : sampler) {
                DEBUG(1, "SAMPLE", sample * pixel_size);
                p.x += sample.x * pixel_size;
                p.y += sample.y * pixel_size;

                Ray r = shoot_ray(p);
            
                /* Ray r(p, n); */
                const Material *m;
                double distance;
                double min = numeric_limits<double>::max();
                ShadeInfo shade, tmp;
                bool hit = false;

                for (unsigned int k = 0; k < world.objects.size(); ++k) {
                    const Shape *s = world.objects[k];
                    if (s->intersects(r, &distance, &tmp) &&
                        distance < min) {
                        min = distance;
                        shade = tmp;
                        hit = true;
                    }
                }
                
                if (hit) {
                    m = shade.material;
                    ColourRGB c = m->getColour();
                    ColourRGB sample_colour;

                    for (unsigned int k = 0; k < world.lights.size(); ++k) {
                        const Light &l = world.lights[k];
                        Vector3D path = l.position - shade.hitpoint;
                        Vector3D normal = shade.normal;
                        Vector3D normalised_path = path.normalised();
                        min = numeric_limits<double>::max();
                        r.direction = normalised_path;
                        r.origin = shade.hitpoint;

                        bool occluded = false;
                        for (int o = 0; o < world.objects.size(); ++o) {
                            const Shape *s = world.objects[o];
                            if (s->intersects(r, &distance, &tmp) && (distance < path.length())) {
                                occluded = true;
                                break;
                            }
                        }

                        // If this light source if occluded, skip it
                        if (occluded)
                            continue;

                        double dot = normal.dot(normalised_path);
                        if (dot > 0) {
                            double diffuse = m->getDiffuse() * dot;
                            sample_colour += diffuse * c * l.colour;
                            DEBUG(4, "Diffuse factor:", diffuse);
                            DEBUG(4, "Light colour:", l.colour);
                            DEBUG(4, "Object colour:", c);
                            DEBUG(3, "Sample colour:", sample_colour);
                        }
                    } 

                    colour += sample_colour / num_samples;
                } else {
                    colour += world.getBackground() / num_samples;
                }
            }

            colour.clamp();
            this->image.push_back(colour);
            DEBUG(3, "Final colour:", colour);
        }
    }
}


OrtographicCamera::OrtographicCamera(Point3D p) :
    Camera(p)
{}

OrtographicCamera::OrtographicCamera(double x, double y, double z) :
    Camera(Point3D(x, y, z))
{}

Ray
OrtographicCamera::shoot_ray(Point3D p) {
    Vector3D normal(0, 0, 1);
    return Ray(p, normal);
}

Ray
PerspectiveCamera::shoot_ray(Point3D p) {
    // FIXME: hardcoded, shouldn't be 
    double dts = 200;
    p.z += get_position().z + dts;
    Vector3D direction = p - get_position();
    return Ray(get_position(), direction);
}

PerspectiveCamera::PerspectiveCamera(Point3D p) :
    Camera(p)
{}

PerspectiveCamera::PerspectiveCamera(double x, double y, double z) :
    Camera(Point3D(x, y, z))
{}

} // namespace Sol



