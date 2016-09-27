#include <prism/h/Quaternion.h>
#include <prism/h/Vector3.h>
#include <prism/h/Vector4.h>
#include <prism/h/Matrix4.h>
#include <prism/h/Mathf.h>
#include <cmath>

namespace prism {

/**
 * Constructs a quaternion set to the identity state (1,0,0,0).
 */
Quaternion::Quaternion(void)
{
	setToIdentity();
}

/**
 * Constructs a quaternion setting the w, x, y and z components to the values passed in.
 */
Quaternion::Quaternion(const float w, const float x, const float y, const float z) 
	: m_w(w), m_x(x), m_y(y), m_z(z)
{
}

/**
 * Constructs a quaternion from the passed in w and vector.
 */
Quaternion::Quaternion(const float w, const Vector3 & v) 
	: m_w(w), m_x(v.x()), m_y(v.y()), m_z(v.z())
{
}

/**
 * Constructs a quaternion which is a copy of q.
 */
Quaternion::Quaternion(const Quaternion & q) {
	copyDataFromSourceToDestination(q, *this);
}

/**
 *
 */
Quaternion::~Quaternion(void)
{
}

/**
 * Returns a new Quaternion which is the result of negating the vector component of this quaternion.
 * This quaternion remains unaltered.
 * Note: when a quaternion has been normalised (has unit length of 1) the conjugate and inverse
 * are identical. The quaternion needs to be of unit length in order to perform rotations correctly.
 */
Quaternion Quaternion::conjugate() const {
	return Quaternion(m_w, -m_x, -m_y, -m_z);
}

/**
 * Returns the inverse of this quaternion. 
 * The inverse is defined as dividing the conjugate by the magnitude.
 * Note: when a quaternion has been normalised (has unit length of 1) the conjugate and inverse
 * are identical. The quaternion needs to be of unit length in order to perform rotations correctly.
 */
Quaternion Quaternion::inverse() const {
	return conjugate() / length();
}

/**
 * Returns true if w=1 and x=y=z=0, false otherwise.
 */
const bool Quaternion::isIdentity() const {
	return m_w==1 && m_x==0 && m_y==0 && m_z==0;
}

/**
 * Returns the length (magnitude) of the quaternion.
 */
const float Quaternion::length() const {
	return sqrt(m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z);
}

/**
 * Returns the squared length of this quaternion.
 */
const float Quaternion::lengthSquared() const {
	return m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z;
}

/**
 * Normalises this quaternion which sets its length to 1.
 */
void Quaternion::normalise() {
	*this = *this / length();
}

/**
 * Returns a copy of this quaternion that has been normalised.
 */
Quaternion Quaternion::normalised() const {
	return *this / length();
}

/**
 * Rotates vector v with this quaternion and returns a new Vector3 with the result.
 */
Vector3 Quaternion::rotatedVector(const Vector3 & v) {
	Quaternion q = *this * v * inverse();
	return q.vector3();
}

/**
 * Sets the w component of this quaternion.
 */
void Quaternion::setW(const float w) {
	m_w = w;
}

/**
 * Sets the x component of this quaternion.
 */
void Quaternion::setX(const float x) {
	m_x = x;
}

/**
 * Sets the y component of this quaternion.
 */
void Quaternion::setY(const float y) {
	m_y = y;
}

/**
 * Sets the z component of this quaternion.
 */
void Quaternion::setZ(const float z) {
	m_z = z;
}

/**
 * Sets the vector component of this quaternion to the values passed in.
 */
void Quaternion::setVector(const float x, const float y, const float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
 * Sets the vector component of this quaternion to the specified vector passed in.
 */
void Quaternion::setVector(const Vector3 & v) {
	setVector(v.x(), v.y(), v.z());
}

/**
 * Sets the quaternion to its identity state which sets w=1 and x=y=z=0 i.e. zero vector
 */
void Quaternion::setToIdentity() {
	m_w = 1;
	m_x=m_y=m_z = 0;
}

/**
 * Returns a Vector3 which is the vector component of this quaternion i.e. x, y and z
 */
Vector3 Quaternion::vector3() const {
	return Vector3(m_x, m_y, m_z);
}

/**
 * Returns a Vector4 which is the vector component of this quaternion, i.e. x, y and z,
 * additionally with the w component set to 1.
 */
Vector4 Quaternion::vector4() const {
	return Vector4(vector3(), 1);
}

/**
 * Returns the w component of this quaternion.
 */
const float Quaternion::w() const {
	return m_w;
}

/**
 * Returns the x component of this quaternion.
 */
const float Quaternion::x() const {
	return m_x;
}

/**
 * Returns the y component of this quaternion.
 */
const float Quaternion::y() const {
	return m_y;
}

/**
 * Returns the z component of this quaternion.
 */
const float Quaternion::z() const {
	return m_z;
}

/**
 * Returns a reference to this Quaternion which has had q added to it.
 */
Quaternion & Quaternion::operator+=(const Quaternion & q) {
	m_w += q.m_w;
	m_x += q.m_x;
	m_y += q.m_y;
	m_z += q.m_z;

	return *this;
}

/**
 * Returns a reference to this Quaternion which has had q subtracted from it.
 */
Quaternion & Quaternion::operator-=(const Quaternion & q) {
	m_w -= q.m_w;
	m_x -= q.m_x;
	m_y -= q.m_y;
	m_z -= q.m_z;

	return *this;
}

/**
 * Returns a reference to this Quaternion which has had each component multiplied by factor.
 */
Quaternion & Quaternion::operator*=(const float factor) {
	m_w *= factor;
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;

	return *this;
}

/**
 * Returns a reference to this Quaternion which has had each component divided by divisor.
 * If divisor is 0 then nothing happens.
 */
Quaternion & Quaternion::operator/=(const float divisor) {
	if (divisor != 0) {
		m_w /= divisor;
		m_x /= divisor;
		m_y /= divisor;
		m_z /= divisor;
	}
	return *this;
}

/**
 * Assignment operator assigns the component values of q to this quaternion.
 */
Quaternion & Quaternion::operator=(const Quaternion & q) {
	if (*this != q) {
		copyDataFromSourceToDestination(q, *this);
	}
	return *this;

}

/**********************************************************************
Static public members
**********************************************************************/
/**
 * Returns a normalised quaternion that represents a rotation of angle degrees 
 * around the specified axis. If the axis specified by xAxis, yAxis and zAxis 
 * is not normalised then this method normalises it. Also, angle is in degrees.
 */
Quaternion Quaternion::fromAxisAndAngle(const float xAxis, const float yAxis, const float zAxis, const float angle) {
	Vector3 axis(xAxis, yAxis, zAxis);
	return Quaternion::fromAxisAndAngle(axis.normalised(), angle);
}

/**
 * Returns a normalised quaternion that represents a rotation of angle degrees around the specified axis.
 * If axis is not normalised then this method normalises it. Also, angle is in degrees.
 * 
 */
Quaternion Quaternion::fromAxisAndAngle(const Vector3 & axis, const float angle) {
	float w, x, y, z, theta;
	Vector3 n = axis.normalised();

//	using namespace prism::utils;
	theta = angle * (prism::Mathf::PI/180);
	w = cosf(theta/2);
	x = n.x() * sinf(theta/2);
	y = n.y() * sinf(theta/2);
	z = n.z() * sinf(theta/2);

	return Quaternion(w, x, y, z).normalised();
}

/**
 * Returns a scalar which is the dot product of the two quaternions in the range [-1, 1].
 * The dot product of two quaternions represents the cosine of half of the angle needed to rotate one 
 * quaternion into the other. The larger the absolute value the result is (the closer it is to 1) means the closer 
 * the two quaternions are in orientation.
 */
const float Quaternion::dotProduct(const Quaternion & q1, const Quaternion &q2) {
	float out = q1.m_w*q2.m_w + q1.m_x*q2.m_x + q1.m_y*q2.m_y + q1.m_z*q2.m_z;
	prism::Mathf::correctFloatingPointError(out);

	return out;
}

/**
 *
 */
Quaternion Quaternion::identity() {
	return Quaternion();
}

/**********************************************************************
Related non-members
**********************************************************************/
/**
 * Returns a Quaternion that is the sum of q1 and q2 
 * i.e. each component of q1 is added to the corresponding component of q2.
 */
Quaternion operator+(const Quaternion & q1, const Quaternion & q2) {
	return Quaternion(q1.m_w+q2.m_w, q1.m_x+q2.m_x, q1.m_y+q2.m_y, q1.m_z+q2.m_z);
}

/**
 * Returns a Quaternion that is the result of subtracting q2 from q1
 * i.e. each component of q2 is subtracted from the corresponding component of q1.
 */
Quaternion operator-(const Quaternion & q1, const Quaternion & q2) {
	return Quaternion(q1.m_w-q2.m_w, q1.m_x-q2.m_x, q1.m_y-q2.m_y, q1.m_z-q2.m_z);
}

/**
 * Returns a Quaternion which has had each component of q negated.
 */
Quaternion operator-(Quaternion & q) {
	return Quaternion(-q.m_w, -q.m_x, -q.m_y, -q.m_z);
}

/**
 * Returns a Quaternion that is the product of q1 and q2.
 * Note: quaternion multiplication is associative so a(bc) = (ab)c but is not 
 * commutitive so q1q2 does not always equal q2q1. Order matters!
 */
Quaternion operator*(const Quaternion & q1, const Quaternion & q2) {
	float w1,w2,x1,x2,y1,y2,z1,z2;
	w1 = q1.m_w;
	x1 = q1.m_x;
	y1 = q1.m_y;
	z1 = q1.m_z;
	w2 = q2.m_w;
	x2 = q2.m_x;
	y2 = q2.m_y;
	z2 = q2.m_z;

	float w,x,y,z;
	w = w1*w2 - x1*x2 - y1*y2 - z1*z2;
	x = w1*x2 + x1*w2 + y1*z2 - z1*y2;
	y = w1*y2 + y1*w2 + z1*x2 - x1*z2;
	z = w1*z2 + z1*w2 + x1*y2 - y1*x2;

//	using namespace prism::utils;
	prism::Mathf::correctFloatingPointError(w);
	prism::Mathf::correctFloatingPointError(x);
	prism::Mathf::correctFloatingPointError(y);
	prism::Mathf::correctFloatingPointError(z);

	return Quaternion(w,x,y,z);

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Qt's implementation of quaternion multiplication
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	/*float ww = (q1.m_z + q1.m_x) * (q2.m_x + q2.m_y);
    float yy = (q1.m_w - q1.m_y) * (q2.m_w + q2.m_z);
    float zz = (q1.m_w + q1.m_y) * (q2.m_w - q2.m_z);
    float xx = ww + yy + zz;
    float qq = 0.5 * (xx + (q1.m_z - q1.m_x) * (q2.m_x - q2.m_y));

    float w = qq - ww + (q1.m_z - q1.m_y) * (q2.m_y - q2.m_z);
    float x = qq - xx + (q1.m_x + q1.m_w) * (q2.m_x + q2.m_w);
    float y = qq - yy + (q1.m_w - q1.m_x) * (q2.m_y + q2.m_z);
    float z = qq - zz + (q1.m_z + q1.m_y) * (q2.m_w - q2.m_x);

    return Quaternion(w, x, y, z);*/
}

/**
 * Returns a Quaternion that is the result of multiplying each component of q by factor.
 */
Quaternion operator*(const Quaternion & q, const float factor) {
	return Quaternion(q.m_w*factor, q.m_x*factor, q.m_y*factor, q.m_z*factor);
}

/**
 * Returns a Quaternion that is the result of multiplying each component of q by factor.
 */
Quaternion operator*(const float factor, const Quaternion & q) {
	return q*factor;
}

/**
 * Multiplies a quaternion and vector3 together and returns a quaternion as a result.
 * The vector is just transformed into a quaternion (setting w = 0) and then the two quaternions are multiplied.
 */
Quaternion operator*(const Quaternion & q, const Vector3 & v) {
	Quaternion a(0, v.x(), v.y(), v.z());
	return q*a;
}

/**
 * Multiplies a quaternion and Vector4 together and returns a quaternion as a result.
 * The vector is just transformed into a quaternion and then the two quaternions are multiplied.
 */
Quaternion operator*(const Quaternion & q, const Vector4 & v) {
	Quaternion a(v.w(), v.x(), v.y(), v.z());
	return q*a;
}

/**
 * Returns a Quaternion that is the result of dividing each component of q by divisor.
 * If divisor is 0 then a identity quaternion is returned instead.
 */
Quaternion operator/(const Quaternion & q, const float divisor) {
	if (divisor == 0)
		return Quaternion(); // identity quaternion
	return Quaternion(q.m_w/divisor, q.m_x/divisor, q.m_y/divisor, q.m_z/divisor);
}

/**
 * Compares q1 and q2 and returns true if they are equal, false otherwise.
 */
const bool operator==(const Quaternion & q1, const Quaternion & q2) {
	if (q1.m_w==q2.m_w && q1.m_x==q2.m_x && q1.m_y==q2.m_y && q1.m_z==q2.m_z)
		return true;
	return false;
}

/**
 * Compares q1 and q2 and returns true if they are not equal, false otherwise.
 */
const bool operator!=(const Quaternion & q1, const Quaternion & q2) {
	return !(q1 == q2);
}

/**
 * Returns a reference to a stream which allows an instance of Quaternion to be written to the stream.
 */
std::ostream & operator<<(std::ostream & out, const Quaternion & q) {
	out << &q << " Quaternion(w:" << q.m_w << ", Vector3(" << q.m_x << ", " << q.m_y << ", " << q.m_z << "))";
	return out;
}

/**
 * @Private:
 * Simply copies the data from the source quaternion into the destination quaternion.
 */
void Quaternion::copyDataFromSourceToDestination(const Quaternion & source, Quaternion & destination) {
	destination.m_w = source.m_w;
	destination.m_x = source.m_x;
	destination.m_y = source.m_y;
	destination.m_z = source.m_z;
}

}
