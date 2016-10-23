/*
 * functor.h
 * v1
 *
 *  Created on: Sep 30, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_FUNCTOR_H_
#define PRISM_FUNCTOR_H_

namespace prism {

/**
 * Returns true if value is even, false otherwise.
 */
template <class T>
struct even {
	bool operator()(const T& value)
	{ return value % 2 == 0; }
};

/**
 * Returns true if a is greater than b, false otherwise.
 */
template <class T>
struct greater {
	bool operator()(const T& a, const T& b)
	{ return a > b; }
};

/**
 * Returns true if a is less than b, false otherwise.
 */
template <class T>
struct less {
	bool operator()(const T& a, const T& b)
	{ return a < b; }
};

/**
 * Returns true if \em i is odd, false otherwise.
 */
template <class T>
struct odd {
	bool operator()(const T& value)
	{ return value % 2 == 1; }
};

} // end namespace prism



#endif /* PRISM_FUNCTOR_H_ */
