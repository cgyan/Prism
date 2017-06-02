/*
 * pair.h
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
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair() : first(T1()), second(T2()) {}

	pair(const T1& val1, const T2& val2)
	: first(val1), second(val2)
	{}

	virtual ~pair() {}

	friend
	const bool
	operator==(const pair<T1,T2>& p1, const pair<T1,T2>& p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

	friend
	const bool
	operator!=(const pair<T1,T2>& p1, const pair<T1,T2>& p2) {
		return !(p1==p2);
	}

	pair<T1,T2>&
	operator=(const pair& rhs) {
		if (*this != rhs) {
			first = rhs.first;
			second = rhs.second;
		}
		return *this;
	}

	template <class T3, class T4>
	pair<T1,T2>&
	operator=(const pair<T3,T4>& rhs) {
		if (*this != rhs) {
			first = rhs.first;
			second = rhs.second;
		}
		return *this;
	}

	friend
	std::ostream & operator<<(std::ostream& out, const pair& p) {
		out << "Pair [" << &p << "] first:" << p.first << " second:" << p.second;
		return out;
	}
};



} /* namespace prism */

#endif /* PRISM_PAIR_H_ */










