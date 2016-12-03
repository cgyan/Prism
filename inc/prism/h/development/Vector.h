/*
 * Vector.h
 * v1
 *
 *  Created on: Dec 1, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_VECTOR_DEVELOPMENT_H_
#define PRISM_VECTOR_DEVELOPMENT_H_

#include <prism/h/global.h>
#include <prism/h/Allocator.h>
#include <prism/h/Iterator.h>

PRISM_BEGIN_NAMESPACE

//=============================================================================================
// Vector
//=============================================================================================
template <typename T, typename Allocator = prism::Allocator<T>>
class Vector {
private:
	using alloc_traits				= prism::AllocatorTraits<Allocator>;
	using iterator_traits			= prism::iterator_traits<prism::SequenceIterator<T,false>>;
public:
	using allocator_type 			= Allocator;
	using value_type 				= typename alloc_traits::value_type;
	using reference 				= typename alloc_traits::reference;
	using const_reference 			= typename alloc_traits::const_reference;
	using pointer 					= typename alloc_traits::pointer;
	using const_pointer 			= typename alloc_traits::const_pointer;
	using difference_type 			= typename alloc_traits::difference_type;
	using size_type 				= typename alloc_traits::size_type;
	using iterator 					= prism::SequenceIterator<T,false>;
	using const_iterator 			= prism::SequenceIterator<T,true>;
	using reverse_iterator			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator	= prism::ReverseIterator<const_iterator>;
};

PRISM_END_NAMESPACE

#endif /* PRISM_VECTOR_DEVELOPMENT_H_ */
