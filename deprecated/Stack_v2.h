/*
 * Stack.h
 * v2
 *
 *  Created on: Jan 23, 2015
 *      Author: iainhemstock
 */

/*
 * todo add support for initializer list constructor and move constructor
 * i.e. array<int> a = {1,2,3.4};
 */

#ifndef PRISM_STACK_H_
#define PRISM_STACK_H_

#include <prism/Vector>
#include <ostream>

namespace prism {

template <class T, class ContainerType=Vector<T> >
class Stack {
private:
	ContainerType container;
public:
				Stack();
	const bool 	empty() const;
	void 		pop();
	void 		push(const T& value);
	const int 	size() const;
	T& 			top();
	const T& 	top() const;

	const bool 					operator==(const Stack<T, ContainerType>& rhs);
	const bool 					operator!=(const Stack<T, ContainerType>& rhs);
	Stack<T, ContainerType>&	operator+=(const T& value);
	Stack<T, ContainerType>&	operator<<(const T& value);
};

/**
 * Constructs an empty stack.
 */
template <class T, class ContainerType>
Stack<T, ContainerType>::Stack() {

}

/**
 * Returns true if the stack containers no elements and false otherwise.
 * Added for STL-compatibility. Equivalent to isEmpty().
 */
template <class T, class ContainerType>
const bool Stack<T, ContainerType>::empty() const {
	return container.empty();
}

/**
 * Removes the last (top) element in the stack.
 */
template <class T, class ContainerType>
void Stack<T, ContainerType>::pop() {
	return container.pop_back();
}

/**
 * Adds \em value to the end (top) of the stack.
 */
template <class T, class ContainerType>
void Stack<T, ContainerType>::push(const T& value){
	container.push_back(value);
}

/**
 * Returns the number of elements currently in the stack.
 */
template <class T, class ContainerType>
const int Stack<T, ContainerType>::size() const {
	return container.size();
}

/**
 * Returns a reference to the last (top) element in the stack.
 */
template <class T, class ContainerType>
T& Stack<T, ContainerType>::top() {
	return container.back();
}

/**
 * Returns a const reference to the last (top) element in the stack.
 */
template <class T, class ContainerType>
const T& Stack<T, ContainerType>::top() const {
	return container.back();
}

/**
 * Compares this stack with \em rhs for equality. They are considered equal if they have the same number of
 * elements in the same order.
 */
template <class T, class ContainerType>
const bool Stack<T, ContainerType>::operator==(const Stack<T, ContainerType>& rhs) {
	return container == rhs.container;
}

/**
 * Compares this stack with \em rhs for equality. They are considered equal if they have the same number of
 * elements in the same order.
 */
template <class T, class ContainerType>
const bool Stack<T, ContainerType>::operator!=(const Stack<T, ContainerType>& rhs) {
	return container != rhs.container;
}

/**
 * Adds \em value to the end (top) of the stack.
 */
template <class T, class ContainerType>
Stack<T, ContainerType>& Stack<T, ContainerType>::operator+=(const T& value) {
	push(value);
	return *this;
}

/**
 * Adds \em value to the end (top) of the stack.
 */
template <class T, class ContainerType>
Stack<T, ContainerType>& Stack<T, ContainerType>::operator<<(const T& value) {
	push(value);
	return *this;
}

/**
 *
 */
//template <class T, class ContainerType>
//std::ostream & operator<<(std::ostream & out, const Stack<T, ContainerType> & stack) {
//	Stack<T, ContainerType> copy(stack);
//	out << "Stack [" << &stack << "] \n";
//	while (!copy.empty()) {
//		out << "--[] " << copy.top();
//		copy.pop();
//	}
//	return out;
//}

}

#endif /* PRISM_STACK_H_ */









