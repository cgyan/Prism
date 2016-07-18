/*
 * Char.h
 * v0.*
 *
 *  Created on: Jul 18, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_CHAR_H_
#define PRISM_CHAR_H_

#include <ostream>

namespace prism {

/*
 *
 */
class Char {
private:
	char c_;
public:
	Char();
	Char(const char c);
	virtual ~Char();

	const bool isLetter() const;
	const bool isLetterOrNumber() const;
	const bool isLower() const;
	const bool isNull() const;
	const bool isNumber() const;
	const bool isUpper() const;
	const int toAscii() const;
	const char tochar() const;


	Char & operator+=(const int i);
	Char & operator-=(const int i);

	// related non members
	friend std::ostream & operator<<(std::ostream & out, const Char & c);
};

} /* namespace prism */

#endif /* PRISM_CHAR_H_ */
