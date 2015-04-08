/**
 * Copyright 2011-2015 Denis Kasak <dkasak[at]termina.org.uk>
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

#include "Material.h"
#include "World.h"
#include "Debug.h"

namespace Sol {

Material::Material() {}

Material::~Material() {}

bool
Material::is_reflective() const {
    return false;
}

ColourRGB
Material::reflectance() const {
    return black;
}

Matte::Matte()
    : lambertian(1.0, ColourRGB(1.0))
{}

Matte::Matte(double diffuse_coefficient, ColourRGB reflectance)
    : lambertian(diffuse_coefficient, reflectance)
{}

ColourRGB
Matte::direct_illumination(Intersection intersection, World* world) {
    ColourRGB radiance;
    Vector3D normal = intersection.normal;
    Vector3D wo = -intersection.ray.direction;
    Point3D p = intersection.hit_point;

    for (const Light* l : world->lights) {
        Vector3D wi = l->get_direction(intersection.hit_point);

        Ray ray;
        ray.direction = wi;
        ray.origin = intersection.hit_point;

        // If this light source if occluded, skip it
        if (l->occluded(ray, world)) {
            DEBUG(3, "Light occluded.");
            continue;
        } else {
            DEBUG(3, "Light visible.");
        }

        double dot = normal.dot(wi);
        if (dot > 0) {
            double attenuation = l->attenuation(p);
            radiance += (this->lambertian(p, wi, wo) * dot * l->emittance()) * attenuation;
            /* DEBUG(4, "Diffuse factor:", diffuse); */
            /* DEBUG(4, "Light colour:", l->colour); */
            /* DEBUG(4, "Object colour:", c); */
            /* DEBUG(3, "Sample colour:", sample_colour); */
        }
    }

    return radiance;
}

Mirror::Mirror()
    : ks(1.0),
      cs(white)
{}

Mirror::Mirror(double specular_coefficient, ColourRGB reflectance)
    : ks(specular_coefficient),
      cs(reflectance)
{}

bool
Mirror::is_reflective() const {
    return true;
}

ColourRGB
Mirror::reflectance() const {
    return this->ks * this->cs;
}

ColourRGB
Mirror::direct_illumination(Intersection intersection, World* world) {
    return black;
}


MatteMirror::MatteMirror()
    : Matte(),
      Mirror()
{}

MatteMirror::MatteMirror(double kd, ColourRGB cd, double ks, ColourRGB cs)
    : Matte(kd, cd),
      Mirror(ks, cs)
{}

ColourRGB
MatteMirror::direct_illumination(Intersection intersection, World* world) {
    return Matte::direct_illumination(intersection, world);
}

bool
MatteMirror::is_reflective() const {
    return Mirror::is_reflective();
}

ColourRGB
MatteMirror::reflectance() const {
    return Mirror::reflectance();
}
} // namespace Sol

