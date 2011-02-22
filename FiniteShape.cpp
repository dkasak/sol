#include "FiniteShape.h"

namespace Sol {

FiniteShape::FiniteShape() {}

FiniteShape::FiniteShape(double x, double y, double z) : origin(x, y, z) {}

FiniteShape::move(double x, double y, double z) {
    this->origin.x = x;
    this->origin.y = y;
    this->origin.z = z;
}

} // namespace Sol

