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
#include <vector>
#include <list>

PRISM_BEGIN_NAMESPACE

template <typename T>
struct Range {
	T* first;
	T* last;
	Range(T* first, T* last=nullptr)
	: first(first), last(last) {}

	const int
	length() const {
		return last - first;
	}
};

template <typename T>
class PVector {
public:
	using iterator 					= prism::SequenceIterator<T, false>;
	using const_iterator 			= prism::SequenceIterator<T, true>;
	using reverse_iterator			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator	= prism::ReverseIterator<const_iterator>;

	T*	_m_start;
	T*	_m_end;
	T*	_m_finish;
	enum { _m_growth = 2 };

	enum { IndexNotFound = -1 };

	PVector()
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{}

	PVector(const int size, const T& value=T())
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

	PVector(const std::initializer_list<T> il)
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{
		_m_rangeInitialize(il.begin(), il.end());
	}

	PVector(const PVector& rhs)
	: _m_start(nullptr),
	  _m_end(nullptr),
	  _m_finish(nullptr)
	{
		_m_rangeInitialize(rhs.cbegin(), rhs.cend());
	}

	PVector(PVector<T>&& rhs)
	: _m_start(rhs._m_start),
	  _m_end(rhs._m_end),
	  _m_finish(rhs._m_finish)
	{
		rhs._m_start = nullptr;
		rhs._m_end = nullptr;
		rhs._m_finish = nullptr;
	}

	~PVector() {
		delete [] _m_start;
	}

	prism::Allocator<T>
	allocator() {
		return prism::Allocator<T>();
	}

	void
	append(const T& value) {
		insert(size(), 1, value);
	}

	void
	append(T&& value) {
		insert(size(), 1, prism::forward<T>(value));
	}

	T&
	at(const int index) {
		if (_m_indexIsOutOfBounds(index))
			throw prism::OutOfBoundsException(index);
		return _m_start[index];
	}

	const T&
	at(const int index) const {
		if (_m_indexIsOutOfBounds(index))
			throw prism::OutOfBoundsException(index);
		return _m_start[index];
	}

	T&
	back() {
		return *(_m_end-1);
	}

	const T&
	back() const {
		return *(_m_end-1);
	}

	iterator
	begin() {
		return iterator(_m_start);
	}

	const_iterator
	begin() const {
		return const_iterator(_m_start);
	}

	const int
	capacity() const {
		return _m_finish - _m_start;
	}

	const_iterator
	cbegin() const {
		return const_iterator(_m_start);
	}

	const T*
	cdata() const {
		return _m_start;
	}

	const_iterator
	cend() const {
		return const_iterator(_m_end);
	}

	void
	clear() {
		// todo - old values need to be destroyed if not fundamental types
		_m_end = _m_start;
	}

	const bool
	contains(const T& value) {
		return indexOf(value) == IndexNotFound ? false : true;
	}

	const int
	count(const T& value) {
		Range<T> source(_m_start, _m_end);
		return prism::count(source.first, source.last, value);
	}

	const_reverse_iterator
	crbegin() const {
		return const_reverse_iterator(_m_end);
	}

	const_reverse_iterator
	crend() const {
		return const_reverse_iterator(_m_start);
	}

	T *
	data() {
		return _m_start;
	}

	const T*
	data() const {
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

	const_iterator
	end() const {
		return const_iterator(_m_end);
	}

	const bool
	endsWith(const T& value) {
		if (empty()) return false;
		return *(_m_end-1) == value;
	}

	void
	fill(const T& value) {
		prism::fill(_m_start, _m_end, value);
	}

	T&
	first() {
		return *_m_start;
	}

	const T&
	first() const {
		return *_m_start;
	}

	T&
	front() {
		return *_m_start;
	}

	const T&
	front() const {
		return *_m_start;
	}

	const int
	indexOf(const T& value, const int from=0) {
		if (empty()) return IndexNotFound;
		return _m_findFirstIndexOf(from, value);
	}

	void
	insert(const int index, const T& value) {
		insert(index, 1, value);
	}

	void
	insert(const int index, T&& value) {
		insert(index, 1, prism::forward<T>(value));
	}

	iterator
	insert(const_iterator pos, const T& value) {
		int index = prism::distance(cbegin(), pos);
		insert(index, 1, value);
		return begin() + index;
	}

	void
	insert(const_iterator pos, const int count, const T& value) {
		int index = prism::distance(cbegin(), pos);
		insert(index, count, value);
	}

	void
	insert(const_iterator pos, T&& value) {
		int index = prism::distance(cbegin(), pos);
		insert(index, 1, prism::forward<T>(value));
	}

	void
	insert(const int index, const int count, const T& value) {
		_m_validateInsertionPoint(index);
		_m_ensureSufficientStorage(count);
		_m_insertAux(index, count, value);
	}

	void
	insert(const_iterator pos, std::initializer_list<T> il) {
		insert(pos, il.begin(), il.end());
	}

	template <typename ForwardIterator>
	void
	insert(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		int index = pos - cbegin();
		_m_validateInsertionPoint(index);
		_m_ensureSufficientStorage(last - first);
		_m_insertRange(index, first, last);
	}

	T&
	last() {
		return *(_m_end-1);
	}

	const T&
	last() const {
		return *(_m_end-1);
	}

	const int
	lastIndexOf(const T& value, const int from=-1) {
		if (empty()) return IndexNotFound;
		return _m_findLastIndexOf(from, value);
	}

	prism::PVector<T>
	mid(const int index, const int count=-1) const {
		T* first = _m_start + index;
		T* last = (count == -1) ? _m_end : first + count;
		Range<T> source(first, last);

		return prism::PVector<T>(source.first, source.last);
	}

	void
	prepend(const T& value) {
		insert(0, 1, value);
	}

	void
	prepend(T&& value) {
		insert(0, 1, prism::forward<T>(value));
	}

	reverse_iterator
	rbegin() {
		return reverse_iterator(_m_end);
	}

	const_reverse_iterator
	rbegin() const {
		return const_reverse_iterator(_m_end);
	}

	reverse_iterator
	rend() {
		return reverse_iterator(_m_start);
	}

	const_reverse_iterator
	rend() const {
		return const_reverse_iterator(_m_start);
	}

	iterator
	remove(const_iterator pos) {
		int index = pos-cbegin();
		remove(index);
		return begin() + index;
	}

	iterator
	remove(const_iterator first, const_iterator last) {
		int index = first-cbegin();
		int rangeLength = last-first;
		remove(index, rangeLength);
		return begin() + index;
	}

	void
	remove(const int index) {
		remove(index, 1);
	}

	void
	remove(const int index, const int count) {
		if (_m_indexIsOutOfBounds(index))
			throw prism::OutOfBoundsException(index);

		// TODO
		// removed values are overwritten, ok if fundamental types
		// otherwise need to be destroyed properly
		Range<T> source(_m_start+index+count, _m_end);
		Range<T> destination(_m_start+index);
		prism::copy(source.first, source.last, destination.first);
		_m_decreaseSizeBy(count);
	}

	void
	removeAll(const T& value) {
		Range<T> source = _m_occupiedRange();
		_m_end = prism::remove(source.first, source.last, value);
	}

	void
	removeFirst() {
		remove(0);
	}

	template <typename Predicate>
	void
	removeIf(Predicate pred) {
		Range<T> source = _m_occupiedRange();
		_m_end = prism::remove_if(source.first, source.last, pred);
	}

	void
	removeLast() {
		remove(size()-1);
	}

	void
	replace(const int index, const T& value) {
		if (_m_indexIsOutOfBounds(index))
			throw prism::OutOfBoundsException(index);
		_m_replaceValueAtIndex(index, value);
	}

	void
	reserve(const int size) {
		int newCapacity = size;

		if(_m_isNegative(newCapacity))
			throw std::bad_alloc();

		if (_m_needsReallocation(newCapacity))
			_m_reallocateAndCopy(newCapacity);
	}

	void
	resize(const int size, const T& paddingValue = T()) {
		if (_m_isNegative(size))
			throw prism::OutOfBoundsException(size);

		if (_m_resizingGreater(size)) {
			int numNewElements = size - this->size();
			_m_resizeGreater(numNewElements, paddingValue);
		}
		else if(_m_resizingSmaller(size))
			_m_resizeSmaller(size);
	}

	const int
	size() const {
		return _m_end - _m_start;
	}

	void
	squeeze() {
		_m_removeUnusedMemoryAtEndOfStorage();
	}

	const bool
	startsWith(const T& value) {
		if (empty()) return false;
		return *_m_start == value;
	}

	void
	swap(PVector<T>& other) {
		using prism::swap;
		swap(_m_start, other._m_start);
		swap(_m_end, other._m_end);
		swap(_m_finish, other._m_finish);
	}

	std::list<T>
	toStdList() {
		return std::list<T>(_m_start, _m_end);
	}

	std::vector<T>
	toStdVector() {
		return std::vector<T>(_m_start, _m_end);

	}

	T&
	operator[](const int index) {
		return _m_start[index];
	}

	const T&
	operator[](const int index) const {
		return _m_start[index];
	}

	PVector<T>&
	operator=(const PVector<T>& rhs) {
		if (*this != rhs) {
			delete [] _m_start;
			_m_start = _m_allocate(rhs.capacity());
			prism::copy(rhs.cbegin(), rhs.cend(), begin());
			_m_end = _m_start + rhs.size();
			_m_finish = _m_start + rhs.capacity();
		}
		return *this;
	}

	PVector<T>&
	operator=(PVector<T>&& rhs) {
		// todo !! existing memory is not deleted !!
		_m_start = rhs._m_start;
		_m_end = rhs._m_end;
		_m_finish = rhs._m_finish;
		rhs._m_start = nullptr;
		rhs._m_end = nullptr;
		rhs._m_finish = nullptr;
		return *this;
	}

	PVector<T>&
	operator<<(const T& value) {
		return *this += value;
	}

	PVector<int>&
	operator+=(const T& value) {
		append(value);
		return *this;
	}

	PVector<T>
	operator+(const PVector<T>& rhs) {
		PVector<T> copy(*this);
		return copy << rhs;
	}

	PVector<T>&
	operator+=(const PVector<T>& rhs) {
		return *this << rhs;
	}

	PVector<T>&
	operator<<(const PVector<T>& rhs) {
		insert(cend(), rhs.cbegin(), rhs.cend());
		return *this;
	}

private:
	T*
	_m_allocate(int newCapacity) {
		return new T[newCapacity];
	}

	void
	_m_reallocateAndCopy(int newCapacity) {
		int oldSize = size();
		T* newStorage = _m_allocate(newCapacity);
		Range<T> source(_m_start, _m_start + oldSize);
		prism::copy(source.first, source.last, newStorage);
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
	_m_indexIsOutOfBounds(const int index) const {
		return index < 0 || index >= size();
	}

	T&
	_m_replaceValueAtIndex(const int index, const T& value) {
		return _m_start[index] = value;
	}

	bool
	_m_isInvalidInsertionPoint(const int index) const {
		return index < 0 || index > size();
	}

	void _m_increaseSizeBy(const int amount) {
		_m_end += amount;
	}

	void
	_m_decreaseSizeBy(const int amount) {
		_m_end -= amount;
	}

	void
	_m_fillInitialize(const int size, const T& value) {
		_m_start = _m_allocate(size);
		_m_end = _m_start + size;
		_m_finish = _m_start + size;
		prism::uninitialized_fill_n(_m_start, size, value);
	}

	bool
	_m_needsReallocation(const int newSize) {
		return newSize > capacity();
	}

	void
	_m_insertAux(const int index, const int count, const T& value) {
		_m_shiftElementsUp(begin()+index, count);
		_m_fillInsert(begin() + index, count, value);
		_m_increaseSizeBy(count);
	}

	void
	_m_shiftElementsUp(iterator from, const int count) {
		prism::copy_backward(from, end(), end()+count);
	}

	void
	_m_fillInsert(iterator from, const int count, const T& value) {
		prism::fill_n(from, count, value);
	}

	void
	_m_resizeSmaller(int newSize) {
		_m_end = _m_start + newSize;
	}

	void
	_m_resizeGreater(int numNewElements, const T& paddingValue) {
		int newSize = size() + numNewElements;
		if (_m_needsReallocation(newSize))
			_m_reallocateAndCopy(newSize);

		_m_increaseSizeBy(numNewElements);
		iterator from = end() - numNewElements;
		_m_padEndWithValue(from, paddingValue);
	}

	void
	_m_padEndWithValue(iterator from, const T& paddingValue) {
		prism::fill(from, end(), paddingValue);
	}

	int
	_m_numNewElements(const int size) {
		return size - this->size();
	}

	template <typename ForwardIterator>
	void
	_m_rangeInitialize(ForwardIterator first, ForwardIterator last) {
		_m_start = _m_allocate(last-first);
		_m_end = _m_start + (last-first);
		_m_finish = _m_end;
		prism::uninitialized_copy(first, last, _m_start);
	}

	const bool
	_m_resizingGreater(const int size) {
		return size > this->size();
	}

	const bool
	_m_resizingSmaller(const int size) {
		return !_m_resizingGreater(size);
	}

	void
	_m_removeUnusedMemoryAtEndOfStorage() {
		int currentSize = size();
		T* newStorage = _m_allocate(currentSize);
		_m_copyRangeToOtherRange(_m_occupiedRange(), newStorage);

		delete[] _m_start;
		_m_start = newStorage;
		_m_end = _m_start + currentSize;
		_m_finish = _m_end;
	}

	void
	_m_copyRangeToOtherRange(const Range<T>& source, T* destination) {
		prism::copy(source.first, source.last, destination);
	}

	Range<T>
	_m_occupiedRange() {
		return Range<T>(_m_start, _m_end);
	}

	const int
	_m_findFirstIndexOf(const int from, const T& value) {
		Range<T> source(_m_start + from, _m_end);
		iterator it = prism::find(source.first, source.last, value);
		return (it == end()) ? IndexNotFound : prism::distance(begin(), it);
	}

	const int
	_m_findLastIndexOf(const int from, const T& value) {
		T* endRange = from == -1 ? _m_end : _m_start + from;
		Range<T> source(_m_start, endRange);
		iterator it = prism::find_last(source.first, source.last, value);
		return (it == end()) ? IndexNotFound : prism::distance(begin(), it);
	}

	template <typename ForwardIterator>
	void
	_m_insertRange(const int index, ForwardIterator first, ForwardIterator last) {
		_m_shiftElementsUp(begin()+index, last-first);
		prism::copy(first, last, begin()+index);
		_m_increaseSizeBy(last-first);
	}

	void
	_m_validateInsertionPoint(const int index) {
		if (_m_isInvalidInsertionPoint(index))
			throw prism::OutOfBoundsException(index);
	}

	void
	_m_ensureSufficientStorage(const int count) {
		if (_m_needsReallocation(size() + count))
			reserve((capacity() == 0) ? count : (capacity() + count) * _m_growth);
	}
};

template <typename T>
const bool
operator==(const PVector<T>& lhs, const PVector<T>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return prism::equal(lhs._m_start, lhs._m_end, rhs._m_start);
}

template <typename T>
const bool
operator!=(const PVector<T>& lhs, const PVector<T>& rhs) {
	return !(lhs==rhs);
}

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_H_ */















