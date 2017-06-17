#include <prism/Size>
#include <prism/DivideByZeroException>
#include <ostream>

PRISM_BEGIN_NAMESPACE

struct SizeData {
    int width;
    int height;
};

Size::Size(const int width, const int height)
:   d{new SizeData}
 {
    set(width, height);
}

Size::~Size() {
    //
}

const int
Size::width() const {
    return d->width;
}

const int
Size::height() const {
    return d->height;
}

void
Size::setWidth(const int width) {
    d->width = width;
}

void
Size::setHeight(const int height) {
    d->height = height;
}

void
Size::set(const int width, const int height) {
    setWidth(width);
    setHeight(height);
}

void
Size::reset() {
    *this = Size();
}

const bool
Size::isReset() const {
    return width() == 0 && height() == 0;
}

const bool
Size::isValid() const {
    return width() >= 0 && height() >= 0;
}

void
Size::transpose() {
    Size copy = *this;
    set(copy.d->height, copy.d->width);
}

Size
Size::transposed() const {
    return Size(d->height, d->width);
}

void
Size::scale(const int widthFactor, const int heightFactor) {
    set(width() * widthFactor, height() * heightFactor);
}

void
Size::scale(const Size& size) {
    set(width() * size.width(), height() * size.height());
}

Size
Size::scaled(const int widthFactor, const int heightFactor) const {
    return Size(width() * widthFactor, height() * heightFactor);
}

Size
Size::scaled(const Size& size) const {
    return Size(width() * size.width(), height() * size.height());
}

Size&
Size::operator+=(const Size& rhs) {
    set(width() + rhs.width(), height() + rhs.height());
    return *this;
}

Size&
Size::operator-=(const Size& rhs) {
    set(width() - rhs.width(), height() - rhs.height());
    return *this;
}

Size&
Size::operator*=(const int factor) {
    set(width() * factor, height() * factor);
    return *this;
}

Size&
Size::operator/=(const int factor) {
    if (factor == 0)
        throw DivideByZeroException();
    set(width() / factor, height() / factor);
    return *this;
}

const bool
operator==(const Size& lhs, const Size& rhs) {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

const bool
operator!=(const Size& lhs, const Size& rhs) {
    return !(lhs == rhs);
}

Size
operator+(const Size& lhs, const Size& rhs) {
    return Size(lhs.width() + rhs.width(), lhs.height() + rhs.height());
}

Size
operator-(const Size& lhs, const Size& rhs) {
    return Size(lhs.width() - rhs.width(), lhs.height() - rhs.height());
}

Size
operator*(const Size& size, const int factor) {
    return Size(size.width() * factor, size.height() * factor);
}

Size
operator*(const int factor, const Size& size) {
    return size * factor;
}

Size
operator/(const Size& size, const int factor) {
    if (factor == 0)
        throw DivideByZeroException();
    return Size(size.width() / factor, size.height() / factor);
}

std::ostream&
operator<<(std::ostream& out, const Size& s) {
    out << "Size [" << &s << "] \n" <<
        "\twidth: " << s.width() << "\n "<<
        "\theight: " << s.height();
    return out;
}

PRISM_END_NAMESPACE
