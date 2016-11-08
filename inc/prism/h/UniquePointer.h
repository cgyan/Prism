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
class UniquePointer {
public:
	using pointer 		= T*;
	using element_type 	= T;

	///
	explicit UniquePointer(pointer p = nullptr);

	///
	UniquePointer(const UniquePointer& copy) = delete;
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

	void
	swap(UniquePointer& other);

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

template <typename T, typename D>
void swap(UniquePointer<T,D>& up1, UniquePointer<T,D>& up2);

PRISM_END_NAMESPACE

#include <prism/h/priv/UniquePointer_priv.h>

#endif /* PRISM_UNIQUE_POINTER_H_ */
