/*
 * Deque.h
 * v0.*
 *
 *  Created on: Aug 20, 2016
 *      Author: iainhemstock
 *
	bool size() const { return first.size + (buckets.size()- 2) * SIZE + last.size; }

	T& operator[](size_t i) {
	if (i < first.size) { return first[SIZE - i]; }

	size_t const correctedIndex = i - first.size;
	return buckets[correctedIndex / SIZE][correctedIndex % SIZE];
}
 */
/*
----------------------------------------
deque_base class line 896
----------------------------------------
line 1058
template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::iterator
__deque_base<_Tp, _Allocator>::begin() _NOEXCEPT
{
    __map_pointer __mp = __map_.begin() + __start_ / __block_size;
    return iterator(__mp, __map_.empty() ? 0 : *__mp + __start_ % __block_size);
}
----------------------------------------
template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::iterator
__deque_base<_Tp, _Allocator>::end() _NOEXCEPT
{
    size_type __p = size() + __start_;
    __map_pointer __mp = __map_.begin() + __p / __block_size;
    return iterator(__mp, __map_.empty() ? 0 : *__mp + __p % __block_size);
}
----------------------------------------
line 266
template <class _ValueType, class _Pointer, class _Reference, class _MapPointer,
          class _DiffType, _DiffType _BlockSize>
class _LIBCPP_TYPE_VIS_ONLY __deque_iterator {}
----------------------------------------
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include <prism/SharedData>
#include <prism/SharedDataPointer>
#include <prism/algorithms>
#include <ostream>

namespace prism {
//============================================================
// DequeBlock
//============================================================
// \cond DO_NOT_DOCUMENT
template <class T>
struct DequeBlock {
	static const int size = 8; // size of each internal block
	struct chunk {
		T* start; // start of the storage
		T* finish;// the end of the storage

		chunk() : start(0), finish(0)
		{
			// does nothing
		}

		chunk(const chunk& copy) : start(0), finish(0)
		{
			allocateAndTransfer(copy.start, copy.finish);
		}

		chunk& operator=(const chunk& other)
		{
			if (*this == other) return *this;
			allocateAndTransfer(other.start, other.finish);
			return *this;
		}

		~chunk()
		{
			delete []start; start=0; finish=0;
		}

		void allocateAndTransfer(T* pStart, T* pEnd)
		{
			T* newStorage = new T[size];
			prism::copy(pStart, pEnd, newStorage);
			delete []start;
			start = newStorage;
			finish = start + size;
		}

		friend bool operator==(const chunk& c1, const chunk& c2) {
			return c1.start == c2.start && c1.finish == c2.finish;
		}
	};
	chunk block;

};
// \endcond
//============================================================
// DequeIterator
// needs to know about:
//		a) DequeBlock array, b) DequeBlock size, c) value type (T)
//============================================================
// \cond DO_NOT_DOCUMENT
template <class T>
class DequeIterator {
private:


};
// \endcond
//============================================================
// DequeData
//============================================================
// \cond DO_NOT_DOCUMENT
template <class T>
struct DequeData : public SharedData {
	struct memory {
		T** start; // pointer to array of T
		T** finish;
		DequeIterator<T> begin;
		DequeIterator<T> end;

		memory() : start(0), finish(0)
		{
			// does nothing
		}

		memory(const memory& copy) : start(0), finish(0)
		{
			allocateAndTransfer(copy.finish-copy.start, copy.start, copy.finish);
		}

		~memory()
		{
			delete []start; start=0; finish=0;
		}

		void allocateAndTransfer(const int capacity, DequeBlock<T>* pStart, DequeBlock<T>* pEnd) {
			DequeBlock<T>* newStorage = new DequeBlock<T>[capacity];
			prism::copy(pStart, pEnd, newStorage);
			delete []start;
			start = newStorage;
			finish = start + capacity;
		}
	};
	memory storage;
};
// \endcond
//============================================================
// Deque
//============================================================
template <class T>
class Deque {
public:
	typedef DequeIterator<T> 					iterator;
//	typedef DequeConstIterator<T>				const_iterator;
//	typedef typename iterator::reference		reference;
//	typedef typename const_iterator::reference	const_reference;
//	typedef typename iterator::pointer			pointer;
//	typedef typename const_iterator::pointer	const_pointer;
//	typedef typename iterator::value_type		value_type;
//	typedef typename iterator::difference_type	difference_type;
//	typedef int									size_type;
private:
	SharedDataPointer<DequeData<T>> d;
public:
	Deque();
	Deque(const Deque<T>& copy);
	~Deque();

	iterator begin();

};

/**
 *
 */
template <class T>
Deque<T>::Deque()
	: d(new DequeData<T>)
{}

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
 * @return Returns an iterator pointing to the first element.
 */
template <class T>
typename Deque<T>::iterator Deque<T>::begin() {
	return iterator();
}

}



#endif /* DEQUE_H_ */










