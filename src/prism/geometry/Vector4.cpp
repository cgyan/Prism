#include <prism/Vector4>
#include <prism/Vector2>
#include <prism/Vector3>
#include <prism/Point>
#include <cmath>
#include <iostream>

namespace prism {
/**
 * Constructs a default Vector4 setting it to a zero vector i.e. x=y=z=w=0.
 */
Vector4::Vector4(void)
	: m_x(0), m_y(0), m_z(0), m_w(0)
{
}

/**
 * Constructs a Vector4 from the x, y, z and w floats passed in.
 */
Vector4::Vector4(const float x, const float y, const float z, const float w)
	: m_x(x), m_y(y), m_z(z), m_w(w)
{
}

/**
 * Constructs a Vector4 from a 2d Point setting z=w=0.
 */
Vector4::Vector4(const Point & p) 
	: m_x((float)p.x()), m_y((float)p.y()), m_z(0), m_w(0)
{
}

/**
 *
 */
Vector4::Vector4(const Point & p, const float z, const float w) 
	: m_x((float)p.x()), m_y((float)p.y()), m_z(z), m_w(w)
{
}

/**
 * Constructs a Vector4 from a Vector2 setting z=w=0.
 */
Vector4::Vector4(const Vector2 & v) 
	: m_x(v.x()), m_y(v.y()), m_z(0), m_w(0)
{
}

/**
 * Constructs a Vector4 from a Vector2 additionally setting the z and w components equal to z and w.
 */
Vector4::Vector4(const Vector2 & v, const float z, const float w) 
	: m_x(v.x()), m_y(v.y()), m_z(z), m_w(w)
{
}

/**
 * Constructs a Vector4 from a Vector3 setting w=0.
 */
Vector4::Vector4(const Vector3 & v) 
	: m_x(v.x()), m_y(v.y()), m_z(v.z()), m_w(0)
{
}

/**
 * Constructs a Vector4 from a Vector3 additionally setting the w component to 0.
 */
Vector4::Vector4(const Vector3 & v, const float w) 
	: m_x(v.x()), m_y(v.y()), m_z(v.z()), m_w(w)
{
}

/**
 * Copy constructor
 */
Vector4::Vector4(const Vector4 & v) {
	copyDataFromSourceToDestination(v, *this);
}

/**
 *
 */
Vector4::~Vector4(void)
{
}

/**
 * Returns the dot product (a scalar value) of this vector and otherVector.
 */
const float Vector4::dotProduct(const Vector4 & otherVector) const {
	return Vector4::dotProduct(*this, otherVector);
}

/**
 * Returns the distance between two points represented by this vector and otherVector. 
 * The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector4::distance(const Vector4 & otherVector) const {
	return Vector4::distance(*this, otherVector);
}

/**
 * Returns true if this Vector4 is x=y=z=w=0, false otherwise..
 */
const bool Vector4::isZero() const {
	return m_x == 0 && m_y == 0 && m_z == 0 && m_w == 0;
}

/**
 * Returns this vector's length (also known as the magnitude).
 */
const float Vector4::length() const {
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

/**
 * Returns the squared length of this vector.
 */
const float Vector4::lengthSquared() const {
	return m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
}

/**
 * This method normalises this vector.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised and so nothing happens.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but 
 * has been scaled to have a length or magnitude of 1. 
 */
void Vector4::normalise() {
	if (isZero()) return;
	*this = *this/length();
}

/**
 * Returns a Vector4 that is a normalised version of this vector. This vector remains unchanged.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised
 * and a zero vector is returned instead.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but 
 * has been scaled to have a length or magnitude of 1.
 */
Vector4 Vector4::normalised() const {
	if (isZero()) return Vector4();
	return *this/length();
}

/**
 * Resets this Vector4 back to x=y=z=w=0.
 */
void Vector4::reset() {
	m_x = m_y = m_z = m_w = 0;
}

/**
 * Sets the x component of this vector.
 */
void Vector4::setX(const float x) {
	m_x = x;
}

/**
 * Sets the y component of this vector.
 */
void Vector4::setY(const float y) {
	m_y = y;
}

/**
 * Sets the z component of this vector.
 */
void Vector4::setZ(const float z) {
	m_z = z;
}

/**
 * Sets the w component of this vector.
 */
void Vector4::setW(const float w) {
	m_w = w;
}

/**
 * Returns the x component of this vector.
 */
const float Vector4::x() const {
	return m_x;
}

/**
 * Returns the y component of this vector.
 */
const float Vector4::y() const {
	return m_y;
}

/**
 * Returns the z component of this vector.
 */
const float Vector4::z() const {
	return m_z;
}

/**
 * Returns the w component of this vector.
 */
const float Vector4::w() const {
	return m_w;
}

/**
 * Returns a Point object containing the x and y components of this vector while the z and w components are dropped.
 * Note: Point uses integer precision so non-integer x and y coordinates will be rounded.
 */
Point Vector4::toPoint() const {
	return Point((int)m_x, (int)m_y);
}

/** 
 * Returns a Vector2 version of this vector dropping the z and w components.
 */
Vector2 Vector4::toVector2() const {
	return Vector2(m_x, m_y);
}

/** 
 * Returns a Vector3 version of this vector dropping the w component.
 */
Vector3 Vector4::toVector3() const {
	return Vector3(m_x, m_y, m_z);
}

/**
 * Adds the corresponding components of this vector and vector v together.
 */
Vector4 & Vector4::operator+=(const Vector4 & v) {
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	m_w += v.m_w;
	return *this;
}

/**
 * Subtracts the components of vector v from the corresponding components of this vector.
 */
Vector4 & Vector4::operator-=(const Vector4 & v) {
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	m_w -= v.m_w;
	return *this;
}

/**
 * Multiplies each component of this vector by factor and returns a reference to this vector.
 */
Vector4 & Vector4::operator*=(const float factor) {
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;
	m_w *= factor;
	return *this;
}

/**
 * Multiplies the components of this vector by the corresponding components of vector v.
 */
Vector4 & Vector4::operator*=(const Vector4 & v) {
	m_x *= v.m_x;
	m_y *= v.m_y;
	m_z *= v.m_z;
	m_w *= v.m_w;
	return *this;
}

/**
 * If divisor is not 0 then each component of this vector is divided by divisor, otherwise nothing happens.
 * Either way a reference to this vector is returned.
 */
Vector4 & Vector4::operator/=(const float divisor) {
	if (divisor != 0) {
		m_x /= divisor;
		m_y /= divisor;
		m_z /= divisor;
		m_w /= divisor;
	}
	return *this;
}

/**
 * Assignment operator assigns the component values of v to this vector.
 */
Vector4 & Vector4::operator=(const Vector4 & v) {
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
const float Vector4::dotProduct(const Vector4 & a, const Vector4 & b) {
	return a.m_x*b.m_x + a.m_y*b.m_y + a.m_z*b.m_z + a.m_w*b.m_w;
}

/**
 * Returns the distance between two points. The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector4::distance(const Vector4 & a, const Vector4 & b) {
	// Note: it doesn't matter which way round the subtraction is done here
	// as the distance will be the same either way whether a-b or b-a is used
	Vector4 d = a - b;
	return d.length();
}

/**********************************************************************
Related non-members
**********************************************************************/
/**
 * Returns a Vector4 that is the result of adding the components of vector a and vector b.
 */
Vector4 operator+(const Vector4 & a, const Vector4 & b) {
	return Vector4(a.m_x+b.m_x, a.m_y+b.m_y, a.m_z+b.m_z, a.m_w+b.m_w);
}

/**
 * Returns a Vector4 that is the result of subtracting the components of vector b from vector a.
 * Note: vector subtraction is not commutitive so a-b does not always equal b-a
 */
Vector4 operator-(const Vector4 & a, const Vector4 & b) {
	return Vector4(a.m_x-b.m_x, a.m_y-b.m_y, a.m_z-b.m_z, a.m_w-b.m_w);
}

/**
 * Returns a Vector4 object where each vector component of v has been negated.
 */
Vector4 operator-(const Vector4 & v) {
	return Vector4(-v.m_x, -v.m_y, -v.m_z, -v.m_w);
}

/**
 * Returns a Vector4 that has had each vector component of v multiplied by factor.
 */
Vector4 operator*(const float factor, const Vector4 & v) {
	return Vector4(factor * v.m_x, factor * v.m_y, factor * v.m_z, factor * v.m_w);
}

/**
 * Returns a Vector4 that has had each vector component of v multiplied by factor.
 */
Vector4 operator*(const Vector4 & v, const float factor) {
	return Vector4(factor * v.m_x, factor * v.m_y, factor * v.m_z, factor * v.m_w);
}

/**
 * Returns a Vector4 where each component of vector v has been divided by divisor.
 * If divisor is 0 then a zero vector is returned instead.
 */
Vector4 operator/(const Vector4 & v, const float divisor) {
	if (divisor == 0) return Vector4();
	return Vector4(v.m_x/divisor, v.m_y/divisor, v.m_z/divisor, v.m_w/divisor);
}

/**
 * Compares the two vectors and if each of the corresponding components are equal in value 
 * then true is returned, false otherwise.
 */
const bool operator==(const Vector4 & a, const Vector4 & b) {
	if (&a == &b) 
		return true;
	if (a.m_x == b.m_x && a.m_y == b.m_y && a.m_z == b.m_z && a.m_w == b.m_w)
		return true;
	return false;
}

/**
 * Compares the vectors and returns true if a and b are not equal, false otherwise.
 */
const bool operator!=(const Vector4 & a, const Vector4 & b) {
	return !(a==b);
}

/**
 * Allows an instance of Vector4 to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Vector4 & v) {
	out << "Vector4 [" << &v << "]: x:" << v.m_x << " y:" << v.m_y << " z:" << v.m_z << " w:" << v.m_w;
	return out;
}

/**********************************************************************
Private members
**********************************************************************/
/**
 * Simply copiesthe components values from the source vector to the detination vector.
 */
void Vector4::copyDataFromSourceToDestination(const Vector4 & source, Vector4 & destination) {
	destination.m_x = source.m_x;
	destination.m_y = source.m_y;
	destination.m_z = source.m_z;
	destination.m_w = source.m_w;
}

}
