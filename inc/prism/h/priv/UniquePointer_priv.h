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
#include <prism/h/algorithm.h>

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

	/*
	 *
	 */
	~UniquePointerData() {
		delete p;
	}
};
//============================================================================================
// UniquePointer
//============================================================================================
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
data() const {
	return d->p;
}

/*
 *
 */
template <typename T, typename D>
const bool
UniquePointer<T,D>::
isNull() const {
	return d->p == nullptr;
}

/*
 *
 */
template <typename T, typename D>
typename UniquePointer<T,D>::pointer
UniquePointer<T,D>::
release() {
	pointer p_tmp = d->p;
	d->p = nullptr;
	return p_tmp;
}

/*
 *
 */
template <typename T, typename D>
void
UniquePointer<T,D>::
reset(typename UniquePointer<T,D>::pointer p) {
	delete d->p;

	if (p == nullptr) d->p = nullptr;
	else d->p = p;
}

/*
 *
 */
template <typename T, typename D>
void
UniquePointer<T,D>::
swap(UniquePointer& other) {
	using prism::swap;
	swap(this->d, other.d);
}

/*
 *
 */
template <typename T, typename D>
typename UniquePointer<T,D>::element_type
UniquePointer<T,D>::
operator*() {
	return *d->p;
}

/*
 *
 */
template <typename T, typename D>
typename UniquePointer<T,D>::pointer
UniquePointer<T,D>::
operator->() {
	return d->p;
}

/*
 *
 */
template <typename T, typename D>
UniquePointer<T,D>::
operator bool() const {
	return (d->p == nullptr) ? false : true;
}

template <typename T, typename D>
void
swap(UniquePointer<T,D>& up1, UniquePointer<T,D>& up2) {
	up1.swap(up2);
}

PRISM_END_NAMESPACE


#endif /* PRISM_UNIQUE_POINTER_PRIV_H_ */




















