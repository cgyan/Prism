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
template <class T>
struct DequeBlock {
	T* start;
	T* finish;
	const int size = 8;
	DequeBlock() : start(0), finish(0) {}
	DequeBlock(const DequeBlock<T>& copy) : start(0), finish(0) {
		T* newStorage = new T[copy.finish-copy.start];
		prism::copy(copy.start, copy.finish, newStorage);
		delete []start;
		start = newStorage;
		finish = start + (copy.finish-copy.start);
	}
	DequeBlock<T>& operator=(const DequeBlock<T>& other) { *this = other; return *this; }
	~DequeBlock() { delete []start; start=0; finish=0; }
};
//============================================================
// DequeData
//============================================================
template <class T>
struct DequeData : public SharedData {
	struct memory {
		DequeBlock<T>* start;
		DequeBlock<T>* end;
		DequeBlock<T>* finish;

		memory() : start(0), end(0), finish(0)
		{}

		memory(const memory& copy) : start(0), end(0), finish(0)
		{
			DequeBlock<T>* newStorage = new DequeBlock<T>[copy.finish-copy.start];
			prism::copy(copy.start, copy.end, newStorage);
			delete []start;
			start = newStorage;
			end = start + (copy.end-copy.start);
			finish = start + (copy.finish-copy.start);
		}

		~memory() { delete []start; start=0; end=0; finish=0; }
	};
	memory storage;
};
//============================================================
// Deque
//============================================================
template <class T>
class Deque {
private:
	SharedDataPointer<DequeData<T>> d;
public:
	Deque();
	Deque(const Deque<T>& copy);
	~Deque();

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

}



#endif /* DEQUE_H_ */










