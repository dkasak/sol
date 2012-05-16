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

#include "Sphere.h"

namespace Sol {

const double kEpsilon = 0.001;

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
    Vector o = r.origin - this->origin;
    double a = r.direction.dot(r.direction);
    double b = o.dot(r.direction) * 2.0;
    double c = o.dot(o) - this->radius * this-> radius;
    double d = b * b - 4.0 * a * c;

    double t = 0.0;

    if (d < 0.0) {
        return false;
    } else {
        double sd = sqrt(d);
        double den = 2.0 * a;

        if (((t = (-b + sd) / den) > kEpsilon) ||
            ((t = (-b - sd) / den) > kEpsilon)) {
            si->normal = (o + t * r.direction).normalised();
            si->hitpoint = r.origin + t * r.direction;
            *distance = t;
            return true;
        } else {
            return false;
        }
    }
}

} // namespace Sol

