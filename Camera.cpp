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

Camera::Camera(Point3D p, Sampler* s) :
    position(p),
    sampler(s)
{}

Camera::Camera(double x, double y, double z, Sampler* s) :
    position(Point3D(x, y, z)),
    sampler(s)
{}

Point3D
Camera::get_position() const {
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
Camera::get_screen() const {
    return this->screen;
}

void
Camera::set_sampler(Sampler* s) {
    this->sampler = s;
}

Sampler*
Camera::get_sampler() const {
    return this->sampler;
}

void
Camera::render(World* world) {
    const unsigned int hres = this->screen.get_hres();
    const unsigned int vres = this->screen.get_vres();
    const double pixel_size = this->screen.get_pixel_size();

    for (unsigned int j = vres-1; j != (unsigned int) -1; --j) {
        for (unsigned int i = 0; i < hres; ++i) {
            DEBUG(2, "Pixel ->", i, j);

            // Calculate lower left corner of pixel
            Point3D p;
            p.x = (i - (hres / 2.0)) * pixel_size;
            p.y = (j - (vres / 2.0)) * pixel_size;
            p.z = 0.0;

            ColourRGB colour;
            unsigned int num_samples = this->sampler->num_samples();
            this->sampler->resample();

            for (auto sample : *sampler) {
                DEBUG(5, "SAMPLE", sample * pixel_size);
                p.x += sample.x * pixel_size;
                p.y += sample.y * pixel_size;

                Ray ray = shoot_ray(p);
                RayCaster tracer;
                colour += tracer.ray_trace(ray, world) / num_samples;
            }

            colour.clamp();
            this->image.push_back(colour);
            DEBUG(3, "Final colour:", colour);
        }
    }
}


OrtographicCamera::OrtographicCamera(Point3D p, Sampler* s) :
    Camera(p, s)
{}

OrtographicCamera::OrtographicCamera(double x, double y, double z, Sampler* s) :
    Camera(Point3D(x, y, z), s)
{}

Ray
OrtographicCamera::shoot_ray(Point3D p) const {
    Vector3D normal(0, 0, 1);
    return Ray(p, normal);
}

Ray
PerspectiveCamera::shoot_ray(Point3D p) const {
    p.z += get_position().z + this->screen_distance;
    Vector3D direction = p - get_position();
    return Ray(get_position(), direction);
}

PerspectiveCamera::PerspectiveCamera(Point3D p, Sampler* s) :
    Camera(p, s),
    screen_distance(1.0)
{}

PerspectiveCamera::PerspectiveCamera(double x, double y, double z, Sampler* s) :
    Camera(Point3D(x, y, z), s),
    screen_distance(1.0)
{}

} // namespace Sol
