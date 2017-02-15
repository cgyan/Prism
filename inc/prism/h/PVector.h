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
#include <prism/BadSizeException>
#include <prism/Allocator>
#include <prism/Iterator>
#include <vector>
#include <list>
#include <ostream>
#include <memory>

PRISM_BEGIN_NAMESPACE

template <typename T, typename Allocator>
class PVectorImpl;

template <typename T, typename Allocator = prism::Allocator<T>>
class PVector {
private:
	using alloc_traits 				= prism::AllocatorTraits<Allocator>;
	using Impl						= prism::PVectorImpl<T, Allocator>;
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
	std::shared_ptr<Impl> impl;
public:
	enum { IndexNotFound = Impl::IndexNotFound };
public:
	PVector()
	: impl{new Impl()}
	{}

	~PVector()
	{}

	PVector(const int size, const T& value=T())
	: impl{new Impl(size, value)}
	{}

	template <typename ForwardIterator>
	PVector(ForwardIterator first, ForwardIterator last)
	: impl{new Impl(first, last)}
	{}

	PVector(std::initializer_list<T> il)
	: impl{new Impl(il.begin(), il.end())}
	{}

	PVector(const PVector& rhs)
	: impl{new Impl(rhs.cbegin(), rhs.cend())}
	{}

	PVector(PVector<T, Allocator>&& rhs)
	: impl{new Impl()}
	{
		impl.swap(rhs.impl);
	}

	PVector<T, Allocator>&
	operator=(const PVector<T, Allocator>& rhs) {
		PVector rhsCopy(rhs);
		this->swap(rhsCopy);
		return *this;
	}

	PVector<T, Allocator>&
	operator=(PVector<T, Allocator>&& rhs) {
		impl.swap(rhs.impl);
		return *this;
	}

	allocator_type
	allocator() {
		return allocator_type();
	}

	void
	append(const T& value) {
		impl->insertAtEnd(value);
	}

	void
	append(T&& value) {
		impl->insertAtEnd(prism::move(value));
	}

	void
	prepend(const T& value) {
		impl->insert(0, value);
	}

	void
	prepend(T&& value) {
		impl->insert(0, prism::move(value));
	}

	void
	insert(const int index, const T& value) {
		insert(cbegin() + index, value);
	}

	void
	insert(const int index, T&& value) {
		insert(cbegin() + index, prism::move(value));
	}

	void
	insert(const int index, const int count, const T& value) {
		insert(cbegin() + index, count, value);
	}

	iterator
	insert(const_iterator pos, const T& value) {
		if (pos == cend()) return impl->insertAtEnd(value);
		else return impl->insert(impl->index(pos), value);
	}

	iterator
	insert(const_iterator pos, T&& value) {
		if (pos == cend()) return impl->insertAtEnd(prism::move(value));
		else return impl->insert(impl->index(pos), prism::move(value));
	}

	iterator
	insert(const_iterator pos, const int count, const T& value) {
		if (pos == cend()) return impl->fillAppend(count, value);
		else return impl->fillInsert(impl->index(pos), count, value);
	}

	iterator
	insert(const_iterator pos, std::initializer_list<T> il) {
		return insert(pos, il.begin(), il.end());
	}

	template <typename ForwardIterator>
	iterator
	insert(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		if (pos == cend()) return impl->rangeAppend(first, last);
		else return impl->rangeInsert(impl->index(pos), first, last);
	}

	const int
	capacity() const {
		return impl->storage.capacity();
	}

	const int
	size() const {
		return impl->storage.size();
	}

	const bool
	empty() const {
		return size() == 0;
	}

	void
	clear() {
		resize(0);
	}

	void
	remove(const int index) {
		remove(cbegin() + index);
	}

	iterator
	remove(const_iterator pos) {
		if (pos == --cend()) return impl->removeAtEnd();
		else return impl->remove(impl->index(pos));
	}

	void
	remove(const int index, const int count) {
		const_iterator first = cbegin() + index;
		const_iterator last = first + count;
		remove(first, last);
	}

	iterator
	remove(const_iterator first, const_iterator last) {
		if (last == cend()) return impl->rangeRemoveAtEnd(impl->index(first));
		else return impl->rangeRemove(impl->index(first), impl->index(last));
	}

	void
	removeFirst() {
		remove(cbegin());
	}

	void
	removeLast() {
		remove(--cend());
	}

	void
	removeAll(const T& value) {
		impl->removeAllOccurrencesOfValue(value);
	}

	template <typename UnaryPredicate>
	void
	removeIf(UnaryPredicate pred) {
		impl->removeElementsForWhichPredIsTrue(pred);
	}

	T&
	at(const int index) {
		return impl->valueAtIndex(index);
	}

	const T&
	at(const int index) const {
		return impl->valueAtIndex(index);
	}

	T&
	first() {
		return impl->valueAtIndex(0);
	}

	const T&
	first() const {
		return impl->valueAtIndex(0);
	}

	T&
	front() {
		return impl->valueAtIndex(0);
	}

	const T&
	front() const {
		return impl->valueAtIndex(0);
	}

	T&
	back() {
		return impl->valueAtIndex(size() - 1);
	}

	const T&
	back() const {
		return impl->valueAtIndex(size() - 1);
	}

	T&
	last() {
		return impl->valueAtIndex(size() - 1);
	}

	const T&
	last() const {
		return impl->valueAtIndex(size() - 1);
	}

	PVector<T, Allocator>
	mid(const int index, const int count=-1) const {
		const_iterator first = cbegin() + index;
		const_iterator last = (count == -1) ? cend() : first + count;
		return PVector<T, Allocator>(first, last);
	}

	const T*
	cdata() const {
		return impl->storage.start;
	}

	T *
	data() {
		return impl->storage.start;
	}

	const T*
	data() const {
		return impl->storage.start;
	}

	void
	fill(const T& value) {
		PVector<T, Allocator> tmp(size(), value);
		swap(tmp);
	}

	void
	replace(const int index, const T& value) {
		impl->replaceValueAtIndex(index, value);
	}

	void
	reserve(const int capacity) {
		impl->reserve(capacity);
	}

	void
	resize(const int size, const T& paddingValue = T()) {
		const int newSize = size;
		if (newSize < 0)
			throw prism::BadSizeException(size);

		reserve(newSize);

		if (newSize > this->size()) impl->resizeGreater(newSize, paddingValue);
		else impl->resizeSmaller(newSize);
	}

	void
	squeeze() {
		impl->reallocate(size());
	}

	const bool
	contains(const T& value) {
		return indexOf(value) == IndexNotFound ? false : true;
	}

	const int
	count(const T& value) {
		return prism::count(cbegin(), cend(), value);
	}

	const bool
	startsWith(const T& value) {
		if (empty()) return false;
		return *cbegin() == value;
	}

	const bool
	endsWith(const T& value) {
		if (empty()) return false;
		return *--end() == value;
	}

	const int
	indexOf(const T& value, const int from=0) {
		if (empty()) return IndexNotFound;
		return impl->findFirstIndexOf(from, value);
	}

	const int
	lastIndexOf(const T& value, const int from=-1) {
		if (empty()) return IndexNotFound;
		return impl->findLastIndexOf(from, value);
	}

	void
	swap(PVector<T, Allocator>& other) {
		impl.swap(other.impl);
	}

	std::list<T>
	toStdList() {
		return std::list<T>(impl->storage.start, impl->storage.end);
	}

	std::vector<T>
	toStdVector() {
		return std::vector<T>(impl->storage.start, impl->storage.end);
	}

	iterator
	begin() {
		return iterator(impl->storage.start);
	}

	const_iterator
	begin() const {
		return const_iterator(impl->storage.start);
	}

	iterator
	end() {
		return iterator(impl->storage.end);
	}

	const_iterator
	end() const {
		return const_iterator(impl->storage.end);
	}

	const_iterator
	cbegin() const {
		return const_iterator(impl->storage.start);
	}

	const_iterator
	cend() const {
		return const_iterator(impl->storage.end);
	}

	reverse_iterator
	rbegin() {
		return reverse_iterator(impl->storage.end);
	}

	const_reverse_iterator
	rbegin() const {
		return const_reverse_iterator(impl->storage.end);
	}

	reverse_iterator
	rend() {
		return reverse_iterator(impl->storage.start);
	}

	const_reverse_iterator
	rend() const {
		return const_reverse_iterator(impl->storage.start);
	}

	const_reverse_iterator
	crbegin() const {
		return const_reverse_iterator(impl->storage.end);
	}

	const_reverse_iterator
	crend() const {
		return const_reverse_iterator(impl->storage.start);
	}

	T&
	operator[](const int index) {
		return *(begin() + index);
	}

	const T&
	operator[](const int index) const {
		return *(begin() + index);
	}

	PVector<T, Allocator>&
	operator<<(const T& value) {
		return *this += value;
	}

	PVector<T, Allocator>&
	operator+=(const T& value) {
		impl->insertAtEnd(value);
		return *this;
	}

	PVector<T, Allocator>
	operator+(const PVector<T, Allocator>& rhs) {
		PVector<T, Allocator> copy(*this);
		return copy << rhs;
	}

	PVector<T, Allocator>&
	operator+=(const PVector<T, Allocator>& rhs) {
		return *this << rhs;
	}

	PVector<T, Allocator>&
	operator<<(const PVector<T, Allocator>& rhs) {
		impl->rangeAppend(rhs.cbegin(), rhs.cend());
		return *this;
	}
};

template <typename T, typename Allocator>
const bool
operator==(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return prism::equal(lhs.cbegin(),
						lhs.cend(),
						rhs.cbegin());
}

template <typename T, typename Allocator>
const bool
operator!=(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	return !(lhs == rhs);
}

template <typename T, typename Allocator>
const bool
operator<(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	return prism::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

template <typename T, typename Allocator>
const bool
operator<=(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

template <typename T, typename Allocator>
const bool
operator>(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	return !(lhs < rhs) && (lhs != rhs);
}

template <typename T, typename Allocator>
const bool
operator>=(const PVector<T, Allocator>& lhs, const PVector<T, Allocator>& rhs) {
	return !(lhs < rhs);
}

template <typename T, typename Allocator>
void
swap(PVector<T, Allocator>& a, PVector<T, Allocator>& b) {
	a.swap(b);
}

template <typename T, typename Allocator>
std::ostream&
operator<<(std::ostream& out, const PVector<T, Allocator>& v) {
	out << "PVector [" << &v << "] size=" << v.size() << " capacity=" << v.capacity();
	for (int i=0; i<v.size(); i++)
		out << "\n[" << i << "] " << v[i];
	return out;
}

PRISM_END_NAMESPACE

#include <prism/h/priv/PVector_priv.h>

#endif /* PRISM_PVECTOR_H_ */















