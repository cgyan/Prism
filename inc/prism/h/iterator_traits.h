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
template <class IterType>
struct iterator_traits  {
	typedef typename IterType::value_type 			value_type;
	typedef typename IterType::difference_type 		difference_type;
	typedef typename IterType::iterator_category 	iterator_category;
	typedef typename IterType::pointer 				pointer;
	typedef typename IterType::reference 			reference;
};

} // end namespace prism

#endif /* PRISM_ITERATOR_TRAITS_H_ */
