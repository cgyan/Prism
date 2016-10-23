/*
 * Iterator.h
 * v1
 *
 *  Created on: Jan 7, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_H_
#define PRISM_ITERATOR_H_

#include <prism/h/utility.h>
#include <prism/h/pair.h>
#include <cstddef> // for std::ptrdiff_t

namespace prism {

/**********************************************************************************************
 * Tags to describe what kind of iterator a particular iterator type is. They are used in the
 * container algorithms to determine which is the best algorithm to use for that particular
 * type of iterator.
 *********************************************************************************************/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/**********************************************************************************************
 * A useful way to extract types from an iterator
 * i.e. Stack<int> * p = iterator_traits<Stack<int> >::pointer;
 * i.e. Vector<float> * p = iterator_traits<RandomAccessIterator>::pointer;
 *********************************************************************************************/
template <class Iterator>
struct iterator_traits  {
	typedef typename Iterator::value_type 			value_type;
	typedef typename Iterator::difference_type 		difference_type;
	typedef typename Iterator::iterator_category 	iterator_category;
	typedef typename Iterator::pointer 				pointer;
	typedef typename Iterator::const_pointer		const_pointer;
	typedef typename Iterator::reference 			reference;
	typedef typename Iterator::const_reference 		const_reference;
};

// specialization for arrays
template<class T>
struct iterator_traits<T*> {
    typedef T 										value_type;
    typedef std::ptrdiff_t 							difference_type;
    typedef prism::random_access_iterator_tag 		iterator_category;
    typedef T* 										pointer;
    typedef const T*								const_pointer;
    typedef T& 										reference;
    typedef const T&								const_reference;
};

/**********************************************************************************************
 * iterator helper functions
 *********************************************************************************************/
/**
 * Moves the iterator forwards by numSteps (or backwards if numSteps is negative).
 */
template <class InputIterator>
void
advance(InputIterator& iterator, const int numSteps);

/**
 * Returns an iterator pointing to the beginning of \em con.
 */
template <class Container>
auto
begin(Container& con) -> decltype (con.begin());

/**
 * Returns a const iterator pointing to the beginning of \em con.
 */
template <class Container>
auto
begin(const Container& con) -> decltype (con.begin());

/**
 * Array specialization.
 */
template <class T, int Size>
T*
begin(T(&array)[Size]);

/**
 * Returns the distance between two iterators.
 */
template <class InputIterator>
typename prism::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last);

/**
 * Returns an iterator pointing to the end of \em con.
 */
template <class Container>
auto
end(Container& con) -> decltype (con.end());

/**
 * Returns a const iterator pointing to the end of \em con.
 */
template <class Container>
auto
end(const Container& con) -> decltype (con.end());

/**
 * Array specialization.
 */
template <class T, int Size>
T*
end(T(&array)[Size]);

/**
 *
 */
template <class InputIterator, class Container>
const bool
has_next(InputIterator& it, Container& con);

/**
 *
 */
template <class InputIterator, class Container>
const bool
has_previous(InputIterator& it, Container& con);

/**
 * Advances the iterator \em it by \em numSteps (1 by default).
 * Returns an iterator.
 */
template <class ForwardIterator>
ForwardIterator
next(ForwardIterator it, int numSteps=1);

/**
 * Moves the iterator \em it back by \em numSteps.
 * Returns an iterator.
 */
template <class BidirectionalIterator>
BidirectionalIterator
previous(BidirectionalIterator it, int numSteps=1);

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

//====================================================================================
// AssociativeIterator
// --- for associative containers such as Map and Set and
// --- binary search and red-black trees
//====================================================================================
/**
 *
 */
template <class NodePointer>
NodePointer
minimumNodeInSubTree(NodePointer node) {
	while (node->left != nullptr)
		node = node->left;
	return node;
}

/**
 *
 */
template <class NodePointer>
NodePointer
maximumNodeInSubTree(NodePointer node) {
	while (node->right != nullptr)
		node = node->right;
	return node;
}

template <	class Key,
			class Value,
			class Node,
			bool isConst>
struct AssociativeIterator {
	typedef AssociativeIterator<Key,Value,Node,false>	iterator;
	typedef AssociativeIterator<Key,Value,Node,true>	const_iterator;
	typedef Node*										node_pointer;

	typedef prism::pair<Key,Value>						value_type;
	typedef const value_type							const_reference;
	typedef const value_type*							const_pointer;
	typedef size_t										size_type;
	typedef std::ptrdiff_t								difference_type;
	typedef prism::bidirectional_iterator_tag			iterator_category;

	typedef typename prism::conditional_type<	isConst, const value_type*,
												value_type*>::type pointer;

	typedef typename prism::conditional_type<	isConst, const value_type&,
												value_type&>::type reference;

	typedef typename prism::conditional_type<	isConst, const_iterator, iterator>::type Self;

	node_pointer np;

	AssociativeIterator()
	: np(nullptr)
	{}

	AssociativeIterator(node_pointer node)
	: np(node)
	{}

	AssociativeIterator(const iterator& copy)
	: np(copy.np)
	{}

	~AssociativeIterator()
	{}

	reference
	operator*() const
	{ return np->value; }

	pointer
	operator->() const
	{ return &np->value; }

	// adapted from Introduction to Algorithms (1990, page 292)
	Self&
	operator++() {
		if (np->right != nullptr) {
			np = minimumNodeInSubTree(np->right);
		}
		else {
			node_pointer parent = np->parent;
			while (parent != nullptr && np == parent->right) {
				np = parent;
				parent = parent->parent;
			}
			np = parent;
		}
		return *this;
	}

	Self
	operator++(int junk) {
		Self tmp(*this);
		this->operator++();
		return tmp;
	}

	// adapted from Introduction to Algorithms (1990, page 292)
	Self&
	operator--() {
		if (np->left != nullptr) {
			np = maximumNodeInSubTree(np->left);
		}
		else {
			node_pointer parent = np->parent;
			while (parent != nullptr && np == parent->left) {
				np = parent;
				parent = parent->parent;
			}
			np = parent;
		}
		return *this;
	}

	Self
	operator--(int junk) {
		Self tmp(*this);
		this->operator--();
		return tmp;
	}

	Self&
	operator=(const iterator& rhs) {
		if (*this != rhs)
			np = rhs.np;
		return *this;
	}

	const bool
	operator==(const Self& other)
	{ return this->np == other.np; }

	const bool
	operator!=(const Self& other)
	{ return !(*this == other); }
};

} // end namespace prism

#include <prism/h/priv/iterator_priv.h>

#endif /* PRISM_ITERATOR_H_ */
