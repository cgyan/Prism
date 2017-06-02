/*
 * Char.h
 * v1
 *
 *  Created on: Jul 18, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_CHAR_H_
#define PRISM_CHAR_H_

#include <ostream>

namespace prism {

class Char {
private:
	char c_;
public:
	Char();
	Char(const char c);
	Char(const int unicode);
	virtual ~Char();

	const bool 	isControl() const;
	const bool 	isLetter() const;
	const bool 	isLetterOrNumber() const;
	const bool 	isLower() const;
	const bool 	isNull() const;
	const bool 	isNumber() const;
	const bool 	isPrint() const;
	const bool 	isPunct() const;
//	const bool	isSpace() const;
	const bool 	isWhitespace() const;
	const bool 	isUpper() const;
	const int 	toAscii() const;
	const char 	tochar() const;
	Char		toLower() const;
	Char		toUpper() const;
	const int 	unicode() const;


	Char & operator+=(const int i);
	Char & operator-=(const int i);

	// static
	// ---------------------
	static const bool 	isControl(const Char & c);
	static const bool 	isLetter(const Char & c);
	static const bool 	isLetterOrNumber(const Char & c);
	static const bool 	isLower(const Char & c);
	static const bool 	isNumber(const Char & c);
	static const bool 	isPrint(const Char & c);
	static const bool 	isPunct(const Char & c);
	static const bool 	isWhitespace(const Char & c);
	static const bool 	isUpper(const Char & c);
	static Char			toLower(const Char & c);
	static Char 		toUpper(const Char & c);


	// related non members
	friend const bool operator==(const Char & c1, const Char & c2);
	friend const bool operator!=(const Char & c1, const Char & c2);
	friend const bool operator<(const Char & c1, const Char & c2);
	friend const bool operator>(const Char & c1, const Char & c2);
	friend const bool operator<=(const Char & c1, const Char & c2);
	friend const bool operator>=(const Char & c1, const Char & c2);
	friend std::ostream & operator<<(std::ostream & out, const Char & c);
};

} /* namespace prism */

#endif /* PRISM_CHAR_H_ */
