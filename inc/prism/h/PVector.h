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

	static const int IndexNotFound = -1;
public:
				PVector();
				~PVector();
	void 		append(const T& value);
	T&			at(const int index);
	const int	capacity() const noexcept;
	void		clear() noexcept;
	const bool	contains(const T& value) const noexcept;
	const int	count(const T& value) const noexcept;
	const bool 	empty() const noexcept;
	const bool	endsWith(const T& value) const noexcept;
	void		fill(const T& value);
	const int	indexOf(const T& value, const int from=0) const noexcept;
	void		insert(const int index, const T& value);
	const int	lastIndexOf(const T& value, const int from=-1) const noexcept;
	void 		removeLast();
	void		replace(const int index, const T& value);
	void 		reserve(const int size);
	void 		resize(const int size);
	const int 	size() const noexcept;
	void		squeeze();
	const bool 	startsWith(const T& value) const noexcept;

private:
	const bool	indexIsWithinBounds(const int index) const;
	void		shiftElementsUpAfterInsertionPoint(const int index);
	const bool 	valueIsEqualToValueAtIndex(int index, const T& value) const noexcept;
	bool indexIsNotValidInsertionPoint(const int index);
};

template <typename T>
const bool
operator==(const PVector<T>& lhs, const PVector<T>& rhs);

template <typename T>
const bool
operator!=(const PVector<T>& lhs, const PVector<T>& rhs);


// ************************************************
// Will be moved to other file

/*
 *
 */
template<typename T>
PVector<T>::
PVector()
: _m_size(0),
  _m_capacity(0),
  _m_data()
{}

/*
 *
 */
template <typename T>
PVector<T>::
~PVector() {

}

/*
 *
 */
template<typename T>
void PVector<T>::
append(const T& value) {
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
	if (!indexIsWithinBounds(index))
		throw prism::OutOfBoundsException(index);
	return _m_data[index];
}

/*
 *
 */
template <typename T>
const bool
PVector<T>::
indexIsWithinBounds(const int index) const {
	return index >= 0 && index < _m_size;
}

/*
 *
 */
template<typename T>
const int PVector<T>::
capacity() const noexcept {
	return _m_capacity;
}

/*
 *
 */
template<typename T>
void PVector<T>::
clear() noexcept {
	_m_size = 0;
}

/*
 *
 */
template<typename T>
const bool PVector<T>::
contains(const T& value) const noexcept {
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
count(const T& value) const noexcept {
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
empty() const noexcept {
	return _m_size == 0;
}

/*
 *
 */
template<typename T>
const bool PVector<T>::
endsWith(const T& value) const noexcept {
	if (valueIsEqualToValueAtIndex(_m_size-1, value))
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

template<typename T>
bool
PVector<T>::
indexIsNotValidInsertionPoint(const int index) {
	return index < 0 || index > _m_size;
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
indexOf(const T& value, const int from) const noexcept {
	for (int index=from; index<_m_size; index++) {
		if (valueIsEqualToValueAtIndex(index, value))
			return index;
	}
	return IndexNotFound;
}

/*
 *
 */
template <typename T>
void
PVector<T>::
insert(const int index, const T& value) {
	if (indexIsNotValidInsertionPoint(index))
		throw prism::OutOfBoundsException(index);

	shiftElementsUpAfterInsertionPoint(index);

	replace(index, value);
	_m_size++;
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
lastIndexOf(const T& value, const int from) const noexcept {
	int startIndex = 0;
	(from == -1) ? startIndex = _m_size - 1
					: startIndex = from;

	for (int index = startIndex; index >= 0; index--) {
		if (valueIsEqualToValueAtIndex(index, value))
			return index;
	}
	return IndexNotFound;
}

/*
 *
 */
template<typename T>
const bool
PVector<T>::
valueIsEqualToValueAtIndex(int index, const T& value) const noexcept {
	return _m_data[index] == value;
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
replace(const int index, const T& value) {
	_m_data[index] = value;
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
void
PVector<T>::
shiftElementsUpAfterInsertionPoint(const int index) {
	for (int i=_m_size; i>index; i--) {
		_m_data[i] = _m_data[i-1];
	}
}

/*
 *
 */
template <typename T>
const int
PVector<T>::
size() const noexcept {
	return _m_size;
}

/*
 *
 */
template<typename T>
void
PVector<T>::
squeeze() {
	_m_capacity = _m_size;
}

/*
 *
 */
template <typename T>
const bool
PVector<T>::
startsWith(const T& value) const noexcept {
	if (_m_data[0] == value)
		return true;
	return false;
}

//==========================================================================================
// Non-member functions
//==========================================================================================
template <typename T>
const bool
operator==(const PVector<T>& lhs, const PVector<T>& rhs) {
	for (int index = 0; index < lhs.size(); index++) {
		if (lhs._m_data[index] != rhs._m_data[index])
			return false;
	}
	return true;
}

/*
 *
 */
template <typename T>
const bool
operator!=(const PVector<T>& lhs, const PVector<T>& rhs) {
	return !(lhs==rhs);
}

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















