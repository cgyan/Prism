#include <prism/h/Point.h>
#include <math.h>
#include <iostream>

namespace prism {

/**
 * Default constructor
 */
Point::Point(void)
	: m_x(0), m_y(0)
{}

/**
 * Constructor override
 */
Point::Point(const int x, const int y)
	: m_x(x), m_y(y)
{}

/**
 *
 */
Point::Point(const Point & copy) {
	std::cout << "[Point::Point(copy)]\n";
	m_x = copy.m_x;
	m_y = copy.m_y;
}

/**
 * Virtual destructor
 */
Point::~Point(void)
{}

/**
 * Resets this point back to x=y=0
 */
void Point::reset() {
	m_x = m_y = 0;
}

/**
 * Returns true if x=0 and y=0, false if not
 */
const bool Point::isReset() const {
	return (m_x == 0) && (m_y == 0);
}

/**
 * Convenience method that sets x and y simultaineously
 */
void Point::set(const int x, const int y) {
	m_x = x;
	m_y = y;
}

/**
 * Sets the x component
 */
void Point::setX(const int x) {
	set(x, m_y);
}

/**
 * Sets the y component
 */
void Point::setY(const int y) {
	set(m_x, y);
}

/**
 * Returns the x component
 */
const int Point::x() const {
	return m_x;
}

/**
 * Returns the y component
 */
const int Point::y() const {
	return m_y;
}

/**
 * Returns a reference to the x component allowing direct manipulation
 * i.e. point.rx() += 5
 */
int & Point::rx() {
	return m_x;
}

/**
 * Returns a reference to the y component allowing direct manipulation
 * i.e. point.ry() += 5
 */
int & Point::ry() {
	return m_y;
}

/**
 *
 */
Point & Point::operator=(const Point & p) {
	std::cout << "[Point::operator=(other)]\n";
	if (*this != p) {
		m_x = p.m_x;
		m_y = p.m_y;
	}
	return *this;
}

/**
 * Returns a reference to this point after adding p to it
 */
Point & Point::operator+=(const Point & p) {
	m_x += p.m_x;
	m_y += p.m_y;
	return *this;
}

/**
 * Returns a reference to this point after subtracting p from it
 */
Point & Point::operator-=(const Point & p) {
	m_x -= p.m_x;
	m_y -= p.m_y;
	return *this;
}

/**
 * Multiplies this point's components by the given factor 
 * and returns a reference to this point.
 * Note: the x and y components are rounded to the nearest integer as they are stored as ints internally.
 * Use Pointf for floating point accuracy instead.
 */
Point & Point::operator*=(const float factor) {
	m_x *= factor;
	m_y *= factor;
	return *this;
}

/**
 * Multiplies this point's coordinates by the given factor 
 * and returns a reference to this point.
 */
Point & Point::operator*=(const int factor) {
	m_x *= factor;
	m_y *= factor;
	return *this;
}

/**
 * Multiplies this point's coordinates by the given factor 
 * and returns a reference to this point
 * Note: the x and y components are rounded to the nearest integer as they are stored as ints internally.
 * Use Pointf for floating point accuracy instead.
 */
Point & Point::operator/=(const float divisor) {
	if (divisor == 0) {
		this->reset();
	}
	else {
		m_x /= divisor;
		m_y /= divisor;
	}
	return *this;
}

/**
 * Divides this point's coordinates by the given factor 
 * and returns a reference to this point.
 * Note: the x and y components are rounded to the nearest integer as they are stored as ints internally.
 * Use Pointf for floating point accuracy instead.
 */
Point & Point::operator/=(const int divisor) {
	if (divisor == 0) {
		this->reset();
	}
	else {
		m_x /= divisor;
		m_y /= divisor;
	}
	return *this;
}

// ============================================================
// Related non-members
// ============================================================
/**
 * Returns an ostream object that allows this object to printed with std::cout
 */
std::ostream & operator<<(std::ostream & out, const Point & p) {
	out << "Point: " << &p << " [x: " << p.m_x << " y: " << p.m_y << "]"; 
	return out;
}

/** 
 * Returns a Point object that is the sum of the components of p1 and p2
 */
Point operator+(const Point & p1, const Point & p2) {
	return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

/** 
 * Returns a Point object that is formed by subtracting the components of p2 from p1
 */
Point operator-(const Point & p1, const Point & p2) {
	return Point(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

/**
 * Returns a Point object that is formed by multiplying the components of p by the int factor
 */
Point operator*(const Point & p, const int factor) {
	return Point(p.m_x * factor, p.m_y * factor);
}

/**
 * Returns a Point object that is formed by multiplying the components of p by the float factor
 * Note: the x and y components are rounded to the nearest integer as they are stored as ints internally.
 * Use Pointf for floating point accuracy instead.
 */
Point operator*(const Point & p, const float factor) {
	return Point(p.m_x * factor, p.m_y * factor);
}

/**
 * Returns a Point object that is formed by multiplying the components of p by the int factor
 */
Point operator*(const int factor, const Point & p) {
	return p*factor;
}

/**
 * Returns a Point object that is formed by multiplying the components of p by the float factor
 * Note: the x and y components are rounded to the nearest integer as they are stored as ints internally.
 * Use Pointf for floating point accuracy instead.
 */
Point operator*(const float factor, const Point & p) {
	return p*factor;
}

/**
 * Returns a Point object that is formed by dividing the components of p1 by the components of p2
 */
Point operator/(const Point & p, const float divisor) {
	if (divisor == 0) return Point();
	return Point(p.m_x / divisor, p.m_y / divisor);
}

/**
 * Returns true if x and y of p1 and p2 are equal, false if not
 */
bool operator==(const Point & p1, const Point & p2) {
	return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
}

/**
 * Returns true if x or y of p1 and p2 are not equal, false if not
 */
bool operator!=(const Point & p1, const Point & p2) {
	return (p1.m_x != p2.m_x) || (p1.m_y != p2.m_y);
}

}
