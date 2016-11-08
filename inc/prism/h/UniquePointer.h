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
	using pointer 		= T*;
	using element_type 	= T;

	///
	explicit UniquePointer();

	///
	explicit UniquePointer(pointer p);

	///
	UniquePointer&
	operator=(const UniquePointer& rhs) = delete;

	///
	~UniquePointer();

	///
	pointer
	get() const;

	///
	const bool
	isNull() const;

	///
	pointer
	release();

	///
	void
	reset(pointer p = nullptr);

	///
	element_type
	operator*();

	///
	pointer
	operator->();

	///
	explicit
	operator bool() const;

private:
	struct UniquePointerData;
	UniquePointerData * d;
};

PRISM_END_NAMESPACE

#include <prism/h/priv/UniquePointer_priv.h>

#endif /* PRISM_UNIQUE_POINTER_H_ */
