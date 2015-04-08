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

#include <iostream>
#include <cmath>
#include "Box.h"
#include "Vector.h"
#include "Debug.h"

using namespace std;

namespace Sol {

const double kEpsilon = 0.0001;

Box::Box(Point3D a, Point3D b) {
    this->a = a;
    this->b = b;
}

Vector3D
Box::get_normal(Face face) const {
    switch(face) {
        default: // pacify compiler

        // x faces
        case Negative_X: return Vector3D(-1, 0, 0);
        case Positive_X: return Vector3D(1, 0, 0);

        // y faces
        case Negative_Y: return Vector3D(0, -1, 0);
        case Positive_Y: return Vector3D(0, 1, 0);

        // z faces
        case Negative_Z: return Vector3D(0, 0, -1);
        case Positive_Z: return Vector3D(0, 0, 1);
    }
}

bool
Box::intersects(const Ray &r, Intersection *si) const {
    double rx = r.origin.x;
    double ry = r.origin.y;
    double rz = r.origin.z;

    double dx = r.direction.x;
    double dy = r.direction.y;
    double dz = r.direction.z;

    // if ray is parallel to slab
    if (dx == 0) {
        // if ray is not inside the slab
        if ((a.x > rx && b.x > rx) ||
            (a.x < rx && b.x < rx))
            // miss
            return false;
    }

    // analogous
    if (dy == 0) {
        if ((a.y > ry && b.y > ry) ||
            (a.y < ry && b.y < ry))
            return false;
    }

    // analogous
    if (dz == 0) {
        if ((a.z > rz && b.z > rz) ||
            (a.z < rz && b.z < rz))
            return false;
    }

    double idx = 1.0 / dx;
    double idy = 1.0 / dy;
    double idz = 1.0 / dz;
    double t_xmin, t_xmax;
    double t_ymin, t_ymax;
    double t_zmin, t_zmax;

    if (idx >= 0) {
        t_xmin = (this->a.x - rx) * idx;
        t_xmax = (this->b.x - rx) * idx;
    } else {
        t_xmax = (this->a.x - rx) * idx;
        t_xmin = (this->b.x - rx) * idx;
    }

    if (idy >= 0) {
        t_ymin = (this->a.y - ry) * idy;
        t_ymax = (this->b.y - ry) * idy;
    } else {
        t_ymax = (this->a.y - ry) * idy;
        t_ymin = (this->b.y - ry) * idy;
    }

    if (idz >= 0) {
        t_zmin = (this->a.z - rz) * idz;
        t_zmax = (this->b.z - rz) * idz;
    } else {
        t_zmax = (this->a.z - rz) * idz;
        t_zmin = (this->b.z - rz) * idz;
    }

    double t1, t2;
    Face face;

    if (t_xmin > t_ymin) {
        face = (idx >= 0.0) ? Negative_X : Positive_X;
        t1 = t_xmin;
    } else {
        face = (idy >= 0.0) ? Negative_Y : Positive_Y;
        t1 = t_ymin;
    }

    if (t_zmin > t1) {
        face = (idz >= 0.0) ? Negative_Z : Positive_Z;
        t1 = t_zmin;
    }

    if (t_xmax < t_ymax) {
        t2 = t_xmax;
    } else {
        t2 = t_ymax;
    }

    if (t_zmax < t2) {
        t2 = t_zmax;
    }

    if (t1 < t2 && t1 > kEpsilon) {
        if (si) {
            si->hit_point = r.origin + t1 * r.direction;
            si->normal = get_normal(face);
            si->distance = t1;
            si->shape = this;
            si->ray = r;
        }

        return true;
    } else {
        return false;
    }
}

} // namespace Sol

