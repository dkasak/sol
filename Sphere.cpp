#include "Sphere.h"

namespace Sol {

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

virtual bool Sphere::intersects(const Vector &v) const {

}

} // namespace Sol

