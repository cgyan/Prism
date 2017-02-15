/*
 * BadSizeException.h
 * v0.*
 *
 *  Created on: 15 Feb 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_BADSIZEEXCEPTION_H_
#define PRISM_BADSIZEEXCEPTION_H_

#include <prism/global>
#include <prism/Exception>

PRISM_BEGIN_NAMESPACE

class BadSizeException : public Exception {
private:
	int i;
	BadSizeException():i(0) {}
public:
	BadSizeException(const int index)
	: Exception(""), i(index)
{
		std::stringstream ss;
		ss << "Error: index '" << index << "' is a bad size";
		msg = ss.str();
	}

	const int index() const { return i; }
};

PRISM_END_NAMESPACE




#endif /* PRISM_BADSIZEEXCEPTION_H_ */
