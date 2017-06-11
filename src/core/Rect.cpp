#include <prism/Rect>
#include <prism/Point>
#include <prism/Size>
#include <prism/algorithm>
#include <ostream>

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

void
Rect::set(const Point& topLeft, const Size& size) {
    *this = Rect(topLeft, size);
}

void
Rect::set(const int x, const int y, const int width, const int height) {
    *this = Rect(x,y,width,height);
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

void
Rect::setX(const int x) {
    moveLeft(x);
}

void
Rect::setY(const int y) {
    moveTop(y);
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
Rect::setTop(const int y) {
    d->topLeft.setY(y);
}

void
Rect::setRight(const int x) {
    d->bottomRight.setX(x);
}

void
Rect::setBottom(const int y) {
    d->bottomRight.setY(y);
}

void
Rect::setLeft(const int x) {
    d->topLeft.setX(x);
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
Rect::moveCentre(const Point & pos) {
    moveLeft(10);
    moveTop(10);
}

void
Rect::moveCentre(const int x, const int y) {
    moveCentre(Point(x,y));
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
    d->bottomRight.rx() += offset;
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
Rect::setWidth(const int width) {
    setSize(width, this->height());
}

void
Rect::setHeight(const int height) {
    setSize(this->width(), height);
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
    if (precise)
        return this->adjusted(1,1,-1,-1).contains(pos);

    return pos.x() >= this->left() && pos.x() <= this->right() &&
        pos.y() >= this->top() && pos.y() <= this->bottom();
}

const bool
Rect::contains(const int x, const int y, const bool precise) const {
    return contains(Point(x,y), precise);
}

const bool
Rect::contains(const Rect& rect, const bool precise) const {
    return this->contains(rect.topLeft(), precise)
        && this->contains(rect.bottomRight(), precise);
}

Rect
Rect::transposed() const {
    Rect r;
    r.setSize(height(), width());
    r.setTopLeft(this->topLeft());
    return r;
}

Rect
Rect::normalised() const {
    Rect copy = *this;
    if (copy.width() < 0)
        copy.setWidth(width() * -1);
    if (copy.height() < 0)
        copy.setHeight(height() * -1);
    return copy;
}

void
Rect::translate(const int dx, const int dy) {
    d->topLeft.rx() += dx;
    d->topLeft.ry() += dy;
    d->bottomRight.rx() += dx;
    d->bottomRight.ry() += dy;
}

void
Rect::translate(const Point& offset) {
    translate(offset.x(), offset.y());
}

Rect
Rect::translated(const int dx, const int dy) const {
    Rect copy = *this;
    copy.translate(dx,dy);
    return copy;
}

Rect
Rect::translated(const Point& offset) const {
    Rect copy = *this;
    copy.translate(offset);
    return copy;
}

Rect
Rect::united(const Rect& r1, const Rect& r2) {
    if (r1.contains(r2)) return r1;
    else if (r2.contains(r1)) return r2;

    Rect r;
    r.setLeft(prism::min(r1.left(), r2.left()));
    r.setTop(prism::min(r1.top(), r2.top()));
    r.setRight(prism::max(r1.right(), r2.right()));
    r.setBottom(prism::max(r1.bottom(), r2.bottom()));
    return r;
}

const bool
Rect::intersects(const Rect& r) const {
    if (this->left() < r.right() &&
            this->right() > r.left() &&
            this->top() < r.bottom() &&
            this->bottom() > r.top()) {
        return true;
    }
    return false;
}

Rect
Rect::intersected(const Rect& r1, const Rect& r2) {
    Rect ret;
    if (r1.intersects(r2)) {
		ret.setLeft(prism::max(r1.left(),r2.left()));
		ret.setRight(prism::min(r1.right(),r2.right()));
		ret.setBottom(prism::min(r1.bottom(),r2.bottom()));
		ret.setTop(prism::max(r1.top(),r2.top()));
        return ret;
    }
    return r1;
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
