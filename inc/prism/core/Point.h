#ifndef PRISM_POINT_H_
#define PRISM_POINT_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

struct PointImpl;

class Point {
private:
    using PointImplPtr = std::shared_ptr<PointImpl>;
    PointImplPtr impl;
public:
    Point(const int x=0, const int y=0);

    const int x() const;
    const int y() const;

    void setX(const int x);
    void setY(const int y);

    int& rx();
    int& ry();

    void set(const int x, const int y);
    void reset();
    const bool isReset() const;

    Point& operator+=(const Point& rhs);
    Point& operator-=(const Point& rhs);
    Point& operator*=(const int factor);
    Point& operator/=(const int divisor);
};

const bool operator==(const Point& lhs, const Point& rhs);
const bool operator!=(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& p, const int factor);
Point operator*(const int factor, const Point& p);
Point operator/(const Point& p, const int divisor);

PRISM_END_NAMESPACE

#endif // PRISM_POINT_H_
