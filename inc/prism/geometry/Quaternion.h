#ifndef PRISM_QUATERNION_H_
#define PRISM_QUATERNION_H_

#include <ostream>

/*!
A Quaternion is made up of four components (w, x, y and z) which are a scalar (w) and a 3d vector (x, y and z).
It does not suffer from gimbal lock and yet can represent any orientation possible.

Some interesting properties of quaternion multiplication:
a) it is associative but not commutitive - 
	(ab)c = a(bc)
	ab != ba

b) the magnitude of a quaternion product equals the product of the individual magnitudes. This is an important
concept because when quaternions are of unit length and are multiplied, this guarentees us that the result
will itself be a unit quaternion -
	||ab|| = ||a||||b||

c) the inverse of a quaternion product is equal to the product of the individual quaternion inverses in reverse order -
	(ab).inverse = (b.inverse) * (a.inverse)

Rotating vectors:
When rotating with a quaternion it is important that the quaternion be normalised i.e. be of unit length. This is
because otherwise scaling will occur and since we only require rotations from our quaternions this won't do.
Rotating a vector using quaternions is done with the following equation:
	v' = q * v * q.inverse
where vector v is represented as a quaternion.

Concatenating rotational transforms together:
Multiple quaternion rotations can be applied to a vector in one single action by concatenating the rotational quaternions
together and then applying them to the vector using the above equation. For example, to rotate the vector v by quaternion a
and then rotating that result by quaternion b would be as follows:
	v' = b * (a * v * a.inverse) * b.inverse
	   = (b * a) * v * (b.inverse * a.inverse)
	   = (b * a) * v * (b * a).inverse
So, rotating by a and then by b is equivalent to the single rotation of the product of ba.
*/

namespace prism {

class Vector3;
class Vector4;
class Matrix4;

class Quaternion
{
private:
	float m_w, m_x, m_y, m_z;

public:
	Quaternion(void);
	Quaternion(const float w, const float x, const float y, const float z);
	Quaternion(const float w, const Vector3 & v);
	Quaternion(const Quaternion & q);
	virtual ~Quaternion(void);

	Quaternion conjugate() const;
	Quaternion inverse() const;
	const bool isIdentity() const;
	const float length() const;
	const float lengthSquared() const;
	void normalise();
	Quaternion normalised() const;
	Vector3 rotatedVector(const Vector3 & v);
	void setW(const float w);
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setVector(const float x, const float y, const float z);
	void setVector(const Vector3 & v);
	void setToIdentity();
	Vector3 vector3() const;
	Vector4 vector4() const;
	const float w() const;
	const float x() const;
	const float y() const;
	const float z() const;

	static const float dotProduct(const Quaternion & q1, const Quaternion & q2);
	static Quaternion fromAxisAndAngle(const Vector3 & axis, const float angle);
	static Quaternion fromAxisAndAngle(const float xAxis, const float yAxis, const float zAxis, const float angle);
	static Quaternion identity();

	Quaternion & operator+=(const Quaternion & q);
	Quaternion & operator-=(const Quaternion & q);
	Quaternion & operator*=(const float factor);
	Quaternion & operator/=(const float divisor);
	Quaternion & operator=(const Quaternion & q);

	// Related non-members
	friend Quaternion operator+(const Quaternion & q1, const Quaternion & q2);
	friend Quaternion operator-(const Quaternion & q1, const Quaternion & q2);
	friend Quaternion operator-(Quaternion & q);
	friend Quaternion operator*(const Quaternion & q1, const Quaternion & q2);
	friend Quaternion operator*(const Quaternion & q, const float factor);
	friend Quaternion operator*(const float factor, const Quaternion & q);
	friend Quaternion operator*(const Quaternion & q, const Vector3 & v);
	friend Quaternion operator*(const Quaternion & q, const Vector4 & v);
	friend Quaternion operator/(const Quaternion & q, const float divisor);
	friend const bool operator==(const Quaternion & q1, const Quaternion & q2);
	friend const bool operator!=(const Quaternion & q1, const Quaternion & q2);
	friend std::ostream & operator<<(std::ostream & out, const Quaternion & q);

private:
	void copyDataFromSourceToDestination(const Quaternion & source, Quaternion & destination);
};

}

#endif /* PRISM_QUATERNION_H_ */
