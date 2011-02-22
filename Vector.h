#include <iostream>

#ifndef SOL_VECTOR_H
#define SOL_VECTOR_H

namespace Sol {

class Vector {

private:
    double x, y, z;

public:
    Vector();
    Vector(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    Vector operator+(const Vector &v) const;
    Vector operator*(const double r) const;
    Vector operator/(const double r) const;
    double dot(const Vector &v) const;
    Vector cross(const Vector &v) const;
    double angle(const Vector &v) const;

    Vector& operator+=(const Vector &v);
    Vector& operator*=(const double r);
    Vector& operator/=(const double r);

    Vector& operator=(const Vector &v);

    void normalise();
    Vector normalised() const;

    double length() const;
};

} // namespace Sol

std::ostream& operator<<(std::ostream& o, const Sol::Vector &v);

#endif // SOL_VECTOR_H

