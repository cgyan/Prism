#include <prism/Point>
#include <prism/DivideByZeroException>

PRISM_BEGIN_NAMESPACE

struct PointData {
    int x{0};
    int y{0};
};

Point::Point(const int x, const int y)
:   impl{new PointData}
{
    impl->x = x;
    impl->y = y;
}

Point::Point(const Point& copy)
:   impl{new PointData}
{
    impl->x = copy.x();
    impl->y = copy.y();
}

Point&
Point::operator=(const Point& rhs) {
    impl.reset(new PointData);
    impl->x = rhs.x();
    impl->y = rhs.y();
    return *this;
}

const int
Point::x() const {
    return impl->x;
}

void
Point::setX(const int x) {
    impl->x = x;
}

const int
Point::y() const {
    return impl->y;
}

void
Point::setY(const int y) {
    impl->y = y;
}

void
Point::set(const int x, const int y) {
    setX(x);
    setY(y);
}

void
Point::reset() {
    *this = Point();
}

const bool
Point::isReset() const {
    return x() == 0 && y() == 0;
}

int&
Point::rx() {
    return impl->x;
}

int&
Point::ry() {
    return impl->y;
}

Point&
Point::operator+=(const Point& rhs) {
    rx() += rhs.x();
    ry() += rhs.y();
    return *this;
}

Point&
Point::operator-=(const Point& rhs) {
    rx() -= rhs.x();
    ry() -= rhs.y();
    return *this;
}

Point&
Point::operator*=(const int factor) {
    rx() *= factor;
    ry() *= factor;
    return *this;
}

Point&
Point::operator/=(const int divisor) {
    if (divisor == 0)
        throw DivideByZeroException();

    rx() /= divisor;
    ry() /= divisor;
    return *this;
}

const bool
operator==(const Point& lhs, const Point& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

const bool
operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

Point
operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

Point
operator-(const Point& lhs, const Point& rhs) {
    return Point(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

Point
operator*(const Point& p, const int factor) {
    return Point(p.x() * factor, p.y() * factor);
}

Point
operator*(const int factor, const Point& p) {
    return p * factor;
}

Point
operator/(const Point& p, const int divisor) {
    if (divisor == 0)
        throw DivideByZeroException();
    return Point(p.x() / divisor, p.y() / divisor);
}

std::ostream&
operator<<(std::ostream& out, const Point& p) {
    out << "Point [" << &p << "] x: " << p.x() << " y: " << p.y();
    return out;
}

PRISM_END_NAMESPACE
