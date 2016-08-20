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

		memory() : start(0), end(0), finish(0) {}
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
	DequeData<T>* d;
public:
	Deque();
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
Deque<T>::~Deque() {

}

}



#endif /* DEQUE_H_ */










