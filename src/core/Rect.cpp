#include <prism/Rect>
#include <prism/Point>
#include <prism/Size>
#include <cassert>

PRISM_BEGIN_NAMESPACE

struct RectData {
    Point topLeft;
    Point bottomRight;
};

Rect::Rect()
:   d{new RectData}
{}

Rect::Rect(const int x, const int y, const int width, const int height)
:   d{new RectData}
{
    d->topLeft.set(x,y);
    d->bottomRight.set(x + width, y + height);
}

Rect::Rect(const Point& topLeft, const Point& bottomRight)
:   d{new RectData}
{
    d->topLeft = topLeft;
    d->bottomRight = bottomRight;
}

Rect::Rect(const Point& topLeft, const Size& size)
:   d{new RectData}
{
    d->topLeft = topLeft;
    d->bottomRight = Point(topLeft.x() + size.width(), topLeft.y() + size.height());
}

Rect::Rect(const Rect& copy)
:   d{new RectData}
{
    d->topLeft = copy.topLeft();
    d->bottomRight = copy.bottomRight();
}

Rect&
Rect::operator=(const Rect& rhs) {
    d.reset(new RectData);
    d->topLeft = rhs.topLeft();
    d->bottomRight = rhs.bottomRight();
    return *this;
}

Point
Rect::centre() const {
    const int x = left() + (width() / 2);
    const int y = top() + (height() / 2);
    return Point(x,y);
}

const int
Rect::x() const {
    return d->topLeft.x();
}

const int
Rect::y() const {
    return d->topLeft.y();
}

const int
Rect::top() const {
    return d->topLeft.y();
}

const int
Rect::right() const {
    return d->topLeft.x() + width();
}

const int
Rect::bottom() const {
    return d->topLeft.y() + height();
}

const int
Rect::left() const {
    return d->topLeft.x();
}

Point
Rect::topLeft() const {
    return d->topLeft;
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
    d->topLeft = pos;

}

void
Rect::setTopRight(const Point& pos) {
    d->topLeft.setY(pos.y());
    d->bottomRight.setX(pos.x());
}

void
Rect::setBottomRight(const Point& pos) {
    d->bottomRight = pos;
}

void
Rect::setBottomLeft(const Point& pos) {
    d->topLeft.setX(pos.x());
    d->bottomRight.setY(pos.y());
}

void
Rect::adjust(const int dx1, const int dy1, const int dx2, const int dy2) {
    d->topLeft.rx() += dx1;
    d->topLeft.ry() += dy1;
    d->bottomRight.rx() += dx2;
    d->bottomRight.ry() += dy2;
}

Rect
Rect::adjusted(const int dx1, const int dy1, const int dx2, const int dy2) const {
    Rect copy = *this;
    copy.adjust(dx1, dy1, dx2, dy2);
    return copy;
}

void
Rect::moveTop(const int y) {
    d->topLeft.ry() += y;
    d->bottomRight.ry() += y;
}

void
Rect::moveRight(const int x) {
    const int offset = x - right();
    d->topLeft.rx() += offset;
    d->bottomRight.rx() += offset;
}

void
Rect::moveBottom(const int y) {
    const int offset = y - bottom();
    d->topLeft.ry() += offset;
    d->bottomRight.ry() += offset;
}

void
Rect::moveLeft(const int x) {
    const int offset = x - left();
    d->topLeft.rx() += offset;
    d->bottomRight.ry() += offset;
}

void
Rect::moveTopLeft(const Point& pos) {
    moveTop(pos.y());
    moveLeft(pos.x());
}

void
Rect::moveTopRight(const Point& pos) {
    moveTop(pos.y());
    moveRight(pos.x());
}

void
Rect::moveBottomRight(const Point& pos) {
    moveBottom(pos.y());
    moveRight(pos.x());
}

void
Rect::moveBottomLeft(const Point& pos) {
    moveBottom(pos.y());
    moveLeft(pos.x());
}

const int
Rect::width() const {
    return d->bottomRight.x() - d->topLeft.x();
}

const int
Rect::height() const {
    return d->bottomRight.y() - d->topLeft.y();
}

void
Rect::setSize(const int width, const int height) {
    d->bottomRight.rx() = left() + width;
    d->bottomRight.ry() = top() + height;
}

Size
Rect::size() const {
    return Size(width(), height());
}

const bool
Rect::isNull() const {
    return width() == 0 && height() == 0;
}

const bool
Rect::isValid() const {
    return width() >= 0 && height() >= 0;
}

const bool
Rect::contains(const Point& pos, const bool precise) const {
    if (precise) {
        return pos.x() > this->left() && pos.x() < this->right() &&
            pos.y() > this->top() && pos.y() < this->bottom();
    }
    return pos.x() >= this->left() && pos.x() <= this->right() &&
        pos.y() >= this->top() && pos.y() <= this->bottom();
}

const bool
Rect::contains(const int x, const int y) const {
    return x >= this->left() && x <= this->right() &&
        y >= this->top() && y <= this->bottom();
}

const bool
operator==(const Rect& lhs, const Rect& rhs) {
    return lhs.topLeft() == rhs.topLeft() && lhs.bottomRight() == rhs.bottomRight();
}

const bool
operator!=(const Rect& lhs, const Rect& rhs) {
    return !(lhs == rhs);
}

std::ostream&
operator<<(std::ostream& out, const Rect& r) {
    out << "Rect [" << &r << "] top left: " << r.topLeft() << " bottom right: " << r.bottomRight();
    return out;
}

PRISM_END_NAMESPACE
