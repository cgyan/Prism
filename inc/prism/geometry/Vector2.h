#ifndef PRISM_VECTOR2_H_
#define PRISM_VECTOR2_H_

#include <ostream>

namespace prism {

class Point;
class Vector3;
class Vector4;

class Vector2
{
private:
	float m_x, m_y;

public:
	Vector2(void);
	Vector2(const float x, const float y);
	Vector2(const Vector2 & v);
	Vector2(const Vector3 & v);
	Vector2(const Vector4 & v);
	Vector2(const Point & p);
	virtual ~Vector2(void);

	const float dotProduct(const Vector2 & otherVector) const;
	const float distance(const Vector2 & otherVector) const;
	const bool isZero() const;
	const float length() const;
	void normalise();
	Vector2 normalised() const;
	void reset();
	void setX(const float x);
	void setY(const float y);
	const float x() const;
	const float y() const;
	Point toPoint() const;
	Vector3 toVector3() const;
	Vector4 toVector4() const;
	
	Vector2 & operator+=(const Vector2 & v);
	Vector2 & operator-=(const Vector2 & v);
	Vector2 & operator*=(const float factor);
	Vector2 & operator*=(const Vector2 & v);
	Vector2 & operator/=(const float divisor);
	Vector2 & operator=(const Vector2 & v);

	// Static public members
	static const float dotProduct(const Vector2 & a, const Vector2 & b);
	static const float distance(const Vector2 & a, const Vector2 & b);

	// Related non-members
	friend Vector2 operator+(const Vector2 & a, const Vector2 & b);
	friend Vector2 operator-(const Vector2 & a, const Vector2 & b);
	friend Vector2 operator-(const Vector2 & v);
	friend Vector2 operator*(const float factor, const Vector2 & v);
	friend Vector2 operator*(const Vector2 & v, const float factor);
	friend Vector2 operator/(const Vector2 & v, const float divisor);
	friend const bool operator==(const Vector2 & a, const Vector2 & b);
	friend const bool operator!=(const Vector2 & a, const Vector2 & b);
	friend std::ostream & operator<<(std::ostream & out, const Vector2 & v);

private:
	void copyDataFromSourceToDestination(const Vector2 & source, Vector2 & destination);

};
}

#endif // PRISM_VECTOR2_H_
