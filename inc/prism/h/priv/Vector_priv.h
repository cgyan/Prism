/*
 * Vector_priv.h
 * v0.*
 *
 *  Created on: 26 Jan 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_PVECTOR_PRIV_H_
#define PRISM_PVECTOR_PRIV_H_

#include <iterator>

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
		using prism::swap;
		swap(start, otherStorage.start);
		swap(end, otherStorage.end);
		swap(finish, otherStorage.finish);
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
	using alloc_traits = prism::AllocatorTraits<Allocator>;
	using iterator = prism::SequenceIterator<T, false>;
	using const_iterator = prism::SequenceIterator<T, true>;
	using ImplPointer = VectorImpl<T, Allocator>*;
	using Storage = VectorStorage<T, Allocator>;
private:
	VectorImpl(const VectorImpl& rhs) = delete;
	VectorImpl& operator=(const VectorImpl& rhs) = delete;
	VectorImpl& operator=(VectorImpl&& rhs) = delete;
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
	reallocate(int newCapacity) {
		Storage newStorage(newCapacity);
		newStorage.end = prism::uninitialized_move(storage.start, storage.end, newStorage.start);
		destroyRange(storage.start, storage.end);
		storage.swap(newStorage);
	}

	template <typename ElementType>
	void
	replace(const int index, ElementType&& value) {
		validateIndex(index);
		storage.start[index] = std::forward<ElementType>(value);
	}

	template <typename ForwardIterator>
	void
	rangeReplace(const int index, ForwardIterator first, ForwardIterator last) {
		validateIndex(index);
		for (int i=index; first != last && i != storage.size(); i++, first++) {
			storage.start[i] = *first;
		}
	}

	void
	resizeGreater(const int newSize, const T& paddingValue) {
		prism::uninitialized_fill(
				storage.start + storage.size(), storage.start + newSize, paddingValue);
		const int numNewElements = newSize - storage.size();
		increaseSizeBy(numNewElements);
	}

	void
	resizeSmaller(const int newSize) {
		destroyRange(storage.start + newSize, storage.end);
		const int numRemovedElements = storage.size() - newSize;
		decreaseSizeBy(numRemovedElements);
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
		T* it = prism::find(storage.start + from, storage.end, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	const int
	findLastIndexOf(const int from, const T& value) const {
		T* endIt = from == -1 ? storage.end : storage.start + from;
		T* it = prism::find_last(storage.start, endIt, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	T&
	valueAtIndex(const int index) const {
		validateIndex(index);
		return storage.start[index];
	}

	template <typename ElementType>
	iterator
	insertAtEnd(ElementType&& value) {
		const int numNewElements = 1;
		ensureSufficientStorage(numNewElements);
		constructElement(storage.size(), std::forward<ElementType>(value));
		increaseSizeBy(1);
		return iterator{storage.end - 1};
	}

	template <typename ElementType>
	iterator
	insert(const int insertIndex, ElementType&& value) {
		const int numNewElements = 1;
		validateInsertionPoint(insertIndex);
		ensureSufficientStorage(numNewElements);
		moveElementsFromIndexUpNumSpaces(insertIndex, numNewElements);
		constructElement(insertIndex, std::forward<ElementType>(value));
		increaseSizeBy(1);
		return iterator(storage.start + insertIndex);
	}

	iterator
	fillAppend(const int count, const T& value) {
		ensureSufficientStorage(count);
		return fillConstruct(storage.size(), count, value);
	}

	iterator
	fillConstruct(const int insertIndex, const int count, const T& value) {
		for (int i=0; i<count; i++) {
			constructElement(insertIndex + i, value);
			increaseSizeBy(1);
		}
		return iterator(storage.start + insertIndex);
	}

	iterator
	fillInsert(const int insertIndex, const int count, const T& value) {
		validateInsertionPoint(insertIndex);
		ensureSufficientStorage(count);
		moveElementsFromIndexUpNumSpaces(insertIndex, count);
		return fillConstruct(insertIndex, count, value);
	}

	template <typename ForwardIterator>
	iterator
	rangeAppend(ForwardIterator first, ForwardIterator last) {
		const int numNewElements = prism::distance(first, last);
		ensureSufficientStorage(numNewElements);
		return rangeConstructElements(storage.size(), first, last);
	}

	template <typename ForwardIterator>
	iterator
	rangeInsert(const int insertIndex, ForwardIterator first, ForwardIterator last) {
		const int numNewElements = prism::distance(first, last);
		validateInsertionPoint(insertIndex);
		ensureSufficientStorage(numNewElements);
		moveElementsFromIndexUpNumSpaces(insertIndex, numNewElements);
		return rangeConstructElements(insertIndex, first, last);
	}

	template <typename ForwardIterator>
	iterator
	rangeConstructElements(const int insertIndex, ForwardIterator first, ForwardIterator last) {
		int current = insertIndex;
		const int numNewElements = prism::distance(first, last);
		try {
			while (first != last)
				constructElement(current++, *first++);
		}
		catch(...) {
			destroyRange(storage.start + insertIndex, storage.start + current);
			throw;
		}
		increaseSizeBy(numNewElements);
		return iterator(storage.start + insertIndex);
	}

	template <typename ...Args>
	void
	constructElement(int insertIndex, Args... args) {
		alloc_traits::construct(storage, storage.start + insertIndex, std::forward<Args>(args)...);
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
	remove(const int index) {
		validateIndex(index);
		T* from = storage.start + index + 1;
		T* to = storage.end;
		T* dest = from - 1;
		prism::move(from, to, dest);

		decreaseSizeBy(1);
		alloc_traits::destroy(storage, storage.end);
		return iterator{storage.start + index};
	}

	iterator
	rangeRemoveAtEnd(const int fromIndex) noexcept {
		validateIndex(fromIndex);
		const int numElementsToRemove = storage.size() - fromIndex;
		destroyRange(storage.start + fromIndex, storage.end);
		decreaseSizeBy(numElementsToRemove);
		return iterator{storage.end};
	}

	iterator
	rangeRemove(const int firstIndex, const int lastIndex) {
		validateIndex(firstIndex);
		validateIndex(lastIndex);
		const int numElementsToRemove = lastIndex - firstIndex;
		T* from = storage.start + firstIndex + numElementsToRemove;
		T* to = storage.end;
		T* dest = storage.start + firstIndex;
		prism::move(from, to, dest);

		from = storage.start + firstIndex + (storage.size() - numElementsToRemove);
		to = storage.end;
		destroyRange(from, to);
		decreaseSizeBy(numElementsToRemove);
		return iterator{storage.start + firstIndex};
	}

	void
	removeAllOccurrencesOfValue(const T& value) {
		storage.end = prism::remove(storage.start, storage.end, value);
	}

	template <typename UnaryPredicate>
	void
	removeElementsForWhichPredIsTrue(UnaryPredicate pred) {
		storage.end = prism::remove_if(storage.start, storage.end, pred);
	}

	void
	clear()
	noexcept {
		const int numElements = storage.size();
		destroyRange(storage.start, storage.end);
		decreaseSizeBy(numElements);
	}

	const int
	index(const_iterator pos) const {
		return prism::distance(const_iterator(storage.start), pos);
	}

	void
	moveElementsFromIndexUpNumSpaces(const int insertIndex, const int count) {
		T* first = storage.start + insertIndex;
		T* last = storage.end;
		T* otherLast = storage.end + count;
		prism::uninitialized_move_backwards(first, last, otherLast);
	}

	void
	moveElementsFromIndexDownNumSpaces(const int index, const int count) {
		prism::uninitialized_move(storage.start + index,
									storage.end,
									storage.start + index - count);
	}

	void
	destroyRange(T* first, T* last) {
		while (first != last)
			alloc_traits::destroy(storage, first++);
	}

	void
	fillInitialize(const int size, const T& value) {
		int i=0;
		try {
			for(; i<size; i++) {
				constructElement(i, value);
				increaseSizeBy(1);
			}
		}
		catch(...) {
			destroyRange(storage.start, storage.start + i);
			storage.start = storage.end = storage.finish = nullptr;
			throw;
		}
	}

	template <typename ForwardIterator>
	void
	rangeInitialize(ForwardIterator first, ForwardIterator last) {
		int index = 0;
		try {
			for (; first != last; first++, index++) {
				constructElement(index, *first);
				increaseSizeBy(1);
			}
		}
		catch(...) {
			destroyRange(storage.start, storage.start + index);
			storage.start = storage.end = storage.finish = nullptr;
			throw;
		}
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
	validateIndex(const int index) const {
		if (index < 0 || index >= storage.size())
			throw prism::OutOfBoundsException(index);
	}

	void
	validateInsertionPoint(const int index) const {
		if (index < 0 || index > storage.size())
			throw prism::OutOfBoundsException(index);
	}
};

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_PRIV_H_ */














