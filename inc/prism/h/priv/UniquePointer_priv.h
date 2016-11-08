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
	T* p;
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

PRISM_END_NAMESPACE


#endif /* PRISM_UNIQUE_POINTER_PRIV_H_ */
