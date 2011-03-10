#ifndef SOL_SPHERE_H
#define SOL_SPHERE_H

namespace Sol {

class Sphere : public FiniteShape {

private:
    double radius;

public:
    Sphere();
    Sphere(double r);
    Sphere(Point p, double r);
    void setRadius(double r);
    double getRadius() const;

    virtual bool intersects(const Shape &s) const;
    virtual bool intersects(const Vector &v) const;
};

} // namespace Sol

#endif // SOL_SPHERE_H

