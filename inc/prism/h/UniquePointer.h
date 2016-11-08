/*
 * UniquePointer.h
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <prism/h/global.h>

#ifndef PRISM_UNIQUEPOINTER_H_
#define PRISM_UNIQUEPOINTER_H_

PRISM_BEGIN_NAMESPACE

template <typename T, typename Deleter>
class UniquePointer {
private:
	struct UniquePointerData;
	UniquePointerData * d;
};

PRISM_END_NAMESPACE



#endif /* PRISM_UNIQUEPOINTER_H_ */
