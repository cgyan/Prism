/*
 * OverflowException.h
 * v0.*
 *
 *  Created on: Aug 12, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_OVERFLOWEXCEPTION_H_
#define PRISM_OVERFLOWEXCEPTION_H_

#include <prism/h/Exception.h>
#include <string>
#include <sstream>

namespace prism {

class OverflowException : public Exception {
public:
	OverflowException() {}
	OverflowException(const int index) : Exception("") {
		std::stringstream ss;
		ss << "Error: overflow";
		msg = ss.str();
	}

};

}


#endif /* PRISM_OVERFLOWEXCEPTION_H_ */
