/*
 * Char.cpp
 * v0.*
 *
 *  Created on: Jul 18, 2016
 *      Author: iainhemstock
 */

#include <prism/core/Char.h>

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
 * Creates a character from the \em unicode value.
 */
Char::Char(const int unicode)
	: c_((char)unicode)
{}

/**
 * Detroys this character.
 */
Char::~Char() {}

/**
 * @return Returns true if the char is a control char, false otherwise.
 */
const bool Char::isControl() const { return c_ >= 0 && c_ <= 31; }

/**
 * @return Returns true if \em c is a control char, false otherwise.
 */
const bool Char::isControl(const Char & c) { Char d(c.c_); return d.isControl(); }

/**
 * @return Returns true if this character is a digit in the range [0-9], false otherwise.
 */
const bool Char::isNumber() const { return c_ >= 48 && c_ <= 57; }

/**
 * @return Returns true if \em c is a digit in the range [0-9], false otherwise.
 */
const bool Char::isNumber(const Char & c) { Char d(c.c_); return d.isNumber(); }

/**
 * @return Returns true if this character is in the range [a-z] or [A-Z], false otherwise.
 */
const bool Char::isLetter() const { return isLower() || isUpper(); }

/**
 * @return Returns true if \em c is in the range [a-z] or [A-Z], false otherwise.
 */
const bool Char::isLetter(const Char & c) { Char d(c.c_); return d.isLetter(); }

/**
 * @return Returns true if this character is a letter or number, false otherwise.
 */
const bool Char::isLetterOrNumber() const { return isLetter() || isNumber(); }

/**
 * @return Returns true if \em c is a letter or number, false otherwise.
 */
const bool Char::isLetterOrNumber(const Char & c) { Char d(c.c_); return d.isLetter() || d.isNumber(); }

/**
 * @return Returns true if this character is in the range [a-z], false otherwise.
 */
const bool Char::isLower() const { return c_ >=97 && c_ <= 122; }

/**
 * @return Returns true if this character is in the range [a-z], false otherwise.
 */
const bool Char::isLower(const Char & c) { Char d(c.c_); return d.isLower(); }

/**
 * @return Returns true if the character is null i.e. '\0', false otherwise.
 */
const bool Char::isNull() const { return c_ == '\0'; }

/**
 * @return Returns true if the character is printable, false otherwise.
 */
const bool Char::isPrint() const { return c_ >=32 && c_ <= 126; }

/**
 * @return Returns true if \em c is printable, false otherwise.
 */
const bool Char::isPrint(const Char & c) { Char d(c.c_); return d.isPrint(); }

/**
 * @return Returns true if the character is punctuation, false otherwise.
 */
const bool Char::isPunct() const { return (c_ >= 33 && c_ <= 47) ||
										  (c_ >= 58 && c_ <= 64) ||
										  (c_ >= 91 && c_ <= 96) ||
										  (c_ <= 123 && c_ <= 126);
}

/**
 * @return Returns true if \em c is punctuation, false otherwise.
 */
const bool Char::isPunct(const Char & c) { Char d(c.c_); return d.isPunct(); }

/**
 * @return Returns true if the character is whitespace, false otherwise.\n
 * Whitespace characters are space (' '), carriage return ('\\r'), tab ('\\t'), newline ('\\n'), vertical tab ('\\v')
 * and formfeed ('\\f').
 */
const bool Char::isWhitespace() const { return c_ == ' ' || c_ == '\r' || c_ == '\t' ||
											   c_ == '\n' || c_ == '\v' || c_ == '\f';
}

/**
 * @return Returns true if \em c is whitespace, false otherwise.\n
 * Whitespace characters are space (' '), carriage return ('\\r'), tab ('\\t'), newline ('\\n'), vertical tab ('\\v')
 * and formfeed ('\\f').
 */
const bool Char::isWhitespace(const Char & c) { Char d(c.c_); return d.isWhitespace(); }

/**
 * @return Returns true if this character is the range [A-Z], false otherwise.
 */
const bool Char::isUpper() const { return c_ >=65 && c_ <= 90; }

/**
 * @return Returns true if \em c is the range [A-Z], false otherwise.
 */
const bool Char::isUpper(const Char & c) { Char d(c.c_); return d.isUpper(); }

/**
 * @return Returns the Ascii value of the character.
 */
const int Char::toAscii() const { return (int)c_; }

/**
 * @return Returns this Char as a standard char.
 */
const char Char::tochar() const { return c_; }

/**
 * @return Returns a copy of this character converted to lowercase if it is a letter and uppercase.
 * Otherwise it just returns this character.
 */
Char Char::toLower() const { return (isUpper()) ? Char(c_+32) : *this; }

/**
 * @return Returns a copy of \em c converted to lowercase if it is a letter and uppercase.
 * Otherwise it just returns \em c.
 */
Char Char::toLower(const Char & c) { Char d(c.c_); return d.toLower(); }

/**
 * @return Returns a copy of this character converted to uppercase if it is a letter and lowercase.
 * Otherwise it just returns this character.
 */
Char Char::toUpper() const { return (isLower()) ? Char(c_-32) : *this; }

/**
 * @return Returns a copy of \em c converted to uppercase if it is a letter and lowercase.
 * Otherwise it just returns \em c.
 */
Char Char::toUpper(const Char & c) { Char d(c.c_); return d.toUpper(); }

/**
 * @return Returns the unicode value of the character.
 */
const int Char::unicode() const { return (int)c_; }

/**
 * @return Returns a copy of this Char with \em i added to it.
 */
Char & Char::operator +=(const int i) { c_ += i; return *this; }

/**
 * @return Returns a copy of this Char with \em i subtracted from it.
 */
Char & Char::operator -=(const int i) { c_ -= i; return *this; }

/**
 * @return Returns true if the chars \em c1 and \em c2 are equal, false otherwise.
 */
const bool operator==(const Char & c1, const Char & c2) { return c1.c_ == c2.c_; }

/**
 * @return Returns true if the chars \em c1 and \em c2 are not equal, false otherwise.
 */
const bool operator!=(const Char & c1, const Char & c2) { return !(c1 == c2); }

/**
 * @return Returns true if the unicode value of \em c1 is less than \em c2, false otherwise.
 */
const bool operator<(const Char & c1, const Char & c2) { return c1.c_ < c2.c_; }

/**
 * @return Returns true if the unicode value of \em c1 is greater than \em c2, false otherwise.
 */
const bool operator>(const Char & c1, const Char & c2) { return c1.c_ > c2.c_; }

/**
 * @return Returns true if the unicode value of \em c1 is less than or equal to \em c2, false otherwise.
 */
const bool operator<=(const Char & c1, const Char & c2) { return c1.c_ <= c2.c_; }

/**
 * @return Returns true if the unicode value of \em c1 is greater than or equal to \em c2, false otherwise.
 */
const bool operator>=(const Char & c1, const Char & c2) { return c1.c_ >= c2.c_; }

/**
 * Allows an instance of Char to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Char & c) {
	out << "Char [" << &c << "] '" << c.c_ << "'";
	return out;
}

} /* namespace prism */
