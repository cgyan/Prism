/*
 * Char.cpp
 * v0.*
 *
 *  Created on: Jul 18, 2016
 *      Author: iainhemstock
 */

#include <prism/Char.h>

namespace prism {

/**
 * Create a null character i.e. \0
 */
Char::Char()
	: c_('\0')
{}

/**
 * Creates a character set to \em c.
 */
Char::Char(const char c)
	: c_(c)
{}

/**
 * Detroys this character.
 */
Char::~Char() {}

/**
 * @return Returns true if this character is in the range [a-z] or [A-Z], false otherwise.
 */
const bool Char::isAlpha() const { return isLower() || isUpper(); }

/**
 * @return Returns true if this character is in the range [A-Z], false otherwise.
 */
const bool Char::isLower() const { return c_ >=97 && c_ <= 122; }

/**
 * @return Returns true if the character is null i.e. '\0', false otherwise.
 */
const bool Char::isNull() const { return c_ == '\0'; }

/**
 * @return Returns true if this character is the range [a-z], false otherwise.
 */
const bool Char::isUpper() const { return c_ >=65 && c_ <= 90; }

/**
 * @return Returns this Char as a standard char.
 */
const char Char::tochar() const { return c_; }

/**
 * @return Returns a copy of this Char with \em i added to it.
 */
Char & Char::operator +=(const int i) { c_ += i; return *this; }

/**
 * @return Returns a copy of this Char with \em i subtracted from it.
 */
Char & Char::operator -=(const int i) { c_ -= i; return *this; }

/**
 * Allows an instance of Char to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Char & c) {
	out << "Char [" << &c << "] '" << c.c_ << "'";
	return out;
}

} /* namespace prism */
