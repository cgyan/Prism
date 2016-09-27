#include <prism/h/Vector2.h>
#include <prism/h/Vector3.h>
#include <prism/h/Vector4.h>
#include <prism/h/Point.h>
#include <cmath>
#include <iostream>

namespace prism {
/**
 * Constructs a default Vector2 setting it to a zero vector i.e. x=y=0.
 */
Vector2::Vector2(void)
	: m_x(0), m_y(0)
{ std::cout << "[Vector2::Vector2()] " << this << std::endl;
}

/**
 * Constructs a Vector2 from the x and y floats passed in.
 */
Vector2::Vector2(const float x, const float y)
	: m_x(x), m_y(y)
{
	std::cout << "[Vector2::Vector2()] " << this << std::endl;
}

/**
 *
 */
Vector2::Vector2(const Vector2 & v) {
	std::cout << "[Vector2::Vector2()] " << this << std::endl;
	copyDataFromSourceToDestination(v, *this);
}

/**
 * Constructs a Vector2 from the x and y components of Vector3 whilst it drops the z component.
 */
Vector2::Vector2(const Vector3 & v) {
	m_x = v.x();
	m_y = v.y();
}

/**
 * Constructs a Vector2 from the x and y components of Vector4 whilst it drops the z and w components.
 */
Vector2::Vector2(const Vector4 & v) {
	m_x = v.x();
	m_y = v.y();
}

/**
 * Constructs a Vector2 from a 2d Point.
 */
Vector2::Vector2(const Point & p) 
	: m_x((float)p.x()), m_y((float)p.y())
{
}

/**
 *
 */
Vector2::~Vector2(void)
{
	std::cout << "[Vector2::~Vector2()] " << this << std::endl;
}

/**
 * Returns the dot product (a scalar value) of this vector and otherVector.
 */
const float Vector2::dotProduct(const Vector2 & otherVector) const {
	return Vector2::dotProduct(*this, otherVector);
}

/**
 * Returns the distance between two points represented by this vector and otherVector. 
 * The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector2::distance(const Vector2 & otherVector) const {
	return Vector2::distance(*this, otherVector);
}

/**
 * Tests whether this Vector2 is x=y=0. If so, true is returned and false if not.
 */
const bool Vector2::isZero() const {
	return m_x == 0 && m_y == 0;
}

/**
 * Returns the calculation of this vector's length (also known as the magnitude).
 */
const float Vector2::length() const {
	return sqrt(m_x*m_x + m_y*m_y);
}

/**
 * This method normalises this vector.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised and so nothing happens.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but 
 * has been scaled to have a length or magnitude of 1. 
 */
void Vector2::normalise() {
	if (isZero()) return;
	*this = *this/length();
}

/**
 * Returns a Vector2 that is a normalised version of this vector. This vector remains unchanged.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised
 * and a zero vector is returned instead.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but 
 * has been scaled to have a length or magnitude of 1.
 */
Vector2 Vector2::normalised() const {
	if (isZero()) return Vector2();
	return *this/length();
}

/**
 * Resets this Vector2 back to x=y=0.
 */
void Vector2::reset() {
	m_x = m_y = 0;
}

/**
 * Sets the x component of this vector.
 */
void Vector2::setX(const float x) {
	m_x = x;
}

/**
 * Sets the y component of this vector.
 */
void Vector2::setY(const float y) {
	m_y = y;
}

/**
 * Returns the x component of this vector.
 */
const float Vector2::x() const {
	return m_x;
}

/**
 * Returns the y component of this vector.
 */
const float Vector2::y() const {
	return m_y;
}

/**
 * Returns a Point object containing the x and y components of this vector.
 * Note: Point uses integer precision so non-integer x and y coordinates will be rounded.
 */
Point Vector2::toPoint() const {
	return Point((int)m_x, (int)m_y);
}

/**
 * Returns a Vector3 with the x and y of this vector additionally setting the z component to 0.
 */
Vector3 Vector2::toVector3() const {
	return Vector3(m_x, m_y, 0);
}

/**
 * Returns a Vector4 with the x and y of this vector additionally setting the z and w components to 0.
 */
Vector4 Vector2::toVector4() const {
	return Vector4(m_x, m_y, 0, 0);
}

/**
 * Adds the corresponding components of this vector and vector v together.
 */
Vector2 & Vector2::operator+=(const Vector2 & v) {
	m_x += v.m_x;
	m_y += v.m_y;
	return *this;
}

/**
 * Subtracts the components of vector v from the corresponding components of this vector.
 */
Vector2 & Vector2::operator-=(const Vector2 & v) {
	m_x -= v.m_x;
	m_y -= v.m_y;
	return *this;
}

/**
 * Multiplies each component of this vector by factor and returns a reference to this vector.
 */
Vector2 & Vector2::operator*=(const float factor) {
	m_x *= factor;
	m_y *= factor;
	return *this;
}

/**
 * Multiplies the components of this vector by the corresponding components of vector v.
 */
Vector2 & Vector2::operator*=(const Vector2 & v) {
	m_x *= v.m_x;
	m_y *= v.m_y;
	return *this;
}

/**
 * If divisor is not 0 then each component of this vector is divided by divisor, otherwise nothing happens.
 * Either way a reference to this vector is returned.
 */
Vector2 & Vector2::operator/=(const float divisor) {
	if (divisor != 0) {
		m_x /= divisor;
		m_y /= divisor;
	}
	return *this;
}

/**
 * Assignment operator assigns the component values of v to this vector.
 */
Vector2 & Vector2::operator=(const Vector2 & v) {
	if (this != &v) {
		copyDataFromSourceToDestination(v, *this);
	}
	return *this;
}

/**********************************************************************
Static public members
**********************************************************************/

/**
 * Returns the dot product of vectors a and b (the length of the projection of b onto a, multiplied by the length of a).
 * The dot product of the two vectors is the sum of the products of corresponding components which
 * results in a scalar.
 * The dot product of two vectors a and b is also equal to the cosine of angle theta between the two vectors
 * placed tail to tail multiplied by the lengths of the vectors i.e. a.b = ||a||||b||cos(theta)
 */
const float Vector2::dotProduct(const Vector2 & a, const Vector2 & b) {
	return a.m_x*b.m_x + a.m_y*b.m_y;
}

/**
 * Returns the distance between two points. The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector2::distance(const Vector2 & a, const Vector2 & b) {
	// Note: it doesn't matter which way round the subtraction is done here
	// as the distance will be the same either way whether a-b or b-a is used
	Vector2 d = a - b;
	return d.length();
}

/**********************************************************************
Related non-members
**********************************************************************/
/**
 * Returns a Vector2 that is the result of adding the components of vector a and vector b.
 */
Vector2 operator+(const Vector2 & a, const Vector2 & b) {
	return Vector2(a.m_x+b.m_x, a.m_y+b.m_y);
}

/**
 * Returns a Vector2 that is the result of subtracting the components of vector b from vector a.
 * Note: vector subtraction is not commutitive so a-b does not always equal b-a
 */
Vector2 operator-(const Vector2 & a, const Vector2 & b) {
	return Vector2(a.m_x-b.m_x, a.m_y-b.m_y);
}

/**
 * Returns a Vector2 object where each vector component of v has been negated.
 */
Vector2 operator-(const Vector2 & v) {
	return Vector2(-v.m_x, -v.m_y);
}

/**
 * Returns a Vector2 that has had each vector component of v multiplied by factor.
 */
Vector2 operator*(const float factor, const Vector2 & v) {
	return Vector2(factor * v.m_x, factor * v.m_y);
}

/**
 * Returns a Vector2 that has had each vector component of v multiplied by factor.
 */
Vector2 operator*(const Vector2 & v, const float factor) {
	return Vector2(factor * v.m_x, factor * v.m_y);
}

/**
 * Returns a Vector2 where each component of vector v has been divided by divisor.
 * If divisor is 0 then a zero vector is returned instead.
 */
Vector2 operator/(const Vector2 & v, const float divisor) {
	if (divisor == 0) 
		return Vector2();
	return Vector2(v.m_x/divisor, v.m_y/divisor);
}

/**
 * Compares the two vectors and if each of the corresponding components are equal in value 
 * then true is returned, false otherwise.
 */
const bool operator==(const Vector2 & a, const Vector2 & b) {
	if (&a == &b) 
		return true;
	if (a.m_x == b.m_x && a.m_y == b.m_y)
		return true;
	return false;
}

/**
 * Compares the vectors and returns true if a and b are not equal, false otherwise.
 */
const bool operator!=(const Vector2 & a, const Vector2 & b) {
	return !(a==b);
}

/**
 * Allows an instance of Vector2 to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Vector2 & v) {
	out << "Vector2 [" << &v << "]: (x=" << v.m_x << ", y=" << v.m_y << ")";
	return out;
}

/**********************************************************************
Private members
**********************************************************************/
/**
 * Simply copiesthe components values from the source vector to the detination vector.
 */
void Vector2::copyDataFromSourceToDestination(const Vector2 & source, Vector2 & destination) {
	destination.m_x = source.m_x;
	destination.m_y = source.m_y;
}

}
