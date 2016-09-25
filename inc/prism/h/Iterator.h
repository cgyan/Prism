/*
 * Iterator.h
 * v1
 *
 *  Created on: Jan 7, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_H_
#define PRISM_ITERATOR_H_

#include <prism/h/iterator_tags.h>
#include <prism/h/iterator_traits.h>
#include <prism/aux/iterator_aux.h>
#include <cstddef> // for std::ptrdiff_t

namespace prism {

/**
 * Moves the iterator forwards by numSteps (or backwards if numSteps is negative).
 */
template <class InputIterator>
void
advance(InputIterator& iterator, const int numSteps) {
	typedef typename prism::iterator_traits<InputIterator>::iterator_category it_cat;
	advance_aux(iterator, numSteps, it_cat());
}

/**
 * Returns the distance between two iterators.
 */
template <class InputIterator>
typename prism::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	typedef typename prism::iterator_traits<InputIterator>::iterator_category it_cat;
	return distance_aux(first, last, it_cat());
}

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class ForwardIterator {
public:
	typedef T								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef forward_iterator_tag 			iterator_category;
	typedef T& 								reference;
	typedef T* 								pointer;

	T * p;
	inline 									ForwardIterator() : p(0) {}
	inline 									ForwardIterator(T * p) : p(p) {}
	inline 									ForwardIterator(const ForwardIterator<T> & copy) { p = copy.p; }
	virtual									~ForwardIterator() {}
	virtual inline reference 				operator*() { return *p; }
	virtual inline pointer 					operator->() { return p; }
	virtual inline ForwardIterator & 		operator++() { p++; return *this; }
	virtual inline ForwardIterator   		operator++(int junk) { T* v=p; p++; return v; }
	virtual inline ForwardIterator & 		operator=(ForwardIterator rhs) { p = rhs.p; return *this;}
	virtual inline bool 					operator!=(const ForwardIterator rhs) { return p != rhs.p; }
	virtual inline bool 					operator==(const ForwardIterator rhs) { return p == rhs.p; }

	// Related non-members
	friend inline difference_type 			operator-(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs.p - rhs.p; }
	friend inline const bool 				operator<(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 				operator>(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 				operator<=(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 				operator>=(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs >= 0; }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class ForwardConstIterator {
public:
	typedef T								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef forward_iterator_tag 			iterator_category;
	typedef T& 								reference;
	typedef T* 								pointer;

	T * p;
	inline 									ForwardConstIterator() : p(0) {}
	inline 									ForwardConstIterator(T * p) : p(p) {}
	inline 									ForwardConstIterator(const ForwardConstIterator<T> & copy) { p = copy.p; }
	virtual									~ForwardConstIterator() {}
	virtual inline reference 				operator*() { return *p; }
	virtual inline pointer 					operator->() { return p; }
	virtual inline ForwardConstIterator & 	operator++() { p++; return *this; }
	virtual inline ForwardConstIterator   	operator++(int junk) { T* v=p; p++; return v; }
	virtual inline ForwardConstIterator & 	operator=(ForwardConstIterator rhs) { p = rhs.p; return *this;}
	virtual inline bool 					operator!=(const ForwardConstIterator rhs) { return p != rhs.p; }
	virtual inline bool 					operator==(const ForwardConstIterator rhs) { return p == rhs.p; }

	// Related non-members
	friend inline difference_type 			operator-(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs.p - rhs.p; }
	friend inline const bool 				operator<(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 				operator>(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 				operator<=(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 				operator>=(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs >= 0; }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class BidirectionalIterator : public ForwardIterator<T> {
public:
	typedef bidirectional_iterator_tag 		iterator_category;

	inline 									BidirectionalIterator() : ForwardIterator<T>() {}
	inline 									BidirectionalIterator(T * p) : ForwardIterator<T>(p) {}
	inline 									BidirectionalIterator(const BidirectionalIterator<T> & copy) : ForwardIterator<T>(copy) {}
	virtual									~BidirectionalIterator() {}
	virtual inline BidirectionalIterator & 	operator--() { this->p--; return *this; }
	virtual inline BidirectionalIterator  	operator--(int junk) { T* v=this->p; --this->p; return v; }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class BidirectionalConstIterator : public ForwardConstIterator<T> {
public:
	typedef bidirectional_iterator_tag 				iterator_category;

	inline 											BidirectionalConstIterator() : ForwardConstIterator<T>() {}
	inline 											BidirectionalConstIterator(T * p) : ForwardConstIterator<T>(p) {}
	inline 											BidirectionalConstIterator(const BidirectionalConstIterator<T> & copy) : ForwardConstIterator<T>(copy) {}
	virtual											~BidirectionalConstIterator() {}
	virtual inline BidirectionalConstIterator & 	operator--() { this->p--; return *this; }
	virtual inline BidirectionalConstIterator 	 	operator--(int junk) { T* v=this->p; --this->p; return v; }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class RandomAccessIterator : public BidirectionalIterator<T> {
public:
	typedef random_access_iterator_tag 	iterator_category;

	inline 								RandomAccessIterator() : BidirectionalIterator<T>() {}
	inline 								RandomAccessIterator(T * p) : BidirectionalIterator<T>(p) {}
	inline 								RandomAccessIterator(const RandomAccessIterator<T> & copy) : BidirectionalIterator<T>(copy) {}
	inline RandomAccessIterator			operator+(const int i) { return RandomAccessIterator(this->p+i); }
	inline RandomAccessIterator & 		operator+=(int i) { this->p += i; return *this; }
	inline RandomAccessIterator 		operator-(const int i) { return RandomAccessIterator(this->p-i); }
	inline RandomAccessIterator & 		operator-=(int i) { this->p -= i; return *this; }

	// Related non-members
	friend inline RandomAccessIterator 	operator+(const int i, RandomAccessIterator & it) { return RandomAccessIterator(it.p + i); }
	friend inline RandomAccessIterator 	operator-(const int i, RandomAccessIterator & it) { return RandomAccessIterator(it.p - i); }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class RandomAccessConstIterator : public BidirectionalConstIterator<T> {
public:
	typedef random_access_iterator_tag 			iterator_category;

	inline 										RandomAccessConstIterator() : BidirectionalConstIterator<T>() {}
	inline 										RandomAccessConstIterator(T * p) : BidirectionalConstIterator<T>(p) {}
	inline 										RandomAccessConstIterator(const RandomAccessConstIterator<T> & copy) : BidirectionalConstIterator<T>(copy) {}
	inline RandomAccessConstIterator			operator+(const int i) { return RandomAccessConstIterator(this->p+i); }
	inline RandomAccessConstIterator & 			operator+=(int i) { this->p += i; return *this; }
	inline RandomAccessConstIterator 			operator-(const int i) { return RandomAccessConstIterator(this->p-i); }
	inline RandomAccessConstIterator & 			operator-=(int i) { this->p -= i; return *this; }

	// Related non-members
	friend inline RandomAccessConstIterator 	operator+(const int i, RandomAccessConstIterator & it) { return RandomAccessConstIterator(it.p + i); }
	friend inline RandomAccessConstIterator 	operator-(const int i, RandomAccessConstIterator & it) { return RandomAccessConstIterator(it.p - i); }
};

}



#endif /* PRISM_ITERATOR_H_ */
