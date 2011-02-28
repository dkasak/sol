#ifndef SOL_LINE_H
#define SOL_LINE_H

namespace Sol {

class Line : public Shape {

private:
    Point  point;
    Vector direction;

public:
    Line();
    Line(const Point &p, const Vector &d);
    Line(const Line &l);

    virtual bool intersects(const Shape &s) const;
};

} // namespace Sol

#endif // SOL_LINE_H

