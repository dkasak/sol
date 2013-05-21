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

#include "Light.h"
#include "World.h"
#include <limits>

namespace Sol {

Light::Light(Point3D position)
    : position(position),
      colour(1.0, 1.0, 1.0) // white
{}

Light::Light(Point3D position, ColourRGB colour)
    : position(position),
      colour(colour)
{}

Vector3D
Light::get_path(Point3D p) const {
    return this->position - p;
}

PointLight::PointLight(Point3D position)
    : Light(position)
{}

PointLight::PointLight(Point3D position, ColourRGB colour)
    : Light(position, colour)
{}

double
PointLight::attenuation(Point3D p) const {
    return 1 / get_path(p).length_squared();
}

bool
PointLight::occluded(Ray ray, const World* world) const {
    bool is_occluded = false;
    Vector3D path = this->position - ray.origin;
    Intersection intersection;

    for (const Shape* s : world->objects) {
        if (s->intersects(ray, &intersection) && 
            intersection.distance < path.length()) {
            is_occluded = true;
            break;
        }
    }

    return is_occluded;
}

DirectionalLight::DirectionalLight(Vector3D direction, ColourRGB colour)
    : Light(-direction.normalised(), colour)
{}

double
DirectionalLight::attenuation(Point3D p) const {
    // no attenuation
    return 1.0;
}

bool
DirectionalLight::occluded(Ray ray, const World* world) const {
    bool is_occluded = false;

    for (const Shape* s : world->objects) {
        if (s->intersects(ray)) {
            is_occluded = true;
            break;
        }
    }

    return is_occluded;
}

Vector3D
DirectionalLight::get_path(Point3D p) const {
    return this->position;
}

} // namespace Sol

