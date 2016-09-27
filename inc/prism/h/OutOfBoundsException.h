/*
 * OutOfBoundsException.h
 * v0.1
 *
 *  Created on: Jan 27, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_OUTOFBOUNDSEXCEPTION_H_
#define PRISM_OUTOFBOUNDSEXCEPTION_H_

#include <prism/h/Exception.h>
#include <string>
#include <sstream>

namespace prism {

class OutOfBoundsException : public Exception {
private:
	int i;
	OutOfBoundsException():i(0) {}
public:
	OutOfBoundsException(const int index) : Exception(""), i(index) {
		std::stringstream ss;
		ss << "Error: index '" << index << "' is out of bounds";
		msg = ss.str();
	}

	const int index() const { return i; }
};

}

#endif /* PRISM_OUTOFBOUNDSEXCEPTION_H_ */
