/*
 * Pair.h
 * v1
 *
 *  Created on: Aug 20, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_PAIR_H_
#define PRISM_PAIR_H_

#include <ostream>

namespace prism {

template <class T1, class T2>
struct Pair
{
	T1 first;
	T2 second;

	Pair() : first(T1()), second(T2()) {}

	Pair(const T1& val1, const T2& val2)  {
		first = val1;
		second = val2;
	}

	virtual ~Pair() {}

	friend
	const bool
	operator==(const Pair<T1,T2>& p1, const Pair<T1,T2>& p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

	friend
	const bool
	operator!=(const Pair<T1,T2>& p1, const Pair<T1,T2>& p2) {
		return !(p1==p2);
	}

	friend
	std::ostream & operator<<(std::ostream& out, const Pair& p) {
		out << "Pair [" << &p << "] first:" << p.first << " second:" << p.second;
		return out;
	}
};



} /* namespace prism */

#endif /* PRISM_PAIR_H_ */










