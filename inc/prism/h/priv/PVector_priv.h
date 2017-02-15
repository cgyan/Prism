/*
 * PVector_priv.h
 * v0.*
 *
 *  Created on: 26 Jan 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_PVECTOR_PRIV_H_
#define PRISM_PVECTOR_PRIV_H_

PRISM_BEGIN_NAMESPACE

template <typename T, typename Allocator>
class PVectorStorage : public Allocator {
private:
	using alloc_traits = prism::AllocatorTraits<Allocator>;
private:
	PVectorStorage() 										= delete;
	PVectorStorage(const PVectorStorage& rhs) 				= delete;
	PVectorStorage(PVectorStorage&& rhs) 					= delete;
	PVectorStorage& operator=(const PVectorStorage& rhs) 	= delete;
	PVectorStorage& operator=(PVectorStorage&& rhs) 		= delete;
public:
	using pointer = typename alloc_traits::pointer;
	pointer start;
	pointer end;
	pointer finish;
public:
	~PVectorStorage() {
		alloc_traits::deallocate(*this, start);
		start = end = finish = nullptr;
	}

	PVectorStorage(const int capacity)
	: start(alloc_traits::allocate(*this, capacity)),
	  end(start),
	  finish(start + capacity)
	{}

	void
	swap(PVectorStorage& otherStorage) {
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
class PVectorImpl {
private:
	using alloc_traits = prism::AllocatorTraits<Allocator>;
	using iterator = prism::SequenceIterator<T, false>;
	using const_iterator = prism::SequenceIterator<T, true>;
	using ImplPointer = PVectorImpl<T, Allocator>*;
	using Storage = PVectorStorage<T, Allocator>;

public:
	Storage storage;
	enum { IndexNotFound = -1 };

public:
	PVectorImpl()
	: storage{0}
	{}

	~PVectorImpl() {
		destroyRange(storage.start, storage.end);
	}

	PVectorImpl(const int size, const T& value)
	: storage{size}
	{
		fillInitialize(size, value);
	}

	template <typename ForwardIterator>
	PVectorImpl(ForwardIterator first, ForwardIterator last)
	: storage(last - first)
	{
		rangeInitialize(first, last);
	}

	void
	reallocate(int newCapacity) {
		Storage newStorage(newCapacity);
		prism::uninitialized_move(storage.start, storage.end, newStorage.start);
		newStorage.end = newStorage.start + storage.size();
		destroyRange(storage.start, storage.end);
		storage.swap(newStorage);
	}

	T&
	replaceValueAtIndex(const int index, const T& value) {
		// todo: value should be copy constructed by the allocator
		validateIndex(index);
		return storage.start[index] = value;
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
	findFirstIndexOf(const int from, const T& value) {
		T* it = prism::find(storage.start + from, storage.end, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	const int
	findLastIndexOf(const int from, const T& value) {
		T* endIt = from == -1 ? storage.end : storage.start + from;
		T* it = prism::find_last(storage.start, endIt, value);
		return (it == storage.end)
				? IndexNotFound
				: prism::distance(storage.start, it);
	}

	T&
	valueAtIndex(const int index) {
		validateIndex(index);
		return storage.start[index];
	}

	template <typename ...Args>
	iterator
	insertAtEnd(Args&& ...args) {
		const int numNewElements = 1;
		ensureSufficientStorage(numNewElements);
		constructElement(storage.size(), std::forward<Args>(args)...);
		increaseSizeBy(1);
		return iterator{storage.end - 1};
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

	template <typename ...Args>
	iterator
	insert(const int insertIndex, Args&& ...args) {
		const int numNewElements = 1;
		validateInsertionPoint(insertIndex);
		ensureSufficientStorage(numNewElements);
		moveElementsFromIndexUpNumSpaces(insertIndex, numNewElements);
		constructElement(insertIndex, std::forward<Args>(args)...);
		increaseSizeBy(1);
		return iterator(storage.start + insertIndex);
	}

	template <typename ForwardIterator>
	iterator
	rangeAppend(ForwardIterator first, ForwardIterator last) {
		const int numNewElements = last - first;
		ensureSufficientStorage(numNewElements);
		return rangeConstructElements(storage.size(), first, last);
	}

	template <typename ForwardIterator>
	iterator
	rangeInsert(const int insertIndex, ForwardIterator first, ForwardIterator last) {
		const int numNewElements = last - first;
		validateInsertionPoint(insertIndex);
		ensureSufficientStorage(numNewElements);
		moveElementsFromIndexUpNumSpaces(insertIndex, numNewElements);
		return rangeConstructElements(insertIndex, first, last);
	}

	iterator
	removeAtEnd() {
		if (storage.end == storage.start)
			throw prism::OutOfBoundsException(-1);
		alloc_traits::destroy(storage, storage.end - 1);
		decreaseSizeBy(1);
		return iterator{storage.end};
	}

	iterator
	remove(const int index) {
		validateIndex(index);
		alloc_traits::destroy(storage, storage.start + index);
		const int numSpaces = 1;
		moveElementsFromIndexDownNumSpaces(index + 1, numSpaces);
		decreaseSizeBy(1);
		return iterator(storage.start + index);
	}

	iterator
	rangeRemoveAtEnd(const int fromIndex) {
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
		destroyRange(storage.start + firstIndex, storage.start + lastIndex);
		moveElementsFromIndexDownNumSpaces(lastIndex, numElementsToRemove);
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

	const int
	index(const_iterator pos) {
		return prism::distance(const_iterator(storage.start), pos);
	}

	template <typename ForwardIterator>
	iterator
	rangeConstructElements(const int insertIndex, ForwardIterator first, ForwardIterator last) {
		int i = 0;
		while (first != last) {
			constructElement(insertIndex + i++, *first++);
			increaseSizeBy(1);
		}
		return iterator(storage.start + insertIndex);
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

	template <typename ...Args>
	void
	constructElement(int insertIndex, Args... value) {
		alloc_traits::construct(storage, storage.start + insertIndex, std::forward<Args>(value)...);
	}

	void
	fillInitialize(const int size, const T& value) {
		for(int i=0; i<size; i++) {
			constructElement(i, value);
			increaseSizeBy(1);
		}
	}

	template <typename ForwardIterator>
	void
	rangeInitialize(ForwardIterator first, ForwardIterator last) {
		int index = 0;
		while (first != last) {
			constructElement(index++, *first++);
			increaseSizeBy(1);
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
			reserve(newCapacity);
		}
	}

	void
	validateIndex(const int index) {
		if (index < 0 || index >= storage.size())
			throw prism::OutOfBoundsException(index);
	}

	void
	validateInsertionPoint(const int index) {
		if (index < 0 || index > storage.size())
			throw prism::OutOfBoundsException(index);
	}
};

PRISM_END_NAMESPACE

#endif /* PRISM_PVECTOR_PRIV_H_ */














