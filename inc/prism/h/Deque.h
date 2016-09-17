/*
 * Deque.h
 * v1
 *
 *  Created on: Aug 23, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_DEQUE_H_
#define PRISM_DEQUE_H_

#include <prism/SharedData>
#include <prism/SharedDataPointer>
#include <prism/utilities> // for prism::conditional
#include <prism/algorithms>
#include <prism/OutOfBoundsException>
#include <prism/List>
#include <prism/String> // temp for debugging
#include <prism/memory>
#include <prism/Allocator>
#include <ostream>
#include <cstddef> // for std::ptrdiff_t
#include <initializer_list>
#include <deque>
using namespace std;

namespace prism {
namespace aux {
static const int prism_deque_bucket_size = 8;
//================================================================================
// DequeIterator
//================================================================================
// \cond DO_NOT_DOCUMENT
template <class T, bool isConst=true>
class DequeIterator {
public:
	typedef DequeIterator<T, false>		iterator;
	typedef DequeIterator<T, true>		const_iterator;
	typedef T							value_type;
	typedef std::ptrdiff_t 				difference_type;
	typedef random_access_iterator_tag 	iterator_category;
	typedef typename prism::conditional_type<isConst, const T*, T*>::type pointer;
	typedef typename prism::conditional_type<isConst, const T&, T&>::type reference;
	typedef typename prism::conditional_type<isConst, const_iterator, iterator>::type Self;
public:
	T** buckets; // (*buckets) is a pointer to one of the buckets i.e. T*
	T* current;
	T* start;
	T* end;
public:
	DequeIterator()
		: buckets(nullptr),
		  current(nullptr),
		  start(nullptr),
		  end(nullptr) {}

	DequeIterator(T** buckets, T* current)
		: buckets(buckets),
		  current(current),
		  start(*buckets),
		  end(start+prism_deque_bucket_size) {}

	DequeIterator(const iterator& copy)
		: buckets(copy.buckets),
		  current(copy.current),
		  start(copy.start),
		  end(copy.end) {}

	reference
	operator*()
	{ return *current; }

	pointer
	operator->()
	{ return current; }

	Self&
	operator+=(const int n)
	{
		int elementIndex = n + (current-start);
		if (elementIndex >= 0 && elementIndex < prism_deque_bucket_size)
			current += n;
		else {
			int bucketOffset = 0;
			if (elementIndex > 0) bucketOffset = elementIndex / prism_deque_bucket_size;
			else bucketOffset = -((-elementIndex-1) / prism_deque_bucket_size) - 1;

			buckets += bucketOffset;
			start = *buckets;
			end = start + prism_deque_bucket_size;
			current = start + (elementIndex - bucketOffset * prism_deque_bucket_size);
		}
		return *this;
	}

	Self
	operator+(const int n) {
		Self tmp = *this;
		return tmp += n;
	}

	Self&
	operator-=(const int n)
	{ return *this += -n; }

	Self
	operator-(const int n) {
		Self tmp = *this;
		return tmp -= n;
	}

	Self&
	operator++()
	{ return *this += 1; }

	Self
	operator++(int junk) {
		Self tmp(*this);
		*this = *this += 1;
		return tmp;
	}

	Self&
	operator--()
	{ return *this -= 1; }

	Self
	operator--(int junk) {
		Self tmp(*this);
		*this = *this -= 1;
		return tmp;
	}

	Self&
	operator=(const iterator& rhs) {
		if (*this != rhs) {
			buckets = rhs.buckets;
			current = rhs.current;
			start = rhs.start;
			end = rhs.end;
		}
		return *this;
	}
	//------------------------------------------------------------
	// related non members
	//------------------------------------------------------------
	friend const bool
	operator==(const Self& it1, const Self& it2) {
		return it1.buckets == it2.buckets &&
				it1.current == it2.current &&
				it1.start == it2.start &&
				it1.end == it2.end;
	}

	friend const bool
	operator!=(const Self& it1, const Self& it2)
	{ return !(it1==it2); }

	friend const int
	operator-(const Self& lhs, const Self& rhs) {
		return prism_deque_bucket_size *
				(lhs.buckets-rhs.buckets-1) +
				lhs.current-lhs.start +
				rhs.end-rhs.current;
	}

	friend const bool
	operator<(const Self& lhs, const Self& rhs)
	{ return lhs-rhs < 0; }

	friend const bool
	operator>(const Self& lhs, const Self& rhs)
	{ return lhs-rhs > 0; }

	friend const bool
	operator<=(const Self& lhs, const Self& rhs)
	{ return lhs-rhs <= 0; }

	friend const bool
	operator>=(const Self& lhs, const Self& rhs)
	{ return lhs-rhs >= 0; }

	friend std::ostream&
	operator<<(std::ostream& out, const Self& it) {
		out << "[bucket:" << it.buckets;
		out <<	"] [current index:" << it.current-it.start << "]";
		return out;
	}
};
// \endcond
//================================================================================
// DequeMemory
//================================================================================
template <class T, class Alloc>
struct DequeMemory {
	typedef T**											storagePtr;
	typedef typename Alloc::value_type					value_type;
	typedef typename Alloc::difference_type				difference_type;
	typedef typename Alloc::pointer						pointer;	 	// to T
	typedef typename Alloc::reference					reference; 		// to T
	typedef typename Alloc::const_pointer				const_pointer; 	// to T
	typedef typename Alloc::const_reference				const_reference;// to T
	typedef typename Alloc::template rebind<T>::other 	T_Alloc;
	typedef typename Alloc::template rebind<T*>::other 	StorageAlloc;
	typedef typename Alloc::template rebind<T>::other 	BucketAlloc;

	T_Alloc 		T_Allocator; // allocator for type T
	StorageAlloc 	storageAllocator;
	BucketAlloc 	bucketAllocator;
	T** 			start;
	T** 			finish;

	//todo add exponent growth value for use when reallocating

	DequeMemory()
	: start(nullptr), finish(nullptr)
	{}

	~DequeMemory() {
		destroyBuckets(start, finish);
		deallocateStorage(start);
	};

	pointer
	allocateBucket()
	{ return bucketAllocator.allocate(prism_deque_bucket_size); }

	void
	allocateBuckets(storagePtr start, storagePtr finish) {
		while (start != finish) {
			*start = allocateBucket();
			++start;
		}
	}

	storagePtr
	allocateStorage(const int numBuckets)
	{ return storageAllocator.allocate(numBuckets); }

	void
	deallocateBucket(pointer bucket)
	{ bucketAllocator.deallocate(bucket); }

	void
	deallocateStorage(storagePtr storageStart)
	{ storageAllocator.deallocate(storageStart); }

	void
	destroyBuckets(storagePtr first, storagePtr last) {
		while (first != last)
			deallocateBucket(*first++);
	}

	const int
	numBuckets() const
	{ return finish-start; }
};
//================================================================================
// DequeData
//================================================================================
// \cond DO_NOT_DOCUMENT
template <class T, class Alloc>
struct DequeData : public SharedData {

	typedef typename Alloc::template rebind<T>::other 	T_Alloc;
	typedef typename Alloc::template rebind<T*>::other 	StorageAlloc;
	typedef typename Alloc::template rebind<T>::other 	BucketAlloc;
	typedef DequeMemory<T, Alloc>						Memory;
	typedef DequeIterator<T,false>						iterator;
	typedef DequeIterator<T,true>						const_iterator;
	typedef typename Alloc::value_type					value_type;
	typedef typename Alloc::difference_type				difference_type;
	typedef typename Alloc::pointer						pointer;
	typedef typename Alloc::reference					reference;
	typedef typename Alloc::const_pointer				const_pointer;
	typedef typename Alloc::const_reference				const_reference;
	typedef typename iterator::iterator_category 		iterator_category;

	Memory		storage;
	iterator 	begin;
	iterator 	end;

	/**
	 *
	 */
	DequeData() {
		initializeStorage(0);
	}
	/**
	 *
	 */
	DequeData(const int size, const T& value) {
		initializeStorage(size);
		fillInitialize(value);
	}

	/**
	 *
	 */
	template <class ForwardIterator>
	DequeData(ForwardIterator first, ForwardIterator last) {
		initializeStorage(last-first);
		prism::uninitialized_copy(first, last, this->begin);
	}

	/**
	 *
	 */
	DequeData(std::initializer_list<T> list) {
		initializeStorage(list.size());
		prism::copy(list.begin(), list.end(), this->begin);
	}


	/**
	 *
	 */
	~DequeData()
	{ destroyElements(begin, end); }

	/**
	 *
	 */
	void
	appendValue(const T& value) {
		if (end.current != end.end)
			++end.current;
		else
			reserveElementsAtBack(1);

		get_T_Allocator().construct(end.current-1, value);
	}

	/**
	 *
	 */
	const int
	capacity() const {
		return (storage.finish-storage.start) * prism_deque_bucket_size;
	}

	/**
	 * Sets the begin and end iterators to the middle index of the whole Deque.
	 */
	void
	clear() {
		destroyElements(begin, end);

		begin.buckets = storage.start + storage.numBuckets() / 2;
		begin.start = *begin.buckets;
		begin.current = begin.start + prism_deque_bucket_size / 2;
		begin.end = begin.start + prism_deque_bucket_size;

		end = begin;
	}

	/**
	 *
	 */
	void
	destroyElements(iterator first, iterator last) {
		while (first != last)
			get_T_Allocator().destroy(&*first++);
	}

	/**
	 *
	 */
	void
	eraseAtBack(iterator pos) {
		destroyElements(pos, end);
		end = pos;
	}

	/**
	 * Destroys all elements from begin up to (but not including) pos.
	 */
	void
	eraseAtFront(iterator pos) {
		destroyElements(begin, pos);
		begin = pos;
	}

	/**
	 *
	 */
	iterator
	eraseRange(iterator first, iterator last) {
		if (first == last)
			return first;
		else if (first == begin && last == end) {
			clear();
			return end;
		}
		else {
			int numElements = last-first;
			int numElementsBeforeRange = first - begin;

			bool b = numElementsBeforeRange <= (size() - numElements) / 2;
			if (b) {
//				if (first != begin) {
					// copies elements up from the front
					prism::copy_backward(this->begin, first, last);
					eraseAtFront(begin+numElements);
//				}
			}
			else {
//				if (last != end) {
					// copies elements down from the back
					prism::copy(last, end, first);
					eraseAtBack(end-numElements);
//				}
			}

			return begin + numElementsBeforeRange;
		}
	}

	/**
	 * Only called when the memory has been allocated but not initialized so:
	 * 1) there are no existing elements to destroy before filling.
	 * 2) calls prism::uninitialized_fill instead of prism::fill so as to avoid
	 *    the iterator dereferencing in prism::fill.
	 */
	void
	fillInitialize(const T& value) {
		prism::uninitialized_fill(this->begin, this->end, value);
	}

	/**
	 *
	 */
	typename DequeData<T, Alloc>::iterator
	fillInsert(iterator pos, const int numElements, const T& value) {
		int insertIndex = pos-begin;

		// insert at beginning
		if (pos.current == begin.current) {
			reserveElementsAtFront(numElements);
			prism::uninitialized_fill(begin, begin+numElements, value);
			return begin;
		}
		// inserting at end
		else if (pos.current == end.current) {
			int oldSize = size();
			reserveElementsAtBack(numElements);
			prism::uninitialized_fill(begin+oldSize, begin+oldSize+numElements, value);
			return begin+oldSize;
		}
		// inserting somewhere between beginning and end
		else {
			bool indexLocatedInFirstHalf = pos-begin < size() / 2;

			// insertion index is located in first half
			if (indexLocatedInFirstHalf) {
				reserveElementsAtFront(numElements);
				prism::copy_n(begin+numElements, insertIndex, begin);
				prism::fill(begin+insertIndex, begin+insertIndex+numElements, value);
			}
			// insertion index is located in second half
			else {
				reserveElementsAtBack(numElements);
				prism::copy_backward(begin+insertIndex, end-numElements, end);
				prism::fill(begin+insertIndex, begin+insertIndex+numElements, value);
			}
		}
		return begin+insertIndex;
	}

	/**
	 *
	 */
	StorageAlloc
	getStorageAllocator() const
	{ return storage.storageAllocator; }

	/**
	 *
	 */
	T_Alloc
	get_T_Allocator() const
	{ return storage.T_Allocator; }

	/**
	 * Allocates storage, creates buckets and sets the begin and end iterators accordingly.
	 * If numElements is 0 then one bucket is created in preparation for future elements.
	 * If numElements is greater than 0 then enough buckets to hold the elements are created.
	 * The new elements to be inserted start from a position such that there are equal free
	 * spaces at the start and end of the storage.
	 */
	void
	initializeStorage(const int numElements) {
		int numBuckets = numElements / prism_deque_bucket_size + 1;

		storage.start = storage.allocateStorage(numBuckets);
		storage.finish = storage.start + numBuckets;

		storage.allocateBuckets(storage.start, storage.finish);

		begin.buckets = storage.start;
		begin.start = *storage.start;
		begin.current = begin.start
				+ (numBuckets * prism_deque_bucket_size) / 2
				- numElements / 2;
		begin.end = begin.start + prism_deque_bucket_size;
		end = begin + numElements;
	}

	const int numElementVacanciesAtFront() const {
		return (begin.buckets - storage.start) * prism_deque_bucket_size
					+ begin.current - begin.start;
	}

	/**
	 *
	 */
	void
	prependValue(const T& value) {
		if (begin.current != begin.start)
			--begin.current;
		else
			reserveElementsAtFront(1);

		get_T_Allocator().construct(begin.current, value);
	}

	/**
	 * Sanity check to make sure i is within range.
	 */
	const bool
	rangeCheck(const int i) const {
		int s = size();
		return i >= 0 && i < s;
	}

	/**
	 * Storage is reallocated with the new buckets either added at the front or the back
	 * as necessary.
	 */
	void
	reallocateStorage(const int numBucketsToAdd, const bool newBucketsAtFront) {
		int numTotalBucketsToAdd = storage.numBuckets() + numBucketsToAdd;
		T** newStorage = storage.allocateStorage(numTotalBucketsToAdd);

		if (newBucketsAtFront) {
			prism::copy(storage.start, storage.finish, newStorage+numBucketsToAdd);
			storage.allocateBuckets(newStorage, newStorage+numBucketsToAdd);
		}
		else {
			prism::copy(storage.start, storage.finish, newStorage);
			storage.allocateBuckets(newStorage+storage.numBuckets(),
									newStorage+storage.numBuckets()+numBucketsToAdd);
		}

		storage.deallocateStorage(storage.start);

		storage.start = newStorage;
		storage.finish = storage.start + numTotalBucketsToAdd;

		begin.buckets = storage.start;
		begin.start = *storage.start;
		begin.end = begin.start + prism_deque_bucket_size;
	}

	/**
	 * Determines if there are enough buckets after to the bucket holding the last element
	 * for the new elements. If not then the storage is reallocated.
	 */
	void
	reserveBucketsAtBack(const int numBucketsToAdd) {
		int numBucketsForExcessElements = numBucketsToAdd / prism_deque_bucket_size + 1;
		int bucketVacancies = storage.finish - end.buckets - 1;
		if (bucketVacancies < numBucketsForExcessElements) {
			reallocateStorage(numBucketsForExcessElements, false);
		}
	}

	/**
	 * Determines if there are enough buckets prior to the bucket holding the first element
	 * for the new elements. If not then the storage is reallocated.
	 */
	void
	reserveBucketsAtFront(const int numExcessElements) {
		int numBucketsForExcessElements = numExcessElements / prism_deque_bucket_size + 1;
		int bucketVacancies = begin.buckets - storage.start;
		if (bucketVacancies < numBucketsForExcessElements)
			reallocateStorage(numBucketsForExcessElements, true);
	}

	/**
	 * Determines if there is enough space in the last bucket after the last element
	 * for the new elements and passes onto reserveBucketsAtBack if not.
	 * begin and end iterators are also updated.
	 */
	void
	reserveElementsAtBack(const int numElementsToAdd) {
		int beginIndex = begin.current - begin.start;
		int oldSize = size();

		int elementVacancies = 0;
		if (end.current != end.start)
			elementVacancies = end.end - end.current;

		if (elementVacancies < numElementsToAdd) {
			int numExcessElements = numElementsToAdd - elementVacancies;
			reserveBucketsAtBack(numExcessElements);

			begin.current = begin.start + beginIndex;
			end = begin + oldSize + numElementsToAdd;
		}
		else
			end += numElementsToAdd;
	}

	/**
	 * Determines if there is enough space in the first bucket before the first element
	 * for the new elements and passes onto reserveBucketsAtFront if not.
	 * begin and end iterators are also updated.
	 */
	void
	reserveElementsAtFront(const int numElementsToAdd) {
		int oldSize = size();
		int elementVacancies = begin.current - begin.start;

		if (elementVacancies < numElementsToAdd) {
			int numExcessElements = numElementsToAdd - elementVacancies;
			reserveBucketsAtFront(numExcessElements);

			begin.current = begin.end - numExcessElements % prism_deque_bucket_size;
		}
		else
			begin -= numElementsToAdd;

		end = begin + oldSize + numElementsToAdd;
	}

	/**
	 *
	 */
	const int
	size() const {
		return end-begin;
	}

};
// \endcond

} // namespace aux
//================================================================================
// Deque
//================================================================================
template <class T, class Alloc = prism::Allocator<T>>
class Deque {
public:
	typedef typename aux::DequeData<T, Alloc>					Data;
	typedef typename aux::DequeData<T, Alloc>::iterator			iterator;
	typedef typename aux::DequeData<T, Alloc>::const_iterator	const_iterator;
	typedef typename Alloc::value_type							value_type;
	typedef typename Alloc::difference_type						difference_type;
	typedef typename Alloc::pointer								pointer;
	typedef typename Alloc::reference							reference;
	typedef typename Alloc::const_pointer						const_pointer;
	typedef typename Alloc::const_reference						const_reference;
	typedef typename iterator::iterator_category 				iterator_category;
private:
	SharedDataPointer<Data> d;
public:
	/**
	 * Creates an empty Deque.
	 */
	Deque()
	: d(new Data)
	{}

	/**
	 * Creates a Deque that contains \em size amount of elements
	 * initialized to \em value.
	 */
	Deque(const int size, const T& value=T())
	: d(new Data(size, value))
	{}

	/**
	 *
	 */
	template <class ForwardIterator>
	Deque(ForwardIterator first, ForwardIterator last)
	: d(new Data(first, last))
	{}

	/**
	 * Creates a Deque and assigns the elements in the initializer list
	 * to the Deque.
	 */
	Deque(std::initializer_list<T> list)
	: d(new Data(list))
	{}

	/**
	 * Creates a new Deque which is a copy of \em copy.
	 */
	Deque(const Deque<T>& copy)
	: d(copy.d)
	{}

	/**
	 * Destroys this Deque.
	 */
	~Deque()
	{}

	/**
	 *
	 */
	void
	append(const T& value)
	{ d->appendValue(value); }

	/**
	 * @return Returns a reference to the the element at index \em i.
	 * @exception Throws an OutOfBoundsException if \em i is less than 0 or
	 * greater than or equal to \em size().
	 */
	reference
	at(const int i) {
		if (d->rangeCheck(i))
			return *(d->begin+i);
		throw OutOfBoundsException(i);
	}

	/**
	 * @return Returns a const reference to the the element at index \em i.
	 * @exception Throws an OutOfBoundsException if \em i is less than 0 or
	 * greater than or equal to \em size().
	 */
	const_reference
	at(const int i) const {
		if (d->rangeCheck(i))
			return *(d->begin+i);
		throw OutOfBoundsException(i);
	}

	/**
	 * @return Returns a reference to the last element in the Deque.
	 */
	reference
	back()
	{ return *(end()-1); }

	/**
	 * @return Returns a const reference to the last element in the Deque.
	 */
	const_reference
	back() const
	{ return *(end()-1); }

	/**
	 * @return Returns an iterator that points to the first element in the Deque.
	 */
	iterator
	begin()
	{ return d->begin; }

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	begin() const
	{ return d->begin; }

	/**
	 * @return Returns the capacity of the Deque.
	 */
	const int
	capacity() const
	{ return d->capacity(); }

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	cbegin() const
	{ return d->begin; }

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	cend() const
	{ return d->end; }

	/**
	 * Clears all elements from the Deque so that its size is 0. \n
	 * Note that this does not affect the capacity.
	 */
	void
	clear()
	{ d->clear(); }

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	constBegin() const
	{ return d->begin; }

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	constEnd() const
	{ return d->end; }

	/**
	 * @return Returns true if the Deque contains \em value, false otherwise.
	 */
	const bool
	contains(const T& value) const
	{ return prism::count(d->begin, d->end, value); }

	/**
	 *
	 */
	const int
	count(const T& value) const
	{ return prism::count(d->begin, d->end, value); }

	/**
	 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
	 */
	const bool
	empty() const
	{ return d->end == d->begin; }

	/**
	 * @return Returns an iterator that points to one position past the last element in the Deque.
	 */
	iterator
	end()
	{ return d->end; }

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	end() const
	{ return d->end; }

	/**
	 *
	 */
	const bool
	endsWith(const T& value) const
	{ return back() == value; }

	/**
	 *
	 */
	iterator
	erase(iterator pos)
	{ return erase(pos, pos+1); }

	/**
	 * @return Returns an iterator to the new position of the element that follows the
	 * last element erased.
	 * \code
	 * Deque<int> d({1,2,3,4,5,6});
	 * iterator it = d.erase(d.begin()+2, d.begin()+5);
	 * // *it == 6 since the integers 3, 4 and 5 were erased
	 * \endcode
	 */
	iterator
	erase(iterator first, iterator last)
	{ return d->eraseRange(first, last); }

	/**
	 * Sets each element in the Deque to \em value.
	 */
	void
	fill(const T& value)
	{ d->fill(value); }

	/**
	 * @return Returns a reference to the first element in the Deque.
	 */
	reference
	first()
	{ return *begin(); }

	/**
	 * @return Returns a const reference to the first element in the Deque.
	 */
	const_reference
	first() const
	{ return *begin(); }

	/**
	 * @return Returns a reference to the first element in the Deque.
	 */
	reference
	front()
	{ return *begin(); }

	/**
	 * @return Returns a const reference to the first element in the Deque.
	 */
	const_reference
	front() const
	{ return *begin(); }

	/**
	 * Searches for the first index starting from index \em from that contains \em value.
	 * @return Returns the index of of the first occurrence of \em value or -1 if \em value
	 * does not occur in the Deque.
	 */
	const int
	indexOf(const T& value, const int from=0) {
		iterator it = prism::find(d->begin+from, d->end, value);
		if (it == d->end)
			return -1;
		return it - d->begin;
	}

	/**
	 *
	 */
	void
	insert(const int index, const T& value)
	{ d->fillInsert(d->begin+index, 1, value); }

	/**
	 *
	 */
	void
	insert(const int index, const int count, const T& value)
	{ d->fillInsert(d->begin+index, count, value); }

	/**
	 *
	 */
	iterator
	insert(iterator insertBefore, const T& value)
	{ return d->fillInsert(insertBefore, 1, value); }

	/**
	 *
	 */
	iterator
	insert(iterator insertBefore, const int count, const T& value)
	{ return d->fillInsert(insertBefore, count, value); }

	/**
	 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
	 */
	const bool
	isEmpty() const
	{ return d->end == d->begin; }

	/**
	 * @return Returns a reference to the last element in the Deque.
	 */
	reference
	last()
	{ return *(end()-1); }

	/**
	 * @return Returns a const reference to the last element in the Deque.
	 */
	const_reference
	last() const
	{ return *(end()-1); }

	/**
	 *
	 */
	const int
	lastIndexOf(const T& value, int from=-1) {
		if (from == -1) from = size();
		else from += 1;
		iterator it = prism::find_last(d->begin, d->begin+from, value);
		return (it == d->end) ? -1 : it-d->begin;
	}

	/**
	 *
	 */
	Deque<T>
	mid(const int startIndex, const int count) const {
		const_iterator first = begin() + startIndex;
		const_iterator last;

		if (startIndex + count >= d->size()) last = end();
		else last = first + count;

		return Deque<T>(first, last);
	}

	/**
	 *
	 */
	void
	prepend(const T& value)
	{ d->prependValue(value); }

	/**
	 *
	 */
	void
	push_back(const T& value)
	{ d->appendValue(value); }

	/**
	 *
	 */
	void
	push_front(const T& value)
	{ d->prependValue(value); }

	/**
	 *
	 */
	void
	remove(const int index)
	{ erase(d->begin+index); }

	/**
	 *
	 */
	void
	remove(const int index, const int count)
	{ erase(d->begin+index, d->begin+index+count); }

	/**
	 *
	 */
	void
	removeFirst()
	{ remove(0); }

	/**
	 *
	 */
	void
	removeLast()
	{ remove(size()-1); }

	/**
	 *
	 */
	void
	replace(const int index, const T& value) {
		T* p = &*(d->begin+index);
		d->get_T_Allocator().destroy(p);
		d->get_T_Allocator().construct(p, value);
	}

	/**
	 * @return Returns the number of elements currently in the Deque.
	 */
	const int
	size() const
	{ return d->size(); }

	/**
	 *
	 */
	const bool
	startsWith(const T& value) const
	{ return first() == value; }

	/**
	 *
	 */
	List<T>
	toList() const {
		const_iterator cit = cbegin();
		List<T> list;

		while(cit != cend())
			list.append(*cit++);

		return list;
	}

	/**
	 *
	 */
	//template <class T>
	//std::deque<T>
	//Deque<T>::
	//toStdDeque() const {
	//	return std::deque<T>(constBegin(), constEnd());
	//}

	/**
	 * @return Returns a reference to the element at index \em i.
	 * \note Note that no bounds checking is performed on \em i.
	 */
	reference
	operator [](const int i)
	{ return *(d->begin+i); }

	/**
	 * @return Returns a const reference to the element at index \em i.
	 * \note Note that no bounds checking is performed on \em i.
	 */
	const_reference
	operator [](const int i) const
	{ return *(d->begin+i); }

	/**
	 *
	 */
	Deque<T>&
	operator=(const Deque<T>& rhs) {
		if (*this != rhs) {
			d = rhs.d;
		}
		return *this;
	}

	/**
	 *
	 */
	const bool
	operator==(const Deque<T>& rhs)
	{ return this->d == rhs.d; }

	/**
	 *
	 */
	const bool
	operator!=(const Deque<T>& rhs)
	{ return !(*this == rhs); }

	/**
	 *
	 */
	Deque<T, Alloc>&
	operator<<(const T& value) {
		d->appendValue(value);
		return *this;
	}

	/**
	 *
	 */
	friend std::ostream&
	operator<<(std::ostream& out, const Deque<T>& d) {
		out << "Deque [" << &d << "]\n"
				"----size:          " << d.size() << "\n" <<
				"----capacity:      " << d.capacity() << "\n" <<
				"----numBuckets:    " << d.d->storage.numBuckets() << endl;
		out << "----storage.start: [" << d.d->storage.start << "]" << endl;
		out << "----begin:\n" <<
			   "      [buckets address: " << d.d->begin.buckets << "]\n" <<
			   "      [buckets index: " << d.d->begin.buckets-d.d->storage.start << "] \n" <<
			   "      [bucket address: " << d.d->begin.start << "]\n" <<
			   "      [current index:" << d.d->begin.current-d.d->begin.start << "]\n";
		out << "----end: \n" <<
			   "      [buckets address: " << d.d->end.buckets << "] \n" <<
			   "      [buckets index:" << d.d->end.buckets-d.d->storage.start << "] \n" <<
			   "      [bucket address: " << d.d->end.start << "] \n" <<
			   "      [current index:" << d.d->end.current-d.d->end.start << "]\n";

		int startIndex = (d.d->begin.buckets - d.d->storage.start) *
							aux::prism_deque_bucket_size
							+ d.d->begin.current - d.d->begin.start;

		const_iterator cit = d.cbegin();

		for (int i=0; i<d.capacity(); i++) {
			if (i % aux::prism_deque_bucket_size == 0) {
				cout << "---------------------------------" << endl;
				cout << "Bucket " << (cit.buckets-d.d->storage.start) << ": " << cit.buckets << endl;
				cout << "---------------------------------" << endl;
			}

			if (i < startIndex || i >= startIndex+d.size())
				out << "[-] *" << endl;
			else
				out << "[" << (cit-d.cbegin()) << "] " << *cit++ << endl;
		}

		return out;
	}

}; // class Deque

} // namespace prism

#endif // PRISM_DEQUE_H

