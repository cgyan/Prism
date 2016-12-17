/*
 * PVector.h
 * v0.*
 *
 *  Created on: 13 Dec 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_PVECTOR_H_
#define PRISM_PVECTOR_H_

#include <prism/h/global.h>
#include <prism/h/OutOfBoundsException.h>

PRISM_BEGIN_NAMESPACE

template <typename T>
class PVector {
public:
	int 	_M_size;
	int		_M_capacity;
	T		_M_data[10];
public:
	PVector();
	void 		addAtEnd(const T& value);
	T&			at(const int index);
	const int	capacity();
	void		clear();
	const bool 	empty();
	void		removeLast();
	void		reserve(const int size);
	void		resize(const int size);
	const int	size();
};

/*
 *
 */
template <typename T>
PVector<T>::
PVector()
: _M_size(0),
  _M_capacity(0),
  _M_data()
{}

/*
 *
 */
template <typename T>
void
PVector<T>::
addAtEnd(const T& value) {
	_M_data[_M_size] = value;
	++_M_size;
}

/*
 *
 */
template <typename T>
T&
PVector<T>::
at(const int index) {
	if (index < 0 || index >= this->size())
		throw prism::OutOfBoundsException(index);
	return _M_data[index];
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
capacity() {
	return _M_capacity;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
clear() {
	_M_size = 0;
}

/*
 *
 */
template <typename T>
const bool
PVector<T>::
empty() {
	return _M_size == 0;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
removeLast() {
	--_M_size;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
reserve(const int size) {
	if (size < 0)
		throw std::bad_alloc();
	_M_capacity = size;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
resize(const int size) {
	if (size < 0)
		throw prism::OutOfBoundsException(size);
	_M_size = size;
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
size() {
	return _M_size;
}

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















