/*
 * Iterator.h
 * v1
 *
 *  Created on: Jan 7, 2015
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_H_
#define PRISM_ITERATOR_H_

#include <prism/type_traits> // for prism::ConditionalType
#include <utility>
#include <prism/global>
#include <cstddef> // for std::ptrdiff_t
#include <iterator>

PRISM_BEGIN_NAMESPACE

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
	typedef typename Iterator::reference 			reference;
};

// Specialisation for pointers
template<class T>
struct iterator_traits<T*> {
    typedef T 										value_type;
    typedef std::ptrdiff_t 							difference_type;
    typedef std::random_access_iterator_tag 		iterator_category;
    typedef T* 										pointer;
    typedef T& 										reference;
};

// Specialisation for pointers to const
template<class T>
struct iterator_traits<const T*> {
    typedef T 										value_type;
    typedef std::ptrdiff_t 							difference_type;
    typedef std::random_access_iterator_tag 		iterator_category;
    typedef const T* 								pointer;
    typedef const T& 								reference;
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
template <class T, bool IsConst>
struct SequenceIterator {
private:
	using iterator 				= prism::SequenceIterator<T,false>;
	using const_iterator 		= prism::SequenceIterator<T,true>;
	using Self					= ConditionalType_t<IsConst, const_iterator, iterator>;
public:
	using value_type 			= T;
	using pointer 				= prism::ConditionalType_t<IsConst, const T*, T*>;
	using reference				= prism::ConditionalType_t<IsConst, const T&, T&>;
	using iterator_category 	= std::random_access_iterator_tag;
	using difference_type 		= std::ptrdiff_t;
public:
	pointer p;
public:
	SequenceIterator()
	: p(nullptr)
	{}

	SequenceIterator(pointer p)
	: p(p)
	{}

	// only allow copying of non-const iterator
	SequenceIterator(const prism::SequenceIterator<T,false>& copy)
	: p(copy.p)
	{}

	~SequenceIterator()
	{}

	reference
	operator*() const
	{ return *p; }

	pointer
	operator->() const
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
	operator+=(difference_type i)
	{ p += i; return *this; }

	Self&
	operator-=(difference_type i)
	{ return *this += -i; }

	Self
	operator+(difference_type i) const
	{ Self tmp = *this; return tmp += i; }

	Self
	operator-(difference_type i) const
	{ Self tmp = *this; return tmp += -i; }

	difference_type
	operator-(const Self& rhs) const
	{ return static_cast<difference_type>(this->p - rhs.p); }

	Self&
	operator=(const iterator& it)
	{ if (it.p != this->p) this->p = it.p; return *this; }

	const bool
	operator==(const Self& rhs) const
	{ return this->p == rhs.p; }

	const bool
	operator!=(const Self& rhs) const
	{ return !(*this == rhs); }

	const bool
	operator<(const Self& rhs) const
	{ return this->p < rhs.p; }

	const bool
	operator>(const Self& rhs) const
	{ return this->p > rhs.p; }

	const bool
	operator<=(const Self& rhs) const
	{ return this->p <= rhs.p; }

	const bool
	operator>=(const Self& rhs) const
	{ return this->p >= rhs.p; }
};
//=============================================================================================
// AssociativeIterator helper functions
//=============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
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
PRISM_END_PRIVATE_NAMESPACE
//=============================================================================================
// AssociativeIterator
// --- for associative containers such as Map and Set and
// --- binary search and red-black trees
//=============================================================================================
template <	class Key,
			class Value,
			class Node,
			bool IsConst>
struct AssociativeIterator {
private:
	using iterator 				= AssociativeIterator<Key,Value,Node,false>;
	using const_iterator 		= AssociativeIterator<Key,Value,Node,true>;
	using Self 					= ConditionalType_t<IsConst, const_iterator, iterator>;
	using node_pointer 			= Node*;
public:
	using value_type 			= std::pair<Key,Value>;
	using pointer 				= ConditionalType_t<IsConst, const value_type*, value_type*>;
	using reference 			= ConditionalType_t<IsConst, const value_type&, value_type&>;
	using difference_type 		= std::ptrdiff_t;
	using iterator_category 	= std::bidirectional_iterator_tag;

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
			np = prism_private::minimumNodeInSubTree(np->right);
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
			np = prism_private::maximumNodeInSubTree(np->left);
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
	operator==(const Self& other) const
	{ return this->np == other.np; }

	const bool
	operator!=(const Self& other) const
	{ return !(*this == other); }

private:
	node_pointer np;
};
//=============================================================================================
// ReverseIterator
//=============================================================================================
template <typename BidirectionalIterator>
struct ReverseIterator {
private:
	using iter_traits			= prism::iterator_traits<BidirectionalIterator>;
	using Self					= ReverseIterator<BidirectionalIterator>;
public:
	using iterator_type			= BidirectionalIterator;
	using value_type 			= typename iter_traits::value_type;
	using difference_type 		= typename iter_traits::difference_type;
	using reference 			= typename iter_traits::reference;
	using pointer 				= typename iter_traits::pointer;
	using iterator_category 	= typename iter_traits::iterator_category;

	ReverseIterator()
	: baseIter()
	{}

	explicit
	ReverseIterator(iterator_type it)
	: baseIter(it)
	{}

	ReverseIterator(const Self& rhs)
	: baseIter(rhs.baseIter)
	{}

	iterator_type
	base() const {
		return baseIter;
	}

	reference
	operator*() const {
		iterator_type it = baseIter;
		return *--it;
	}

	pointer
	operator->() const {
		return &(operator*());
	}

	Self
	operator+(difference_type n) const {
		Self tmp(baseIter);
		return tmp += n;
	}

	Self&
	operator++() {
		--baseIter;
		return *this;
	}

	Self
	operator++(int junk) {
		Self tmp(baseIter);
		--baseIter;
		return tmp;
	}

	Self&
	operator+=(difference_type n) {
		baseIter = previous(baseIter, n);
		return *this;
	}

	Self
	operator-(difference_type n) const {
		Self tmp(baseIter);
		return tmp += -n;
	}

	Self&
	operator--() {
		++baseIter;
		return *this;
	}

	Self
	operator--(int junk) {
		Self tmp(baseIter);
		++baseIter;
		return tmp;
	}

	Self&
	operator-=(difference_type n) {
		*this += -n;
		return *this;
	}

	/*
	 * Accesses the element at the offset to the iterator's current position
	 */
	reference
	operator[](difference_type offset) const {
		return *(*this+offset);
	}

private:
	iterator_type baseIter;
};

/*
 *
 */
template <typename Iterator>
const bool
operator==(const ReverseIterator<Iterator>& a,
		   const ReverseIterator<Iterator>& b)
{ return a.base() == b.base(); }

/*
 *
 */
template <typename Iterator>
const bool
operator!=(const ReverseIterator<Iterator>& a,
		   const ReverseIterator<Iterator>& b)
{ return !(a==b); }

/*
 *
 */
template <typename Iterator>
const bool
operator<(const ReverseIterator<Iterator>& a,
		  const ReverseIterator<Iterator>& b)
{ return b.base() < a.base(); }

/*
 *
 */
template <typename Iterator>
const bool
operator<=(const ReverseIterator<Iterator>& a,
		   const ReverseIterator<Iterator>& b)
{ return !(b < a); }

/*
 *
 */
template <typename Iterator>
const bool
operator>(const ReverseIterator<Iterator>& a,
		  const ReverseIterator<Iterator>& b)
{ return b < a; }

/*
 *
 */
template <typename Iterator>
const bool
operator>=(const ReverseIterator<Iterator>& a,
		   const ReverseIterator<Iterator>& b)
{ return !(a < b); }
//=============================================================================================
// MoveIterator
//=============================================================================================
template <typename Iterator>
struct MoveIterator {
	using iterator_type = Iterator;
	using iterator_category = typename prism::iterator_traits<iterator_type>::iterator_category;
	using BaseReference = typename prism::iterator_traits<iterator_type>::reference;
	using value_type = typename prism::iterator_traits<iterator_type>::value_type;
	using difference_type = typename prism::iterator_traits<iterator_type>::difference_type;
	using pointer = iterator_type;
	using reference = typename prism::ConditionalType<
							std::is_reference<BaseReference>::value,
							typename std::add_rvalue_reference<
								typename std::remove_reference<BaseReference>::type
							>::type,
							BaseReference
						>::type;

	MoveIterator()
	: baseIter{}
	{}

	MoveIterator(iterator_type bi)
	: baseIter{bi}
	{}

	MoveIterator(const MoveIterator& rhs)
	: baseIter{rhs.baseIter}
	{}

	iterator_type
	base() const {
		return baseIter;
	}

	reference
	operator*() const {
		return std::move(*baseIter);
	}

	pointer
	operator->() const {
		return baseIter;
	}

	MoveIterator&
	operator++() {
		++baseIter;
		return *this;
	}

	MoveIterator
	operator++(int) {
		MoveIterator tmp = *this;
		++baseIter;
		return tmp;
	}

	MoveIterator&
	operator--() {
		--baseIter;
		return *this;
	}

	MoveIterator
	operator--(int) {
		MoveIterator tmp = *this;
		--baseIter;
		return tmp;
	}

	MoveIterator&
	operator+=(difference_type offset) {
		baseIter += offset;
		return *this;
	}

	MoveIterator&
	operator-=(difference_type offset) {
		baseIter -= offset;
		return *this;
	}

	MoveIterator
	operator+(difference_type offset) {
		MoveIterator tmp = *this;
		tmp += offset;
		return tmp;
	}

	MoveIterator
	operator-(difference_type offset) {
		MoveIterator tmp = *this;
		tmp -= offset;
		return tmp;
	}

	iterator_type baseIter;
};

template <typename Iterator>
const bool
operator==(const MoveIterator<Iterator>& lhs,
		   const MoveIterator<Iterator>& rhs)
{ return lhs.base() == rhs.base(); }

template <typename Iterator>
const bool
operator!=(const MoveIterator<Iterator>& lhs,
		   const MoveIterator<Iterator>& rhs)
{ return !(lhs == rhs); }

template <typename Iterator>
const bool
operator<(const MoveIterator<Iterator>& lhs,
		  const MoveIterator<Iterator>& rhs)
{ return lhs.base() < rhs.base(); }

template <typename Iterator>
const bool
operator<=(const MoveIterator<Iterator>& lhs,
		   const MoveIterator<Iterator>& rhs)
{ return lhs.base() <= rhs.base(); }

template <typename Iterator>
const bool
operator>(const MoveIterator<Iterator>& lhs,
		  const MoveIterator<Iterator>& rhs)
{ return lhs.base() > rhs.base(); }

template <typename Iterator>
const bool
operator>=(const MoveIterator<Iterator>& lhs,
		   const MoveIterator<Iterator>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename Iterator>
MoveIterator<Iterator>
make_move_iterator(Iterator iter)
{ return MoveIterator<Iterator>(iter); }


PRISM_END_NAMESPACE

#include <prism/core/priv/iterator_priv.h>

#endif /* PRISM_ITERATOR_H_ */
