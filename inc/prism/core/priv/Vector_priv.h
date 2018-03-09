/*
 * Vector_priv.h
 * v0.*
 *
 *  Created on: 26 Jan 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_PVECTOR_PRIV_H_
#define PRISM_PVECTOR_PRIV_H_


PRISM_BEGIN_NAMESPACE

template <typename T, typename Allocator>
class VectorStorage : public Allocator {
private:
	using alloc_traits = prism::AllocatorTraits<Allocator>;
private:
	VectorStorage() 									= delete;
	VectorStorage(const VectorStorage& rhs) 			= delete;
	VectorStorage(VectorStorage&& rhs) 					= delete;
	VectorStorage& operator=(const VectorStorage& rhs) 	= delete;
	VectorStorage& operator=(VectorStorage&& rhs) 		= delete;
public:
	using pointer = typename alloc_traits::pointer;
	pointer start;
	pointer end;
	pointer finish;
public:
	~VectorStorage() {
		alloc_traits::deallocate(*this, start);
		start = end = finish = nullptr;
	}

	VectorStorage(const int capacity)
	: start(alloc_traits::allocate(*this, capacity)),
	  end(start),
	  finish(start + capacity)
	{}

	void
	swap(VectorStorage& otherStorage) {
		prism::swap(start, otherStorage.start);
		prism::swap(end, otherStorage.end);
		prism::swap(finish, otherStorage.finish);
	}

	const int
	size() const {
		return end - start;
	}

	const int
	capacity() const {
		return finish - start;
	}
};

template <typename T, typename Allocator>
class VectorImpl {
private:
	using alloc_traits 		= prism::AllocatorTraits<Allocator>;
	using iterator 			= prism::SequenceIterator<T, false>;
	using const_iterator 	= prism::SequenceIterator<T, true>;
	using ImplPointer 		= VectorImpl<T, Allocator>*;
	using Storage 			= VectorStorage<T, Allocator>;
	using pointer			= typename alloc_traits::pointer;
private:
	VectorImpl(const VectorImpl& rhs) 				= delete;
	VectorImpl& operator=(const VectorImpl& rhs) 	= delete;
	VectorImpl& operator=(VectorImpl&& rhs) 		= delete;
public:
	Storage storage;
	enum { IndexNotFound = -1 };
public:
	VectorImpl()
	: storage{0}
	{}

	VectorImpl(VectorImpl&& rhs)
	: storage{0}
	{
		storage.swap(rhs.storage);
	}

	~VectorImpl() {
		destroyRange(storage.start, storage.end);
	}

	VectorImpl(const int size, const T& value)
	: storage{size}
	{
		fillInitialize(size, value);
	}

	template <typename ForwardIterator>
	VectorImpl(ForwardIterator first, ForwardIterator last)
	: storage(prism::distance(first, last))
	{
		rangeInitialize(first, last);
	}

	void
	swap(VectorImpl& otherImpl) {
		storage.swap(otherImpl.storage);
	}

	void
	fillInitialize(const int size, const T& value) {
		fillConstruct(storage.start, storage.start + size, value);
	}

	template <typename ForwardIterator>
	void
	rangeInitialize(ForwardIterator first, ForwardIterator last) {
		const int numElements = prism::distance(first, last);
		prism::uninitialized_copy_alloc(first, last, storage.start, storage);
		increaseSizeBy(numElements);
	}

	void
	reallocate(int newCapacity) {
		Storage newStorage(newCapacity);
		newStorage.end = prism::uninitialized_move(storage.start, storage.end, newStorage.start);
		destroyRange(storage.start, storage.end);
		storage.swap(newStorage);
	}

	template <typename ElementType>
	void
	replace(const_iterator pos, ElementType&& value) {
		const int offset = pos - cbegin();
		validatePos(pos);
		storage.start[offset] = std::forward<ElementType>(value);
	}

	template <typename ForwardIterator>
	void
	rangeReplace(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		const int offset = pos - cbegin();
		validatePos(pos);
		auto current = storage.start + offset;
		for (; first != last && current != storage.end; ++current, ++first) {
			*current = *first;
		}
	}

	void
	reserve(const int newCapacity) {
		if(newCapacity < 0)
			throw prism::BadSizeException(newCapacity);

		if (newCapacity > storage.capacity()) {
			reallocate(newCapacity);
		}
	}

	const int
	findFirstIndexOf(const int from, const T& value) const {
		pointer it = prism::find(storage.start + from, storage.end, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	const int
	findLastIndexOf(const int from, const T& value) const {
		pointer endIt = from == -1 ? storage.end : storage.start + from;
		pointer it = prism::find_last(storage.start, endIt, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	T&
	valueAtIndex(const int index) const {
		validatePos(cbegin() + index);
		return storage.start[index];
	}

	template <typename ElementType>
	iterator
	insertAtEnd(ElementType&& value) {
		const int numNewElements = 1;
		ensureSufficientStorage(numNewElements);
		constructElement(storage.end, std::forward<ElementType>(value));
		increaseSizeBy(1);
		return iterator{storage.end - 1};
	}

	template <typename ElementType>
	iterator
	insert(const_iterator pos, ElementType&& value) {
		const int offset = pos - cbegin();
		validateInsertionPoint(pos);
		const int numNewElements = 1;
		ensureSufficientStorage(numNewElements);
		prism::uninitialized_move_backwards(storage.start + offset, storage.end,
				storage.end + numNewElements);
		constructElement(storage.start + offset, std::forward<ElementType>(value));
		increaseSizeBy(1);
		return iterator(storage.start + offset);
	}

	iterator
	fillAppend(const int count, const T& value) {
		ensureSufficientStorage(count);
		return fillConstruct(storage.end, storage.end + count, value);
	}

	iterator
	fillConstruct(pointer first, pointer last, const T& value) {
		const int numElements = last - first;
		prism::uninitialized_fill_alloc(first, last, value, storage);
		increaseSizeBy(numElements);
		return iterator(first);
	}

	iterator
	fillInsert(const_iterator pos, const int count, const T& value) {
		const int offset = pos - cbegin();
		validateInsertionPoint(pos);
		ensureSufficientStorage(count);
		prism::uninitialized_move_backwards(storage.start + offset, storage.end,
				storage.end + count);
		auto from = storage.start + offset;
		return fillConstruct(from, from + count, value);
	}

	template <typename ForwardIterator>
	iterator
	rangeAppend(ForwardIterator first, ForwardIterator last) {
		const int numNewElements = prism::distance(first, last);
		ensureSufficientStorage(numNewElements);
		return rangeConstruct(storage.end, first, last);
	}

	template <typename ForwardIterator>
	iterator
	rangeInsert(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		const int offset = pos - cbegin();
		const int numNewElements = prism::distance(first, last);
		validateInsertionPoint(pos);
		ensureSufficientStorage(numNewElements);
		prism::uninitialized_move_backwards(storage.start + offset, storage.end,
				storage.end + numNewElements);
		return rangeConstruct(storage.start + offset, first, last);
	}

	template <typename ForwardIterator>
	iterator
	rangeConstruct(pointer pos, ForwardIterator first, ForwardIterator last) {
		prism::uninitialized_copy_alloc(first, last, pos, storage);
		const int numElements = prism::distance(first, last);
		increaseSizeBy(numElements);
		return iterator(pos);
	}

	template <typename ...Args>
	void
	constructElement(pointer pos, Args... args) {
		alloc_traits::construct(storage, pos, std::forward<Args>(args)...);
	}

	iterator
	removeAtEnd() noexcept {
		if (storage.end != storage.start) {
			decreaseSizeBy(1);
			alloc_traits::destroy(storage, storage.end);
		}
		return iterator{storage.end};
	}

	iterator
	remove(const_iterator pos) {
		const int offset = pos - cbegin();
		validatePos(pos);
		auto first = storage.start + offset + 1;
		auto otherFirst = storage.start + offset;
		prism::move(first, storage.end, otherFirst);

		decreaseSizeBy(1);
		alloc_traits::destroy(storage, storage.end);
		return iterator{storage.start + offset};
	}

	iterator
	rangeRemoveAtEnd(const_iterator from) noexcept {
		const int offset = from - cbegin();
		validatePos(from);
		const int numElementsToRemove = cend() - from;
		destroyRange(storage.start + offset, storage.end);
		decreaseSizeBy(numElementsToRemove);
		return iterator{storage.end};
	}

	iterator
	rangeRemove(const_iterator first, const_iterator last) {
		const int firstOffset = first - cbegin();
		const int lastOffset = last - cbegin();
		validatePos(first);
		validatePos(last);
		prism::uninitialized_move(storage.start + lastOffset, storage.end,
				storage.start + firstOffset);

		destroyRange(storage.start + lastOffset, storage.end);
		decreaseSizeBy(last - first);
		return iterator{storage.start + firstOffset};
	}

	void
	removeAllOccurrencesOfValue(const T& value) {
		pointer it = prism::remove(storage.start, storage.end, value);
		destroyRange(it, storage.end);
		storage.end = it;
	}

	template <typename UnaryPredicate>
	void
	removeElementsForWhichPredIsTrue(UnaryPredicate pred) {
		pointer it = prism::remove_if(storage.start, storage.end, pred);
		destroyRange(it, storage.end);
		storage.end = it;
	}

	void
	clear()
	noexcept {
		destroyRange(storage.start, storage.end);
		decreaseSizeBy(storage.size());
	}

	void
	destroyRange(iterator first, iterator last) {
		while (first != last)
			alloc_traits::destroy(storage, &*first++);
	}

	void
	increaseSizeBy(const int amount) {
		storage.end += amount;
	}

	void
	decreaseSizeBy(const int amount) {
		storage.end -= amount;
	}

	void
	ensureSufficientStorage(const int numNewElements) {
		const int totalElements = storage.size() + numNewElements;
		const bool needsReallocation = totalElements > storage.capacity();
		if (needsReallocation) {
			const int newCapacity = storage.size() + prism::max(storage.size(), numNewElements);
			reallocate(newCapacity);
		}
	}

	void
	validatePos(const_iterator pos) const {
		if (pos < cbegin() || pos >= cend())
			throw prism::OutOfBoundsException(pos - cbegin());
	}

	void
	validateInsertionPoint(const_iterator pos) const {
		if (pos < cbegin()|| pos > cend())
			throw prism::OutOfBoundsException(pos - cbegin());
	}

	const_iterator
	cbegin() const {
		return storage.start;
	}

	const_iterator
	cend() const {
		return storage.end;
	}
};

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_PRIV_H_ */
