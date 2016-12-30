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
#include <prism/Allocator>
#include <prism/type_traits>
#include <prism/Iterator>
#include <initializer_list>

PRISM_BEGIN_NAMESPACE

class PVector {
public:
	using iterator 			= prism::SequenceIterator<int, false>;
	using const_iterator 	= prism::SequenceIterator<int, true>;

	int*	_m_start;
	int*	_m_end;
	int*	_m_finish;

	PVector()
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{}

	PVector(const int size, const int value=int())
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{
		_m_fillInitialize(size, value);
	}

	template <typename ForwardIterator>
	PVector(ForwardIterator first, ForwardIterator last)
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{
		_m_rangeInitialize(first, last);
	}

	PVector(const std::initializer_list<int> il)
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{
		_m_rangeInitialize(il.begin(), il.end());
	}

	~PVector() {
		delete [] _m_start;
	}

	void
	append(const int value) {
		insert(size(), 1, value);
	}

	int&
	at(const int index) {
		if (_m_outOfBounds(index))
			throw prism::OutOfBoundsException(index);
		return _m_start[index];
	}

	iterator
	begin() {
		return iterator(_m_start);
	}

	const int
	capacity() const {
		return _m_finish - _m_start;
	}

	const_iterator
	cbegin() {
		return const_iterator(_m_start);
	}

	const_iterator
	cend() {
		return const_iterator(_m_end);
	}

	int *
	data() {
		return _m_start;
	}

	const bool
	empty() const {
		return size() == 0;
	}

	iterator
	end() {
		return iterator(_m_end);
	}

	void
	insert(const int index, const int value) {
		insert(index, 1, value);
	}

	void
	insert(const int index, const int count, const int value) {
		if (_m_invalidInsertionPoint(index))
			throw prism::OutOfBoundsException(index);
		if (size() + count > capacity())
			reserve(capacity() * 2 + count);

		prism::copy_backward(_m_start+index, _m_end, _m_end+count);
		prism::fill(_m_start+index, _m_start+index+count, value);
		_m_increaseSizeeBy(count);
	}

	void
	prepend(const int value) {
		insert(0, 1, value);
	}

	void
	remove(const int index) {
		remove(index, 1);
	}

	void
	remove(const int index, const int count) {
		if (_m_outOfBounds(index))
			throw prism::OutOfBoundsException(index);

		prism::copy(_m_start+index+count, _m_end, _m_start+index);
		_m_decreaseSizeBy(count);
	}

	void
	removeAll(const int value) {
		_m_end = prism::remove(_m_start, _m_end, value);
	}

	void
	removeFirst() {
		remove(0);
	}

	template <typename Predicate>
	void
	removeIf(Predicate pred) {
		_m_end = prism::remove_if(_m_start, _m_end, pred);
	}

	void
	removeLast() {
		remove(size()-1);
	}

	void
	replace(const int index, const int value) {
		if (_m_outOfBounds(index))
			throw prism::OutOfBoundsException(index);
		_m_replaceValueAtIndex(index, value);
	}

	void
	reserve(const int size) {
		int newCapacity = size;

		if(_m_isNegative(newCapacity))
			throw std::bad_alloc();

		if (newCapacity > capacity()) {
			_m_reallocateAndCopy(newCapacity);
		}
	}

	const int
	size() const {
		return _m_end - _m_start;
	}

	int&
	operator[](const int index) {
		return _m_start[index];
	}

private:
	int*
	_m_allocate(int newCapacity) {
		return new int[newCapacity];
	}

	void
	_m_reallocateAndCopy(int newCapacity) {
		int oldSize = size();
		int* newStorage = _m_allocate(newCapacity);
		prism::copy(_m_start, _m_start + oldSize, newStorage);
		delete [] _m_start;
		_m_start = newStorage;
		_m_end = _m_start + oldSize;
		_m_finish = _m_start + newCapacity;
	}

	const bool
	_m_isNegative(int num) const {
		return num < 0;
	}

	const bool
	_m_outOfBounds(const int index) const {
		return index < 0 || index >= size();
	}

	int
	_m_replaceValueAtIndex(const int index, const int value) {
		return _m_start[index] = value;
	}

	bool
	_m_invalidInsertionPoint(const int index) const {
		return index < 0 || index > size();
	}

	void _m_increaseSizeeBy(const int amount) {
		_m_end += amount;
	}

	void
	_m_decreaseSizeBy(const int amount) {
		_m_end -= amount;
	}

	void
	_m_fillInitialize(const int size, const int value) {
		_m_start = _m_allocate(size);
		_m_end = _m_start + size;
		_m_finish = _m_start + size;
		prism::uninitialized_fill_n(_m_start, size, value);
	}

	template <typename ForwardIterator>
	void
	_m_rangeInitialize(ForwardIterator first, ForwardIterator last) {
		_m_start = _m_allocate(last-first);
		_m_end = _m_start + (last-first);
		_m_finish = _m_start + (last-first);
		prism::uninitialized_copy(first, last, _m_start);
	}
};



PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















