/*
 * Algorithms.h
 * v0.1
 *
 *  Created on: Jul 13, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHMS_H_
#define PRISM_ALGORITHMS_H_

// todo remove this
#include <iostream>

namespace prism {

/**
 * Returns true if \em pred returns true for all the elements in the range \em [first,last)
 * or if the range is empty, and false otherwise.
 */
template <class InputIterator, class Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (!pred(*first)) return false;
		first++;
	}
	return true;
}

/**
 * Returns true if \em pred returns true for any of the elements in the range \em [first, last].
 */
template <class InputIterator, class Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (pred(*first)) return true;
		first++;
	}
	return false;
}

/**
 * Copies the elements in the range \em [first,last) into the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator otherFirst) {
	while (first != last) {
		*otherFirst = *first;
		first++;
		otherFirst++;
	}
	return otherFirst;
}

/**
 * Copies the elements in the range \em [first,last) for
 * which \em pred returns true to the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred) {
	while (first != last) {
		if (pred(*first)) {
			*otherFirst = *first;
			otherFirst++;
		}
		first++;

	}
	return otherFirst;
}

/**
 * Returns the number of elements in the range \em [first,last) that compare equal to \em value.
 */
template <class InputIterator, class T>
int count(InputIterator first, InputIterator last, const T& value) {
	int c = 0;
	while (first++ != last) {
		if (*first == value) c++;
	}
	return c;
}

/**
 * Returns the number of elements in the range \em [first,last) for which \em pred is true.
 */
template <class InputIterator, class Predicate>
int count_if(InputIterator first, InputIterator last, Predicate pred) {
	int c = 0;
	while (first != last)  {
		if (pred(*first)) c++;
		first++;
	}
	return c;
}

/**
 * Compares the elements in the range \em [first1,last1) with those in the
 * range beginning at \em first2, and returns true if all of the
 * elements in both ranges match. \n
 * The elements are compared using operator==.
 */
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst) {
	while (first != last) {
		if (!(*first == *otherFirst)) return false;
		first++;
		otherFirst++;
	}
	return true;
}

/**
 * Assigns \em value to all the elements in the range \em [first,last).
 */
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
	while (first != last) {
		*first = value;
		std::cout << *first << std::endl;
		first++;
	}
}

/**
 * Assigns \em value to the first \em n elements of the sequence pointed by \em first.
 */
template <class ForwardIterator, class T>
void fill_n(ForwardIterator first, int size, const T& value) {
	while (size > 0) {
		*first = value;
		size--;
		first++;
	}
}

/**
 * Returns an iterator to the first element in the range \em [first,last)
 * that compares equal to \em value. If no such element is found, the function returns \em last.
 */
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
	while (first != last) {
		if (*first == value) return first;
		first++;
	}
	return last;
}

/**
 * Returns an iterator to the first element in the range \em [first,last) for which \em pred returns true.
 * If no such element is found, the function returns \em last.
 */
template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if(pred(*first)) return first;
		first++;
	}
	return last;
}

/**
 * Applies function \em func to each of the elements in the range \em [first,last).
 */
template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function func) {
	while (first != last) {
		func(*first);
		first++;
	}
	return func;
}

/**
 *
 */
template <class T>
const T& max(const T& a, const T& b) {
	if (b > a) return b;
	return a;
}

/**
 *
 */
template <class T>
const T& min(const T& a, const T& b) {
	if (b > a) return a;
	return b;
}

/**
 * Exchanges the values of \em a and \em b.
 */
template <class T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

}

#endif /* PRISM_ALGORITHMS_H_ */
