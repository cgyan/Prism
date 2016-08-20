/*
 * Deque.h
 * v0.2
 *
 *  Created on: Jan 31, 2015
 *      Author: iainhemstock
 *
 *  DequeBase handles all memory allocation/deallocation
 *  DequeData handles the implementation details
 *  Deque is unaware of the lack of continuous storage and so DequeIterator provides the means of bridging that gap
 *
	+----++----++----++----++----++----++----++----+
	| T* || T* || T* || T* || T* || T* || T* || T* |
	+----++----++----++----++----++----++----++----+
	   0     1     2     3     4     5     6     7

 */

/*
 * todo add support for itializer list constructor and move constructor
 * i.e. array<int> a = {1,2,3.4};
 */

#ifndef PRISM_DEQUE_H_
#define PRISM_DEQUE_H_

#include <ostream>
#include "aux/_DequeImpl.h"
#include "OutOfBoundsException.h"

// todo remove this
using namespace std;

namespace prism {

// ====================================================
// Deque
// ====================================================
template <class T>
class Deque {
public:
	typedef DequeIterator<T>		iterator;
	typedef DequeConstIterator<T>	const_iterator;
public:
					Deque();
					Deque(const int size, const T& value=T());
					~Deque();
	T&				at(const int index);
	const T&		at(const int index) const;
	iterator		begin();
	iterator		begin() const;
	const_iterator	cbegin() const;
	const_iterator	cend() const;
	iterator		end();
	iterator		end() const;
	iterator		insert(iterator before, const int count, const T& value);
	const int		size() const;

	T& 				operator[](const int i);
	const T&		operator[](const int i) const;

public:				// only temp
	void			debugMap() const;
private:
	DequeImpl<T>*	impl;
public:
// 	Related non-members
// 	===================
	template <class _T> friend std::ostream& operator<<(std::ostream& out,  Deque<_T>& deque);
};

/**
 * Creates an empty deque.
 */
template <class T>
Deque<T>::Deque()
: impl(new DequeImpl<T>) {

}

/**
 *
 */
template <class T>
Deque<T>::Deque(const int size, const T& value)
: impl(new DequeImpl<T>(size, value)) {

}

/**
 * Destroys this deque.
 */
template <class T>
Deque<T>::~Deque() {
	delete impl;
}

/**
 *
 */
template <class T>
T& Deque<T>::at(const int index) {
	// This implementation calls the const version of at() to reduce
	// code duplication. See p24 of Scott Meyer's Effective C++ for details.
	return const_cast<T&>(static_cast<const Deque<T>&>(*this).at(index));
}

/**
 *
 */
template <class T>
const T& Deque<T>::at(const int index) const {
	if (impl->rangeCheckOk(index))
		return (*this)[index];
	throw prism::exceptions::OutOfBoundsException(index);
}

/**
 *
 */
template <class T>
typename Deque<T>::iterator Deque<T>::begin() {
	return impl->data->firstChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::iterator Deque<T>::begin() const {
	return impl->data->firstChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const {
	return impl->data->firstChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::const_iterator Deque<T>::cend() const {
	return impl->data->lastChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::iterator Deque<T>::end() {
	return impl->data->lastChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::iterator Deque<T>::end() const {
	return impl->data->lastChunk;
}

/**
 *
 */
template <class T>
typename Deque<T>::iterator Deque<T>::insert(iterator before, const int count, const T& value) {
	if (before == impl->data->firstChunk)
		impl->insertInFront(count, value);

	else if (before == impl->data->lastChunk)
		impl->insertInBack(count, value);

	else
		impl->insertInMiddle(before, count, value);
}

/**
 *
 */
template <class T>
const int Deque<T>::size() const {
	return impl->data->lastChunk - impl->data->firstChunk;
}

/**
 *
 */
template <class T>
T& Deque<T>::operator[](const int i) {
	return *(impl->data->firstChunk+i);
}

/**
 *
 */
template <class T>
const T& Deque<T>::operator[](const int i) const {
	return *(impl->data->firstChunk+i);
}

/**
 *
 */
template <class T>
void Deque<T>::debugMap() const {
	impl->data->debugMap();
}

/**
 *
 */
template <class _T>
std::ostream& operator<<(std::ostream& out,  Deque<_T>& deque) {
	out << "-----------------------------\n";
	out << "Deque [" << &deque << "]";
	out << " size:" << deque.size();
	out << endl;
	out << "-----------------------------\n";
	int i = 0;
	typename Deque<_T>::iterator it = deque.begin();
	while (it != deque.end()) {
		out << "-- [" << i++ << "] " << *it;
		out << endl;
		++it;
	}
	out << "-----------------------------\n";
	return out << std::endl;
}

}


#endif /* PRISM_DEQUE_H_ */
