/*
 * Queue.h
 * v0.1
 *
 *  Created on: Jan 15, 2015
 *      Author: iainhemstock
 *
 *  Queue is a container adapter that is based on the FIFO (first in first out) principle. It allows items to be added only at
 *  the end of the queue and items can only be removed from the start of the queue. A Queue has no iterators.
 *  It uses a List as the underlying container by default and basically forwards all function calls onto the list. Actually any container
 *  can be used as the underlying container by passing it along at construction i.e. Queue<int, vector<int> >, as long as
 *  the following functions are defined:
 *  empty()
 *  size()
 *  front()
 *  back()
 *  push_back()
 *  pop_front()
 */

/*
 * todo add support for move constructor
 */

#ifndef PRISM_QUEUE_H_
#define PRISM_QUEUE_H_

#include <prism/h/Vector.h>
#include <ostream>

namespace prism {

template <class T, class ContainerType=Vector<T> >
class Queue {
private:
	ContainerType container;
public:
				Queue();

	T& 			back();
	const T& 	back() const;
	T 			dequeue();
	void 		enqueue(const T& value);
	T& 			front();
	const T& 	front() const;
	const bool 	isEmpty() const;
	T			pop();
	void		push(const T& value);
	const int 	size() const;
};

/**
 * Creates an empty queue.
 */
template <class T, class ContainerType>
Queue<T, ContainerType>::Queue() {

}

/**
 * Returns a reference to the last item in the queue.
 */
template <class T, class ContainerType>
T& Queue<T, ContainerType>::back() {
	return container.back();
}

/**
 * Returns a const reference to the last item in the queue.
 */
template <class T, class ContainerType>
const T& Queue<T, ContainerType>::back() const {
	return container.back();
}

/**
 * Removes and returns the item at the front of the queue.
 */
template <class T, class ContainerType>
T Queue<T, ContainerType>::dequeue() {
	T item = container.front();
	container.erase(container.begin());
	return item;
}

/**
 * Adds \em value at the end of the queue.
 */
template <class T, class ContainerType>
void Queue<T, ContainerType>::enqueue(const T& value) {
	container.push_back(value);
}

/**
 * Returns a reference to the item at the front of the queue.
 */
template <class T, class ContainerType>
T& Queue<T, ContainerType>::front() {
	return container.front();
}

/**
 * Returns a const reference to the item at the front of the queue.
 */
template <class T, class ContainerType>
const T& Queue<T, ContainerType>::front() const {
	return container.front();
}

/**
 * Returns true if the queue is empty, false otherwise.
 */
template <class T, class ContainerType>
const bool Queue<T, ContainerType>::isEmpty() const {
	return container.empty();
}

/**
 * Removes and returns the first item in the queue.
 * Equivalent to dequeue().
 */
template <class T, class ContainerType>
T Queue<T, ContainerType>::pop() {
	return dequeue();
}

/**
 * Adds \em value at the end of the queue.
 * Equivalent to enqueue().
 */
template <class T, class ContainerType>
void Queue<T, ContainerType>::push(const T& value) {
	return enqueue(value);
}

/**
 * Returns how many items are in the queue.
 */
template <class T, class ContainerType>
const int Queue<T, ContainerType>::size() const {
	return container.size();
}

}

#endif /* PRISM_QUEUE_H_ */
