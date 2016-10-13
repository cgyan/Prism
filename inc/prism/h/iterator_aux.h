/*
 * iterator_aux.h
 * v1
 *
 *  Created on: Sep 25, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_AUX_H_
#define PRISM_ITERATOR_AUX_H_

namespace prism {

/**
 * Advance function for input iterators.
 * Can only advance forwards and not backwards.
 */
template <class InputIterator>
void
advance_aux(InputIterator& iterator, int numSteps, prism::forward_iterator_tag) {
	while (numSteps-- >= 0)
		++iterator;
}

/**
 * Advance function for bidirectional iterators.
 * Can advance forwards and also backwards (if numSteps is negative).
 */
template <class BidirectionalIterator>
void
advance_aux(BidirectionalIterator& iterator, int numSteps, prism::bidirectional_iterator_tag) {
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
 * Advance function for random access iterators.
 */
template <class RandomAccessIterator>
void
advance_aux(RandomAccessIterator& iterator, int numSteps, prism::random_access_iterator_tag)
{ iterator += numSteps; }

/**
 * Returns the distance between two ForwardIterators.
 */
template <class ForwardIterator>
typename prism::iterator_traits<ForwardIterator>::difference_type
distance_aux(ForwardIterator first, ForwardIterator last, forward_iterator_tag) {
	int count = 0;
	while (first++ != last)
		++count;
	return count;
}

/**
 * Returns the distance between two RandomAccessIterators.
 */
template <class RandomAccessIterator>
typename prism::iterator_traits<RandomAccessIterator>::difference_type
distance_aux(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
	return last - first;
}

/**
 *
 */
template <class BidirectionalIterator>
BidirectionalIterator
previous_aux(BidirectionalIterator it, int numSteps=1) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	prism::advance_aux(it, -numSteps, it_cat());
	return it;
}



} // end namespace prism



#endif /* PRISM_ITERATOR_AUX_H_ */









