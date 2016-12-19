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
	int 	_m_size;
	int		_m_capacity;
	T		_m_data[10];
public:
	PVector();
	void 		addAtEnd(const T& value);
	T&			at(const int index);
	const int	capacity();
	void		clear();
	const bool	contains(const T& value);
	const int	count(const T& value);
	const bool 	empty();
	const bool	endsWith(const T& value);
	void		fill(const T& value);
	const int 	lastIndexOf(const T& value, const int from = -1);
	void 		removeLast();
	void 		reserve(const int size);
	void 		resize(const int size);
	const int 	size();
	const bool 	startsWith(const T& value);

private:
	const bool 	valueIsEqualToValueAtIndex(int index, const T& value);
	const bool	indexToSearchFromIsNegative(int indexToStartSearchFrom);
	const int	setStartIndexToLastIndex(int& indexToStartSearchFrom);
};

/*
 *
 */
template<typename T>
PVector<T>::
PVector() :
		_m_size(0), _m_capacity(0), _m_data() {
}

/*
 *
 */
template<typename T>
void PVector<T>::
addAtEnd(const T& value) {
	_m_data[_m_size] = value;
	++_m_size;
}

/*
 *
 */
template<typename T>
T&
PVector<T>::
at(const int index) {
	if (index < 0 || index >= this->size())
		throw prism::OutOfBoundsException(index);
	return _m_data[index];
}

/*
 *
 */
template<typename T>
const int PVector<T>::
capacity() {
	return _m_capacity;
}

/*
 *
 */
template<typename T>
void PVector<T>::
clear() {
	_m_size = 0;
}

/*
 *
 */
template<typename T>
const bool PVector<T>::
contains(const T& value) {
	int i = 0;
	while (i < _m_size) {
		if (_m_data[i] == value)
			return true;
		++i;
	}
	return false;
}

/*
 *
 */
template<typename T>
const int PVector<T>::
count(const T& value) {
	int c = 0;
	for (int i = 0; i < _m_size; i++)
		if (_m_data[i] == value)
			++c;
	return c;
}

/*
 *
 */
template<typename T>
const bool PVector<T>::
empty() {
	return _m_size == 0;
}

/*
 *
 */
template<typename T>
const bool PVector<T>::
endsWith(const T& value) {
	if (value == _m_data[_m_size - 1])
		return true;
	return false;
}

/*
 *
 */
template<typename T>
void PVector<T>::
fill(const T& value) {
	for (int i = 0; i < _m_size; i++)
		_m_data[i] = value;
}

/*
 *
 */
template<typename T>
const bool
PVector<T>::
valueIsEqualToValueAtIndex(int index, const T& value) {
	return _m_data[index] == value;
}

template<typename T>
const bool
PVector<T>::
indexToSearchFromIsNegative(int indexToStartSearchFrom) {
	return indexToStartSearchFrom == -1;
}

template<typename T>
const int
PVector<T>::
setStartIndexToLastIndex(int& indexToStartSearchFrom) {
	return indexToStartSearchFrom = _m_size - 1;
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
lastIndexOf(const T& value, const int from) {
	int indexNotFound = -1;
	int indexToStartSearchFrom = from;

	if (indexToSearchFromIsNegative(indexToStartSearchFrom))
		setStartIndexToLastIndex(indexToStartSearchFrom);

	for (int index = indexToStartSearchFrom; index >= 0; index--) {
		if (valueIsEqualToValueAtIndex(index, value))
			return index;
	}
	return indexNotFound;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
removeLast() {
	--_m_size;
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
	if (size > 0)
		_m_capacity = size;
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
	_m_size = size;
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
size() {
	return _m_size;
}

/*
 *
 */
template <typename T>
const bool
PVector<T>::
startsWith(const T& value) {
	if (_m_data[0] == value)
		return true;
	return false;
}

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















