/*
 * iterator_priv.h
 * v1
 *
 *  Created on: Sep 25, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_PRIV_H_
#define PRISM_ITERATOR_PRIV_H_

namespace prism {
namespace priv {

/**
 * Advance function for input iterators.
 * Can only advance forwards and not backwards.
 */
template <class InputIterator>
void
advance_aux(InputIterator& iterator, int numSteps, std::forward_iterator_tag) {
	while (numSteps-- >= 0)
		++iterator;
}

/**
 * Advance function for bidirectional iterators.
 * Can advance forwards and also backwards (if numSteps is negative).
 */
template <class BidirectionalIterator>
void
advance_aux(BidirectionalIterator& iterator, int numSteps, std::bidirectional_iterator_tag) {
	if (numSteps > 0) {
		while (numSteps-- > 0)
			++iterator;
	}
	else {
		while (numSteps++ < 0)
			--iterator;
	}
}

/**
 *
 */
template <class RandomAccessIterator>
void
advance_aux(RandomAccessIterator& iterator, int numSteps, std::random_access_iterator_tag)
{ iterator += numSteps; }

/**
 *
 */
template <class InputIterator>
typename prism::iterator_traits<InputIterator>::difference_type
distance_aux(InputIterator first, InputIterator last, std::input_iterator_tag) {
	int count = 0;
	while (first++ != last)
		++count;
	return count;
}

/**
 *
 */
template <class RandomAccessIterator>
typename prism::iterator_traits<RandomAccessIterator>::difference_type
distance_aux(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
	return last - first;
}

} // end namespace priv

/*
 *
 */
template <class InputIterator>
void
advance(InputIterator& iterator, const int numSteps) {
	typedef typename prism::iterator_traits<InputIterator>::iterator_category it_cat;
	advance_aux(iterator, numSteps, it_cat());
}

/*
 *
 */
template <class Container>
auto
begin(Container& con) -> decltype (con.begin())
{ return con.begin(); }

/*
 *
 */
template <class Container>
auto
begin(const Container& con) -> decltype (con.begin())
{ return con.begin(); }

/*
 *
 */
template <class T, int Size>
T*
begin(T(&array)[Size])
{ return array; }

/*
 *
 */
template <class InputIterator>
typename prism::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	using it_cat =  typename prism::iterator_traits<InputIterator>::iterator_category;
	return prism::priv::distance_aux(first, last, it_cat());
}

/*
 *
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

/*
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

/*
 *
 */
template <class ForwardIterator>
ForwardIterator
next(ForwardIterator it, int numSteps) {
	typedef typename prism::iterator_traits<ForwardIterator>::iterator_category it_cat;
	prism::priv::advance_aux(it, numSteps, it_cat());
	return it;
}

/**
 *
 */
template <class BidirectionalIterator>
BidirectionalIterator
previous(BidirectionalIterator it, int numSteps) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	prism::priv::advance_aux(it, -numSteps, it_cat());
	return it;
}

} // end namespace prism



#endif /* PRISM_ITERATOR_PRIV_H_ */









