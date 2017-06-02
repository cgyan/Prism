#ifndef PRISM_VECTOR3_H_
#define PRISM_VECTOR3_H_

#include <ostream>

namespace prism {

class Point;
class Vector2;
class Vector4;

class Vector3
{
private:
	float m_x, m_y, m_z;

public:
	Vector3(void);
	Vector3(const float x, const float y, const float z);
	Vector3(const Vector2 & v);
	Vector3(const Vector2 & v, const float z);
	Vector3(const Vector3 & v);
	Vector3(const Vector4 & v);
	Vector3(const Point & p);
	virtual ~Vector3(void);

	Vector3 crossProduct(const Vector3 & otherVector) const;
	const float dotProduct(const Vector3 & otherVector) const;
	const float distance(const Vector3 & otherVector) const;
	const bool isZero() const;
	const float length() const;
	Vector3 normal(const Vector3 & otherVector) const;
	void normalise();
	Vector3 normalised() const;
	void reset();
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	const float x() const;
	const float y() const;
	const float z() const;
	Point toPoint() const;
	Vector2 toVector2() const;
	Vector4 toVector4() const;
	
	Vector3 & operator+=(const Vector3 & v);
	Vector3 & operator-=(const Vector3 & v);
	Vector3 & operator*=(const float factor);
	Vector3 & operator*=(const Vector3 & v);
	Vector3 & operator/=(const float divisor);
	Vector3 & operator=(const Vector3 & v);

	// Static public members
	static Vector3 forward();
	static Vector3 up();
	static Vector3 right();
	static Vector3 crossProduct(const Vector3 & a, const Vector3 & b);
	static const float dotProduct(const Vector3 & a, const Vector3 & b);
	static const float distance(const Vector3 & a, const Vector3 & b);
	static Vector3 normal(const Vector3 & a, const Vector3 & b);
	static Vector3 normal(const Vector3 & a, const Vector3 & b, const Vector3 & c);

	// Related non-members
	friend Vector3 operator+(const Vector3 & a, const Vector3 & b);
	friend Vector3 operator-(const Vector3 & a, const Vector3 & b);
	friend Vector3 operator-(const Vector3 & v);
	friend Vector3 operator*(const float factor, const Vector3 & v);
	friend Vector3 operator*(const Vector3 & v, const float factor);
	friend Vector3 operator/(const Vector3 & v, const float divisor);
	friend const bool operator==(const Vector3 & a, const Vector3 & b);
	friend const bool operator!=(const Vector3 & a, const Vector3 & b);
	friend std::ostream & operator<<(std::ostream & out, const Vector3 & v);

private:
	void copyDataFromSourceToDestination(const Vector3 & source, Vector3 & destination);

};
}

#endif // PRISM_VECTOR3_H_
