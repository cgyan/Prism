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
// UniquePointerDeleter (non-array)
//============================================================================================
template <typename T>
struct UniquePointerDeleter {
	using pointer = T*;

	void
	operator()(pointer p) {
//		std::cout << "Non-Array deleter\n";
		delete p;
	}
};
//============================================================================================
// UniquePointerDeleter array specialization
//============================================================================================
template <typename T>
struct UniquePointerDeleter<T[]> {
	using pointer = T*;

	void
	operator()(pointer p) {
		if (p == nullptr) {
//			std::cout << "Array deleter says p is null and nothing is to be deleted\n";
		} else {
//			std::cout << "Array deleter says p is not null and is being deleted\n";
		}
		delete []p;
	}
};
//============================================================================================
// UniquePointerData
//============================================================================================
template <typename T, typename D>
struct UniquePointer<T,D>::UniquePointerData {
	using pointer = T*;
	using deleter_type = D;

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
		getDeleter()(p);
	}

	/*
	 *
	 */
	deleter_type
	getDeleter() const {
		return deleter_type();
	}

	/*
	 *
	 */
	pointer
	releaseCurrentPointerOwnership() {
		pointer tmp = p;
		p = nullptr;
		return tmp;
	}

	/*
	 *
	 */
	void reset(pointer newPointer) {
		pointer oldPointer = releaseCurrentPointerOwnership();
		getDeleter()(oldPointer);
		takeOwnershipOfNewPointer(newPointer);
	}

	/*
	 *
	 */
	void takeOwnershipOfNewPointer(pointer newPointer) {
		this->p = newPointer;
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
UniquePointer(UniquePointer&& rhs)
: d(nullptr)
{
	using prism::swap;
	swap(this->d, rhs.d);
}

/*
 *
 */
template <typename T, typename D>
UniquePointer<T,D>&
UniquePointer<T,D>::
operator=(UniquePointer&& rhs) {
	using prism::swap;
	swap(this->d, rhs.d);
	return *this;
}

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
typename UniquePointer<T,D>::deleter_type
UniquePointer<T,D>::
getDeleter() const {
	return d->getDeleter();
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
	return d->releaseCurrentPointerOwnership();
}

/*
 *
 */
template <typename T, typename D>
void
UniquePointer<T,D>::
reset(typename UniquePointer<T,D>::pointer p) {
	d->reset(p);
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




















