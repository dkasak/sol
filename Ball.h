#ifndef SOL_BALL_H
#define SOL_BALL_H

namespace Sol {

class Ball : public FiniteShape {

    private:
        double radius;

    public:
        Ball();
        Ball(double r);
        Ball(Point p, double r);
        void setRadius(double r);
        double getRadius() const;

        virtual bool intersects(const Shape &s) const;
        virtual bool intersects(const Vector &v) const;
};

} // namespace Sol

#endif // SOL_BALL_H
