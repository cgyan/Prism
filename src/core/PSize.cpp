#include <prism/PSize>
#include <prism/DivideByZeroException>

PRISM_BEGIN_NAMESPACE

struct SizeData {
    int width;
    int height;
};

PSize::PSize(const int width, const int height)
:   d{new SizeData}
 {
    set(width, height);
}

PSize::~PSize() {
    //
}

const int
PSize::width() const {
    return d->width;
}

const int
PSize::height() const {
    return d->height;
}

void
PSize::setWidth(const int width) {
    d->width = width;
}

void
PSize::setHeight(const int height) {
    d->height = height;
}

void
PSize::set(const int width, const int height) {
    setWidth(width);
    setHeight(height);
}

void
PSize::reset() {
    *this = PSize();
}

const bool
PSize::isReset() const {
    return width() == 0 && height() == 0;
}

const bool
PSize::isValid() const {
    return width() >= 0 && height() >= 0;
}

void
PSize::transpose() {
    PSize copy = *this;
    set(copy.d->height, copy.d->width);
}

PSize
PSize::transposed() const {
    return PSize(d->height, d->width);
}

void
PSize::scale(const int widthFactor, const int heightFactor) {
    set(width() * widthFactor, height() * heightFactor);
}

void
PSize::scale(const PSize& size) {
    set(width() * size.width(), height() * size.height());
}

PSize
PSize::scaled(const int widthFactor, const int heightFactor) const {
    return PSize(width() * widthFactor, height() * heightFactor);
}

PSize
PSize::scaled(const PSize& size) const {
    return PSize(width() * size.width(), height() * size.height());
}

PSize&
PSize::operator+=(const PSize& rhs) {
    set(width() + rhs.width(), height() + rhs.height());
    return *this;
}

PSize&
PSize::operator-=(const PSize& rhs) {
    set(width() - rhs.width(), height() - rhs.height());
    return *this;
}

PSize&
PSize::operator*=(const PSize& rhs) {
    set(width() * rhs.width(), height() * rhs.height());
    return *this;
}

PSize&
PSize::operator/=(const PSize& rhs) {
    if (rhs.width() == 0 || rhs.height() == 0)
        throw DivideByZeroException();
    set(width() / rhs.width(), height() / rhs.height());
    return *this;
}

const bool
operator==(const PSize& lhs, const PSize& rhs) {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

const bool
operator!=(const PSize& lhs, const PSize& rhs) {
    return !(lhs == rhs);
}

PSize
operator+(const PSize& lhs, const PSize& rhs) {
    return PSize(lhs.width() + rhs.width(), lhs.height() + rhs.height());
}

PSize
operator-(const PSize& lhs, const PSize& rhs) {
    return PSize(lhs.width() - rhs.width(), lhs.height() - rhs.height());
}

PSize
operator*(const PSize& size, const int factor) {
    return PSize(size.width() * factor, size.height() * factor);
}

PSize
operator*(const int factor, const PSize& size) {
    return size * factor;
}

PSize
operator/(const PSize& size, const int factor) {
    if (factor == 0)
        throw DivideByZeroException();
    return PSize(size.width() / factor, size.height() / factor);
}

PRISM_END_NAMESPACE
