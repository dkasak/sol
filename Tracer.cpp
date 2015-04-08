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

#include "Tracer.h"
#include "Debug.h"

namespace Sol {

ColourRGB
RayCaster::ray_trace(Ray ray, World* world) {
    Intersection intersection;
    ColourRGB colour;

    bool hit = world->nearest_intersection(ray, &intersection);

    if (hit) {
        Material *m = intersection.shape->get_material();
        colour = m->direct_illumination(intersection, world);
    } else {
        colour = world->get_background();
    }

    return colour;
}

ColourRGB
RayTracer::ray_trace(Ray ray, World* world, long depth) {
    Intersection intersection;
    ColourRGB colour;

    if (depth > 5) {
        return black;
    }

    bool hit = world->nearest_intersection(ray, &intersection);

    if (hit) {
        Material *m = intersection.shape->get_material();
        colour = m->direct_illumination(intersection, world);

        if (m->is_reflective()) {
            Vector3D v = ray.direction;
            Vector3D n = intersection.normal;
            Point3D p = intersection.hit_point;
            Vector3D r = v - (2 * n * n.dot(v));
            Ray reflected(p, r);

            colour += m->reflectance() * this->ray_trace(reflected, world, depth + 1);
        }
    } else {
        colour = world->get_background();
    }

    return colour;
}

} // namespace Sol

