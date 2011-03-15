#ifndef SOL_RAY_H
#define SOL_RAY_H

namespace Sol {

// Default constructor
// Creates a ray from mathematical origin along the x axis
Ray::Ray() {
    this->point = Point();
    this->direction = Vector(1, 0, 0);
}

Ray(const Point &p, const Vector &d) {
    this->point = p;
    this->direction = d;
}

Ray(const Ray &r) {
    this->point = r->point;
    this->direction = r->direction;
}

virtual bool intersects(const Shape &s) const {
    return s.intersects(this);
};

} // namespace Sol

#endif // SOL_RAY_H

