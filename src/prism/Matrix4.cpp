#include <prism/h/Matrix4.h>
#include <prism/h/Vector3.h>
#include <prism/h/Vector4.h>
#include <prism/h/Point.h>
#include <prism/h/Mathf.h>
#include <iostream>
#include <math.h>

namespace prism {

/**
 * Inits with a 'default' identity matrix.
 *
 * [1 0 0 0]
 * [0 1 0 0]
 * [0 0 1 0]
 * [0 0 0 1]
 *
 */
Matrix4::Matrix4(void) 
{
	setIdentity();
}

/**
 * Constructs a matrix from the pointer to the sixteen floating-point values passed in.
 * It is assumed that 'values' is in a row-major order.
 *
 * [m1  m2  m3   m4 ]
 * [m5  m6  m7   m8 ]
 * [m9  m10 m11  m12]
 * [m13 m14 m15  m16]
 *
 */
Matrix4::Matrix4(const float * values) 
{
	copyDataFromSourceToDestination(values, m_data);
}

/**
 * Constructs a matrix from the sixteen floating-point values passed in.
 * It is assumed that the values are in row-major order.
 *
 * [m1  m2  m3   m4 ]
 * [m5  m6  m7   m8 ]
 * [m9  m10 m11  m12]
 * [m13 m14 m15  m16]
 *
 */
Matrix4::Matrix4(const float r1c1, const float r1c2, const float r1c3, const float r1c4,
			         const float r2c1, const float r2c2, const float r2c3, const float r2c4,
			         const float r3c1, const float r3c2, const float r3c3, const float r3c4, 
			         const float r4c1, const float r4c2, const float r4c3, const float r4c4)
{
	m_data[0]  = r1c1;	m_data[1]  = r1c2;	m_data[2]  = r1c3;	m_data[3]  = r1c4;
	m_data[4]  = r2c1;	m_data[5]  = r2c2;	m_data[6]  = r2c3;	m_data[7]  = r2c4;
	m_data[8]  = r3c1;	m_data[9]  = r3c2;	m_data[10] = r3c3;	m_data[11] = r3c4;
	m_data[12] = r4c1;	m_data[13] = r4c2;	m_data[14] = r4c3;	m_data[15] = r4c4;
}

/**
 * Copy constructor
 * Simply copies the data array from copy to this matrix.
 */
Matrix4::Matrix4(const Matrix4 & copy)
{
	copyDataFromSourceToDestination(copy.m_data, this->m_data);
}

/**
 *
 */
Matrix4::~Matrix4(void) {

}

/**
 * Returns a Vector 4 that is composed from the column specified by index from this matrix.
 * The index is zero-based so an index of 0 retrieves the first column and an index of 3 retrieves
 * the last column.
 */
Vector4 Matrix4::column(const int index) const {
	float x,y,z,w;
	x = m_data[index];
	y = m_data[4+index];
	z = m_data[8+index];
	w = m_data[12+index];

	return Vector4(x,y,z,w);
}

/**
 * Returns a constant pointer to the raw data of this matrix.
 * The data is in column-major order.
 */
const float * Matrix4::constData() const {
	return &m_data[0];
}

/**
 * Copies the raw data from this matrix and 
 * populates the supplied matrix with that data
 */
void Matrix4::copyDataTo(float * destMatrix) {
	copyDataFromSourceToDestination(m_data, destMatrix);
}

/**
 * Returns a pointer to the raw data of this matrix.
 * The data is in column-major order.
 */
float * Matrix4::data() {
	return &m_data[0];
}

/**
 * Returns a single number which is the determinant of this matrix. 
 * One use for the determinant is if the determinant is 0 then this matrix is not invertible
 * i.e. hasInverse() is false whereas if it is non-zero then it is invertible. 
 * This implementation multiplies each element in the first row of the 
 * matrix by its corresponding cofactor and sums them together to produce the determinant.
 */
const float Matrix4::determinant() const {
	const float * m = m_data;

	return m[0] * ( m[5] * (m[10] * m[15] - m[11]*m[14])   + 
				    m[6] * (m[11] * m[13] - m[9]*m[15])    + 
				    m[7] * (m[9]  * m[14] - m[10]*m[13]) ) - 
		   m[1] * ( m[4] * (m[10] * m[15] - m[11]*m[14])   + 
				    m[6] * (m[11] * m[12] - m[8]*m[15])    + 
				    m[7] * (m[8]  * m[14] - m[10]*m[12]) ) + 
		   m[2] * ( m[4] * (m[9]  * m[15] - m[11]*m[13])   + 
				    m[5] * (m[11] * m[12] - m[8]*m[15])    + 
				    m[7] * (m[8]  * m[13] - m[9]*m[12])  ) - 
		   m[3] * ( m[4] * (m[9]  * m[14] - m[10]*m[13])   + 
				    m[5] * (m[10] * m[12] - m[8]*m[14])    + 
				    m[6] * (m[8]  * m[13] - m[9]*m[12])  );

	/*return m[0] * (m[5]*(m[10]*m[15] - m[11]*m[14]) + m[6] * (m[11]*m[13] - m[9]*m[15]) + m[7] * (m[9]*m[14] - m[10]*m[13]))
		 - m[1] * (m[4]*(m[10]*m[15] - m[11]*m[14]) + m[6] * (m[11]*m[12] - m[8]*m[15]) + m[7] * (m[8]*m[14] - m[10]*m[12]))
		 + m[2] * (m[4]*(m[9]*m[15]  - m[11]*m[13]) + m[5] * (m[11]*m[12] - m[8]*m[15]) + m[7] * (m[8]*m[13] - m[9]*m[12]))
		 - m[3] * (m[4]*(m[9]*m[14]  - m[10]*m[13]) + m[5] * (m[10]*m[12] - m[8]*m[14]) + m[6] * (m[8]*m[13] - m[9]*m[12]));*/
}

/**
 * Fills each element of the matrix with the specified value
 */
void Matrix4::fill(const float value) {
	for (int i=0; i<16; i++)
		m_data[i] = value;
}

/**
 * Returns true if this matrix has an inverse and false if not.
 * The method used is to calculate the determinant of the matrix first. If the determinant is 0 then the
 * matrix does not have an inverse. If the determinant is non-zero then it does have an inverse.
 */
const bool Matrix4::hasInverse() const {
	if (determinant()) return true;
	return false;
}

/**
 *
 */
Matrix4 Matrix4::inverted() const {
	const float * m = constData();
	float cofactors[16];

    cofactors[0] =	m[5]  * m[10] * m[15] - 
					m[5]  * m[11] * m[14] - 
					m[9]  * m[6]  * m[15] + 
					m[9]  * m[7]  * m[14] +
					m[13] * m[6]  * m[11] - 
					m[13] * m[7]  * m[10];

    cofactors[4] = -m[4]  * m[10] * m[15] + 
					m[4]  * m[11] * m[14] + 
					m[8]  * m[6]  * m[15] - 
					m[8]  * m[7]  * m[14] - 
					m[12] * m[6]  * m[11] + 
					m[12] * m[7]  * m[10];

    cofactors[8] =	m[4]  * m[9] * m[15] - 
					m[4]  * m[11] * m[13] - 
					m[8]  * m[5] * m[15] + 
					m[8]  * m[7] * m[13] + 
					m[12] * m[5] * m[11] - 
					m[12] * m[7] * m[9];

    cofactors[12] = -m[4]  * m[9] * m[14] + 
					m[4]  * m[10] * m[13] +
					m[8]  * m[5] * m[14] - 
					m[8]  * m[6] * m[13] - 
					m[12] * m[5] * m[10] + 
					m[12] * m[6] * m[9];

    cofactors[1] = -m[1]  * m[10] * m[15] + 
					m[1]  * m[11] * m[14] + 
					m[9]  * m[2] * m[15] - 
					m[9]  * m[3] * m[14] - 
					m[13] * m[2] * m[11] + 
					m[13] * m[3] * m[10];

    cofactors[5] =	m[0]  * m[10] * m[15] - 
					m[0]  * m[11] * m[14] - 
					m[8]  * m[2] * m[15] + 
					m[8]  * m[3] * m[14] + 
					m[12] * m[2] * m[11] - 
					m[12] * m[3] * m[10];

    cofactors[9] = -m[0]  * m[9] * m[15] + 
					m[0]  * m[11] * m[13] + 
					m[8]  * m[1] * m[15] - 
					m[8]  * m[3] * m[13] - 
					m[12] * m[1] * m[11] + 
					m[12] * m[3] * m[9];

    cofactors[13] = m[0]  * m[9] * m[14] - 
					m[0]  * m[10] * m[13] - 
					m[8]  * m[1] * m[14] + 
					m[8]  * m[2] * m[13] + 
					m[12] * m[1] * m[10] - 
					m[12] * m[2] * m[9];

    cofactors[2] =	m[1]  * m[6] * m[15] - 
					m[1]  * m[7] * m[14] - 
					m[5]  * m[2] * m[15] + 
					m[5]  * m[3] * m[14] + 
					m[13] * m[2] * m[7] - 
					m[13] * m[3] * m[6];

    cofactors[6] = -m[0]  * m[6] * m[15] + 
					m[0]  * m[7] * m[14] + 
					m[4]  * m[2] * m[15] - 
					m[4]  * m[3] * m[14] - 
					m[12] * m[2] * m[7] + 
					m[12] * m[3] * m[6];

    cofactors[10] = m[0]  * m[5] * m[15] - 
					m[0]  * m[7] * m[13] - 
					m[4]  * m[1] * m[15] + 
					m[4]  * m[3] * m[13] + 
					m[12] * m[1] * m[7] - 
					m[12] * m[3] * m[5];

    cofactors[14] = -m[0]  * m[5] * m[14] + 
					m[0]  * m[6] * m[13] + 
					m[4]  * m[1] * m[14] - 
					m[4]  * m[2] * m[13] - 
					m[12] * m[1] * m[6] + 
					m[12] * m[2] * m[5];

    cofactors[3] = -m[1] * m[6] * m[11] + 
					m[1] * m[7] * m[10] + 
					m[5] * m[2] * m[11] - 
					m[5] * m[3] * m[10] - 
					m[9] * m[2] * m[7] + 
					m[9] * m[3] * m[6];

    cofactors[7] =	m[0] * m[6] * m[11] - 
					m[0] * m[7] * m[10] - 
					m[4] * m[2] * m[11] + 
					m[4] * m[3] * m[10] + 
					m[8] * m[2] * m[7] - 
					m[8] * m[3] * m[6];

    cofactors[11] = -m[0] * m[5] * m[11] + 
					m[0] * m[7] * m[9] + 
					m[4] * m[1] * m[11] - 
					m[4] * m[3] * m[9] - 
					m[8] * m[1] * m[7] + 
					m[8] * m[3] * m[5];

    cofactors[15] = m[0] * m[5] * m[10] - 
					m[0] * m[6] * m[9] - 
					m[4] * m[1] * m[10] + 
					m[4] * m[2] * m[9] + 
					m[8] * m[1] * m[6] - 
					m[8] * m[2] * m[5];

	// cofactors matrix does not need to be transposed at this point as is usual with classical adjoint.
	// The way each element in the cofactors matrix is calculated above effectively transposes it ready for the next stage.

	float det = determinant();
	if (det == 0)
		return Matrix4();

	det = 1/det;

	float inverse[16];
	for (int i=0; i<16; i++)
		inverse[i] = cofactors[i] * det;

	return Matrix4(inverse);
}

/**
 * Checks if this matrix is in the identity form, returns true if it is and false if not.
 */
const bool Matrix4::isIdentity() const {
	bool bIdent = true;

	for (int i=0; i<16; i++) {
		if (i==0 || i==5 || i==10 || i==15) {
			if (m_data[i] != 1) {
				bIdent = false;
				break;
			}
		}
		else {
			if (m_data[i] != 0) {
				bIdent = false;
				break;
			}
		}
	}
	return bIdent;
}

/**
 * The Vector3 that represents the axis of rotation should be normalised but if it isn't this method
 * does it for you.
 */
void Matrix4::rotate(Vector3 & axis, const float degrees) {
//	using namespace prism::utils;
	
	float angle = degrees;
	prism::Mathf::degreeToRadian(angle);

	if (axis.length() != 1)
		axis.normalise();

	float c = cosf(angle);
	float s = sinf(angle);
	float x = axis.x();
	float y = axis.y();
	float z = axis.z();
	
	const float r[16] = {
		(x*x)*(1-c)+c,        (x*y)*(1-c)+(z*s),    (x*z)*(1-c)-(y*s),    0,
        (y*x)*(1-c)-(z*s),    (y*y)*(1-c)+c,        (y*z)*(1-c)+(x*s),    0,
        (x*z)*(1-c)+(y*s),    (y*z)*(1-c)-(x*s),    (z*z)*(1-c)+c,        0,
        0,                    0,                    0,                    1
	};

	const float * m = constData();
	float mr[16];
	multiplyMatrices(m, r, mr);

	copyDataFromSourceToDestination(mr, m_data);
}

/**
 *
 */
void Matrix4::rotate(const float xAxis, const float yAxis, const float zAxis, const float degrees) {
	Vector3 v(xAxis, yAxis, zAxis);
	rotate(v, degrees);
}

/**
 * Returns a Vector 4 that is composed from the row specified by index from this matrix.
 * The index is zero-based so an index of 0 retrieves the first row and an index of 3 retrieves
 * the last row.
 */
Vector4 Matrix4::row(const int index) const {
	float x,y,z,w;
	x = m_data[index*4];
	y = m_data[1+index*4];
	z = m_data[2+index*4];
	w = m_data[3+index*4];

	return Vector4(x,y,z,w);
}

//void degToRad(const float deg, float & rad) {
//	rad = deg * (180 / 3.14);
//}

/**
 *
 */
//void Matrix4::rotate(const float angle, const float x, const float y, const float z) {
//	float rad;
//	degToRad(angle, rad);
//	float r[16] = { 
//		(x*x)*(1-cosf(rad))+cosf(rad),		(x*y)*(1-cosf(rad))-(z*sinf(rad)),	(x*z)*(1-cosf(rad))+(y*sinf(rad)),	0,
//        (y*x)*(1-cosf(rad))+z*sinf(rad),	(y*y)*(1-cosf(rad))+cosf(rad),      (y*z)*(1-cosf(rad))-(x*sinf(rad)),  0,
//        (x*z)*(1-cosf(rad))-(y*sinf(rad)),  (y*z)*(1-cosf(rad))+(x*sinf(rad)),  (z*z)*(1-cosf(rad))+cosf(rad),      0,
//         0,							         0,                                  0,                                 1
//	};
//	const float * m = constData();
//	float mr[16];
//	multiplyMatrices(m, r, mr);
//}

/**
 * Multiplies this matrix by another matrix that scales this matrix by factor.
 * i.e. if this matrix is M and the scaling matrix is S, then the raw data of this
 * matrix is set to MS.
 * Note: each subsequent call to scale() builds on top of the last transformation. So, initially scale(2)
 * scales the matrix to [2], then if called again, say, scale(5) then the resulting scaling transformation 
 * becomes [10]. 
 * To actually scale a matrix to a given size call setIdentity() first which resets the matrix 
 * and then call scale(*).
 */
void Matrix4::scale(const float factor) {
	scale(factor, factor, factor);
}

/**
 * Multiplies this matrix by another matrix that scales this matrix by x, y and z.
 * i.e. if this matrix is M and the scaling matrix is S, then the raw data of this
 * matrix is set to MS.
 * Note: each subsequent call to scale() builds on top of the last transformation. So, initially scale(2,2)
 * scales the matrix to [2,2], then if called again, say, scale(5,5) then the resulting scaling transformation 
 * becomes [10,10]. 
 * To actually scale a matrix to a given size call setIdentity() first which resets the matrix 
 * and then call scale(*,*).
 */
void Matrix4::scale(const float x, const float y, const float z) {
	const float s[16] = { x,0,0,0,
					      0,y,0,0,
					      0,0,z,0,
					      0,0,0,1 };
	const float * m = constData();
	float ms[16];
	multiplyMatrices(m, s, ms);

	copyDataFromSourceToDestination(ms, m_data);
}

/**
 * Sets the specified column of this matrix using the values of vector v.
 * The col is zero-based so col 0 is the first column and col 3 is the last column.
 */
void Matrix4::setColumn(const int col, const Vector4 & v) {
	m_data[col] = v.x();
	m_data[4+col] = v.y();
	m_data[8+col] = v.z();
	m_data[12+col] = v.w();
}

/**
 * Sets the specified row of this matrix using the values of vector v.
 * The row is zero-based so row 0 is the first row and row 3 is the last row.
 */
void Matrix4::setRow(const int row, const Vector4 & v) {
	m_data[row*4] = v.x();
	m_data[1+row*4] = v.y();
	m_data[2+row*4] = v.z();
	m_data[3+row*4] = v.w();
}

/**
 * Sets this matrix to the identity matrix.
 * [1 0 0 0]
 * [0 1 0 0]
 * [0 0 1 0]
 * [0 0 0 1]
 */
void Matrix4::setIdentity() {
	int i = 0;
	for(int col=0; col<4; col++) {
		for (int row=0; row<4; row++) {
			if (row == col) m_data[i] = 1;
			else m_data[i] = 0;
			i++;
		}
	}
}

/**
 * Multiplies this matrix by another matrix that translates this matrix by the floats x, y and z.
 * i.e. if this matrix is M and the translation matrix is T, then the raw data of this
 * matrix is set to MT.
 * Note: each subsequent call to translate() builds on top of the last transformation. So, initially translate(5,5,5)
 * translates the matrix to [5,5,5], then if called again, say, translate(15,15,15) then the resulting translating
 * transformation becomes [20,20,20]. 
 * To actually place a matrix at a given location call setIdentity() first which resets the matrix 
 * and then call translate(*,*,*).
 */
void Matrix4::translate(const float x, const float y, const float z) {
	const float t[16] = { 1,0,0,0,
					      0,1,0,0,
					      0,0,1,0,
					      x,y,z,1 };
	const float * m = constData();
	float mt[16];
	multiplyMatrices(m, t, mt);

	copyDataFromSourceToDestination(mt, m_data);
}

/**
 * Returns a new matrix which is a copy of this matrix that 
 * has been transposed across its diagonal. 
 * This matrix remains unaltered, however.
 */
Matrix4 Matrix4::transposed() const {
	float tmp1[16];
	float tmp2[16];
	Matrix4 tempMatrix(m_data);
	tempMatrix.copyDataTo(tmp1);
	tempMatrix.copyDataTo(tmp2);

	tmp1[1]  = tmp2[4];
	tmp1[2]  = tmp2[8];
	tmp1[3]  = tmp2[12];
	tmp1[4]  = tmp2[1];
	tmp1[6]  = tmp2[9];
	tmp1[7]  = tmp2[13];
	tmp1[8]  = tmp2[2];
	tmp1[9]  = tmp2[6];
	tmp1[11] = tmp2[14];
	tmp1[12] = tmp2[3];
	tmp1[13] = tmp2[7];
	tmp1[14] = tmp2[11];

	return Matrix4(tmp1);
}

/**
 * Returns a reference to the element located at (row, col) in the matrix.
 * row and col are zero based so (0,0) is the first element and (3,3) is the last element.
 * This just provides easy access to directly modify the internal matrix.
 */
float & Matrix4::operator()(const int row, const int col) {
	int index = 4*row+col;
	return m_data[index];
}

/**
 * Returns a constant reference to the element located at (row, col) in the matrix.
 * row and col are zero based so (0,0) is the first element and (3,3) is the last element.
 */
const float & Matrix4::operator()(const int row, const int col) const {
	int index = 4*row+col;
	return m_data[index];
}

/**
 * Overloaded assignment operator - copies the data array from copy to this matrix.
 * A quick check prevents a matrix being assigned to to itself which is dangerous if dynamic memory is involved.
 */
Matrix4 & Matrix4::operator=(const Matrix4 & copy) {
	if (this != &copy) {
		copyDataFromSourceToDestination(copy.m_data, this->m_data);
	}
	return *this;
}

/****************************************************
	Related non-members
****************************************************/
/**
 * Returns a new Matrix4 which is the sum of m1 and m2.
 */
Matrix4 operator+(const Matrix4 & m1, const Matrix4 & m2) {
	const float * a = m1.constData();
	const float * b = m2.constData();
	float ab[16];

	for (int i=0; i<16; i++)
		ab[i] = a[i] + b[i];

	return Matrix4(ab);
}

/**
 * Returns a new Matrix4 which is the result of subtracting m2 from m1.
 */
Matrix4 operator-(const Matrix4 & m1, const Matrix4 & m2) {
	const float * a = m1.constData();
	const float * b = m2.constData();
	float ab[16];

	for (int i=0; i<16; i++)
		ab[i] = a[i] - b[i];

	return Matrix4(ab);
}

/**
 * Returns a new Matrix4 where each component of matrix m has been negated (multiplyed by -1).
 */
Matrix4 operator-(const Matrix4 & m) {
	const float * a = m.constData();
	float b[16];
	for (int i=0; i<16; i++) {
		if (a[i] == 0) b[i] = 0;
		else b[i] = a[i] * -1;
	}

	return Matrix4(b);
}
/**
 * Returns a new Matrix4 that is the product of m1 and m2 i.e. m1m2
 */
Matrix4 operator*(const Matrix4 & m1, const Matrix4 & m2) {
	const float * a = m1.constData();
	const float * b = m2.constData();
	float ab[16];
	m1.multiplyMatrices(a, b, ab);

	return Matrix4(ab);
}

/**
 * Returns a new Matrix4 where each component of m is multiplied by factor.
 */
Matrix4 operator*(const float factor, const Matrix4 & m) {
	const float * a = m.constData();
	float b[16];
	for (int i=0; i<16; i++) {
		b[i] = a[i];
		b[i] *= factor;
	}

	return Matrix4(b);
}

/**
 * Returns a new Matrix4 where each component of m is multiplied by factor.
 */
Matrix4 operator*(const Matrix4 & m, const float factor) {
	const float * a = m.constData();
	float b[16];
	for (int i=0; i<16; i++) {
		b[i] = a[i];
		b[i] *= factor;
	}

	return Matrix4(b);
}

/**
 * Returns a Matrix4 that is the result of multiplying a Matrix4 with a float array.
 */
Matrix4 operator*(const Matrix4 & m1, const float * m2) {
	const float * a = m1.constData();
	const float * b = m2;
	float ab[16];
	m1.multiplyMatrices(a, b, ab);

	return Matrix4(ab);
}

/**
 * Returns a Matrix4 that is the result of multiplying a Matrix4 with a float array.
 */
Matrix4 operator*(const float * m1, const Matrix4 & m2) {
	return operator*(m2, m1);
}

/**
 * Returns a Vector3 which has been transformed by the matrix M in the order of vM.
 */
Vector3 operator*(const Vector3 & v, const Matrix4 & m) {
	Vector4 v4(v,1);
	return Vector3(v4*m);
}

/**
 * Returns a Vector3 which has been transformed by the matrix M in the order of Mv.
 */
Vector3 operator*(const Matrix4 & m, const Vector3 & v) {
	Vector4 v4(v,1);
	return Vector3(m*v4);
}

/**
 * Returns a Vector4 which has been transformed by the matrix M in the order of vM.
 */
Vector4 operator*(const Vector4 & v, const Matrix4 & m) {
	float x,y,z,w;

	x = v.x() * m(0,0) + v.y() * m(1,0) + v.z() * m(2,0) + v.w() * m(3,0);
	y = v.x() * m(0,1) + v.y() * m(1,1) + v.z() * m(2,1) + v.w() * m(3,1);
	z = v.x() * m(0,2) + v.y() * m(1,2) + v.z() * m(2,2) + v.w() * m(3,2);
	w = v.x() * m(0,3) + v.y() * m(1,3) + v.z() * m(2,3) + v.w() * m(3,3);

	return Vector4(x,y,z,w);
	
}

/**
 * Returns a Vector4 which has been transformed by the matrix M in the order of Mv.
 */
Vector4 operator*(const Matrix4 & m, const Vector4 & v) {
	float x, y, z, w;

	x = v.x() * m(0,0) + v.y() * m(0,1) + v.z() * m(0,2) + v.w() * m(0,3);
	y = v.x() * m(1,0) + v.y() * m(1,1) + v.z() * m(1,2) + v.w() * m(1,3);
	z = v.x() * m(2,0) + v.y() * m(2,1) + v.z() * m(2,2) + v.w() * m(2,3);
	w = v.x() * m(3,0) + v.y() * m(3,1) + v.z() * m(3,2) + v.w() * m(3,3);
	
	return Vector4(x,y,z,w);
}

/**
 * Returns a Point which has been transformed by the matrix m in the order of pM
 */
Point operator*(const Point & p, const Matrix4 & m) {
	Vector4 v(p,0,1);
	v = v*m;
	return v.toPoint();
}

/**
 * Returns a Point which has been transformed by the matrix M in the order of Mp
 */
Point operator*(const Matrix4 & m, const Point & p) {
	Vector4 v(p,0,1);
	v = m*v;
	return v.toPoint();
}

/**
 * Returns a new Matrix4 where each component of matrix m is divided by divisor.
 * If divisor is 0 a new Matrix4 is returned set to the identity matrix instead.
 */
Matrix4 operator/(const Matrix4 & m, const float divisor) {
	if (divisor == 0) return Matrix4();

	const float * a = m.constData();
	float b[16];
	for (int i=0; i<16; i++) {
		b[i] = a[i] / divisor;
	}

	return Matrix4(b);
}

/**
 * Compares the elements of the two matrices and returns true if 
 * they contain the same data, false otherwise.
 */
const bool operator==(const Matrix4 & m1, const Matrix4 & m2) {
	bool out = true;
	for (int i=0; i<16; i++) {
		if (m1.m_data[i] != m2.m_data[i]) {
			out = false;
			break;
		}
	}

	return out;
}

/**
 * Compares the elements of the two matrices and returns true if 
 * they don't contain the same data, false otherwise.
 */
const bool operator!=(const Matrix4 & m1, const Matrix4 & m2) {
	bool out = false;
	for (int i=0; i<16; i++) {
		if (m1.m_data[i] != m2.m_data[i]){
			out = true;
			break;
		}
	}

	return out;
}

/**
 * Allows an instance of Matrx4x4 to be written to the ostream out and returns a reference to the ostream.
 * i.e. std::cout << matrix << std::endl;
 */
std::ostream & operator<<(std::ostream & out, const Matrix4 & matrix) {
	out << "Matrix4 (" << &matrix << ")\n";
	out << "------------------ \n";
	for (int i=0; i<16; i++) {
		out << matrix.m_data[i];
		if (i < 15) out << ", ";
		if ((i+1) % 4 == 0) out << " \n";
	}
	return out;
}

/**
 * Very simply copies the elements from source matrix to destination matrix one by one.
 */
void Matrix4::copyDataFromSourceToDestination(const float * source, float * destination) {
	for (int i=0; i<16; i++)
		destination[i] = source[i];
}

/**
 * Multiples float array matrices a and b together, in that order, the result of which is stored in the
 * float array ab. This method specifically multiplies the raw data matrices rather than the
 * object Matrix4 type. That can be done instead easily with the * operator
 * i.e. Matrix4 m_4x4 = m1_4x4 * m2_4x4
 */
void Matrix4::multiplyMatrices(const float * a, const float * b, float * ab) const {
	ab[0] = a[0]*b[0]   + a[1]*b[4]  + a[2]*b[8]   + a[3]*b[12];
	ab[1] = a[0]*b[1]   + a[1]*b[5]  + a[2]*b[9]   + a[3]*b[13];
	ab[2] = a[0]*b[2]   + a[1]*b[6]  + a[2]*b[10]  + a[3]*b[14];
	ab[3] = a[0]*b[3]   + a[1]*b[7]  + a[2]*b[11]  + a[3]*b[15];
	ab[4] = a[4]*b[0]   + a[5]*b[4]  + a[6]*b[8]   + a[7]*b[12];
	ab[5] = a[4]*b[1]   + a[5]*b[5]  + a[6]*b[9]   + a[7]*b[13];
	ab[6] = a[4]*b[2]   + a[5]*b[6]  + a[6]*b[10]  + a[7]*b[14];
	ab[7] = a[4]*b[3]   + a[5]*b[7]  + a[6]*b[11]  + a[7]*b[15];
	ab[8] = a[8]*b[0]   + a[9]*b[4]  + a[10]*b[8]  + a[11]*b[12];
	ab[9] = a[8]*b[1]   + a[9]*b[5]  + a[10]*b[9]  + a[11]*b[13];
	ab[10] = a[8]*b[2]  + a[9]*b[6]  + a[10]*b[10] + a[11]*b[14];
	ab[11] = a[8]*b[3]  + a[9]*b[7]  + a[10]*b[11] + a[11]*b[15];
	ab[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8]  + a[15]*b[12];
	ab[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9]  + a[15]*b[13];
	ab[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
	ab[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];

	for (int i=0; i<16; i++) {
		//ab[i] = static_cast<float>(static_cast<int>(ab[i] * 100.)) / 100.;
		prism::Mathf::correctFloatingPointError(ab[i]);
	}
}

}
