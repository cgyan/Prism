/*
 * List.h
 * v0.*
 *
 *  Created on: Sep 22, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_LIST_DEBUG_H_
#define PRISM_LIST_DEBUG_H_

#include <prism/List>
#include <prism/Allocator>
#include <ostream>
using namespace std; // todo remove this

namespace prism {
namespace debug {

//============================================================
// SafeIterator
//============================================================
template <class BaseIterator, class SafeSequence>
class SafeIterator {
private:
	typedef SafeIterator<BaseIterator,SafeSequence>		Self;
	typedef typename SafeSequence::const_iterator		ConstIterator;

	BaseIterator										m_currentIterator;
public:
	/**
	 *
	 */
	SafeIterator(const BaseIterator& baseIt, SafeSequence * sequence)
	: m_currentIterator(baseIt)
	{

	}
};
//============================================================
// SafeSequence
//============================================================
template <class Sequence>
class SafeSequence {
private:
	int m_version;
	prism::List<SafeIterator<typename Sequence::iterator, Sequence>> 		m_mutableIterators;
	prism::List<SafeIterator<typename Sequence::const_iterator, Sequence>> 	m_constIterators;
public:

};
//============================================================
// List (debug version)
//============================================================
template <class T, class TAllocator = prism::Allocator<T>>
class List :
		public prism::List<T,TAllocator>,
		public prism::debug::SafeSequence<prism::debug::List<T,TAllocator>>
{
private:
	typedef prism::debug::List<T,TAllocator> 	Self;
	typedef prism::List<T,TAllocator> 			Base;
	typedef typename Base::iterator				BaseIterator;
	typedef typename Base::const_iterator		BaseConstIterator;
public:
	typedef prism::debug::SafeIterator<typename Base::iterator, Self> 			iterator;
	typedef prism::debug::SafeIterator<typename Base::const_iterator, Self> 	const_iterator;
public:
	/**
	 *
	 */
	List()
	: Base()
	{ cout << "List(Debug)" << endl; }

	/**
	 *
	 */
	iterator
	begin() {
		return iterator(Base::begin(), this);
	}

};

} // end namespace debug
} // end namespace prism



#endif /* PRISM_LIST_DEBUG_H_ */
