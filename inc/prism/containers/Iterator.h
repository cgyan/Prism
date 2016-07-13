/*
 * Iterator.h
 * v0.1
 *
 *  Created on: Jan 7, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_H_
#define PRISM_ITERATOR_H_

#include <cstddef> // for std::ptrdiff_t

namespace prism {

/****************************************************************************************************************
 * Tags to describe what kind of iterator a particular iterator type is. They are used in the container algorithms
 * to determine which is the best algorithm to use for that particular type of iterator.
 ****************************************************************************************************************/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/****************************************************************************************************************
 * A useful way to extract types from an iterator i.e. iterator_traits<Stack<int> >::pointer.
 ****************************************************************************************************************/
template <class IterType>
struct iterator_traits  {
	typedef typename IterType::value_type 			value_type;
	typedef typename IterType::difference_type 		difference_type;
	typedef typename IterType::iterator_category 	iterator_category;
	typedef typename IterType::pointer 				pointer;
	typedef typename IterType::reference 			reference;
};

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

/****************************************************************************************************************
 * Special iterator for the List container (implemented as a bidirectional iterator. A list contains a linked
 * list of nodes and each node contains the actual values stored by the user. As such the iterator needs to return that
 * value and not the node as that is part of the private implementation.
 ****************************************************************************************************************/
template <class Node, class T>
struct ListIterator {
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;
	typedef bidirectional_iterator_tag 	iterator_category;
	typedef std::ptrdiff_t 				difference_type;

										Node * node;
										ListIterator() : node(0) {}
										ListIterator(Node * node) : node(node) {}
										ListIterator(const ListIterator & copy) { node = copy.node; }
	reference 							operator*() { return node->value; }
	pointer 							operator->() { return &node->value; }
	ListIterator & 						operator++() { node = node->next; return *this; }
	ListIterator   						operator++(int junk) { Node * n = node; node = node->next; return n; }
	ListIterator & 						operator--() { node = node->prev; return *this; }
	ListIterator  						operator--(int junk) { Node * n = node; node = node->prev; return n; }
	ListIterator & 						operator=(const ListIterator & rhs) { node = rhs.node; return *this;}
	bool 								operator!=(const ListIterator & rhs) { return node != rhs.node; }
	bool 								operator==(const ListIterator & rhs) const { return node == rhs.node; }

	// Related non-members
	friend inline difference_type 		operator-(const ListIterator & lhs, const ListIterator & rhs) { return lhs.node - rhs.node; }
	friend inline const bool 			operator<(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 			operator>(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 			operator<=(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 			operator>=(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs >= 0; }
};

/****************************************************************************************************************
 * Const List iterator
 ****************************************************************************************************************/
template <class Node, class T>
struct ListConstIterator {
	typedef const T						value_type;
	typedef const T&					reference;
	typedef const T*					pointer;
	typedef bidirectional_iterator_tag 	iterator_category;
	typedef std::ptrdiff_t 				difference_type;

										Node * node;
										ListConstIterator() : node(0) {}
										ListConstIterator(Node * node) : node(node) {}
										ListConstIterator(const ListConstIterator & copy) { node = copy.node; }
	reference 							operator*() { return node->value; }
	pointer 							operator->() { return &node->value; }
	ListConstIterator & 				operator++() { node = node->next; return *this; }
	ListConstIterator   				operator++(int junk) { Node * n = node; node = node->next; return n; }
	ListConstIterator & 				operator--() { node = node->prev; return *this; }
	ListConstIterator 	 				operator--(int junk) { Node * n = node; node = node->prev; return n; }
	ListConstIterator & 				operator=(const ListConstIterator & rhs) { node = rhs.node; return *this;}
	bool 								operator!=(const ListConstIterator & rhs) { return node != rhs.node; }
	bool 								operator==(const ListConstIterator & rhs) const { return node == rhs.node; }

	// Related non-members
	friend inline difference_type 		operator-(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs.node - rhs.node; }
	friend inline const bool 			operator<(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 			operator>(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 			operator<=(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 			operator>=(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs >= 0; }
};

}



#endif /* PRISM_ITERATOR_H_ */
