#ifndef PRISM_MATRIX4_H_
#define PRISM_MATRIX4_H_

#include <ostream>

namespace prism {

class Vector3;
class Vector4;
class Point;

class Matrix4
{
private:
	float m_data[16];

public:
	Matrix4(void);
	Matrix4(const float * values);
	Matrix4(const float r1c1, const float r1c2, const float r1c3, const float r1c4,
			  const float r2c1, const float r2c2, const float r2c3, const float r2c4,
			  const float r3c1, const float r3c2, const float r3c3, const float r3c4, 
			  const float r4c1, const float r4c2, const float r4c3, const float r4c4); 
	Matrix4(const Matrix4 & copy);
	virtual ~Matrix4(void);

	Vector4 column(const int index) const;
	const float * constData() const;
	void copyDataTo(float * destMatrix);
	float * data();
	const float determinant() const;
	void fill(const float value);
	const bool hasInverse() const;
	Matrix4 inverted() const;
	const bool isIdentity() const;
	void rotate(Vector3 & axis, const float degrees);
	void rotate(const float xAxis, const float yAxis, const float zAxis, const float degrees);
	Vector4 row(const int index) const;
	void scale(const float factor);
	void scale(const float x, const float y, const float z=1);
	void setColumn(const int col, const Vector4 & vec);
	void setRow(const int row, const Vector4 & vec);
	void setIdentity();
	void translate(const float x, const float y, const float z=0);
	Matrix4 transposed() const;

	float & operator()(const int row, const int col);
	const float & operator()(const int row, const int col) const;
	Matrix4 & operator=(const Matrix4 & copy);

//  Related non-members
//  ===================
	friend Matrix4 operator+(const Matrix4 & m1, const Matrix4 & m2);
	friend Matrix4 operator-(const Matrix4 & m1, const Matrix4 & m2);
	friend Matrix4 operator-(const Matrix4 & m);
	friend Matrix4 operator*(const Matrix4 & m1, const Matrix4 & m2);
	friend Matrix4 operator*(const float factor, const Matrix4 & m);
	friend Matrix4 operator*(const Matrix4 & m, const float factor);
	friend Matrix4 operator*(const Matrix4 & m1, const float * m2);
	friend Matrix4 operator*(const float * m1, const Matrix4 & m2);
	friend Vector3 operator*(const Vector3 & v, const Matrix4 & m);
	friend Vector3 operator*(const Matrix4 & m, const Vector3 & v);
	friend Vector4 operator*(const Vector4 & v, const Matrix4 & m);
	friend Vector4 operator*(const Matrix4 & m, const Vector4 & v);
	friend Point operator*(const Point & p, const Matrix4 & m);
	friend Point operator*(const Matrix4 & m, const Point & p);
	friend Matrix4 operator/(const Matrix4 & m, const float divisor);
	friend const bool operator==(const Matrix4 & m1, const Matrix4 & m2);
	friend const bool operator!=(const Matrix4 & m1, const Matrix4 & m2);
	friend std::ostream & operator<<(std::ostream & out, const Matrix4 & matrix);

private:
	void copyDataFromSourceToDestination(const float * sourceMatrix, float * destinationMatrix);
	void multiplyMatrices(const float * a, const float * b, float * ab) const;
};
}

#endif /* PRISM_MATRIX4_H_ */
