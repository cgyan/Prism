/*
 * Size.h
 * v0.1
 *
 *  Created on: Jul 1, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_SIZE_H_
#define PRISM_SIZE_H_

#include <ostream>

namespace prism {

class Size {
private:
	int m_width;
	int m_height;

public:
	Size();
	Size(const int width, const int height);
	Size(const Size &copy);
	virtual ~Size();

	const int 	height() const;
	const bool 	isEmpty() const;
	const bool 	isNull() const;
	const bool 	isValid() const;
	void 		setHeight(const int height);
	void 		setWidth(const int width);
	void 		scale(const int widthFactor, const int heightFactor);
	void		scale(const Size &size);
	Size 		scaled(const int widthFactor, const int heightFactor) const;
	Size		scaled(const Size &size) const;
	void		transpose();
	Size		transposed() const;
	const int 	width() const;

	Size & operator+=(const Size &size);
	Size & operator-=(const Size &size);
	Size & operator*=(const Size &size);
	Size & operator/=(const Size &size);
	Size & operator=(const Size &size);

	// related non-members
	friend const bool operator==(const Size &s1, const Size &s2);
	friend const bool operator!=(const Size &s1, const Size &s2);
	friend Size operator+(const Size &s1, const Size &s2);
	friend Size operator-(const Size &s1, const Size &s2);
	friend Size operator*(const Size &size, const int factor);
	friend Size operator*(const int factor, const Size &size);
	friend Size operator/(const Size &size, const int factor);
	friend std::ostream & operator<<(std::ostream & out, const Size & size);
};

} /* namespace prism */

#endif /* PRISM_SIZE_H_ */
