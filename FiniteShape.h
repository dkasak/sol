#ifndef SOL_FINITESHAPE_H
#define SOL_FINITESHAPE_H

namespace Sol {

class FiniteShape : public Shape {

private:
    Point origin;

public:
    FiniteShape();
    FiniteShape(double x, double y, double z);
    move(double x, double y, double z);

    virtual bool intersects(const Shape &s) const = 0;
    virtual bool intersects(const Vector &v) const = 0;
};

} // namespace Sol

#endif // SOL_FINITESHAPE_H

