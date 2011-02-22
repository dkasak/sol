#ifndef SOL_POINT_H
#define SOL_POINT_H

namespace Sol {

struct Point {
    double x, y, z;

    Point() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

} // namespace Sol

#endif // SOL_POINT_H

