/*
 * Stack.h
 * v0.1
 *
 *  Created on: Jan 6, 2015
 *      Author: iainhemstock
 */

#ifndef STACK_
#define STACK_

#include <iostream>
#include "Iterator.h"

namespace prism {
namespace containers {

template <class T>
class Stack {
public:
	typedef RandomAccessIterator<T> 		iterator;
	typedef RandomAccessConstIterator<T> 	const_iterator;

private:
	T *				m_array;
	int 			m_size;
	int 			m_capacity;
	const int 		m_growth;

public:
					Stack();
					Stack(const int size, const T & value=T());
	virtual 		~Stack();
	iterator 		begin();
	const_iterator 	begin() const;
	const int 		capacity() const;
	const_iterator 	constBegin() const;
	const_iterator 	constEnd() const;
	iterator 		end();
	const_iterator 	end() const;
	const bool 		isEmpty() const;
	T 				pop();
	void 			push(const T & value);
	void 			reallocate(const int newCapacity);
	const int 		size() const;
	T & 			top();
	const T & 		top() const;

	T & 			operator[](const int index);
	const T & 		operator[](const int index) const;
};

/**
 * Constructs an empty stack.
 */
template <class T>
Stack<T>::Stack() : m_array(0), m_size(0), m_capacity(0), m_growth(2) {


}

/**
 * Constructs a stack of size \em size and each element is set to its default-constructed value.
 */
template <class T>
Stack<T>::Stack(const int size, const T & value) : m_array(new T[size]), m_size(size), m_capacity(m_size), m_growth(2) {
	for (int i=0; i<size; i++)
		m_array[i] = value;
}

/**
 * Destroys this stack.
 */
template <class T>
Stack<T>::~Stack() {
	if (m_array != 0) {
		delete [] m_array;
		m_array = 0;
		m_size = 0;
		m_capacity = 0;
	}
}

/**
 * Returns an iterator that points to the first element in the stack.
 */
template <class T>
typename Stack<T>::iterator Stack<T>::begin() {
	return iterator(m_array);
}

/**
 * Returns a const iterator that points to the first element in the stack.
 */
template <class T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
	return const_iterator(m_array);
}

/**
 * Returns the capacity of the stack. The capacity is theoretically how many elements can be stored in the stack
 * before a memory reallocation is triggered whilst the size is the actual number of elements in the stack.
 */
template <class T>
const int Stack<T>::capacity() const {
	return m_capacity;
}

/**
 * Returns a const iterator that points to the first element in the stack.
 */
template <class T>
typename Stack<T>::const_iterator Stack<T>::constBegin() const {
	return const_iterator(m_array);
}

/**
 * Returns a const iterator to the imaginary element one after the last element in the stack.
 */
template <class T>
typename Stack<T>::const_iterator Stack<T>::constEnd() const {
	return const_iterator(m_array+m_size);
}

/**
 * Returns an iterator to the imaginary element one after the last element in the stack.
 */
template <class T>
typename Stack<T>::iterator Stack<T>::end() {
	return iterator(m_array+m_size);
}

/**
 * Returns an iterator to the imaginary element one after the last element in the stack.
 */
template <class T>
typename Stack<T>::const_iterator Stack<T>::end() const {
	return const_iterator(m_array+m_size);
}

/**
 * Returns true if the stack is empty, false otherwise.
 */
template <class T>
const bool Stack<T>::isEmpty() const {
	return m_size == 0;
}

/**
 * Removes the top element from the stack and returns it.
 */
template <class T>
T Stack<T>::pop() {
	T t = top();
	--m_size;
	return t;
}

/**
 * Appends \em value to the top of the stack.
 */
template <class T>
void Stack<T>::push(const T & value) {
	if (m_array == 0) reallocate(1);
	if ((m_size+1) > m_capacity)
		reallocate(m_capacity*m_growth);

	m_array[m_size] = value;
	m_size++;
}

/**
 * Reallocates a new block of memory to be able to contain \em newCapacity elements.
 * if \em newCapacity is equal or less than the current capacity then nothing happens.
 * The existing elements in the stack are unaffected.
 * The capacity will only ever grow and will never shrink regardless of whether elements are removed or not.
 */
template <class T>
void Stack<T>::reallocate(const int newCapacity) {
	if (newCapacity <= m_capacity) return;

	T * newArray = new T[newCapacity];
	for (int i=0; i<m_size; i++)
		newArray[i] = m_array[i];

	delete [] m_array;
	m_array = 0;

	m_array = newArray;
	m_capacity = newCapacity;

}

/**
 * Returns the number of elements in the stack.
 */
template <class T>
const int Stack<T>::size() const {
	return m_size;
}

/**
 * Returns a reference to the element at the top of the stack.
 * The stack should not be empty when calling this function.
 */
template <class T>
T & Stack<T>::top() {
	return m_array[m_size-1];
}

/**
 * Returns a const reference to the element at the top of the stack.
 * The stack should not be empty when calling this function.
 */
template <class T>
const T & Stack<T>::top() const {
	return m_array[m_size-1];
}

/**
 * Returns a reference to the element at index \em index.
 */
template <class T>
T & Stack<T>::operator [](const int index) {
	return m_array[index];
}

/**
 * Returns a const reference to the element at index \em index.
 */
template <class T>
const T & Stack<T>::operator [](const int index) const {
	return m_array[index];
}

/**
 *
 */
template <class T>
std::ostream & operator<<(std::ostream & out, const Stack<T> & stack) {
	out << "------------------ \n";
	out << "Stack (" << &stack << ") size:" << stack.size() << " capacity:" << stack.capacity() << "\n";
	out << "------------------ \n";
	for (int i=0; i<stack.size(); i++)
		out << "[" << i << "] " << stack[i] << "\n";
	out << "------------------ \n";
	return out;
}

}
}

#endif /* STACK_ */
