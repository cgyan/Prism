/*
 * SharedData.h
 * v0.1
 *
 *  Created on: Jul 8, 2013
 *      Author: iainhemstock
 */

#ifndef PRISM_SHAREDPOINTER_H_
#define PRISM_SHAREDPOINTER_H_
#include <ostream>
#include "ReferenceCounter.h"

namespace prism {

// Todo: add dynamic and const cast support for shared pointer

template <class T>
class SharedPointer {
private:
	T * d;
	ReferenceCounter * m_ref;

public:
	SharedPointer();
	SharedPointer(T * data);
	SharedPointer(const SharedPointer<T> & copy);
	~SharedPointer();

	void clear();
	T * data() const;
	const bool isNull() const;
	const bool isUnique() const;
	const int refCount() const;

	T * operator->() const;
	T & operator*() const;
	operator bool() const;
	const bool operator!() const;
	SharedPointer & operator=(const SharedPointer & rhs);

	// Related non-members
	/* 	Note: friend functions of a template class cannot use the same template name given to the class - i.e. they cannot use T.
		So the friend functions are given a different template name, U in this case, although it actually represents the same type as T. */
	template <class U> friend const bool operator!=(const SharedPointer<U> & p1, const SharedPointer<U> & p2);
	template <class U> friend const bool operator!=(const SharedPointer<U> & p1, const U * p2);
	template <class U> friend const bool operator!=(const U * p1, const SharedPointer<U> & p2);
	template <class U> friend const bool operator==(const SharedPointer<U> & p1, const SharedPointer<U> & p2);
	template <class U> friend const bool operator==(const SharedPointer<U> & p1, const U * p2);
	template <class U> friend const bool operator==(const U * p1, const SharedPointer<U> & p2);

	friend std::ostream & operator<<(std::ostream & out, SharedPointer & p) {
		if (p.isNull()) out << "SharedPointer &=" << &p << " (null)";
		else {
			out << "SharedPointer &=" << &p << " (ReferenceCounter &=" << p.m_ref << " count=" << p.m_ref->count << ")";
			out << ", (Pointer &=" << p.d << ")";
			out << std::endl;
		}
		return out;
	}
};

/**
 * Constructs an empty null shared pointer instance. The managed pointer is set to 0.
 */
template <class T>
SharedPointer<T>::SharedPointer()
	: d(0), m_ref(0)
{
}

/**
 * Constructs a shared pointer that points to the data pointer.
 * The data pointer becomes managed by this shared pointer and so must not be passed to another
 * SharedPointer instance or deleted outside of this object.
 */
template <class T>
SharedPointer<T>::SharedPointer(T * data)
	: d(data), m_ref(new ReferenceCounter)
{
	if (m_ref) m_ref->ref();
}

/**
 * Constructs a shared pointer that is a copy of copy. The new SharedPointer instance will point to
 * the pointer that copy points to and the internal reference counter is incremented.
 */
template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer<T> & copy)
	: d(copy.d), m_ref(copy.m_ref)
{
	if (m_ref) m_ref->ref();
}

/**
 * Destroys this SharedPointer instance.
 * The internal reference count for the managed pointer is decremented and if this SharedPointer instance held
 * the last reference to the managed pointer then the managed pointer is also deleted.
 */
template <class T>
SharedPointer<T>::~SharedPointer() {
	if (m_ref->deref() == 0) { delete d; delete m_ref; }
	std::cout << "destructing SharedPointer" << std::endl;
}

/**
 * Resets this SharedPointer instance (i.e. isNull() == true). The managed pointer is set to 0.
 * The internal reference count for the managed pointer is decremented and if this SharedPointer instance held
 * the last reference to the managed pointer then the managed pointer is also deleted.
 */
template <class T>
void SharedPointer<T>::clear() {
	if (m_ref->deref() == 0) { delete d; delete m_ref; }
	d = 0; m_ref = 0;
}

/**
 * Returns the managed pointer.
 * Note: do not delete or pass this  pointer to another SharedPointer as the SharedPointer instances will become corrupt.
 */
template <class T>
T * SharedPointer<T>::data() const { return d; }

/**
 * Returns true if the managed pointer is set to 0, false if otherwise it points to a valid object.
 */
template <class T>
const bool SharedPointer<T>::isNull() const { return d==0 && m_ref == 0; }

/**
 * Returns true if this SharedPointer instance is the only object that holds a reference to the managed pointer, false otherwise.
 * Note: null pointers are never unique as they don't point to anything.
 */
template <class T>
const bool SharedPointer<T>::isUnique() const { return m_ref->count == 1; };

/**
 * Returns the number of SharedPointer objects that have ownership of the managed pointer.
 */
template <class T>
const int SharedPointer<T>::refCount() const { return m_ref->count; }

/**
 * Overloads the -> operator so that it returns the managed pointer.
 */
template <class T>
T * SharedPointer<T>::operator->() const { return d; }

/**
 * Overloads the * operator so that it returns a reference to the value that the managed pointer points to.
 */
template <class T>
T & SharedPointer<T>::operator*() const { return *d; }

/**
 * Returns true if this SharedPointer instance is not null, false otherwise.
 * It can be used in if statements:
 * 		if (shared_pointer) { ... }
 */
template <class T>
SharedPointer<T>::operator bool() const { return !isNull(); }

/**
 * Returns true if this SharedPointer instance is null, false otherwise.
 * It can be used in if statements:
 * 		if (!shared_pointer) { ... }
 */
template <class T>
const bool SharedPointer<T>::operator!() const { return isNull(); }

/**
 * This SharedPointer instance takes ownership of the managed pointer in rhs
 * and the internal reference counter is incremented.
 */
template <class T>
SharedPointer<T> & SharedPointer<T>::operator=(const SharedPointer & rhs) {
	std::cout << "assignment" << std::endl;
	if (d != rhs.d) { // don't assign to itself
		d = rhs.d;
		m_ref = rhs.m_ref;
		m_ref->ref();
	}
	return *this;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// Related non-members
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/**
 * Returns true if the managed pointers of p1 and p2 do not point to the same data, false otherwise.
 */
template <class U>
const bool operator!=(const SharedPointer<U> & p1, const SharedPointer<U> & p2) {
	return p1.data() != p2.data();
}

/**
 * Returns true if the managed pointer of p1 and the raw pointer p2 do not point to the same data, false otherwise.
 */
template <class U>
const bool operator!=(const SharedPointer<U> & p1, const U * p2) {
	return p1.data() != p2;
}

/**
 * Returns true if the raw pointer p1 and the managed pointer of p2 do not point to the same data, false otherwise.
 */
template <class U>
const bool operator!=(const U * p1, const SharedPointer<U> & p2) {
	return p1 != p2.data();
}

/**
 * Returns true if the managed pointers of p1 and p2 point to the same data, false otherwise.
 */
template <class U>
const bool operator==(const SharedPointer<U> & p1, const SharedPointer<U> & p2) {
	return p1.data() == p2.data();
}

/**
 * Returns true if the managed pointer of p1 and the raw pointer p2 point to the same data, false otherwise.
 */
template <class U>
const bool operator==(const SharedPointer<U> & p1, const U * p2) {
	return p1.data() == p2;
}

/**
 * Returns true if the raw pointer p1 and the managed pointer of p2 point to the same data, false otherwise.
 */
template <class U>
const bool operator==(const U * p1, const SharedPointer<U> & p2) {
	return p1 == p2.data();
}

}


#endif /* PRISM_SHAREDPOINTER_H_ */









