/*
 * UniquePointer_priv.h
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_UNIQUE_POINTER_PRIV_H_
#define PRISM_UNIQUE_POINTER_PRIV_H_

#include <prism/h/global.h>

PRISM_BEGIN_NAMESPACE

//============================================================================================
// UniquePointerData
//============================================================================================
template <typename T, typename D>
struct UniquePointer<T,D>::UniquePointerData {
	using pointer = T*;
	pointer p;

	/*
	 *
	 */
	UniquePointerData()
	: p(nullptr)
	{}

	/*
	 *
	 */
	UniquePointerData(pointer p)
	: p(p)
	{}
};
//============================================================================================
// UniquePointer
//============================================================================================
/*
 *
 */
template <typename T, typename D>
UniquePointer<T,D>::
UniquePointer()
: d(new UniquePointerData)
{}

/*
 *
 */
template <typename T, typename D>
UniquePointer<T,D>::
UniquePointer(typename UniquePointer<T,D>::pointer p)
: d(new UniquePointerData(p))
{}

/*
 *
 */
template <typename T, typename D>
UniquePointer<T,D>::
~UniquePointer() {
	delete d;
}

/*
 *
 */
template <typename T, typename D>
typename UniquePointer<T,D>::pointer
UniquePointer<T,D>::
get() const {
	return d->p;
}

PRISM_END_NAMESPACE


#endif /* PRISM_UNIQUE_POINTER_PRIV_H_ */
