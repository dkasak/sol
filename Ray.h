#ifndef SOL_RAY_H
#define SOL_RAY_H

namespace Sol {

class Ray {

private:
    Point  point;
    Vector direction;

public:
    Ray();
    Ray(const Point &p, const Vector &d);
    Ray(const Ray &r);

    virtual bool intersects(const Shape &s) const;
};

} // namespace Sol

#endif // SOL_RAY_H

