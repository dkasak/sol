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

#include <iostream>
#include <cmath>
#include "Plane.h"
#include "Debug.h"

using namespace std;

namespace Sol {

const double kEpsilon = 0.01;

Plane::Plane(Vector3D n) {
    this->normal = n;
}

Plane::Plane(Point3D p, Vector3D n) {
    this->origin = p;
    this->normal = n;
}

void
Plane::set_normal(Vector3D n) {
    this->normal = n;
}

Vector3D
Plane::get_normal() const {
    return this->normal;
}

bool
Plane::intersects(const Ray &r, Intersection *si) const {
    Point3D p = this->origin;
    Vector3D n = this->normal.normalised();
    Point3D ro = r.origin;
    Vector3D dir = r.direction.normalised();

    DEBUG(2, "[plane]");
    DEBUG(4, "  ray origin:", ro);
    DEBUG(4, "  ray direction:", dir);
    DEBUG(4, "  p:", p);
    DEBUG(4, "  n:", n);
    double num, den;

    num = (p - ro).dot(n);
    den = dir.dot(n);
    double t = num / den;

    // If the denominator is zero, the ray is parallel with the plane
    // (either lying on it or not touching it at all)
    if (fabs(den) > kEpsilon && t > kEpsilon) {
        auto hit_point = r.origin + t * dir;
        
        if (si) {
            si->hit_point = hit_point;
            si->normal = n;
            si->distance = t;
            si->shape = this;
        }

        DEBUG(2, "  -> hit");
        DEBUG(4, "    distance:", t);
        DEBUG(4, "    hit point:", hit_point);
        DEBUG(4, "    normal:", n);

        return true;
    } else {
        return false;
    }
}

} // namespace Sol

