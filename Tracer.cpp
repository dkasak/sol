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

#include "Tracer.h"
#include "Debug.h"

#include <limits>

namespace Sol {
    
ColourRGB
RayCaster::ray_trace(Ray ray, World* world) {
    ShadeInfo shade;
    const Shape* shape;
    bool hit = false;
    double distance;
    double min = numeric_limits<double>::max();

    for (const Shape* s : world->objects) {
        ShadeInfo si;

        if (s->intersects(ray, &distance, &si) &&
            distance < min) {
            min = distance;
            shape = s;
            shade = si;
            hit = true;
        }
    }

    ColourRGB colour;
    
    if (hit) {
        Material m = shape->getMaterial();
        ColourRGB c = m.getColour();
        ColourRGB sample_colour;

        for (const Light& l : world->lights) {
            Vector3D path = l.position - shade.hitpoint;
            Vector3D normal = shade.normal;
            Vector3D normalised_path = path.normalised();
            min = numeric_limits<double>::max();
            ray.direction = normalised_path;
            ray.origin = shade.hitpoint;

            bool occluded = false;
            for (const Shape* s : world->objects) {
                ShadeInfo si;

                if (s->intersects(ray, &distance, &si) && 
                    distance < path.length()) {
                    occluded = true;
                    break;
                }
            }

            // If this light source if occluded, skip it
            if (occluded)
                continue;

            double dot = normal.dot(normalised_path);
            if (dot > 0) {
                double diffuse = m.getDiffuse() * dot;
                sample_colour += (diffuse * c * l.colour) / path.length_squared();
                DEBUG(4, "Diffuse factor:", diffuse);
                DEBUG(4, "Light colour:", l.colour);
                DEBUG(4, "Object colour:", c);
                DEBUG(3, "Sample colour:", sample_colour);
            }
        } 

        colour = sample_colour;
    } else {
        colour = world->getBackground();
    }

    return colour;
}

} // namespace Sol
