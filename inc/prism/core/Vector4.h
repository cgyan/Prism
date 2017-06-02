#ifndef PRISM_VECTOR4_H_
#define PRISM_VECTOR4_H_

#include <ostream>

namespace prism {

class Point;
class Vector2;
class Vector3;

class Vector4
{
private:
	float m_x, m_y, m_z, m_w;

public:
	Vector4(void);
	Vector4(const float x, const float y, const float z, const float w);
	Vector4(const Point & p);
	Vector4(const Point & p, const float z, const float w);
	Vector4(const Vector2 & v);
	Vector4(const Vector2 & v, const float z, const float w);
	Vector4(const Vector3 & v);
	Vector4(const Vector3 & v, const float w);
	Vector4(const Vector4 & v);
	virtual ~Vector4(void);

	const float dotProduct(const Vector4 & otherVector) const;
	const float distance(const Vector4 & otherVector) const;
	const bool isZero() const;
	const float length() const;
	const float lengthSquared() const;
	void normalise();
	Vector4 normalised() const;
	void reset();
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setW(const float w);
	const float x() const;
	const float y() const;
	const float z() const;
	const float w() const;
	Point toPoint() const;
	Vector3 toVector3() const;
	Vector2 toVector2() const;
	
	Vector4 & operator+=(const Vector4 & v);
	Vector4 & operator-=(const Vector4 & v);
	Vector4 & operator*=(const float factor);
	Vector4 & operator*=(const Vector4 & v);
	Vector4 & operator/=(const float divisor);
	Vector4 & operator=(const Vector4 & v);

	// Static public members
	static const float dotProduct(const Vector4 & a, const Vector4 & b);
	static const float distance(const Vector4 & a, const Vector4 & b);

	// Related non-members
	friend Vector4 operator+(const Vector4 & a, const Vector4 & b);
	friend Vector4 operator-(const Vector4 & a, const Vector4 & b);
	friend Vector4 operator-(const Vector4 & v);
	friend Vector4 operator*(const float factor, const Vector4 & v);
	friend Vector4 operator*(const Vector4 & v, const float factor);
	friend Vector4 operator/(const Vector4 & v, const float divisor);
	friend const bool operator==(const Vector4 & a, const Vector4 & b);
	friend const bool operator!=(const Vector4 & a, const Vector4 & b);
	friend std::ostream & operator<<(std::ostream & out, const Vector4 & v);

private:
	void copyDataFromSourceToDestination(const Vector4 & source, Vector4 & destination);
};
}

#endif // PRISM_VECTOR4_H_

