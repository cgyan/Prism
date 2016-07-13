/*
 * Algorithms.h
 * v0.1
 *
 *  Created on: Jul 13, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHMS_H_
#define PRISM_ALGORITHMS_H_

#include <prism/Iterator>

namespace prism {

template <class InputIterator, class T>
int count(InputIterator first, InputIterator last, const T& value) {
	int c = 0;
	while (first++ != last) {
		if (*first == value) c++;
	}
	return c;
}

template <class InputIterator, class Predicate>
int count_if(InputIterator first, InputIterator last, Predicate pred) {
	int c = 0;
	while (first != last)  {
		if (pred(*first)) c++;
		first++;
	}
	return c;
}

template <class T>
void swap(T& a, T& b) { T temp=a; a=b; b=temp; }

}

#endif /* PRISM_ALGORITHMS_H_ */
