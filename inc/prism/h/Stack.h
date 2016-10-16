/*
 * Stack.h
 * v3
 *
 *  Created on: Aug 8, 2016
 *      Author: iainhemstock
 */

#ifndef STACK_H_
#define STACK_H_

#include <prism/h/algorithm.h>
#include <prism/h/Vector.h>
#include <prism/h/List.h>
#include <prism/h/SharedData.h>
#include <prism/h/SharedDataPointer.h>
#include <ostream>

namespace prism {
// ========================================================================
// StackData
// ========================================================================
// \cond DO_NOT_DOCUMENT
template <class T>
struct StackData : public SharedData {
	struct memory {
		T * start;
		T * end;
		T * finish;
		const int exponent;

		memory() : start(0), end(0), finish(0), exponent(2) {
			// does nothing
		}

		memory(const memory & copy) : start(0), end(0), finish(0), exponent(copy.exponent){
			allocateAndTransfer(copy.finish-copy.start, copy.start, copy.end);
		}

		~memory() {
			delete []start; start = 0; end = 0; finish = 0;
		}

		// allocates new storage and transfers existing data from the range [pStart,pEnd]
		// to the new storage
		void allocateAndTransfer(int capacity, T* pStart, T* pEnd) {
			T* newStorage = new T[capacity];
			prism::copy(pStart, pEnd, newStorage);

			delete []start;
			start = newStorage;
			end = start + (pEnd-pStart);
			finish = start + capacity;
		}

		void reserve(const int newCapacity) {
			allocateAndTransfer(newCapacity, start, end);
		}
	};
	memory storage;
};
// \endcond
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
	SharedDataPointer< StackData<T> > d;
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
	Stack &		operator=(const Stack<T> & other);

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

	friend std::ostream & operator<<(std::ostream & out, const Stack<T> & stack) {
		out << "Stack [" << &stack << "] size=" << stack.size() << " capacity=" << stack.capacity() << "\n";
		for (int i=0; i<stack.size(); i++)
			out << "--[" << i << "] " << *(stack.d->storage.start+i) << "\n";
		return out;
	}
};

} // end namespace prism

#include <prism/h/priv/Stack_priv.h>

#endif /* STACK_H_ */
















