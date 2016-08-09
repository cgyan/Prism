/*
 * Stack.h
 * v3
 *
 *  Created on: Aug 8, 2016
 *      Author: iainhemstock
 */

#ifndef STACK_H_
#define STACK_H_

#include <prism/algorithms>
#include <prism/Vector>
#include <prism/List>

namespace prism {
// ========================================================================
// StackData
// ========================================================================
template <class T>
struct StackData {
	struct memory {
		T * start;
		T * end;
		T * finish;
		const int exponent;
		memory() : start(0), end(0), finish(0), exponent(2) {}
		~memory() { delete []start; start = 0; end = 0; finish = 0; }
	};
	memory storage;
};
// ========================================================================
// Stack
// ========================================================================
/*!
 * A Stack is an abstract data type (ADT) meaning it can be implemented in different ways (vectors, lists etc).
 * This class internally is implemented with a Vector-like structure so that the memory allocation
 * and deallocation is handled.\n
 * A Stack is a LIFO (last-in-first-out) container meaning that a new element can only be added and removed
 * at the end (or top). The common analogy is a stack of plates where a new plate is added to the top of the
 * stack and is the first one to be removed. This implies that in order to retrieve a particular plate in the
 * middle of the stack, the other plates on top must first be removed.
 */
template <class T>
class Stack {
private:
	StackData<T> * d;
public:
	Stack();
	Stack(const Stack<T> & copy);
	~Stack();

	const int	capacity() const;
	const bool 	empty() const;
	void 		push(const T& value);
	void 		pop();
	void 		reserve(const int newCapacity);
	const int 	size() const;
	void		squeeze();
	const T& 	top() const;
	T& 			top();
	List<T>		toList() const;
	Vector<T>	toVector() const;

	void		operator+=(const T& value);
	Stack<T> &	operator<<(const T& value);

	// related non-members
	friend const bool operator==(const Stack<T> & s1, const Stack<T> & s2) {
		if (s1.size() != s2.size()) return false;
		return prism::equal(s1.d->storage.start, s1.d->storage.end, s2.d->storage.start);
	}

	friend const bool operator!=(const Stack<T> & s1, const Stack<T> & s2) {
		return !(s1==s2);
	}





};

/**
 * Creates an empty stack.
 */
template <class T>
Stack<T>::Stack()
	: d(new StackData<T>)
{}

/**
 * Creates a new stack which is a copy of \em copy
 */
template <class T>
Stack<T>::Stack(const Stack<T> & copy)
	: d(new StackData<T>)
{
	if (!copy.empty()) {
		reserve(copy.capacity());
		prism::copy(copy.d->storage.start, copy.d->storage.end, this->d->storage.start);
		d->storage.end = d->storage.start + copy.size();
	}

}

/**
 * Destroys this stack.
 */
template <class T>
Stack<T>::~Stack() {
	delete d;
}

/**
 * @return Returns the capacity of this stack.
 */
template <class T>
const int Stack<T>::capacity() const {
	return d->storage.finish - d->storage.start;
}

/**
 * @return Returns true if this stack contains no elements, false otherwise.
 */
template <class T>
const bool Stack<T>::empty() const {
	return d->storage.start == d->storage.end;
}

/**
 * Removes the last element from the stack.
 */
template <class T>
void Stack<T>::pop() {
	--d->storage.end;
}

/**
 * Appends \em value to the end (top) of the stack.
 */
template <class T>
void Stack<T>::push(const T& value) {
	int s = size();
	if (s + 1 > capacity())
		reserve((s+1)*d->storage.exponent);

	*(d->storage.end) = value;
	++d->storage.end;
}

/**
 * Reserves enough memory for the stack to contain \em newCapacity characters
 * i.e. newCapacity * sizeof(T). The capacity can only grow and will not
 * lessen. Only squeeze() can alter the capacity to a lower amount. If \em newCapacity
 * is less than or equal to the current capacity then nothing changes. Any existing
 * values in the stack are not affected by this function.
 */
template <class T>
void Stack<T>::reserve(const int newCapacity) {
	if (newCapacity > d->storage.finish-d->storage.start) {

		T * newStorage = new T[newCapacity];
		if (!empty())
			prism::copy(d->storage.start, d->storage.end, newStorage);

		int s = size();
		delete [] d->storage.start;
		d->storage.start = newStorage;
		d->storage.end = d->storage.start + s;
		d->storage.finish = d->storage.start + newCapacity;
	}
}

/**
 * @return Returns the number of elements contained in the stack.
 */
template <class T>
const int Stack<T>::size() const {
	return d->storage.end - d->storage.start;
}

/**
 * Destroys any unused memory currently held by the stack. For example, if the stack has a capacity
 * of 10 and a size of 4, squeeze() will release the extra memory of the capacity resulting in a
 * capacity and size of 4. If size() and capacity() are already equal then nothing happens.
 */
template <class T>
void Stack<T>::squeeze() {
	if (d->storage.finish - d->storage.start > 0) {
		int s = size();
		T * newStorage = new T[s];
		prism::copy(d->storage.start, d->storage.end, newStorage);
		delete []d->storage.start;
		d->storage.start = newStorage;
		d->storage.end = d->storage.start + s;
		d->storage.finish = d->storage.end;
	}
}

/**
 * @return Returns the last (top) value contained in the stack.
 */
template <class T>
const T& Stack<T>::top() const {
	return *(d->storage.end-1);
}

/**
 * @return Returns the last (top) value contained in the stack.
 */
template <class T>
T& Stack<T>::top() {
	return *(d->storage.end-1);
}

/**
 * @return Returns this stack as a List. The stack remains unaffected.
 */
template <class T>
List<T> Stack<T>::toList() const {
	List<T> list;
	T * it = d->storage.start;

	while (it != d->storage.end)
		list << *it++;

	return list;
}

/**
 * @return Returns this stack as a Vector. The stack remains unaffected.
 */
template <class T>
Vector<T> Stack<T>::toVector() const {
	Vector<T> v;
	v.resize(this->size());
	prism::copy(d->storage.start, d->storage.end, v.data());

	return v;
}

/**
 * Appends \em value to the end (top) of the stack. Equivalent to push().
 */
template <class T>
void Stack<T>::operator+=(const T& value) {
	push(value);
}

/**
 * Appends \em value to the end (top) of the stack. Equivalent to push().
 */
template <class T>
Stack<T> & Stack<T>::operator<<(const T& value) {
	push(value);
	return *this;
}

}



#endif /* STACK_H_ */
















