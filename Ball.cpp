#include "Ball.h"

namespace Sol {

Ball::Ball() {
    this->radius = 0.0;
}

Ball::Ball(double r) {
    this->radius = r;
}

Ball::Ball(Point p, double r) {
    this->origin = p;
    this->radius = r;
}

void Ball::setRadius(double r) {
    this->radius = r;
}

double Ball::getRadius() const {
    return this->radius;
}

virtual bool Ball::intersects(const Vector &v) const {

}

} // namespace Sol
