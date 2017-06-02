/*
 * PrismVersion.h
 * v1
 *
 *  Created on: Oct 13, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_PRISMVERSION_H_
#define PRISM_PRISMVERSION_H_

#define PRISM_API_MAJOR 1
#define PRISM_API_MINOR 0
#define PRISM_API_PATCH 0

#include <prism/String>

namespace prism {

class PrismVersion final {
public:
	static const int 		major();
	static const int 		minor();
	static const int 		patch();
	static const String 	string();
};

/**
 *
 */
const int
PrismVersion::
major()
{ return int(PRISM_API_MAJOR); }

/**
 *
 */
const int
PrismVersion::
minor()
{ return int(PRISM_API_MINOR); }

/**
 *
 */
const int
PrismVersion::
patch()
{ return int(PRISM_API_PATCH); }

/**
 *
 */
const String
PrismVersion::
string()
{ return String(	String::number(PRISM_API_MAJOR) + "." +
					String::number(PRISM_API_MINOR) + "." +
					String::number(PRISM_API_PATCH));
}

} // end namespace prism



#endif /* PRISM_PRISMVERSION_H_ */
