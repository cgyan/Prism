#include <prism/Rect>

PRISM_BEGIN_NAMESPACE

Rect::Rect()
:   m_topLeft{Point(0,0)},
    m_bottomRight{Point(0,0)}
{}

Rect::Rect(const Point& topLeft, const Size& size)
:   m_topLeft{topLeft},
    m_bottomRight{Point(topLeft.x() + size.width(), topLeft.y() + size.height())}
{}

Point
Rect::centre() const {
    return Point(0,0);
}

const int
Rect::x() const {
    return m_topLeft.x();
}

const int
Rect::y() const {
    return m_topLeft.y();
}

const int
Rect::top() const {
    return m_topLeft.y();
}

const int
Rect::right() const {
    return m_topLeft.x() + width();
}

const int
Rect::bottom() const {
    return m_topLeft.y() + height();
}

const int
Rect::left() const {
    return m_topLeft.x();
}

Point
Rect::topLeft() const {
    return m_topLeft;
}

Point
Rect::topRight() const {
    return Point(right(), top());
}

Point
Rect::bottomLeft() const {
    return Point(left(), bottom());
}

Point
Rect::bottomRight() const {
    return Point(right(), bottom());
}

void
Rect::setTopLeft(const Point& pos) {
    m_topLeft = pos;

}

void
Rect::setTopRight(const Point& pos) {
    m_topLeft.setY(pos.y());
    m_bottomRight.setX(pos.x());
}

void
Rect::setBottomRight(const Point& pos) {
    m_bottomRight = pos;
}

void
Rect::setBottomLeft(const Point& pos) {
    m_topLeft.setX(pos.x());
    m_bottomRight.setY(pos.y());
}

const int
Rect::width() const {
    return m_bottomRight.x() - m_topLeft.x();
}

const int
Rect::height() const {
    return m_bottomRight.y() - m_topLeft.y();
}

Size
Rect::size() const {
    return Size(width(), height());
}

PRISM_END_NAMESPACE
