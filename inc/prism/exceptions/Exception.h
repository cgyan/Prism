/*
 * Exception.h
 * v0.1
 *
 *  Created on: Jan 27, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_EXCEPTION_H_
#define PRISM_EXCEPTION_H_

#include <string>

namespace prism {

class Exception {
protected:
	std::string msg;
	Exception() {}
public:
	Exception(const std::string& msg) : msg(msg) {}
	const std::string& errorMsg() const { return msg; }
};

}



#endif /* PRISM_EXCEPTION_H_ */
