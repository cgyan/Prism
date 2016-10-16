/*
 * List.h
 * v2
 *
 *  Created on: Sep 19, 2016
 *      Author: iainhemstock
 */

/// @file List.h
///
/// @brief A container suitable for fast insertion and deletion
///
/// @since 1.0.0

/**
 * todo
 *
 * functions to add:
 * -- move constructor and move assignment operator
 * -- TAllocator allocator();
 * -- prism::sort() needs a specialization for List
 */

#ifndef PRISM_LIST_H_
#define PRISM_LIST_H_

#include <prism/h/SharedData.h>
#include <prism/h/SharedDataPointer.h>
#include <prism/h/Allocator.h>
#include <prism/h/algorithm.h>
#include <prism/h/iterator.h>
#include <prism/h/utility.h> // for prism::conditional_type
#include <cstddef> // for std::ptrdiff_t
#include <ostream>
#include <utility> // for std::forward
#include <initializer_list>
#include <list>

namespace prism {

/// @cond DO_NOT_DOCUMENT
template <class T, class TAllocator>
struct ListData;

template <class T, bool isConst>
struct ListIterator;
/// @endcond

//============================================================
// List
//============================================================
/// @class 	List prism/h/List.h prism/List
///
/// @brief 	A node-based container
///
/// 		More detailed description here
///
/// @since	1.0.0
template <class T, class TAllocator = prism::Allocator<T>>
class List {
private:
	typedef ListData<T, TAllocator>					Data;
public:
	typedef ListIterator<T, false>					iterator;
	typedef ListIterator<T, true>					const_iterator;
	typedef typename TAllocator::value_type			value_type;
	typedef typename TAllocator::pointer			pointer;
	typedef typename TAllocator::reference			reference;
	typedef typename TAllocator::const_pointer		const_pointer;
	typedef typename TAllocator::const_reference	const_reference;
	typedef typename TAllocator::size_type			size_type;
	typedef typename TAllocator::difference_type	difference_type;
	typedef typename iterator::iterator_category	iterator_category;
private:
	SharedDataPointer<Data> d;
public:
	/**
	 *
	 */
	List();

	/**
	 *
	 */
	List(const int numElements, const_reference value=T());

	/**
	 *
	 */
	template <class InputIterator>
	List(InputIterator first, InputIterator last);

	/**
	 *
	 */
	List(const std::initializer_list<T>& il);

	/**
	 *
	 */
	List(const List<T,TAllocator>& copy);

	/**
	 *
	 */
	~List();

	/**
	 *
	 */
	void
	append(const_reference value);

	/**
	 *
	 */
	reference
	back();

	/**
	 *
	 */
	const_reference
	back() const;

	/**
	 *
	 */
	iterator
	begin();

	/**
	 *
	 */
	iterator
	begin() const;

	/**
	 *
	 */
	const_iterator
	cbegin() const;

	/**
	 *
	 */
	iterator
	cend() const;

	/**
	 *
	 */
	void
	clear();

	/**
	 *
	 */
	const_iterator
	constBegin() const;

	/**
	 *
	 */
	iterator
	constEnd() const;

	/**
	 *
	 */
	const bool
	contains(const_reference value) const;

	/**
	 *
	 */
	const int
	count(const_reference value) const;

	/**
	 *
	 */
	const bool
	empty();

	/**
	 *
	 */
	iterator
	end();

	/**
	 *
	 */
	iterator
	end() const;

	/**
	 *
	 */
	const bool
	endsWith(const_reference value) const;

	/**
     * This function only erases the element, and that if the element
     * is itself a pointer, the pointed-to memory is not touched in
     * any way.  Managing the pointer is the user's responsibility.
	 */
	iterator
	erase(const_iterator pos);

	/**
     * This function only erases the element, and that if the element
     * is itself a pointer, the pointed-to memory is not touched in
     * any way.  Managing the pointer is the user's responsibility.
	 */
	iterator
	erase(const_iterator first, const_iterator last);

	/**
	 *
	 */
	reference
	first();

	/**
	 *
	 */
	const_reference
	first() const;

	/**
	 *
	 */
	reference
	front();

	/**
	 *
	 */
	const_reference
	front() const;

	/**
	 * Inserts \em value after the value pointed to be \em pos.
	 * @return Returns an iterator that points to the newly inserted value.
	 */
	iterator
	insert(const_iterator insertBefore, const_reference value);

	/**
	 *
	 */
	iterator
	insert(const_iterator insertBefore, const int count, const_reference value);

	/**
	 *
	 */
	template <class InputIterator>
	iterator
	insert(const_iterator insertBefore, InputIterator first, InputIterator last);

	/**
	 *
	 */
	iterator
	insert(const_iterator insertBefore, std::initializer_list<T>& il);

	/**
	 *
	 */
	const bool
	isEmpty() const;

	/**
	 *
	 */
	reference
	last();

	/**
	 *
	 */
	const_reference
	last() const;

	/**
	 *
	 */
	void
	pop_back();

	/**
	 *
	 */
	void
	pop_front();

	/**
	 *
	 */
	void
	prepend(const_reference value);

	/**
	 *
	 */
	void
	push_back(const_reference value);

	/**
	 *
	 */
	void
	push_front(const_reference value);



	/**
	 * The remove... family of functions remove the elements based on value whereas
	 * the erase... family of functions remove the elements based on iterators.
	 */
	void
	removeAll(const_reference value);

	/**
	 *
	 */
	void
	removeFirst();

	/**
	 *
	 */
	template <class Predicate>
	void
	removeIf(Predicate pred);

	/**
	 *
	 */
	void
	removeLast();

	/**
	 *
	 */
	void
	resize(const int newSize, const_reference value=value_type());

	/**
	 *
	 */
	const int
	size() const;

	/**
	 *
	 */
	const bool
	startsWith(const_reference value);

	/**
	 *
	 */
	value_type
	takeFirst();

	/**
	 *
	 */
	value_type
	takeLast();

	/**
	 *
	 */
	std::list<T>
	toStdList() const;

	/**
	 *
	 */
	const bool
	operator==(const List<T,TAllocator>& rhs);

	/**
	 *
	 */
	const bool
	operator!=(const List<T,TAllocator>& rhs);

	/**
	 *
	 */
	List<T,TAllocator>
	operator+(const List<T,TAllocator>& rhs);

	/**
	 *
	 */
	List<T,TAllocator>&
	operator+=(const List<T,TAllocator>& rhs);

	/**
	 *
	 */
	List<T,TAllocator>&
	operator+=(const_reference value);

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const_reference value);

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const List<T,TAllocator>& other);

	/**
	 *
	 */
	List<T,TAllocator>&
	operator=(const List<T,TAllocator>& rhs);

	/**
	 *
	 */
	template <class U>
	friend
	std::ostream& operator<<(std::ostream & out, const List<U>& list);
}; // end List class

} // end namespace prism

#include <prism/h/priv/List_priv.h>

#endif /* PRISM_LIST_H_ */
