#ifndef SOL_SHAPE_H
#define SOL_SHAPE_H

namespace Sol {

class Shape {

public:
    virtual bool intersects(const Shape &s) const = 0;
    virtual bool intersects(const Vector &v) const = 0;
};

} // namespace Sol

#endif // SOL_SHAPE_H

