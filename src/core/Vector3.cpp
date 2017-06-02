#include <prism/Vector3>
#include <prism/Vector2>
#include <prism/Vector4>
#include <prism/Point>
#include <cmath>
#include <iostream>

namespace prism {
/**
 * Constructs a default Vector3 setting it to a zero vector i.e. x=y=z=0.
 */
Vector3::Vector3(void)
	: m_x(0), m_y(0), m_z(0)
{
	//std::cout << "[Vector3::Vector3()]" << std::endl;
}

/**
 * Constructs a Vector3 from the x, y and z floats passed in.
 */
Vector3::Vector3(const float x, const float y, const float z)
	: m_x(x), m_y(y), m_z(z)
{
	//std::cout << "[Vector3::Vector3()]" << std::endl;
}

/**
 * Constructs a Vector3 from the vector2 additionally setting the z component of this vector to 0.
 */
Vector3::Vector3(const Vector2 & v) {
	m_x = v.x();
	m_y = v.y();
	m_z = 0;
}

/**
 * Constructs a Vector3 from the Vector2 addionally setting the z component to z.
 */
Vector3::Vector3(const Vector2 & v, const float z) {
	m_x = v.x();
	m_y = v.y();
	m_z = z;
}

/**
 *
 */
Vector3::Vector3(const Vector3 & v) {
	copyDataFromSourceToDestination(v, *this);
}

/**
 * Constructs a Vector3 from the Vector4 dropping the w component of the Vector4.
 */
Vector3::Vector3(const Vector4 & v) {
	m_x = v.x();
	m_y = v.y();
	m_z = v.z();
}

/**
 * Constructs a Vector3 from a 2d Point setting z=0.
 */
Vector3::Vector3(const Point & p)
	: m_x((float)p.x()), m_y((float)p.y()), m_z(0)
{
}

/**
 * todo in game loop Vector3 is constantly allocating and detroying each frame .... ?
 */
Vector3::~Vector3(void)
{
	//std::cout << "[Vector3::~Vector3()] " << std::endl;
}

/**
 * Returns a Vector3 that is the cross product of this vector and otherVector i.e. this x otherVector.
 * Note: The cross product is anticommutitive so a x b is not always equal to b x a.
 */
Vector3 Vector3::crossProduct(const Vector3 & otherVector) const {
	return Vector3::crossProduct(*this, otherVector);
}

/**
 * Returns the dot product (a scalar value) of this vector and otherVector.
 */
const float Vector3::dotProduct(const Vector3 & otherVector) const {
	return Vector3::dotProduct(*this, otherVector);
}

/**
 * Returns the distance between two points represented by this vector and otherVector.
 * The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector3::distance(const Vector3 & otherVector) const {
	return Vector3::distance(*this, otherVector);
}

/**
 * Tests whether this Vector3 is x=y=z=0. If so, true is returned and false if not.
 */
const bool Vector3::isZero() const {
	return m_x == 0 && m_y == 0 && m_z == 0;
}

/**
 * Returns the calculation of this vector's length (also known as the magnitude).
 */
const float Vector3::length() const {
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

/**
 * Returns a normalised vector (has length of 1) that is perpendicular
 * to this vector and vector b when the two vectors are placed tail to tail.
 * i.e. a normalised version of the cross product of a and b.
 * Note: if the vector does not need to be normalised then the cross product is sufficient enough and is slightly quicker.
 */
Vector3 Vector3::normal(const Vector3 & otherVector) const {
	return Vector3::normal(*this, otherVector);
}

/**
 * This method normalises this vector.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised and so nothing happens.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but
 * has been scaled to have a length or magnitude of 1.
 */
void Vector3::normalise() {
	if (isZero()) return;
	*this = *this/length();
}

/**
 * Returns a Vector3 that is a normalised version of this vector. This vector remains unchanged.
 * If this vector is a zero vector (i.e. where each component is 0) then it cannot be normalised
 * and a zero vector is returned instead.
 * A normlised vector (also called a unit vector) is one which still points in the same direction but
 * has been scaled to have a length or magnitude of 1.
 */
Vector3 Vector3::normalised() const {
	if (isZero()) return Vector3();
	return *this/length();
}

/**
 * Resets this Vector3 back to x=y=z=0.
 */
void Vector3::reset() {
	m_x = m_y = m_z = 0;
}

/**
 * Sets the x component of this vector.
 */
void Vector3::setX(const float x) {
	m_x = x;
}

/**
 * Sets the y component of this vector.
 */
void Vector3::setY(const float y) {
	m_y = y;
}

/**
 * Sets the z component of this vector.
 */
void Vector3::setZ(const float z) {
	m_z = z;
}

/**
 * Returns the x component of this vector.
 */
const float Vector3::x() const {
	return m_x;
}

/**
 * Returns the y component of this vector.
 */
const float Vector3::y() const {
	return m_y;
}

/**
 * Returns the z component of this vector.
 */
const float Vector3::z() const {
	return m_z;
}

/**
 * Returns a Point object containing the x and y components of this vector while the z component is dropped.
 * Note: Point uses integer precision so non-integer x and y coordinates will be rounded.
 */
Point Vector3::toPoint() const {
	return Point((int)m_x, (int)m_y);
}

/**
 * Returns a Vector2 version of this vector dropping the z component.
 */
Vector2 Vector3::toVector2() const {
	return Vector2(m_x, m_y);
}

/**
 * Returns a Vector2 version of this vector dropping the z component.
 */
Vector4 Vector3::toVector4() const {
	return Vector4(m_x, m_y, m_z, 0);
}

/**
 * Adds the corresponding components of this vector and vector v together.
 */
Vector3 & Vector3::operator+=(const Vector3 & v) {
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	return *this;
}

/**
 * Subtracts the components of vector v from the corresponding components of this vector.
 */
Vector3 & Vector3::operator-=(const Vector3 & v) {
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	return *this;
}

/**
 * Multiplies each component of this vector by factor and returns a reference to this vector.
 */
Vector3 & Vector3::operator*=(const float factor) {
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;
	return *this;
}

/**
 * Multiplies the components of this vector by the corresponding components of vector v.
 */
Vector3 & Vector3::operator*=(const Vector3 & v) {
	m_x *= v.m_x;
	m_y *= v.m_y;
	m_z *= v.m_z;
	return *this;
}

/**
 * If divisor is not 0 then each component of this vector is divided by divisor, otherwise nothing happens.
 * Either way a reference to this vector is returned.
 */
Vector3 & Vector3::operator/=(const float divisor) {
	if (divisor != 0) {
		m_x /= divisor;
		m_y /= divisor;
		m_z /= divisor;
	}
	return *this;
}

/**
 * Assignment operator assigns the component values of v to this vector.
 */
Vector3 & Vector3::operator=(const Vector3 & v) {
	if (this != &v) {
		copyDataFromSourceToDestination(v, *this);
	}
	return *this;
}

/**********************************************************************
Static public members
**********************************************************************/
/**
 * Returns a basic vector that represents the up axis (0,1,0).
 */
Vector3 Vector3::up() {
	return Vector3(0,1,0);
}

/**
 * Returns a basix vector that represents the right axis (1,0,0).
 */
Vector3 Vector3::right() {
	return Vector3(1,0,0);
}

/**
 * Returns a basic vector that represents the forward axis (0,0,1).
 */
Vector3 Vector3::forward() {
	return Vector3(0,0,1);
}

/**
 * Returns a Vector3 that is the cross product of a and b i.e. a x b.
 * The cross product of two vectors yields a vector that is perpendicular to the two vectors
 * when the two vectors are placed tail to tail.
 * Note: The cross product is anticommutitive so a x b is not always equal to b x a.
 */
Vector3 Vector3::crossProduct(const Vector3 & a, const Vector3 & b) {
	return Vector3(a.m_y*b.m_z - a.m_z*b.m_y,
				   a.m_z*b.m_x - a.m_x*b.m_z,
				   a.m_x*b.m_y - a.m_y*b.m_x);
}

/**
 * Returns the dot product of vectors a and b (the length of the projection of b onto a, multiplied by the length of a).
 * The dot product of the two vectors is the sum of the products of corresponding components which
 * results in a scalar.
 * The dot product of two vectors a and b is also equal to the cosine of angle theta between the two vectors
 * placed tail to tail multiplied by the lengths of the vectors i.e. a.b = ||a||||b||cos(theta)
 */
const float Vector3::dotProduct(const Vector3 & a, const Vector3 & b) {
	return a.m_x*b.m_x + a.m_y*b.m_y + a.m_z*b.m_z;
}

/**
 * Returns the distance between two points. The distance is defined as the length of the line segment
 * between two points represented here with the vectors.
 */
const float Vector3::distance(const Vector3 & a, const Vector3 & b) {
	// Note: it doesn't matter which way round the subtraction is done here
	// as the distance will be the same either way whether a-b or b-a is used
	Vector3 d = a - b;
	return d.length();
}

/**
 * Returns a normalised vector (has length of 1) that is perpendicular to the vectors a and b
 * when they are placed tail to tail.
 * i.e. a normalised version of the cross product of a and b.
 * Note: if the vector does not need to be normalised then the cross product is sufficient enough and is slightly quicker.
 */
Vector3 Vector3::normal(const Vector3 & a, const Vector3 & b) {
	return Vector3::crossProduct(a, b).normalised();
}

/**
 * Returns a normalised vector that is perpendicular to the plane defined by the vectors b-a and c-a.
 * It will have unit length i.e. 1.
 */
Vector3 Vector3::normal(const Vector3 & a, const Vector3 & b, const Vector3 & c) {
	Vector3 d = b-a;
	Vector3 e = c-a;
	return Vector3::crossProduct(d,e).normalised();
}

/**********************************************************************
Related non-members
**********************************************************************/
/**
 * Returns a Vector3 that is the result of adding the components of vector a and vector b.
 */
Vector3 operator+(const Vector3 & a, const Vector3 & b) {
	return Vector3(a.m_x+b.m_x, a.m_y+b.m_y, a.m_z+b.m_z);
}

/**
 * Returns a Vector3 that is the result of subtracting the components of vector b from vector a.
 * Note: vector subtraction is not commutitive so a-b does not always equal b-a
 */
Vector3 operator-(const Vector3 & a, const Vector3 & b) {
	return Vector3(a.m_x-b.m_x, a.m_y-b.m_y, a.m_z-b.m_z);
}

/**
 * Returns a Vector3 object where each vector component of v has been negated.
 */
Vector3 operator-(const Vector3 & v) {
	return Vector3(v.m_x*-1, v.m_y*-1, v.m_z*-1);
}

/**
 * Returns a Vector3 that has had each vector component of v multiplied by factor.
 */
Vector3 operator*(const float factor, const Vector3 & v) {
	return Vector3(factor * v.m_x, factor * v.m_y, factor * v.m_z);
}

/**
 * Returns a Vector3 that has had each vector component of v multiplied by factor.
 */
Vector3 operator*(const Vector3 & v, const float factor) {
	return Vector3(factor * v.m_x, factor * v.m_y, factor * v.m_z);
}

/**
 * Returns a Vector3 where each component of vector v has been divided by divisor.
 * If divisor is 0 then a zero vector is returned instead.
 */
Vector3 operator/(const Vector3 & v, const float divisor) {
	if (divisor == 0) return Vector3();
	return Vector3(v.m_x/divisor, v.m_y/divisor, v.m_z/divisor);
}

/**
 * Compares the two vectors and if each of the corresponding components are equal in value
 * then true is returned, false otherwise.
 */
const bool operator==(const Vector3 & a, const Vector3 & b) {
	if (&a == &b)
		return true;
	if (a.m_x == b.m_x && a.m_y == b.m_y && a.m_z == b.m_z)
		return true;
	return false;
}

/**
 * Compares the vectors and returns true if a and b are not equal, false otherwise.
 */
const bool operator!=(const Vector3 & a, const Vector3 & b) {
	return !(a==b);
}

/**
 * Allows an instance of Vector3 to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Vector3 & v) {
	out << "Vector3 [" << &v << "]: x:" << v.m_x << " y:" << v.m_y << " z:" << v.m_z;
	return out;
}

/**********************************************************************
Private members
**********************************************************************/
/**
 * Simply copiesthe components values from the source vector to the detination vector.
 */
void Vector3::copyDataFromSourceToDestination(const Vector3 & source, Vector3 & destination) {
	destination.m_x = source.m_x;
	destination.m_y = source.m_y;
	destination.m_z = source.m_z;
}

}
