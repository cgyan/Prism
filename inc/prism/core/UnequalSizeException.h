/*
 * UnequalSizeException.h
 * v1
 *
 *  Created on: Aug 11, 2016
 *      Author: iainhemstock
 */

#ifndef UNEQUALSIZEEXCEPTION_H_
#define UNEQUALSIZEEXCEPTION_H_

#include <prism/Exception>
#include <string>
#include <sstream>

namespace prism {

class UnequalSizeException : public Exception {
private:
	UnequalSizeException() {}
public:
	UnequalSizeException(const int sze1, const int sze2)
		: Exception("")
	{
		std::stringstream ss;
		ss << "Error: sizes do not match - size 1:" << sze1 << " and size 2:" << sze2;
		msg = ss.str();
	}

};

}


#endif /* UNEQUALSIZEEXCEPTION_H_ */
