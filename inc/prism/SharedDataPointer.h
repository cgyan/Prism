/*
 * SharedDataPointer.h
 * v0.1
 *
 *  Created on: Jul 10, 2013
 *      Author: iainhemstock
 */

#ifndef PRISM_SHAREDDATAPOINTER_H_
#define PRISM_SHAREDDATAPOINTER_H_

#include <ostream>
using namespace std;

namespace prism {

// todo document each method

template <typename SharedDataType>
class SharedDataPointer {
public:
	SharedDataPointer();
	SharedDataPointer(SharedDataType * p);
	SharedDataPointer(const SharedDataPointer & copy);
	SharedDataPointer & operator=(const SharedDataPointer & rhs);
	~SharedDataPointer();

	const SharedDataType * 	constData() const;
	SharedDataType * 		data();
	const SharedDataType * 	data() const;
	void					detach();
	const bool 				isNull() const;
	const bool				isShareable() const;
	const bool				isShared() const;
	const int 				refCount() const;
	void					setUnshareable();

	SharedDataType * 		operator->();
	const SharedDataType * 	operator->() const;
	SharedDataType & 		operator*();
	const SharedDataType & 	operator*() const;
	const bool 				operator!() const;
	const bool 				operator!=(const SharedDataPointer & rhs) const;
	const bool 				operator==(const SharedDataPointer<SharedDataType> & rhs) const;

private:
	SharedDataType * p;
};

/**
 *
 */
template <class SharedDataType>
inline SharedDataPointer<SharedDataType>::SharedDataPointer()
	: p(0)
{

}

/**
 *
 */
template <class SharedDataType>
inline SharedDataPointer<SharedDataType>::SharedDataPointer(SharedDataType * p)
{
	if (!p->isShareable())
		p = new SharedDataType(*p);
	else this->p = p;
	p->incRef();
}

/**
 *
 */
template <class SharedDataType>
inline SharedDataPointer<SharedDataType>::SharedDataPointer(const SharedDataPointer & copy)
{
	if (!copy.p->isShareable())
		p = new SharedDataType(*copy.p);
	else p = copy.p;
	p->incRef();
}

/**
 *
 */
template <class SharedDataType>
inline SharedDataPointer<SharedDataType>::~SharedDataPointer() {
	if (p) p->decRef();
}

/**
 *
 */
template <class SharedDataType>
inline const SharedDataType * SharedDataPointer<SharedDataType>::constData() const {
	return p;
}

/**
 *
 */
template <class SharedDataType>
inline SharedDataType * SharedDataPointer<SharedDataType>::data() {
	return p;
}

/**
 *
 */
template <class SharedDataType>
inline const SharedDataType * SharedDataPointer<SharedDataType>::data() const {
	return p;
}

/**
 *
 */
template <typename SharedDataType>
inline void SharedDataPointer<SharedDataType>::detach() {
	if (p->refCount() > 1) {
		p->decRef();
		p = new SharedDataType(*p);
		p->incRef();
		setUnshareable();
	}
}

/**
 *
 */
template <class SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::isNull() const {
	return p == 0;
}

/**
 *
 */
template <typename SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::isShareable() const {
	return (p) ? p->isShareable() : 0;
}

/**
 *
 */
template <typename SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::isShared() const {
	return (p) ? p->isShared() : 0;
}

/**
 *
 */
template <class SharedDataType>
inline const int SharedDataPointer<SharedDataType>::refCount() const {
	return (p) ? p->refCount() : 0;
}

/**
 *
 */
template <typename SharedDataType>
inline void SharedDataPointer<SharedDataType>::setUnshareable() {
	p->setUnshareable();
}

/**
 *
 */
template <class SharedDataType>
inline SharedDataType * SharedDataPointer<SharedDataType>::operator->() {
	return p;
};

/**
 *
 */
template <class SharedDataType>
inline const SharedDataType * SharedDataPointer<SharedDataType>::operator->() const {
	return p;
};

/**
 *
 */
template <class SharedDataType>
inline SharedDataType & SharedDataPointer<SharedDataType>::operator*() {
	return *p;
}

/**
 *
 */
template <class SharedDataType>
inline const SharedDataType & SharedDataPointer<SharedDataType>::operator*() const {
	return *p;
}

/**
 *
 */
template <class SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::operator!() const {
	return isNull();
}

/**
 *
 */
template <class SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::operator!=(const SharedDataPointer<SharedDataType> & rhs) const {
	return p != rhs.p;
}

/**
 *
 */
template <class SharedDataType>
inline const bool SharedDataPointer<SharedDataType>::operator==(const SharedDataPointer<SharedDataType> & rhs) const {
	return p == rhs.p;
}

/**
 *
 */
template <class SharedDataType>
inline SharedDataPointer<SharedDataType> & SharedDataPointer<SharedDataType>::operator=(const SharedDataPointer<SharedDataType> & rhs) {
	if (p != rhs.p) { // don't assign to self

		if (!rhs.p->isShareable())
			p = new SharedDataType(*rhs.p);
		else p = rhs.p;
		p->incRef();
	}
	return *this;
}

}


#endif /* PRISM_SHAREDDATAPOINTER_H_ */


