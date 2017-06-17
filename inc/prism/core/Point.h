#ifndef PRISM_POINT_H_
#define PRISM_POINT_H_

#include <prism/global>
#include <memory>
#include <ostream>

PRISM_BEGIN_NAMESPACE

struct PointData;

class Point {
public:
    explicit Point(const int x=0, const int y=0);
    Point(const Point& copy);
    Point& operator=(const Point& rhs);

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
private:
    using PointDataPtr = std::shared_ptr<PointData>;
    PointDataPtr impl;
};

const bool operator==(const Point& lhs, const Point& rhs);
const bool operator!=(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& p, const int factor);
Point operator*(const int factor, const Point& p);
Point operator/(const Point& p, const int divisor);
std::ostream& operator<<(std::ostream& out, const Point& p);

PRISM_END_NAMESPACE

#endif // PRISM_POINT_H_
