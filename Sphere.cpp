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
#include "Sphere.h"
#include "Debug.h"
using namespace std;
namespace Sol {

const double kEpsilon = 0.01;

Sphere::Sphere() {
    this->radius = 0.0;
}

Sphere::Sphere(double r) {
    this->radius = r;
}

Sphere::Sphere(Point p, double r) {
    this->origin = p;
    this->radius = r;
}

void Sphere::setRadius(double r) {
    this->radius = r;
}

double Sphere::getRadius() const {
    return this->radius;
}

bool Sphere::intersects(const Ray &r, double *distance, ShadeInfo *si) const {
    Vector o(this->origin.x, this->origin.y, this->origin.z);
    Vector ro(r.origin.x, r.origin.y, r.origin.z);
    Vector dir = r.direction.normalised();
    double a = 1;
    double b = 2 * (ro - o).dot(dir);
    double c = (ro - o).dot(ro - o) - pow(this->radius, 2.0);
    double d = b * b - 4 * c;

    DEBUG(2, "[sphere]");
    DEBUG(4, "  ray origin:", ro);
    DEBUG(4, "  origin:", o);
    DEBUG(4, "  b:", b);
    DEBUG(4, "  d:", d);
    DEBUG(4, "  c:", c);
    DEBUG(4, "  ray direction:", dir);
    if (d < 0.0) {
        return false;
    } else {
        double sd = sqrt(d);
        double den = 2;
        double t, t1, t2;

        t1 = (-b + sd) / den;
        t2 = (-b - sd) / den;
        if (t1 < 0 && t2 < 0) {
            return false;
        } else if (t1 < t2 && t1 > 0) {
            t = t1;
        } else {
            t = t2;
        }

        si->hitpoint = r.origin + t * dir;
        si->normal = (si->hitpoint - this->origin).normalised();

        DEBUG(2, "  -> hit");
        DEBUG(4, "    distance:", t);
        DEBUG(4, "    hitpoint:", si->hitpoint);
        DEBUG(4, "    normal:", si->normal);
        *distance = t;
        return true;
    }
}

} // namespace Sol

