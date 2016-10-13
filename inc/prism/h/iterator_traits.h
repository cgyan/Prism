/*
 * iterator_traits.h
 * v1
 *
 *  Created on: Sep 25, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_TRAITS_H_
#define PRISM_ITERATOR_TRAITS_H_

namespace prism {

/****************************************************************************************************************
 * A useful way to extract types from an iterator
 * i.e. Stack<int> * p = iterator_traits<Stack<int> >::pointer;
 * i.e. Vector<float> * p = iterator_traits<RandomAccessIterator>::pointer;
 ****************************************************************************************************************/
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

} // end namespace prism

#endif /* PRISM_ITERATOR_TRAITS_H_ */
