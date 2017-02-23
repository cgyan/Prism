/*
 * Vector.h
 * v0.*
 *
 *  Created on: 13 Dec 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_VECTOR_H_
#define PRISM_VECTOR_H_

#include <prism/h/global.h>
#include <prism/algorithm>
#include <prism/OutOfBoundsException>
#include <prism/BadSizeException>
#include <prism/Allocator>
#include <prism/Iterator>
#include <ostream>

PRISM_BEGIN_NAMESPACE

template <typename T, typename Allocator>
class VectorImpl;

template <typename T, typename Allocator = prism::Allocator<T>>
class Vector {
private:
	using alloc_traits 				= prism::AllocatorTraits<Allocator>;
	using Impl						= prism::VectorImpl<T, Allocator>;
public:
	using allocator_type			= Allocator;
	using value_type				= typename alloc_traits::value_type;
	using reference					= typename alloc_traits::reference;
	using const_reference			= typename alloc_traits::const_reference;
	using pointer					= typename alloc_traits::pointer;
	using const_pointer				= typename alloc_traits::const_pointer;
	using difference_type			= typename alloc_traits::difference_type;
	using size_type					= typename alloc_traits::size_type;
	using iterator 					= prism::SequenceIterator<T, false>;
	using const_iterator 			= prism::SequenceIterator<T, true>;
	using reverse_iterator			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator	= prism::ReverseIterator<const_iterator>;
private:
	Impl impl;
public:
	enum { IndexNotFound = Impl::IndexNotFound };
public:
	Vector()
	: impl{}
	{}

	~Vector() noexcept = default;

	Vector(const int size, const T& value=T())
	: impl{size, value}
	{}

	template <typename ForwardIterator>
	Vector(ForwardIterator first, ForwardIterator last)
	: impl{first, last}
	{}

	Vector(std::initializer_list<T> il)
	: impl{il.begin(), il.end()}
	{}

	Vector(const Vector& rhs)
	: impl{rhs.cbegin(), rhs.cend()}
	{}

	Vector(Vector<T, Allocator>&& rhs) noexcept
	: impl{std::move(rhs.impl)}
	{}

	Vector<T, Allocator>&
	operator=(const Vector<T, Allocator>& rhs) {
		Vector rhsCopy(rhs);
		this->swap(rhsCopy);
		return *this;
	}

	Vector<T, Allocator>&
	operator=(Vector<T, Allocator>&& rhs) noexcept {
		clear();
		this->swap(rhs);
		return *this;
	}

	allocator_type
	allocator() const noexcept {
		return allocator_type(impl.storage);
	}

	void
	append(const T& value) {
		impl.insertAtEnd(value);
	}

	void
	append(T&& value) {
		impl.insertAtEnd(std::move(value));
	}

	void
	prepend(const T& value) {
		impl.insert(cbegin(), value);
	}

	void
	prepend(T&& value) {
		impl.insert(cbegin(), std::move(value));
	}

	void
	insert(const int index, const T& value) {
		insert(cbegin() + index, value);
	}

	void
	insert(const int index, T&& value) {
		insert(cbegin() + index, std::move(value));
	}

	void
	insert(const int index, const int count, const T& value) {
		insert(cbegin() + index, count, value);
	}

	iterator
	insert(const_iterator pos, const T& value) {
		if (pos == cend()) return impl.insertAtEnd(value);
		else return impl.insert(pos, value);
	}

	iterator
	insert(const_iterator pos, T&& value) {
		if (pos == cend()) return impl.insertAtEnd(std::move(value));
		else return impl.insert(pos, std::move(value));
	}

	iterator
	insert(const_iterator pos, const int count, const T& value) {
		if (pos == cend()) return impl.fillAppend(count, value);
		else return impl.fillInsert(pos, count, value);
	}

	iterator
	insert(const_iterator pos, std::initializer_list<T> il) {
		return insert(pos, il.begin(), il.end());
	}

	template <typename ForwardIterator>
	iterator
	insert(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		if (pos == cend()) return impl.rangeAppend(first, last);
		else return impl.rangeInsert(pos, first, last);
	}

	const int
	capacity() const noexcept {
		return impl.storage.capacity();
	}

	const int
	size() const noexcept {
		return impl.storage.size();
	}

	const bool
	empty() const noexcept {
		return size() == 0;
	}

	void
	clear() noexcept {
		impl.clear();
	}

	void
	remove(const int index) {
		remove(cbegin() + index);
	}

	iterator
	remove(const_iterator pos) {
		if (pos == --cend()) return impl.removeAtEnd();
		else return impl.remove(pos);
	}

	void
	remove(const int index, const int count) {
		const_iterator first = cbegin() + index;
		const_iterator last = first + count;
		remove(cbegin() + index, first + count);
	}

	iterator
	remove(const_iterator first, const_iterator last) {
		if (last == cend()) return impl.rangeRemoveAtEnd(first);
		else return impl.rangeRemove(first, last);
	}

	void
	removeFirst() {
		remove(cbegin());
	}

	void
	removeLast() noexcept {
		remove(--cend());
	}

	void
	removeAll(const T& value) {
		impl.removeAllOccurrencesOfValue(value);
	}

	template <typename UnaryPredicate>
	void
	removeIf(UnaryPredicate pred) {
		impl.removeElementsForWhichPredIsTrue(pred);
	}

	T&
	at(const int index) {
		return impl.valueAtIndex(index);
	}

	const T&
	at(const int index) const {
		return impl.valueAtIndex(index);
	}

	T&
	first() {
		return impl.valueAtIndex(0);
	}

	const T&
	first() const {
		return impl.valueAtIndex(0);
	}

	T&
	front() {
		return impl.valueAtIndex(0);
	}

	const T&
	front() const {
		return impl.valueAtIndex(0);
	}

	T&
	back() {
		return impl.valueAtIndex(size() - 1);
	}

	const T&
	back() const {
		return impl.valueAtIndex(size() - 1);
	}

	T&
	last() {
		return impl.valueAtIndex(size() - 1);
	}

	const T&
	last() const {
		return impl.valueAtIndex(size() - 1);
	}

	Vector<T, Allocator>
	mid(const int index, const int count=-1) const {
		const_iterator first = cbegin() + index;
		const_iterator last = (count == -1) ? cend() : first + count;
		return Vector<T, Allocator>(first, last);
	}

	const T*
	cdata() const noexcept {
		return impl.storage.start;
	}

	T *
	data() noexcept {
		return impl.storage.start;
	}

	const T*
	data() const noexcept {
		return impl.storage.start;
	}

	void
	fill(const T& value) {
		Vector<T, Allocator> tmp(size(), value);
		swap(tmp);
	}

	void
	replace(const int index, const T& value) {
		impl.replace(cbegin() + index, value);
	}

	void
	replace(const int index, T&& value) {
		impl.replace(cbegin() + index, std::move(value));
	}

	void
	replace(const_iterator pos, const T& value) {
		impl.replace(pos, value);
	}

	void
	replace(const_iterator pos, T&& value) {
		impl.replace(pos, std::move(value));
	}

	template <typename ForwardIterator>
	void
	replace(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		impl.rangeReplace(pos, first, last);
	}

	void
	replace(const_iterator pos, std::initializer_list<T> il) {
		replace(pos, il.begin(), il.end());
	}

	template <typename ForwardIterator>
	void
	replace(ForwardIterator first, ForwardIterator last) {
		*this = Vector<T, Allocator>(first, last);
	}

	void
	replace(std::initializer_list<T> il) {
		*this = Vector<T, Allocator>(il.begin(), il.end());
	}

	void
	reserve(const int capacity) {
		impl.reserve(capacity);
	}

	void
	resize(const int size, const T& paddingValue = T()) {
		const int newSize = size;
		const int currentSize = this->size();
		if (newSize < 0)
			throw prism::BadSizeException(size);

		reserve(newSize);

		if (newSize > currentSize) impl.fillAppend(newSize - currentSize, paddingValue);
		else if (newSize < currentSize) impl.rangeRemoveAtEnd(cbegin() + newSize);
	}

	void
	squeeze() {
		impl.reallocate(size());
	}

	const bool
	contains(const T& value) noexcept {
		return indexOf(value) == IndexNotFound ? false : true;
	}

	const int
	count(const T& value) noexcept {
		return prism::count(cbegin(), cend(), value);
	}

	const bool
	startsWith(const T& value) noexcept {
		if (empty()) return false;
		return *cbegin() == value;
	}

	const bool
	endsWith(const T& value) noexcept {
		if (empty()) return false;
		return *--end() == value;
	}

	const int
	indexOf(const T& value, const int from=0) noexcept {
		if (empty()) return IndexNotFound;
		return impl.findFirstIndexOf(from, value);
	}

	const int
	lastIndexOf(const T& value, const int from=-1) noexcept {
		if (empty()) return IndexNotFound;
		return impl.findLastIndexOf(from, value);
	}

	void
	swap(Vector<T, Allocator>& other) noexcept {
		impl.swap(other.impl);
	}

	iterator
	begin() noexcept {
		return iterator(impl.storage.start);
	}

	const_iterator
	begin() const noexcept {
		return const_iterator(impl.storage.start);
	}

	iterator
	end() noexcept {
		return iterator(impl.storage.end);
	}

	const_iterator
	end() const noexcept {
		return const_iterator(impl.storage.end);
	}

	const_iterator
	cbegin() const noexcept {
		return const_iterator(impl.storage.start);
	}

	const_iterator
	cend() const noexcept {
		return const_iterator(impl.storage.end);
	}

	reverse_iterator
	rbegin() noexcept {
		return reverse_iterator(impl.storage.end);
	}

	const_reverse_iterator
	rbegin() const noexcept {
		return const_reverse_iterator(impl.storage.end);
	}

	reverse_iterator
	rend() noexcept {
		return reverse_iterator(impl.storage.start);
	}

	const_reverse_iterator
	rend() const noexcept {
		return const_reverse_iterator(impl.storage.start);
	}

	const_reverse_iterator
	crbegin() const noexcept {
		return const_reverse_iterator(impl.storage.end);
	}

	const_reverse_iterator
	crend() const noexcept {
		return const_reverse_iterator(impl.storage.start);
	}

	T&
	operator[](const int index) {
		return *(begin() + index);
	}

	const T&
	operator[](const int index) const {
		return *(begin() + index);
	}

	Vector<T, Allocator>&
	operator<<(const T& value) {
		return *this += value;
	}

	Vector<T, Allocator>&
	operator+=(const T& value) {
		impl.insertAtEnd(value);
		return *this;
	}

	Vector<T, Allocator>
	operator+(const Vector<T, Allocator>& rhs) {
		Vector<T, Allocator> copy(*this);
		return copy << rhs;
	}

	Vector<T, Allocator>&
	operator+=(const Vector<T, Allocator>& rhs) {
		return *this << rhs;
	}

	Vector<T, Allocator>&
	operator<<(const Vector<T, Allocator>& rhs) {
		impl.rangeAppend(rhs.cbegin(), rhs.cend());
		return *this;
	}
};

template <typename T, typename Allocator>
const bool
operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return prism::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T, typename Allocator>
const bool
operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	return !(lhs == rhs);
}

template <typename T, typename Allocator>
const bool
operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	return prism::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

template <typename T, typename Allocator>
const bool
operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

template <typename T, typename Allocator>
const bool
operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	return !(lhs < rhs) && (lhs != rhs);
}

template <typename T, typename Allocator>
const bool
operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
	return !(lhs < rhs);
}

template <typename T, typename Allocator>
void
swap(Vector<T, Allocator>& a, Vector<T, Allocator>& b)
noexcept {
	a.swap(b);
}

template <typename T, typename Allocator>
std::ostream&
operator<<(std::ostream& out, const Vector<T, Allocator>& v) {
	out << "Vector [" << &v << "] size=" << v.size() << " capacity=" << v.capacity();
	for (int i=0; i<v.size(); i++)
		out << "\n[" << i << "] " << v[i];
	return out;
}

PRISM_END_NAMESPACE

#include <prism/h/priv/Vector_priv.h>

#endif /* PRISM_VECTOR_H_ */















