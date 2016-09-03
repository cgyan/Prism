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
#include <ostream>
#include <cstddef> // for std::ptrdiff_t
using namespace std;

namespace prism {
static const int prism_deque_bucket_size = 8;
//================================================================================
// DequeIterator
//================================================================================
// \cond DO_NOT_DOCUMENT
template <class T>
class DequeIterator {
	typedef DequeIterator<T> 				iterator;
	typedef T								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef random_access_iterator_tag 		iterator_category;
	typedef T& 								reference;
	typedef T* 								pointer;
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

	T& operator*() {
		return *current;
	}

	T* operator->() {
		return current;
	}

	iterator& operator+=(const int n)
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

	iterator operator+(const int n) {
		iterator tmp = *this;
		return tmp += n;
	}

	iterator& operator-=(const int n) {
		return *this += -n;
	}

	iterator operator-(const int n) {
		iterator tmp = *this;
		return tmp -= n;
	}

	iterator& operator++() {
		return *this += 1;
	}

	iterator operator++(int junk) {
		iterator tmp(*this);
		*this = *this += 1;
		return tmp;
	}

	iterator& operator--() {
		return *this -= 1;
	}

	iterator operator--(int junk) {
		iterator tmp(*this);
		*this = *this -= 1;
		return tmp;
	}

	iterator& operator=(const iterator& rhs) {
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
	friend const bool operator==(const iterator& it1, const iterator& it2) {
		return it1.buckets == it2.buckets &&
				it1.current == it2.current &&
				it1.start == it2.start &&
				it1.end == it2.end;
	}

	friend const bool operator!=(const iterator& it1, const iterator& it2) {
		return !(it1==it2);
	}

	friend const int operator-(const iterator& lhs, const iterator& rhs) {
		return prism_deque_bucket_size *
				(lhs.buckets-rhs.buckets-1) +
				lhs.current-lhs.start +
				rhs.end-rhs.current;
	}

	friend const bool operator<(const iterator& lhs, const iterator& rhs) {
		return lhs-rhs < 0;
	}

	friend const bool operator>(const iterator& lhs, const iterator& rhs) {
		return lhs-rhs > 0;
	}

	friend const bool operator<=(const iterator& lhs, const iterator& rhs) {
		return lhs-rhs <= 0;
	}

	friend const bool operator>=(const iterator& lhs, const iterator& rhs) {
		return lhs-rhs >= 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const DequeIterator<T>& it) {
		out << "iterator: current:" << it.current-it.start;
		return out;
	}
};
// \endcond
//struct map {
//	int** data;
//	int mapSize;
//	int bucketSize;
//
//	map() : data(nullptr), mapSize(2), bucketSize(8) {
//		data = new int*[mapSize];
//
//		int* block = new int[bucketSize];
//		block[4] = 4; block[5] = 5; block[6] = 6; block[7] = 7;
//		data[0] = block;
//
//		block = new int[8];
//		block[0] = 10; block[1] = 11; block[2] = 12; block[3] = 13;
//		block[4] = 14; block[5] = 15; block[6] = 16; block[7] = 17;
//		data[1] = block;
//	}
//
//};
//================================================================================
// DequeData
//================================================================================
// \cond DO_NOT_DOCUMENT
template <class T>
struct DequeData : public SharedData {
	typedef DequeIterator<T> iterator;
//	map map;
	struct memory {
		T** start;
		T** finish;

		memory() : start(0), finish(0)
		{}

		~memory() {
			deallocateStorage();
		};

		T* allocateBucket() {
			return new T[prism_deque_bucket_size];
		}

		T** allocateStorage(const int size) {
			return new T*[size];
		}

		void createBuckets(T** start, T** finish) {
			while (start != finish) {
				*start = allocateBucket();
				++start;
			}
		}

		void deallocateBucket(T* bucket) {
			delete bucket;
		}

		void deallocateStorage() {
			if (start != nullptr) {
				for (int i=0; i<finish-start; i++)
					deallocateBucket(start[i]);
				delete []start;
			}
		}
	};

	memory 		storage;
	iterator 	begin;
	iterator 	end;

	DequeData();
	~DequeData();

	const int 	capacity() const;
	void 		initializeStorage(const int numElements);
	const int 	size() const;
};
// \endcond
/**
 *
 */
template <class T>
DequeData<T>::DequeData() {
	initializeStorage(0);
}

/**
 *
 */
template <class T>
DequeData<T>::~DequeData() {

}

/**
 *
 */
template <class T>
const int DequeData<T>::capacity() const {
	return (storage.finish-storage.start) * prism_deque_bucket_size;
}

/**
 * Allocates storage, creates buckets and sets the iterators accordingly.
 * If numElements is 0 then one bucket is created in preparation for future elements.
 * If numElements is greater than 0 then enough buckets to hold the elements are created.
 * The new elements start from a position such that there are equal free spaces at the
 * start and end of the storage.
 */
template <class T>
void DequeData<T>::initializeStorage(const int numElements) {
	int numBuckets = numElements / prism_deque_bucket_size + 1;

	storage.start = storage.allocateStorage(numBuckets);
	storage.finish = storage.start + numBuckets;

	T** startBucket = storage.start;
	T** endBucket = startBucket + numBuckets;
	storage.createBuckets(startBucket, endBucket);

	begin.buckets = startBucket;
	begin.start = *startBucket;
	begin.current = begin.start
			+ (numBuckets * prism_deque_bucket_size) / 2
			- numElements / 2;
	begin.end = begin.start + prism_deque_bucket_size;
	end = begin + numElements;
}

/**
 *
 */
template <class T>
const int DequeData<T>::size() const {
	return end-begin;
}
//================================================================================
// Deque
//================================================================================
template <class T>
class Deque {
	typedef DequeIterator<T> iterator;
private:
	SharedDataPointer<DequeData<T>> d;
public:
	Deque();
	Deque(const Deque<T>& copy);
	~Deque();

	iterator 	begin() const;
	const int 	capacity() const;
	iterator 	end() const;
	iterator	insert(iterator& pos, const int count, const T& value);
	const int 	size() const;

	friend std::ostream& operator<<(std::ostream& out, const Deque<T>& d) {
		out << "Deque [" << &d << "]"
				" size=" << d.size() <<
				" capacity=" << d.capacity() <<
				" numBuckets=" << d.d->storage.finish-d.d->storage.start << endl;
		out << "----begin: " << d.d->begin << endl;
		out << "----end: " << d.d->end;
		return out;
	}
};

/**
 *
 */
template <class T>
Deque<T>::Deque()
	: d(new DequeData<T>)
{


}

/**
 *
 */
template <class T>
Deque<T>::Deque(const Deque<T>& copy)
	: d(copy.d)
{}

/**
 *
 */
template <class T>
Deque<T>::~Deque() {

}

/**
 *
 */
template <class T>
DequeIterator<T> Deque<T>::begin() const {
	return d->begin;
}

/**
 *
 */
template <class T>
const int Deque<T>::capacity() const {
	return d->capacity();
}

/**
 *
 */
template <class T>
DequeIterator<T> Deque<T>::end() const {
	return d->end;
}

/**
 *
 */
template <class T>
DequeIterator<T> Deque<T>::insert(iterator& pos, const int count, const T& value) {

}

/**
 *
 */
template <class T>
const int Deque<T>::size() const {
	return d->size();
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
