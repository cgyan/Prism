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
#include <ostream>
#include <cstddef> // for std::ptrdiff_t
#include <initializer_list>
using namespace std;

namespace prism {
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

	// can converts non-const iterator into const iterator but not the other way around
	DequeIterator(const iterator& copy)
		: buckets(copy.buckets),
		  current(copy.current),
		  start(copy.start),
		  end(copy.end) {}

	reference
	operator*() {
		return *current;
	}

	pointer
	operator->() {
		return current;
	}

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
	operator-=(const int n) {
		return *this += -n;
	}

	Self
	operator-(const int n) {
		Self tmp = *this;
		return tmp -= n;
	}

	Self&
	operator++() {
		return *this += 1;
	}

	Self
	operator++(int junk) {
		Self tmp(*this);
		*this = *this += 1;
		return tmp;
	}

	Self&
	operator--() {
		return *this -= 1;
	}

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
	operator!=(const Self& it1, const Self& it2) {
		return !(it1==it2);
	}

	friend const int
	operator-(const Self& lhs, const Self& rhs) {
		return prism_deque_bucket_size *
				(lhs.buckets-rhs.buckets-1) +
				lhs.current-lhs.start +
				rhs.end-rhs.current;
	}

	friend const bool
	operator<(const Self& lhs, const Self& rhs) {
		return lhs-rhs < 0;
	}

	friend const bool
	operator>(const Self& lhs, const Self& rhs) {
		return lhs-rhs > 0;
	}

	friend const bool
	operator<=(const Self& lhs, const Self& rhs) {
		return lhs-rhs <= 0;
	}

	friend const bool
	operator>=(const Self& lhs, const Self& rhs) {
		return lhs-rhs >= 0;
	}

	friend std::ostream&
	operator<<(std::ostream& out, const Self& it) {
		out <<	"current index:" << it.current-it.start;
		return out;
	}
};
// \endcond
//================================================================================
// DequeData
//================================================================================
// \cond DO_NOT_DOCUMENT
template <class T>
struct DequeData : public SharedData {
	typedef DequeIterator<T,false>					iterator;
	typedef DequeIterator<T,true>					const_iterator;
	typedef typename iterator::value_type			value_type;
	typedef typename iterator::difference_type		difference_type;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::reference			reference;
	typedef typename const_iterator::pointer		const_pointer;
	typedef typename const_iterator::reference		const_reference;
	typedef typename iterator::iterator_category 	iterator_category;

	struct memory {
		T** start;
		T** finish;

		memory() : start(0), finish(0)
		{}

		~memory() {
			deallocateStorage();
		};

		T*
		allocateBucket() {
			return new T[prism_deque_bucket_size];
		}

		T**
		allocateStorage(const int size) {
			return new T*[size];
		}

		void
		createBuckets(T** start, T** finish) {
			while (start != finish) {
				*start = allocateBucket();
				++start;
			}
		}

		void
		deallocateBucket(T* bucket) {
			delete bucket;
		}

		void
		deallocateStorage() {
			if (start != nullptr) {
				for (int i=0; i<finish-start; i++)
					deallocateBucket(start[i]);
				delete []start;
			}
		}

		const int
		numBuckets() const {
			return finish-start;
		}
	};

	memory 		storage;
	iterator 	begin;
	iterator 	end;

	DequeData();
	DequeData(const int size, const T& value);
	DequeData(std::initializer_list<T> list);
	~DequeData();

	const int 	capacity() const;
	void		clear();
	void		fill(const T& value);
	void 		initializeStorage(const int numElements);
	const bool	rangeCheck(const int i) const;
	const int 	size() const;
};
// \endcond
/**
 *
 */
template <class T>
DequeData<T>::
DequeData() {
	initializeStorage(0);
}
/**
 *
 */
template <class T>
DequeData<T>::
DequeData(const int size, const T& value) {
	initializeStorage(size);
	fill(value);
}

/**
 *
 */
template <class T>
DequeData<T>::
DequeData(std::initializer_list<T> list) {
	initializeStorage(list.size());
	prism::copy(list.begin(), list.end(), this->begin);
}


/**
 *
 */
template <class T>
DequeData<T>::
~DequeData() {

}

/**
 *
 */
template <class T>
const int
DequeData<T>::
capacity() const {
	return (storage.finish-storage.start) * prism_deque_bucket_size;
}

/**
 * Sets the begin and end iterators to the middle index of the whole Deque.
 */
template <class T>
void
DequeData<T>::
clear() {
	begin.buckets = storage.start + storage.numBuckets() / 2;
	begin.start = *begin.buckets;
	begin.current = begin.start + prism_deque_bucket_size / 2;
	begin.end = begin.start + prism_deque_bucket_size;

	end = begin;
}

/**
 *
 */
template <class T>
void
DequeData<T>::
fill(const T& value) {
	prism::fill(this->begin, this->end, T(value));
}

/**
 * Allocates storage, creates buckets and sets the begin and end iterators accordingly.
 * If numElements is 0 then one bucket is created in preparation for future elements.
 * If numElements is greater than 0 then enough buckets to hold the elements are created.
 * The new elements to be inserted start from a position such that there are equal free
 * spaces at the start and end of the storage.
 */
template <class T>
void
DequeData<T>::
initializeStorage(const int numElements) {
	int numBuckets = numElements / prism_deque_bucket_size + 1;

	storage.start = storage.allocateStorage(numBuckets);
	storage.finish = storage.start + numBuckets;

	storage.createBuckets(storage.start, storage.finish);

	begin.buckets = storage.start;
	begin.start = *storage.start;
	begin.current = begin.start
			+ (numBuckets * prism_deque_bucket_size) / 2
			- numElements / 2;
	begin.end = begin.start + prism_deque_bucket_size;
	end = begin + numElements;
}

/**
 * Sanity check to make sure i is within range.
 */
template <class T>
const bool
DequeData<T>::
rangeCheck(const int i) const {
	int s = size();
	return i >= 0 && i < s;
}

/**
 *
 */
template <class T>
const int
DequeData<T>::
size() const {
	return end-begin;
}
//================================================================================
// Deque
//================================================================================
template <class T>
class Deque {
public:
	typedef typename DequeData<T>::iterator			iterator;
	typedef typename DequeData<T>::const_iterator	const_iterator;
	typedef typename iterator::value_type			value_type;
	typedef typename iterator::difference_type		difference_type;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::reference			reference;
	typedef typename const_iterator::pointer		const_pointer;
	typedef typename const_iterator::reference		const_reference;
	typedef typename iterator::iterator_category 	iterator_category;
private:
	SharedDataPointer<DequeData<T>> d;
public:
						Deque();
						Deque(const int size, const T& value=T());
						Deque(std::initializer_list<T> list);
						Deque(const Deque<T>& copy);
						~Deque();

	reference			at(const int i);
	const_reference		at(const int i) const;
	reference			back();
	const_reference		back() const;
	iterator 			begin();
	const_iterator 		begin() const;
	const int 			capacity() const;
	const_iterator		cbegin() const;
	const_iterator		cend() const;
	void				clear();
	const_iterator		constBegin() const;
	const_iterator		constEnd() const;
	const bool			contains(const T& value) const;
	const int			count(const T& value) const;
	const bool			empty() const;
	iterator 			end();
	const_iterator		end() const;
	const bool			endsWith(const T& value) const;
	void				fill(const T& value);
	reference			first();
	const_reference		first() const;
	reference			front();
	const_reference		front() const;
	const int			indexOf(const T& value, const int from=0);
	const bool			isEmpty() const;
	reference			last();
	const_reference		last() const;
	const int			lastIndexOf(const T& value, int from=-1);
//	Deque<T>			mid(const int startIndex, const int count) const;
	void 				replace(const int index, const T& value);
	const int 			size() const;
	const bool			startsWith(const T& value) const;
	List<T>				toList() const;

	reference			operator[](const int i);
	const_reference		operator[](const int i) const;
	Deque<T>&			operator=(const Deque<T>& rhs);
	const bool			operator==(const Deque<T>& rhs);
	const bool			operator!=(const Deque<T>& rhs);

	friend std::ostream&
	operator<<(std::ostream& out, const Deque<T>& d) {
		out << "Deque [" << &d << "]"
				" size=" << d.size() <<
				" capacity=" << d.capacity() <<
				" numBuckets=" << d.d->storage.finish-d.d->storage.start << endl;
		out << "----begin: " << d.d->begin << endl;
		out << "----end:   " << d.d->end;
		return out;
	}
};

/**
 * Creates an empty Deque.
 */
template <class T>
Deque<T>::
Deque()
	: d(new DequeData<T>)
{}

/**
 * Creates a Deque that contains \em size amount of elements set to \em value.
 */
template <class T>
Deque<T>::
Deque(const int size, const T& value)
	: d(new DequeData<T>(size, value))
{}

/**
 * Creates a Deque and assigns the elements in the initializer list
 * to the Deque.
 */
template <class T>
Deque<T>::
Deque(std::initializer_list<T> list)
	: d(new DequeData<T>(list))
{}

/**
 * Creates a new Deque which is a copy of \em copy.
 */
template <class T>
Deque<T>::
Deque(const Deque<T>& copy)
	: d(copy.d)
{}

/**
 * Destroys this Deque.
 */
template <class T>
Deque<T>::
~Deque()
{}

/**
 * @return Returns a reference to the the element at index \em i.
 * @exception Throws an OutOfBoundsException if \em i is less than 0 or
 * greater than or equal to \em size().
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
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
template <class T>
typename Deque<T>::const_reference
Deque<T>::
at(const int i) const {
	if (d->rangeCheck(i))
		return *(d->begin+i);
	throw OutOfBoundsException(i);
}

/**
 * @return Returns a reference to the last element in the Deque.
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
back() {
	return *(end()-1);
}

/**
 * @return Returns a const reference to the last element in the Deque.
 */
template <class T>
typename Deque<T>::const_reference
Deque<T>::
back() const {
	return *(end()-1);
}

/**
 * @return Returns an iterator that points to the first element in the Deque.
 */
template <class T>
typename Deque<T>::iterator
Deque<T>::
begin() {
	return d->begin;
}

/**
 * @return Returns a const_iterator that points to the first element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
begin() const {
	return d->begin;
}

/**
 * @return Returns the capacity of the Deque.
 */
template <class T>
const int
Deque<T>::
capacity() const {
	return d->capacity();
}

/**
 * @return Returns a const_iterator that points to the first element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
cbegin() const {
	return d->begin;
}

/**
 * @return Returns a const_iterator that points to one position past the last element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
cend() const {
	return d->end;
}

/**
 * Clears all elements from the Deque so that its size is 0. \n
 * Note that this does not affect the capacity.
 */
template <class T>
void
Deque<T>::
clear() {
	d->clear();
}

/**
 * @return Returns a const_iterator that points to the first element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
constBegin() const {
	return d->begin;
}

/**
 * @return Returns a const_iterator that points to one position past the last element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
constEnd() const {
	return d->end;
}

/**
 * @return Returns true if the Deque contains \em value, false otherwise.
 */
template <class T>
const bool
Deque<T>::
contains(const T& value) const {
	return prism::count(d->begin, d->end, value);
}

/**
 *
 */
template <class T>
const int
Deque<T>::
count(const T& value) const {
	return prism::count(d->begin, d->end, value);
}

/**
 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
 */
template <class T>
const bool
Deque<T>::
empty() const {
	return d->end == d->begin;
}

/**
 * @return Returns an iterator that points to one position past the last element in the Deque.
 */
template <class T>
typename Deque<T>::iterator
Deque<T>::
end() {
	return d->end;
}

/**
 * @return Returns a const_iterator that points to one position past the last element in the Deque.
 */
template <class T>
typename Deque<T>::const_iterator
Deque<T>::
end() const {
	return d->end;
}

/**
 *
 */
template <class T>
const bool
Deque<T>::
endsWith(const T& value) const {
	return last() == value;
}

/**
 * Sets each element in the Deque to \em value.
 */
template <class T>
void
Deque<T>::
fill(const T& value) {
	d->fill(value);
}

/**
 * @return Returns a reference to the first element in the Deque.
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
first() {
	return *begin();
}

/**
 * @return Returns a const reference to the first element in the Deque.
 */
template <class T>
typename Deque<T>::const_reference
Deque<T>::
first() const {
	return *begin();
}

/**
 * @return Returns a reference to the first element in the Deque.
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
front() {
	return *begin();
}

/**
 * @return Returns a const reference to the first element in the Deque.
 */
template <class T>
typename Deque<T>::const_reference
Deque<T>::
front() const {
	return *begin();
}

/**
 * Searches for the first index starting from index \em from that contains \em value.
 * @return Returns the index of of the first occurrence of \em value or -1 if \em value
 * does not occur in the Deque.
 */
template <class T>
const int
Deque<T>::
indexOf(const T& value, const int from) {
	iterator it = prism::find(d->begin+from, d->end, value);
	if (it == d->end)
		return -1;
	return it - d->begin;
}

/**
 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
 */
template <class T>
const bool
Deque<T>::
isEmpty() const {
	return d->end == d->begin;
}

/**
 * @return Returns a reference to the last element in the Deque.
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
last() {
	return *(end()-1);
}

/**
 * @return Returns a const reference to the last element in the Deque.
 */
template <class T>
typename Deque<T>::const_reference
Deque<T>::
last() const {
	return *(end()-1);
}

/**
 *
 */
template <class T>
const int
Deque<T>::
lastIndexOf(const T& value, int from) {
	if (from == -1) from = size();
	else from += 1;
	iterator it = prism::find_last(d->begin, d->begin+from, value);
	return (it == d->end) ? -1 : it-d->begin;
}

/**
 *
 */
//template <class T>
//Deque<T>
//Deque<T>::
//mid(const int startIndex, const int count) const {
//	return d->mid(startIndex, count);
//}

/**
 *
 */
template <class T>
void
Deque<T>::
replace(const int index, const T& value) {
	*(d->begin+index) = value;
}

/**
 * @return Returns the number of elements curently in the Deque.
 */
template <class T>
const int
Deque<T>::
size() const {
	return d->size();
}

/**
 *
 */
template <class T>
const bool
Deque<T>::
startsWith(const T& value) const {
	return first() == value;
}

/**
 *
 */
template <class T>
List<T>
Deque<T>::
toList() const {
	const_iterator cit = cbegin();
	List<T> list;

	while(cit != cend())
		list.append(*cit++);

	return list;
}

/**
 * @return Returns a reference to the element at index \em i.
 * \note Note that no bounds checking is performed on \em i.
 */
template <class T>
typename Deque<T>::reference
Deque<T>::
operator [](const int i) {
	return *(d->begin+i);
}

/**
 * @return Returns a const reference to the element at index \em i.
 * \note Note that no bounds checking is performed on \em i.
 */
template <class T>
typename Deque<T>::const_reference
Deque<T>::
operator [](const int i) const {
	return *(d->begin+i);
}

/**
 *
 */
template <class T>
Deque<T>&
Deque<T>::
operator=(const Deque<T>& rhs) {
	if (*this != rhs) {
		d = rhs.d;
	}
	return *this;
}

/**
 *
 */
template <class T>
const bool
Deque<T>::
operator==(const Deque<T>& rhs) {
	return this->d == rhs.d;
}

/**
 *
 */
template <class T>
const bool
Deque<T>::
operator!=(const Deque<T>& rhs) {
	return !(*this == rhs);
}

} // namespace prism

#endif // PRISM_DEQUE_H

//namespace prism {
////================================================================================
//// DequeBlock
////================================================================================
//// \cond DO_NOT_DOCUMENT
////template <class T>
////struct Block {
////	static const int BLOCKSIZE = 8;
////	struct memory {
////		T* start;	// the start of the storage
////		T* finish;	// the end of the storage
////		T* begin;	// the first element of T
////		T* end;		// one position past the last element of T
////		memory() {
////			start = new T[BLOCKSIZE];
////			finish = start + BLOCKSIZE;
////			begin = start + BLOCKSIZE/2;
////			end = begin;
////		}
////		~memory() { delete []start; }
////	};
////	memory storage;
////};
//// \endcond
//
//static const int prism_deque_block_size = 8;
////================================================================================
//// DequeIterator
////================================================================================
//// \cond DO_NOT_DOCUMENT
//template <class T>
//class DequeIterator {
//private:
//	T* curr;
//	T* first;
//	T* last;
//	T** blockPtr;
//public:
//	DequeIterator();
//	DequeIterator(T* curr, T** blockPtr);
//	DequeIterator(const DequeIterator& copy);
//
//	T& 				operator*() const;
//	T* 				operator->() const;
//	DequeIterator& 	operator+=(const int i);
//	DequeIterator 	operator+(const int i);
//	DequeIterator& 	operator-=(const int i);
//	DequeIterator 	operator-(const int i);
//	DequeIterator& 	operator++();
//	DequeIterator 	operator++(const int junk);
//	DequeIterator& 	operator--();
//	DequeIterator 	operator--(int junk);
//	DequeIterator& 	operator=(const DequeIterator& other);
//
//	// related non members
//	//--------------------
//	friend const bool operator==(const DequeIterator<T>& it1, const DequeIterator<T>& it2) {
//		return it1.curr == it2.curr && it1.first == it2.first &&
//				it1.last == it2.last && it1.blockPtr == it2.blockPtr;
//	}
//
//	friend const bool operator!=(const DequeIterator<T>& it1, const DequeIterator<T>& it2) {
//		return !(it1==it2);
//	}
//
//	friend const int operator-(const DequeIterator& lhs, const DequeIterator& rhs) {
//		return prism_deque_block_size * (lhs.blockPtr-rhs.blockPtr-1) +
//				lhs.curr-lhs.first + rhs.last-rhs.curr;
//	}
//
//	friend const bool operator<(const DequeIterator& lhs, const DequeIterator& rhs) {
//		return lhs-rhs < 0;
//	}
//
//	friend const bool operator>(const DequeIterator& lhs, const DequeIterator& rhs) {
//		return lhs-rhs > 0;
//	}
//
//	friend const bool operator<=(const DequeIterator& lhs, const DequeIterator& rhs) {
//		return lhs-rhs <= 0;
//	}
//
//	friend const bool operator>=(const DequeIterator& lhs, const DequeIterator& rhs) {
//		return lhs-rhs >= 0;
//	}
//
//};
//
//template <class T>
//DequeIterator<T>::DequeIterator()
//		: curr(0), first(0), last(0), blockPtr(0)
//{}
//
//template <class T>
//DequeIterator<T>::DequeIterator(T* curr, T** blockPtr)
//	: curr(curr),
//	  first(*blockPtr),
//	  last(first+prism_deque_block_size),
//	  blockPtr(blockPtr)
//{}
//
//template <class T>
//DequeIterator<T>::DequeIterator(const DequeIterator& copy)
//	: curr(copy.curr),
//	  first(*copy.blockPtr),
//	  last(first+prism_deque_block_size),
//	  blockPtr(copy.blockPtr)
//{}
//
//template <class T>
//T& DequeIterator<T>::operator*() const {
//	return *curr;
//}
//
//template <class T>
//T* DequeIterator<T>::operator->() const {
//	return curr;
//}
//
//template <class T>
//DequeIterator<T>& DequeIterator<T>::operator+=(const int i)
//{
//	int offset = i + (curr - first);
//	if (offset >= 0 && offset < prism_deque_block_size)
//		curr += i;
//	else {
//		int mapOffset = 0;
//		if (offset > 0) mapOffset = offset / prism_deque_block_size;
//		else mapOffset = -((-offset-1) / prism_deque_block_size) - 1;
//
//		blockPtr = blockPtr+mapOffset;
//		curr = first + (offset-mapOffset * prism_deque_block_size);
//	}
//
//	return *this;
//}
//
//template <class T>
//DequeIterator<T> DequeIterator<T>::operator+(const int i) {
//	DequeIterator tmp(*this);
//	return tmp += i;
//}
//
//template <class T>
//DequeIterator<T>& DequeIterator<T>::operator-=(const int i) {
//	return *this += -i;
//}
//
//template <class T>
//DequeIterator<T> DequeIterator<T>::operator-(const int i) {
//	DequeIterator tmp(*this);
//	return tmp -= i;
//}
//
//template <class T>
//DequeIterator<T>& DequeIterator<T>::operator++()
//{
//	curr++;
//	if (curr == last) {
//		blockPtr = blockPtr+1;
//		curr = first;
//	}
//
//	return *this;
//}
//
//template <class T>
//DequeIterator<T> DequeIterator<T>::operator++(const int junk)
//{
//	T* tmp = curr;
//	curr++;
//	if (curr == last) {
//		blockPtr = blockPtr+1;
//		curr = first;
//	}
//
//	return DequeIterator(tmp, blockPtr);
//}
//
//template <class T>
//DequeIterator<T>& DequeIterator<T>::operator--() {
//	curr--;
//	if (curr < first) {
//		blockPtr = blockPtr-1;
//		curr = last-1;
//	}
//	return *this;
//}
//
//template <class T>
//DequeIterator<T> DequeIterator<T>::operator--(int junk) {
//	T* tmp = curr;
//	curr--;
//	if (curr < first) {
//		blockPtr = blockPtr-1;
//		curr = last-1;
//	}
//	return DequeIterator(tmp, blockPtr);
//}
//
//template <class T>
//DequeIterator<T>& DequeIterator<T>::operator=(const DequeIterator& other)
//{
//	if (*this != other) {
//		*this = DequeIterator(curr, blockPtr);
//	}
//	return *this;
//
//}
//
//template <class T>
//const bool operator==(const DequeIterator<T>& lhs, const DequeIterator<T>& rhs) {
//	return lhs.p == rhs.p && lhs.blocks == rhs.blocks && lhs.block == rhs.block;
//}
//
//template <class T>
//const bool operator!=(const DequeIterator<T>& lhs, const DequeIterator<T>& rhs) {
//	return !(lhs==rhs);
//}
//// \endcond
////================================================================================
//// DequeData
////================================================================================
//// \cond DO_NOT_DOCUMENT
//template <class T>
//struct DequeData : public SharedData {
//	struct memory {
//		T** start;
//		int size;
//
//		memory() : start(new T*[1])
//		{}
//
//		~memory() {
////			T** block = start;
////			while (block < size)
////				delete *block++;
////			delete [] start;
//		}
//	};
//	memory storage;
//	DequeIterator<T> begin;
//	DequeIterator<T> end;
//
//	const int size() const {
//		return end - begin;
//	}
//};
//// \endcond
////================================================================================
//// Deque
////================================================================================
//template <class T>
//class Deque {
//private:
//	SharedDataPointer<DequeData<T>> d;
//public:
//	Deque();
//	Deque(const Deque<T>& copy);
//
//	const int size() const;
//};
//
///**
// *
// */
//template <class T>
//Deque<T>::Deque()
//	: d(new DequeData<T>)
//{
//	d->storage.start = new T*[1];
//	d->storage.size = 1;
//
//	d->storage.start[0] = new T[prism_deque_block_size];
////	block->storage.start[0] = 0;
////	block->storage.start[1] = 1;
////	block->storage.start[2] = 2;
////	block->storage.start[3] = 3;
//	d->storage.start[0][4] = 4;
//	d->storage.start[0][5] = 5;
//	d->storage.start[0][6] = 6;
//	d->storage.start[0][7] = 7;
//
////
////	d->begin = DequeIterator<T>(block+4, d->storage.start);
////	d->end = d->begin + 1;
//	d->begin = DequeIterator<T>(*(d->storage.start+4), d->storage.start);
//	d->end = DequeIterator<T>(*(d->storage.start+8), d->storage.start);
//}
//
///**
// *
// */
//template <class T>
//Deque<T>::Deque(const Deque<T>& copy)
//	: d(copy.d)
// {}
//
///**
// *
// */
//template <class T>
//const int Deque<T>::size() const {
//	return d->size();
//}
//
//} // namespace prism
//
//
//
//
//
//
//
//
//
//#endif /* PRSIM_DEQUE_H_ */
