/*
 * DequeIterator.h
 * v0.2
 *
 *  Created on: Feb 2, 2015
 *      Author: iainhemstock
 */

// todo comment each method in DequeIterator

#ifndef DEQUEITERATOR_H_
#define DEQUEITERATOR_H_

#include <ostream>
#include <cstddef> // for size_t and ptrdiff_t

using namespace std; // todo remove this

namespace prism {
namespace containers {

// ====================================================
// DequeIterator
// ====================================================
// \cond DO_NOT_DOCUMENT
template <class T>
class DequeIterator {
public:
	typedef			std::random_access_iterator_tag			iterator_category;
	typedef			T										value_type;
	typedef			T&										reference;
	typedef			T*										pointer;
	typedef			size_t									size_type;
	typedef			ptrdiff_t								difference_type;
	typedef 		DequeIterator							_Self;
public:
	// todo: have to remove this enum as it duplicates the same enum in DequeData
	// need to get both DequeData and DequeIterator to share the same enum
	enum			{ CHUNK_SIZE = 8 };
	T** 			chunk;		// pointer to pointer to T array
	T*				current; 	// pointer to the current value in chunk
	T*				begin;		// pointer to the first value in the chunk (may not be the first cell)
	T*				end;		// pointer to the position one past the last value in the chunk
public:
					DequeIterator();
					DequeIterator(const _Self& copy);
	void			setChunk(T** newChunk);

	T&				operator*() const;
	T*				operator->() const;
	_Self&			operator++();
	_Self			operator++(const int junk);
	_Self			operator+(const int i);
	_Self&			operator--();
	_Self			operator--(const int junk);
	_Self			operator-(const int i);
	_Self&			operator+=(const int i);
	_Self&			operator-=(const int i);

	// Related non-members
	template <class _T>
	friend const int operator-(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator==(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator!=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator<(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator>(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator<=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
	template <class _T>
	friend const bool operator>=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs);
};
// \endcond

/**
 *
 */
template <class T>
DequeIterator<T>::DequeIterator()
: chunk(0), current(0), begin(0), end(0) {

}

/**
 *
 */
template <class T>
DequeIterator<T>::DequeIterator(const _Self& copy)
: chunk(copy.chunk), current(copy.current), begin(copy.begin), end(copy.end) {

}

/**
 *
 */
template <class T>
void DequeIterator<T>::setChunk(T** newChunk) {
	chunk = newChunk;
	begin = *newChunk;
	end = begin + CHUNK_SIZE;
}

/**
 *
 */
template <class T>
T& DequeIterator<T>::operator*() const {
	return *current;
}

/**
 *
 */
template <class T>
T* DequeIterator<T>::operator->() const {
	return current;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self& DequeIterator<T>::operator++() {
	current++;
	if (current == end) {
		setChunk(chunk+1);
		current = begin;
	}
	return *this;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self DequeIterator<T>::operator++(const int junk) {
	_Self tmp = _Self(*this);
	++*this;
	return tmp;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self& DequeIterator<T>::operator+=(const int i) {
	if (current + i >= begin && current+i < end)
		current += i;
	else {
		int offset = i - (current - begin);
		int chunkOffset = offset / CHUNK_SIZE;
		setChunk(chunk + chunkOffset);
		current = begin + (i % CHUNK_SIZE);
	}

	return *this;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self DequeIterator<T>::operator+(const int i) {
	return *this += i;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self& DequeIterator<T>::operator--() {
	if (current == begin) {
		setChunk(chunk-1);
		current = end;
	}
	current--;
	return *this;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self DequeIterator<T>::operator--(const int junk) {
	_Self tmp = _Self(*this);
	--*this;
	return tmp;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self& DequeIterator<T>::operator-=(const int i) {
	return *this += -i;
}

/**
 *
 */
template <class T>
typename DequeIterator<T>::_Self DequeIterator<T>::operator-(const int i) {
	return *this -= i;
}

// ====================================================
// Related non-members
// ====================================================
/**
 *
 */
template <class _T>
const int operator-(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	int i = lhs.chunk - rhs.chunk + 1;
	i *= lhs.CHUNK_SIZE;
	i -= lhs.end - lhs.current;
	i -= rhs.current - rhs.begin;

	return i;
}

/**
 *
 */
template <class _T>
const bool operator==(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	return lhs.current == rhs.current;
}

/**
 *
 */
template <class _T>
const bool operator!=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	return !(lhs.current == rhs.current);
}

/**
 *
 */
template <class _T>
const bool operator<(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	if (lhs.chunk < rhs.chunk) return true;
	if (lhs.chunk == rhs.chunk) {
		if (lhs.current < rhs.current) return true;
		else return false;
	}
	return false;
}

/**
 *
 */
template <class _T>
const bool operator>(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	return rhs < lhs;
}

/**
 *
 */
template <class _T, class _Ref, class _Ptr>
const bool operator<=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	return !(rhs < lhs);
}

/**
 *
 */
template <class _T>
const bool operator>=(const DequeIterator<_T>& lhs, const DequeIterator<_T>& rhs) {
	return !(rhs > lhs);
}

// ====================================================
// DequeConstIterator
// ====================================================
// \cond DO_NOT_DOCUMENT
template <class T>
class DequeConstIterator {
public:
	typedef			std::random_access_iterator_tag			iterator_category;
	typedef			T										value_type;
	typedef			const T&								const_reference;
	typedef			const T*								const_pointer;
	typedef			size_t									size_type;
	typedef			ptrdiff_t								difference_type;
	typedef 		DequeConstIterator						_Self;
public:
	// todo: have to remove this enum as it duplicates the same enum in DequeData
	// need to get both DequeData and DequeIterator to share the same enum
	enum			{ CHUNK_SIZE = 8 };
	T** 			chunk;		// pointer to pointer to T array
	T*				current; 	// pointer to the current value in chunk
	T*				begin;		// pointer to the first value in the chunk (may not be the first cell)
	T*				end;		// pointer to the position one past the last value in the chunk
public:
					DequeConstIterator();
					DequeConstIterator(const _Self& copy);
					DequeConstIterator(const DequeIterator<T>& copy);
	void			setChunk(T** newChunk);

	const_reference	operator*() const;
	const_pointer	operator->() const;
	_Self&			operator++();
	_Self			operator++(const int junk);
	_Self			operator+(const int i);
	_Self&			operator--();
	_Self			operator--(const int junk);
	_Self			operator-(const int i);
	_Self&			operator+=(const int i);
	_Self&			operator-=(const int i);

	// Related non-members
	template <class _T>
	friend const int operator-(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator==(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator!=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator<(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator>(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator<=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
	template <class _T>
	friend const bool operator>=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs);
};

// \endcond

/**
 *
 */
template <class T>
DequeConstIterator<T>::DequeConstIterator()
: chunk(0), current(0), begin(0), end(0) {

}

/**
 *
 */
template <class T>
DequeConstIterator<T>::DequeConstIterator(const _Self& copy)
: chunk(copy.chunk), current(copy.current), begin(copy.begin), end(copy.end) {

}

/**
 * Conversion from non-const iterator to const iterator.
 */
template <class T>
DequeConstIterator<T>::DequeConstIterator(const DequeIterator<T>& copy)
: chunk(copy.chunk), current(copy.current), begin(copy.begin), end(copy.end) {

}

/**
 *
 */
template <class T>
void DequeConstIterator<T>::setChunk(T** newChunk) {
	chunk = newChunk;
	begin = *newChunk;
	end = begin + CHUNK_SIZE;
}

/**
 *
 */
template <class T>
const T& DequeConstIterator<T>::operator*() const {
	return *current;
}

/**
 *
 */
template <class T>
const T* DequeConstIterator<T>::operator->() const {
	return current;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self& DequeConstIterator<T>::operator++() {
	current++;
	if (current == end) {
		setChunk(chunk+1);
		current = begin;
	}
	return *this;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self DequeConstIterator<T>::operator++(const int junk) {
	_Self tmp = _Self(*this);
	++*this;
	return tmp;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self& DequeConstIterator<T>::operator+=(const int i) {
	if (current + i >= begin && current+i < end)
		current += i;
	else {
		int offset = i - (current - begin);
		int chunkOffset = offset / CHUNK_SIZE;
		setChunk(chunk + chunkOffset);
		current = begin + (i % CHUNK_SIZE);
	}

	return *this;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self DequeConstIterator<T>::operator+(const int i) {
	return *this += i;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self& DequeConstIterator<T>::operator--() {
	if (current == begin) {
		setChunk(chunk-1);
		current = end;
	}
	current--;
	return *this;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self DequeConstIterator<T>::operator--(const int junk) {
	_Self tmp = _Self(*this);
	--*this;
	return tmp;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self& DequeConstIterator<T>::operator-=(const int i) {
	return *this += -i;
}

/**
 *
 */
template <class T>
typename DequeConstIterator<T>::_Self DequeConstIterator<T>::operator-(const int i) {
	return *this -= i;
}

// ====================================================
// Related non-members
// ====================================================
/**
 *
 */
template <class _T>
const int operator-(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	int i = lhs.chunk - rhs.chunk + 1;
	i *= lhs.CHUNK_SIZE;
	i -= lhs.end - lhs.current;
	i -= rhs.current - rhs.begin;

	return i;
}

/**
 *
 */
template <class _T>
const bool operator==(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	return lhs.current == rhs.current;
}

/**
 *
 */
template <class _T>
const bool operator!=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	return !(lhs.current == rhs.current);
}

/**
 *
 */
template <class _T>
const bool operator<(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	if (lhs.chunk < rhs.chunk) return true;
	if (lhs.chunk == rhs.chunk) {
		if (lhs.current < rhs.current) return true;
		else return false;
	}
	return false;
}

/**
 *
 */
template <class _T>
const bool operator>(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	return rhs < lhs;
}

/**
 *
 */
template <class _T, class _Ref, class _Ptr>
const bool operator<=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	return !(rhs < lhs);
}

/**
 *
 */
template <class _T>
const bool operator>=(const DequeConstIterator<_T>& lhs, const DequeConstIterator<_T>& rhs) {
	return !(rhs > lhs);
}

}
}


#endif /* DEQUEITERATOR_H_ */
