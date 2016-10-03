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
#include <prism/h/utility.h>
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
 * Returns an iterator pointing to the beginning of \em con.
 */
template <class Container>
auto
begin(Container& con) -> decltype (con.begin())
{ return con.begin(); }

/**
 * Returns a const iterator pointing to the beginning of \em con.
 */
template <class Container>
auto
begin(const Container& con) -> decltype (con.begin())
{ return con.begin(); }

/**
 * Array specialization.
 */
template <class T, int Size>
T*
begin(T(&array)[Size])
{ return array; }

/**
 * Returns the distance between two iterators.
 */
template <class InputIterator>
typename prism::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	typedef typename prism::iterator_traits<InputIterator>::iterator_category it_cat;
	return distance_aux(first, last, it_cat());
}

/**
 * Returns an iterator pointing to the end of \em con.
 */
template <class Container>
auto
end(Container& con) -> decltype (con.end())
{ return con.end(); }

/**
 * Returns a const iterator pointing to the end of \em con.
 */
template <class Container>
auto
end(const Container& con) -> decltype (con.end())
{ return con.end(); }

/**
 * Array specialization.
 */
template <class T, int Size>
T*
end(T(&array)[Size])
{ return array+Size; }

/**
 *
 */
template <class InputIterator, class Container>
const bool
has_next(InputIterator& it, Container& con)
{ return !(it == con.end()); }

/**
 *
 */
template <class InputIterator, class Container>
const bool
has_previous(InputIterator& it, Container& con)
{ return !(it == con.begin()); }

/**
 * Advances the iterator \em it by \em numSteps (1 by default).
 * Returns an iterator.
 */
template <class ForwardIterator>
ForwardIterator
next(ForwardIterator it, int numSteps=1) {
	typedef typename prism::iterator_traits<ForwardIterator>::iterator_category it_cat;
	prism::advance_aux(it, numSteps, it_cat());
	return it;
}

/**
 * Moves the iterator \em it back by \em numSteps.
 * Returns an iterator.
 */
template <class BidirectionalIterator>
BidirectionalIterator
previous(BidirectionalIterator it, int numSteps=1)
{ return prism::previous_aux(it, numSteps); }

/******************************************************************************
 * SequenceIterator (random access)
 * --- for containers that hold their elements in a continuous sequence of memory
 * --- like Vector, String etc
 *****************************************************************************/
template <class T, bool isConst>
struct SequenceIterator {
	typedef T 							value_type;
	typedef const T* 					const_pointer;
	typedef const T&					const_reference;
	typedef random_access_iterator_tag 	iterator_category;
	typedef size_t 						size_type;
	typedef std::ptrdiff_t 				difference_type;
	typedef SequenceIterator<T, false>	iterator;
	typedef SequenceIterator<T, true>	const_iterator;
	typedef typename prism::conditional_type<isConst, const T*, T*>::type 				pointer;
	typedef typename prism::conditional_type<isConst, const T&, T&>::type 			reference;
	typedef typename prism::conditional_type<isConst, const_iterator, iterator>::type 	Self;

	pointer p;

	SequenceIterator()
	: p(nullptr)
	{}

	SequenceIterator(pointer p)
	: p(p)
	{}

	// only allow non-const iterator to be passed as arg.
	SequenceIterator(const iterator& copy)
	: p(copy.p)
	{}

	~SequenceIterator()
	{}

	reference
	operator*()
	{ return *p; }

	pointer
	operator->()
	{ return p; }

	Self&
	operator++()
	{ p++; return *this; }

	Self
	operator++(int junk)
	{ pointer tmp = p; p++; return tmp; }

	Self&
	operator--()
	{ p--; return *this; }

	Self
	operator--(int junk)
	{ pointer tmp = p; p--; return tmp; }

	Self&
	operator+=(const int i)
	{ p += i; return *this; }

	Self&
	operator-=(const int i)
	{ return *this += -i; }

	Self
	operator+(const int i)
	{ Self tmp = *this; return tmp += i; }

	Self
	operator-(const int i)
	{ Self tmp = *this; return tmp += -i; }

	difference_type
	operator-(const Self& rhs)
	{ return static_cast<difference_type>(this->p - rhs.p); }

	Self&
	operator=(const iterator& it)
	{ if (it.p != this->p) this->p = it.p; return *this; }

	const bool
	operator==(const Self& rhs)
	{ return this->p == rhs.p; }

	const bool
	operator!=(const Self& rhs)
	{ return !(*this == rhs); }

	const bool
	operator<(const Self& rhs)
	{ return this->p < rhs.p; }

	const bool
	operator>(const Self& rhs)
	{ return this->p > rhs.p; }

	const bool
	operator<=(const Self& rhs)
	{ return this->p <= rhs.p; }

	const bool
	operator>=(const Self& rhs)
	{ return this->p >= rhs.p; }
};

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
//template <class T>
//class ForwardIterator {
//public:
//	typedef T								value_type;
//	typedef std::ptrdiff_t 					difference_type;
//	typedef forward_iterator_tag 			iterator_category;
//	typedef T& 								reference;
//	typedef T* 								pointer;
//
//	T * p;
//	inline 									ForwardIterator() : p(0) {}
//	inline 									ForwardIterator(T * p) : p(p) {}
//	inline 									ForwardIterator(const ForwardIterator<T> & copy) { p = copy.p; }
//	virtual									~ForwardIterator() {}
//	virtual inline reference 				operator*() { return *p; }
//	virtual inline pointer 					operator->() { return p; }
//	virtual inline ForwardIterator & 		operator++() { p++; return *this; }
//	virtual inline ForwardIterator   		operator++(int junk) { T* v=p; p++; return v; }
//	virtual inline ForwardIterator & 		operator=(ForwardIterator rhs) { p = rhs.p; return *this;}
//	virtual inline bool 					operator!=(const ForwardIterator rhs) { return p != rhs.p; }
//	virtual inline bool 					operator==(const ForwardIterator rhs) { return p == rhs.p; }
//
//	// Related non-members
//	friend inline difference_type 			operator-(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs.p - rhs.p; }
//	friend inline const bool 				operator<(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs < 0; }
//	friend inline const bool 				operator>(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs > 0; }
//	friend inline const bool 				operator<=(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs <= 0; }
//	friend inline const bool 				operator>=(const ForwardIterator & lhs, const ForwardIterator & rhs) { return lhs-rhs >= 0; }
//};
//
///****************************************************************************************************************
// *
// ****************************************************************************************************************/
//template <class T>
//class ForwardConstIterator {
//public:
//	typedef T								value_type;
//	typedef std::ptrdiff_t 					difference_type;
//	typedef forward_iterator_tag 			iterator_category;
//	typedef T& 								reference;
//	typedef T* 								pointer;
//
//	T * p;
//	inline 									ForwardConstIterator() : p(0) {}
//	inline 									ForwardConstIterator(T * p) : p(p) {}
//	inline 									ForwardConstIterator(const ForwardConstIterator<T> & copy) { p = copy.p; }
//	virtual									~ForwardConstIterator() {}
//	virtual inline reference 				operator*() { return *p; }
//	virtual inline pointer 					operator->() { return p; }
//	virtual inline ForwardConstIterator & 	operator++() { p++; return *this; }
//	virtual inline ForwardConstIterator   	operator++(int junk) { T* v=p; p++; return v; }
//	virtual inline ForwardConstIterator & 	operator=(ForwardConstIterator rhs) { p = rhs.p; return *this;}
//	virtual inline bool 					operator!=(const ForwardConstIterator rhs) { return p != rhs.p; }
//	virtual inline bool 					operator==(const ForwardConstIterator rhs) { return p == rhs.p; }
//
//	// Related non-members
//	friend inline difference_type 			operator-(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs.p - rhs.p; }
//	friend inline const bool 				operator<(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs < 0; }
//	friend inline const bool 				operator>(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs > 0; }
//	friend inline const bool 				operator<=(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs <= 0; }
//	friend inline const bool 				operator>=(const ForwardConstIterator & lhs, const ForwardConstIterator & rhs) { return lhs-rhs >= 0; }
//};
//
///****************************************************************************************************************
// *
// ****************************************************************************************************************/
//template <class T>
//class BidirectionalIterator : public ForwardIterator<T> {
//public:
//	typedef bidirectional_iterator_tag 		iterator_category;
//
//	inline 									BidirectionalIterator() : ForwardIterator<T>() {}
//	inline 									BidirectionalIterator(T * p) : ForwardIterator<T>(p) {}
//	inline 									BidirectionalIterator(const BidirectionalIterator<T> & copy) : ForwardIterator<T>(copy) {}
//	virtual									~BidirectionalIterator() {}
//	virtual inline BidirectionalIterator & 	operator--() { this->p--; return *this; }
//	virtual inline BidirectionalIterator  	operator--(int junk) { T* v=this->p; --this->p; return v; }
//};
//
///****************************************************************************************************************
// *
// ****************************************************************************************************************/
//template <class T>
//class BidirectionalConstIterator : public ForwardConstIterator<T> {
//public:
//	typedef bidirectional_iterator_tag 				iterator_category;
//
//	inline 											BidirectionalConstIterator() : ForwardConstIterator<T>() {}
//	inline 											BidirectionalConstIterator(T * p) : ForwardConstIterator<T>(p) {}
//	inline 											BidirectionalConstIterator(const BidirectionalConstIterator<T> & copy) : ForwardConstIterator<T>(copy) {}
//	virtual											~BidirectionalConstIterator() {}
//	virtual inline BidirectionalConstIterator & 	operator--() { this->p--; return *this; }
//	virtual inline BidirectionalConstIterator 	 	operator--(int junk) { T* v=this->p; --this->p; return v; }
//};
//
///****************************************************************************************************************
// *
// ****************************************************************************************************************/
//template <class T>
//class RandomAccessIterator : public BidirectionalIterator<T> {
//public:
//	typedef random_access_iterator_tag 	iterator_category;
//
//	inline 								RandomAccessIterator() : BidirectionalIterator<T>() {}
//	inline 								RandomAccessIterator(T * p) : BidirectionalIterator<T>(p) {}
//	inline 								RandomAccessIterator(const RandomAccessIterator<T> & copy) : BidirectionalIterator<T>(copy) {}
//	inline RandomAccessIterator			operator+(const int i) { return RandomAccessIterator(this->p+i); }
//	inline RandomAccessIterator & 		operator+=(int i) { this->p += i; return *this; }
//	inline RandomAccessIterator 		operator-(const int i) { return RandomAccessIterator(this->p-i); }
//	inline RandomAccessIterator & 		operator-=(int i) { this->p -= i; return *this; }
//
//	// Related non-members
//	friend inline RandomAccessIterator 	operator+(const int i, RandomAccessIterator & it) { return RandomAccessIterator(it.p + i); }
//	friend inline RandomAccessIterator 	operator-(const int i, RandomAccessIterator & it) { return RandomAccessIterator(it.p - i); }
//};
//
///****************************************************************************************************************
// *
// ****************************************************************************************************************/
//template <class T>
//class RandomAccessConstIterator : public BidirectionalConstIterator<T> {
//public:
//	typedef random_access_iterator_tag 			iterator_category;
//
//	inline 										RandomAccessConstIterator() : BidirectionalConstIterator<T>() {}
//	inline 										RandomAccessConstIterator(T * p) : BidirectionalConstIterator<T>(p) {}
//	inline 										RandomAccessConstIterator(const RandomAccessConstIterator<T> & copy) : BidirectionalConstIterator<T>(copy) {}
//	inline RandomAccessConstIterator			operator+(const int i) { return RandomAccessConstIterator(this->p+i); }
//	inline RandomAccessConstIterator & 			operator+=(int i) { this->p += i; return *this; }
//	inline RandomAccessConstIterator 			operator-(const int i) { return RandomAccessConstIterator(this->p-i); }
//	inline RandomAccessConstIterator & 			operator-=(int i) { this->p -= i; return *this; }
//
//	// Related non-members
//	friend inline RandomAccessConstIterator 	operator+(const int i, RandomAccessConstIterator & it) { return RandomAccessConstIterator(it.p + i); }
//	friend inline RandomAccessConstIterator 	operator-(const int i, RandomAccessConstIterator & it) { return RandomAccessConstIterator(it.p - i); }
//};

}



#endif /* PRISM_ITERATOR_H_ */
