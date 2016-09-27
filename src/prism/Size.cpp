/*
 * Size.cpp
 * v0.1
 *
 *  Created on: Jul 1, 2016
 *      Author: iainhemstock
 */

#include <prism/h/Size.h>
#include <iostream>


namespace prism {

/**
 * Creates a Size object with a width and height of 0.
 */
Size::Size()
	: m_width(0), m_height(0)
{}

/**
 * Creates a Size object setting the width and height to \em \b width and \em \b height respectively.
 */
Size::Size(const int width, const int height)
	: m_width(width), m_height(height)
{}

/**
 * Copy constructor makes a copy of the Size object passed in.
 */
Size::Size(const Size &copy) {
	m_width = copy.width();
	m_height = copy.height();
}

/**
 * Destroys this Size object.
 */
Size::~Size() {}

/**
 * Returns the height of this Rect.
 */
const int Size::height() const {
	return this->m_height;
}

/**
 * Returns true if either the width or the height is less than 1, false otherwise.
 */
const bool Size::isEmpty() const {
	return m_width < 1 || m_height < 1;
}

/**
 * Returns true if both the width and height are 0, false otherwise.
 */
const bool Size::isNull() const {
	return m_width == 0 && m_height == 0;
}

/**
 * Returns true if both the width and height are greater than 0, false otherwise.
 */
const bool Size::isValid() const {
	return m_width > 0 && m_height > 0;
}

/**
 * Sets the height to \em height.
 */
void Size::setHeight(const int height) {
	this->m_height = height;
}

/**
 * Sets the width to \em width.
 */
void Size::setWidth(const int width) {
	this->m_width = width;
}

/**
 * Scales the dimension of the Size object by multiplying the width by \em widthFactor
 * and multiplying the height by \em heightFactor.
 */
void Size::scale(const int widthFactor, const int heightFactor) {
	m_width = m_width * widthFactor;
	m_height = m_height * heightFactor;
}

/**
 * Scales the dimension of this Size object using \em size.
 */
void Size::scale(const Size &size) {
	m_width = m_width * size.width();
	m_height = m_height * size.height();
}

/**
 * Returns a new Size object which has the dimensions of this Size object scaled
 * by the \em widthFactor and \em heightFactor.
 */
Size Size::scaled(const int widthFactor, const int heightFactor) const {
	Size s(*this);
	s.scale(widthFactor, heightFactor);

	return s;
}

/**
 * Returns a new Size object that has the dimensions of this Size object scaled
 * by \em size.
 */
Size Size::scaled(const Size &size) const {
	Size s(*this);
	s.scale(size);

	return s;
}

/**
 * Swaps the width and height.
 */
void Size::transpose() {
	int temp = m_width;
	m_width = m_height;
	m_height = temp;
}

/**
 * Returns a new Size object with the width and height swapped.
 */
Size Size::transposed() const {
	Size s(*this);
	s.transpose();

	return s;
}

/**
 * Returns the width of this Rect.
 */
const int Size::width() const {
	return this->m_width;
}

/**
 * Adds \em size to this Size object and returns this Size.
 */
Size& Size::operator +=(const Size &size) {
	m_width += size.width();
	m_height += size.height();

	return *this;
}

/**
 * Subtracts \em size from this Size object and returns this Size.
 */
Size& Size::operator -=(const Size &size) {
	m_width -= size.width();
	m_height -= size.height();

	return *this;
}

/**
 * Multiplies \em size by this Size object and returns this Size.
 */
Size& Size::operator *=(const Size &size) {
	m_width *= size.width();
	m_height *= size.height();

	return *this;
}

/**
 * Divides this Size by \em size rounding to integer precision and returns
 * this Size.
 */
Size& Size::operator /=(const Size &size) {
	m_width /= size.width();
	m_height /= size.height();

	return *this;
}

/**
 *
 */
Size& Size::operator =(const Size &size) {
	m_width = size.width();
	m_height = size.height();

	return *this;
}

/**
 * ==========================================================
 * Related non-members
 * ==========================================================
 */

/**
 * Returns true if the widths are equal and the heights are equal of both Size objects.
 */
const bool operator==(const Size &s1, const Size &s2) {
	return s1.m_width == s2.m_width && s1.m_height == s2.m_height;
}

/**
 * Returns true if the widths are equal and the heights are not equal of both Size objects.
 */
const bool operator!=(const Size &s1, const Size &s2) {
	return !(s1==s2);
}

/**
 * Adds \em s1 and \em s2 together and returns a new Size object.
 */
Size operator+(const Size &s1, const Size &s2) {
	Size s;
	s.setWidth(s1.width() + s2.width());
	s.setHeight(s1.height() + s2.height());

	return s;
}

/**
 * Subtracts \em s2 from \em s1 and returns a new Size object.
 */
Size operator-(const Size &s1, const Size &s2) {
	Size s;
	s.setWidth(s1.width() - s2.width());
	s.setHeight(s1.height() - s2.height());

	return s;
}

/**
 * Multiplies \em size by \em factor and returns a new Size object.
 */
Size operator*(const Size &size, const int factor) {
	Size s(size);
	s.scale(factor, factor);

	return s;
}

/**
 * Multiplies \em size by \em factor and returns a new Size object.
 */
Size operator*(const int factor, const Size &size) {
	return size * factor;
}

/**
 * Divides \em size by \em factor rounding to integer precision and returns a new Size object.
 */
Size operator/(const Size &size, const int factor) {
	Size s;
	s.setWidth(size.width() / factor);
	s.setHeight(size.height() / factor);

	return s;
}

/**
 * Allows an instance of Size to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Size & size) {
	out << "Size [" << &size << "]: (width=" << size.m_width << ", height=" << size.m_height << ")";
	return out;
}

} /* namespace prism */
