/*
 * PList.h
 * v0.*
 *
 *  Created on: 24 Feb 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_PLIST_H_
#define PRISM_PLIST_H_

#include <prism/global>
#include <prism/Allocator>

PRISM_BEGIN_NAMESPACE

template <typename T, typename Allocator = prism::Allocator<T>>
class PList {
private:
	using vt_alloc_traits 	= prism::AllocatorTraits<Allocator>;
public:
	using allocator_type 	= Allocator;
	using value_type 		= typename vt_alloc_traits::value_type;
	using reference 		= typename vt_alloc_traits::reference;
	using const_reference 	= typename vt_alloc_traits::const_reference;
	using pointer 			= typename vt_alloc_traits::pointer;
	using const_pointer 	= typename vt_alloc_traits::const_pointer;
	using difference_type 	= typename vt_alloc_traits::difference_type;
	using size_type 		= typename vt_alloc_traits::size_type;
public:


};

PRISM_END_NAMESPACE

#endif /* PRISM_PLIST_H_ */
