/**
 * Copyright 2011, 2012 Denis Kasak <dkasak[at]termina.org.uk>
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
#include <chrono>

using std::chrono::steady_clock;

namespace Sol {

Camera::Camera(Point3D lf, Point3D la, Vector3D vu, double fov) :
    sampler(new RegularSampler(1)),
    look_from_point(lf),
    look_at_point(la),
    view_up_dir(vu.normalised()),
    view_dir((la-lf).normalised()),
    fov(fov),
    zoom_factor(1.0)
{}

Camera::~Camera() {
    delete sampler;
}

void
Camera::look_from(Point3D lf) {
    look_from_point = lf;
    view_dir = (look_from_point - look_at_point).normalised();
}

void
Camera::look_at(Point3D la) {
    look_at_point = la;
    view_dir = (look_at_point - look_from_point).normalised();
}

void
Camera::view_up(Vector3D vu) {
    view_up_dir = vu.normalised();
}

Vector3D
Camera::view_direction() const {
    return view_dir;
}


Vector3D
Camera::w() const {
    return view_dir;
}

Vector3D
Camera::u() const {
    return w().cross(view_up_dir).normalised();
}

Vector3D
Camera::v() const {
    return u().cross(w()).normalised();
}

void
Camera::field_of_view(double fov, bool in_degrees) {
    if (in_degrees) {
        fov = (fov / 180) * pi;
    }

    this->fov = fov;
}

void
Camera::zoom(double zf) {
    // Clamp the zoom factor to [0, +inf>
    zoom_factor = max(zf, 0.0);

    double length = (look_at_point - look_from_point).length();
    double d = zoom_factor * length;

    fov = 2 * atan(screen.get_vres() / (2 * d));
}

void
Camera::set_screen(Screen s) {
    screen = s;

    // We need to re-zoom since the field of view angle depends on screen
    // resolution
    zoom(zoom_factor);
}

Screen
Camera::get_screen() const {
    return screen;
}

void
Camera::set_sampler(Sampler* s) {
    delete sampler;
    sampler = s;
}

Sampler*
Camera::get_sampler() const {
    return sampler;
}

void
Camera::render(World* world) {
    // Screen parameters
    const unsigned int hres = screen.get_hres();
    const unsigned int vres = screen.get_vres();
    const double pixel_size = screen.get_pixel_size();

    // Set up rendering progress reporting
    auto start = steady_clock::now();
    size_t chunk = (vres * hres) / 10;
    size_t next = chunk;

    DEBUG(2, "View direction:", view_dir);
    DEBUG(2, "View up:", view_up_dir);
    DEBUG(2, "Look at:", look_at_point);
    DEBUG(2, "Look from:", look_from_point);
    DEBUG(2, "Field of view:", fov, "radians");
    DEBUG(2, "u:", u());
    DEBUG(2, "v:", v());
    DEBUG(2, "w:", w());

    // Camera screen coordinate bases scaled by pixel size
    Vector3D u_p = u() * pixel_size;
    Vector3D v_p = v() * pixel_size;

    // Distance to screen
    double d = vres / (2 * tan(fov/2));

    // Set up the tracer
    RayTracer tracer;

    // Iterate through the pixels
    for (unsigned int j = 0; j < vres; ++j) {
        for (unsigned int i = 0; i < hres; ++i) {
            DEBUG(2, "Pixel ->", i, j);

            // Print rendering progress
            if ((j * hres + i) == next) {
                print_progress(start, vres * hres, j * hres + i, 10);
                next += chunk;
            }

            // Calculate lower left corner of pixel
            Point3D p = look_from_point
                      + d * w()
                      + (i - (hres / 2.0)) * u_p
                      + (j - (vres / 2.0)) * v_p;

            ColourRGB colour;
            unsigned int num_samples = sampler->num_samples();
            sampler->resample();

            // Sample the pixel and trace rays through the samples
            for (auto sample : *sampler) {
                DEBUG(5, "SAMPLE", sample * pixel_size);

                // Perturb the pixel by the random samples
                Point3D s = p + u_p * sample.x + v_p * sample.y;

                Ray ray = shoot_ray(s);
                colour += tracer.ray_trace(ray, world) / num_samples;
            }

            // Clamp out-of-gamut colours
            colour.clamp();

            // Commit the colour to the film
            DEBUG(3, "Final colour:", colour);
            film.commit(colour);
        }
    }
}


OrtographicCamera::OrtographicCamera(Point3D lf, Point3D la, Vector3D vu, double fov)
    : Camera(lf, la, vu, fov)
{}

Ray
OrtographicCamera::shoot_ray(Point3D p) const {
    Vector3D normal(0, 0, 1);
    return Ray(p, normal);
}

Ray
PerspectiveCamera::shoot_ray(Point3D p) const {
    Vector3D direction = p - look_from_point;
    return Ray(look_from_point, direction);
}

PerspectiveCamera::PerspectiveCamera(Point3D lf, Point3D la, Vector3D vu, double fov) :
    Camera(lf, la, vu, fov)
{}


} // namespace Sol
