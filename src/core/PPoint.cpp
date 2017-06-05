#include <prism/PPoint>

PRISM_BEGIN_NAMESPACE

PPoint::PPoint(const int x, const int y)
:   m_x{x}, m_y{y}
{}

const int
PPoint::x() const {
    return m_x;
}

void
PPoint::setX(const int x) {
    m_x = x;
}

const int
PPoint::y() const {
    return m_y;
}

void
PPoint::setY(const int y) {
    m_y = y;
}

void
PPoint::set(const int x, const int y) {
    setX(x);
    setY(y);
}

void
PPoint::reset() {
    *this = PPoint();
}

const bool
operator==(const PPoint& lhs, const PPoint& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

const bool
operator!=(const PPoint& lhs, const PPoint& rhs) {
    return !(lhs == rhs);
}

PRISM_END_NAMESPACE
