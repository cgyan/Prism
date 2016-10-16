/*
 * Vector.h
 * v1
 *
 *  Created on: Jan 16, 2015
 *      Author: iainhemstock
 */

/*
 * todo add support for move constructor
 */

#ifndef PRISM_VECTOR_H_
#define PRISM_VECTOR_H_

#include <prism/h/iterator.h>
#include <prism/h/List.h>
#include <prism/h/OutOfBoundsException.h>
#include <prism/h/algorithm.h>
#include <iostream>
#include <vector>
#include <initializer_list>

namespace prism {

template <class T>
struct VectorData;

/******************************************************************************
 * Vector
 *****************************************************************************/
template <class T>
class Vector {
public:
	typedef SequenceIterator<T,false> 			iterator;
	typedef SequenceIterator<T,true>			const_iterator;
	typedef typename iterator::reference		reference;
	typedef typename const_iterator::reference	const_reference;
	typedef typename iterator::pointer			pointer;
	typedef typename const_iterator::pointer	const_pointer;
	typedef typename iterator::value_type		value_type;
	typedef typename iterator::difference_type	difference_type;
	typedef int									size_type;

public:
						Vector();
						Vector(const int size, const T& value=T());
						Vector(const_iterator first, const_iterator last);
						Vector(std::initializer_list<T> list);
						Vector(const Vector<T>& copy);
						~Vector();
	void				append(const T& value);
	T&					at(const int index);
	const T&			at(const int index) const;
	reference			back();
	const_reference		back() const;
	iterator			begin();
	const_iterator		begin() const;
	const int			capacity() const;
	const_iterator		cbegin() const;
	const_iterator		cend() const;
	void				clear();
	const_iterator		constBegin() const;
	const T *			constData() const;
	const_iterator		constEnd() const;
	const bool			contains(const T& value) const;
	const int			count(const T& value) const;
	T *					data();
	const T * 			data() const;
	const bool			empty() const;
	iterator			end();
	const_iterator		end() const;
	const bool			endsWith(const T& value) const;
	iterator			erase(iterator pos);
	iterator			erase(iterator from, iterator to);
	void				fill(const T& value);
	T&					first();
	const T&			first() const;
	reference			front();
	const_reference		front() const;
	const int			indexOf(const T& value, const int from=0) const;
	void				insert(const int index, const T& value);
	void				insert(const int index, const int count, const T& value);
	iterator			insert(iterator insertBefore, const T& value);
	iterator			insert(iterator insertBefore, const int count, const T& value);
	const bool			isEmpty() const;
	T&					last();
	const T&			last() const;
	const int			lastIndexOf(const T& value, const int from=-1) const;
	Vector<T>			mid(const int startIndex, const int count=-1);
	void				pop_back();
	void				pop_front();
	void 				prepend(const T& value);
	void				push_back(const T& value);
	void				push_front(const T& value);
	void				remove(const int index);
	void				remove(const int index, const int count);
	void				removeAll(const T& value);
	void				removeFirst();
	void				removeLast();
	void				replace(const int index, const T& value);
	void 				reserve(const int newCapacity);
	void				resize(const int newSize);
	const int			size() const;
	void				squeeze();
	const bool			startsWith(const T& value) const;
	List<T>				toList() const;
	std::vector<T>		toStdVector() const;

	static Vector<T>	fromList(const List<T>& list);
	static Vector<T>	fromStdVector(const std::vector<T>& stdVec);

	T&					operator[](const int index);
	const T&			operator[](const int index) const;
	Vector<T>&			operator<<(const T& value);
	Vector<T>& 			operator<<(const Vector<T> & rhs);
	Vector<T>&	 		operator=(const Vector<T> & rhs);
	const bool 			operator==(const Vector<T> & rhs) const;
	const bool 			operator!=(const Vector<T> & rhs) const;
	Vector<T> 			operator+(const Vector<T> & rhs) const;
	Vector<T> & 		operator+=(const Vector<T> & rhs);

	template <class U>
	friend
	std::ostream& 		operator<<(std::ostream & out, const Vector<U> & v);
private:
	VectorData<T> * d;
private:
	const bool rangeCheck(const int index) const;
}; // end class Vector

} // end namespace prism

#include <prism/h/priv/Vector_priv.h>

#endif /* PRISM_VECTOR_H_ */
