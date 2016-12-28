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
#include <prism/algorithm>
#include <prism/OutOfBoundsException>

PRISM_BEGIN_NAMESPACE

class PVector {
public:
	int*		_m_start;
	int*		_m_end;
	int*		_m_finish;
	/*
	 *
	 */
	PVector()
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{}

	/*
	 *
	 */
	~PVector() {
		delete [] _m_start;
	}

	int&
	at(const int index) {
		if (outOfBounds(index))
			throw prism::OutOfBoundsException(index);
		return _m_start[index];
	}

	/*
	 *
	 */
	const int
	capacity() {
		return _m_finish - _m_start;
	}
	/*
	 *
	 */
	int *
	data() {
		return _m_start;
	}
	/*
	 *
	 */
	const bool
	empty() {
		return size() == 0;
	}
	/*
	 *
	 */
	void
	insert(const int value) {
		if (size() + 1 > capacity())
			reserve(capacity() * 2 + 1);

		_m_start[size()] = value;
		_m_end += 1;
	}
	/*
	 *
	 */
	void
	reserve(const int size) {
		int newCapacity = size;

		throwIfNewCapacityIsNegative(newCapacity);

		if (newCapacity > capacity()) {
			reallocateAndCopy(newCapacity);
		}
	}
	/*
	 *
	 */
	const int
	size() {
		return _m_end - _m_start;
	}

	int&
	operator[](const int index) {
		return _m_start[index];
	}

private:
	int*
	allocate(int newCapacity) {
		return new int[newCapacity];
	}

	void
	reallocateAndCopy(int newCapacity) {
		int oldSize = size();
		int* newStorage = allocate(newCapacity);
		prism::copy(_m_start, _m_start + oldSize, newStorage);
		delete [] _m_start;
		_m_start = newStorage;
		_m_end = _m_start + oldSize;
		_m_finish = _m_start + newCapacity;
	}

	void
	throwIfNewCapacityIsNegative(int newCapacity) {
		if (newCapacity < 0)
			throw std::bad_alloc();
	}

	const bool
	outOfBounds(const int index) {
		return index < 0 || index >= size();
	}
};



PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















