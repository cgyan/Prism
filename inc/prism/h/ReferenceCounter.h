/*
 * ReferenceCounter.h
 * v0.1
 *
 *  Created on: Jul 10, 2013
 *      Author: iainhemstock
 */

#ifndef PRISM_REFERENCECOUNTER_H_
#define PRISM_REFERENCECOUNTER_H_

#include <ostream>

namespace prism {

class ReferenceCounter {
public:
	int count;
	ReferenceCounter() : count(0) {}
	~ReferenceCounter() {}
	const int ref() { return ++count; }
	const int deref() { return --count; }
};

}

#endif /* PRISM_REFERENCECOUNTER_H_ */
