/*
 * UniquePointer.h
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <prism/h/global.h>

#ifndef PRISM_UNIQUE_POINTER_H_
#define PRISM_UNIQUE_POINTER_H_

PRISM_BEGIN_NAMESPACE

template <typename T, typename Deleter>
class UniquePointer final {
public:
	///
	explicit UniquePointer();

	///
	~UniquePointer();

	///
	T*
	get() const;

private:
	struct UniquePointerData;
	UniquePointerData * d;
};

PRISM_END_NAMESPACE

#include <prism/h/priv/UniquePointer_priv.h>

#endif /* PRISM_UNIQUE_POINTER_H_ */
