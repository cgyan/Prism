/*
 * Array.h
 * v0.1
 *
 *  Created on: Dec 28, 2014
 *      Author: iainhemstock
 */

#ifndef PRISM_ARRAY_H_
#define PRISM_ARRAY_H_

/*
 * todo add support for move constructor
 */

#include <prism/h/iterator.h>
#include <prism/h/algorithm.h>
#include <iostream>
#include <initializer_list>

namespace prism {

/******************************************************************************
 * Array
 *****************************************************************************/
/*! Arrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.
 */
template <class T>
class Array {
public:
	typedef T 								value_type;
	typedef T* 								pointer;
	typedef T& 								reference;
	typedef const pointer 					const_pointer;
	typedef const reference 				const_reference;
	typedef size_t 							size_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef random_access_iterator_tag		iterator_category;
	typedef SequenceIterator<T,false> 		iterator;
	typedef SequenceIterator<T,true>		 const_iterator;

private:
	T * m_array;
	int m_size;

private:
	Array();
	void allocate(const int size);
public:
	Array(const int size);
	Array(const int size, const T & value);
	Array(std::initializer_list<T> il);
	Array(const Array<T> & copy);
	virtual ~Array();

	T&				at(const int index);
	const T & 		at(const int index) const;
	T & 			back();
	const T & 		back() const;
	iterator 		begin();
	const_iterator 	begin() const;
	const_iterator	constBegin() const;
	const T * 		constData() const;
	const_iterator	constEnd() const;
	const bool 		contains(const T & value) const;
	const int		count(const T & value) const;
	T * 			data();
	const T * 		data() const;
	iterator 		end();
	const_iterator 	end() const;
	const bool		endsWith(const T & value) const;
	void			fill(const T & value);
	T &				first();
	const T &		first() const;
	const int		indexOf(const T & value, const int from=0) const;
	T & 			last();
	const T & 		last() const;
	const int		lastIndexOf(const T & value, const int index=-1) const;
	const int		length() const;
	Array<T>		mid(const int index, const int length=-1) const;
	void 			replace(const int index, const T & value);
	const int 		size() const;
	const bool		startsWith(const T & value) const;
	T				value(const int index) const;

	T & 			operator[](const int index);
	const T & 		operator[](const int index) const;
	const bool		operator==(const Array<T> & rhs) const;
	const bool		operator!=(const Array<T> & rhs) const;
};

/**
 * This constructor is made private so that it cannot be called externally.
 */
template <class T>
Array<T>::Array()
	: m_array(0), m_size(0)
{}

/**
 * Creates an array of size \em size and fills each element with default-constructed values.
 */
template <class T>
Array<T>::Array(const int size)
	: m_array(0), m_size(size)
{
	m_array = new T[m_size];
}

/**
 * Creates an array of size \em size and fills each element with \em value.
 */
template <class T>
Array<T>::Array(const int size, const T & value)
	: m_array(new T[size]), m_size(size)
{
	for (int i=0; i<m_size; i++)
		m_array[i] = value;
}

/**
 * Creates an array populated from the elements of the initializer list.
 */
template <class T>
Array<T>::Array(std::initializer_list<T> il)
	: m_array(0), m_size(0)
{
	m_array = new T[il.size()];
	m_size = il.size();
	prism::copy(il.begin(), il.end(), m_array);
}

/**
 * Copy-constructs this array from \em copy.
 */
template <class T>
Array<T>::Array(const Array<T> & copy)
	: m_array(new T[copy.size()]), m_size(copy.size())
{
	iterator thisIt = begin();
	const_iterator copyIt = copy.begin();
	while (thisIt != end())
		*thisIt++ = *copyIt++;
}

/**
 * Deletes this array. User is responsible for memory pointed to by pointers if applicable.
 */
template <class T>
Array<T>::~Array() {
	if (m_array != 0) {
		delete [] m_array;
		m_array = 0;
		m_size = 0;
	}
}

/**
 * Allocates enough memory for a new array of length \em size.
 */
template <class T>
void Array<T>::allocate(const int size) {
	*this = Array<T>();
	m_array = new T[size];
	m_size = size;
}

/**
 * Returns a reference to the value stored in the array at the index \em i.
 * This method performs bounds checking on \em i.
 */
template <class T>
T & Array<T>::at(const int i)  {
	if (i < 0 || i >= m_size) std::cerr << "[Array] index is out of bounds" << std::endl;
	else return m_array[i];
}

/**
 * Returns a const reference to the value stored in the array at the index \em i.
 * This method performs bounds checking on \em i.
 */
template <class T>
const T & Array<T>::at(const int i) const {
	if (i < 0 || i >= m_size) std::cerr << "[Array] index is out of bounds" << std::endl;
	else return m_array[i];
}

/**
 * Returns a reference to the last element in the array.
 * Equivalent to last().
 */
template <class T>
T & Array<T>::back() {
	return m_array[m_size-1];
}

/**
 * Returns a const reference to the last element in the array.
 * Equivalent to last().
 */
template <class T>
const T & Array<T>::back() const {
	return m_array[m_size-1];
}

/**
 * Returns an iterator which points to the first element in the array.
 */
template <class T>
typename Array<T>::iterator Array<T>::begin() {
	return iterator(m_array);
}

/**
 * Returns a const_iterator to the first element in the array.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::begin() const {
	return iterator(m_array);
}

/**
 * Returns a const_iterator to the first element in the array.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::constBegin() const {
	return const_iterator(m_array);
}

/**
 * Returns a const pointer to the internal array data.
 */
template <class T>
const T * Array<T>::constData() const {
	return m_array;
}

/**
 * Returns a const_iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::constEnd() const {
	return const_iterator(m_array+m_size);
}

/**
 * Returns true if the array contains \em value, false otherwise.
 */
template <class T>
const bool Array<T>::contains(const T & value) const {
	const_iterator it = begin();
	while (it != end())
		if (*it++ == value) return true;
	return false;
}

/**
 * Returns the number of times that \em value appears in the array.
 */
template <class T>
const int Array<T>::count(const T & value) const {
	int j = 0;
	const_iterator it = begin();
	while (it != end())
		if (*it++ == value) j++;
	return j;
}

/**
 * Returns a pointer to the internal array data.
 */
template <class T>
T * Array<T>::data() {
	return m_array;
}

/**
 * Returns a const_pointer to the internal array data.
 */
template <class T>
const T * Array<T>::data() const {
	return m_array;
}

/**
 * Returns an iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::iterator Array<T>::end() {
	return iterator(m_array+m_size);
}

/**
 * Returns a const_iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::end() const {
	return iterator(m_array+m_size);
}

/**
 * Returns true if the last element in the array is equal to \em value.
 * The element in the array must implement operator==().
 */
template <class T>
const bool Array<T>::endsWith(const T & value) const {
	if (last() == value) return true;
	return false;
}

/**
 * Fills each element in the array with \em value.
 * User is responsible for memory of original elements if applicable.
 */
template <class T>
void Array<T>::fill(const T & value) {
	iterator it = begin();
	while (it != end()) {
		*it++ = value;
	}
}

/**
 * Returns a reference to the first element in the array.
 */
template <class T>
T & Array<T>::first() {
	return *begin();
}

/**
 * Returns a const reference to the first element in the array.
 */
template <class T>
const T & Array<T>::first() const {
	return *begin();
}

/**
 * Returns the index of the first occurrence of \em value starting the search from \em index.
 * If no occurrence is found, -1 is returned instead.
 */
template <class T>
const int Array<T>::indexOf(const T & value, const int index) const {
	const_iterator it = begin() + index;
	while (it != end()) {
		if (*it == value) return it-begin();
		it++;
	}
	return -1;
}

/**
 * Returns a reference to the last element in the array.
 * Equivalent to \em back().
 */
template <class T>
T & Array<T>::last() {
	return back();
}

/**
 * Returns a const reference to the last element in the array.
 * Equivalent to \em back().
 */
template <class T>
const T & Array<T>::last() const {
	return back();
}

/**
 * Returns the index of the last occurrence of \em value searching backwards from \em index.
 * If no occurrence is found then -1 is returned instead.
 */
template <class T>
const int Array<T>::lastIndexOf(const T & value, const int index) const {
	const_iterator it = end()-1;
	if (index != -1) it = begin()+index;
	while (it != begin()-1) {
		if (*it == value) return it-begin();
		--it;
	}
	return -1;
}

/**
 * Returns the number of elements in the array.
 * Equivalent to size().
 */
template <class T>
const int Array<T>::length() const {
	return m_size;
}

/**
 * Returns a new array that is a subsection of this array. The new array starts from \em index in this array.
 * If \em length is -1 then all elements after \em index are copied over otherwise \em length elements are copied instead.
 */
template <class T>
Array<T> Array<T>::mid(const int index, const int length) const {
	int subLength = length;
	if (length == -1) subLength = m_size-index;

	Array<T> sub(subLength);
	const_iterator thisIt = begin()+index;
	iterator subIt = sub.begin();
	while (subIt != sub.end())
		*subIt++ = *thisIt++;

	return sub;
}

/**
 * Replaces the value of the element currently stored at \em index with \em value.
 * The user is responsible for memory deallocation if necessary of the element being replaced.
 */
template <class T>
void Array<T>::replace(const int index, const T & value) {
	iterator it = begin()+index;
	*it = value;
}

/**
 * Returns the number of elements in the array.
 * Equivalent to length().
 */
template <class T>
const int Array<T>::size() const {
	return m_size;
}

/**
 * Returns true if the first element in the array is equal to \em value.
 * The element in the array must implement operator==().
 */
template <class T>
const bool Array<T>::startsWith(const T & value) const {
	if (*begin() == value) return true;
	return false;
}

/**
 * Returns the value stored at \em index in the array.
 */
template <class T>
T Array<T>::value(const int index) const {
	if (index >= m_size || index < 0) return T();
	return m_array[index];
}

/**
 * Returns a reference to the element stored at \em index.
 */
template <class T>
T & Array<T>::operator [](const int index) {
	return m_array[index];
}

/**
 * Returns a const reference to the element stored at \em index.
 */
template <class T>
const T & Array<T>::operator [](const int index) const {
	return m_array[index];
}

/**
 * Compares this array with \em rhs to see if they are equal to each other.
 * They are considered equal if they have the same length and the same values in the same order.
 */
template <class T>
const bool Array<T>::operator==(const Array<T> & rhs) const {
	if (m_size != rhs.size()) return false;
	const_iterator thisIt = constBegin();
	const_iterator rhsIt = rhs.constBegin();

	while (thisIt != constEnd())
		if (*thisIt++ != *rhsIt++) return false;

	return true;
}

/**
 * Compares this array with \em rhs to see if they are not equal to each other.
 * They are considered equal if they have the same length and the same values in the same order.
 */
template <class T>
const bool Array<T>::operator!=(const Array<T> & rhs) const {
	return !(*this == rhs);
}

/**
 *
 */
template <class T>
std::ostream & operator<<(std::ostream & out, const Array<T> & array) {
	out << "Array (" << &array << ") size:" << array.size() << "\n";
	out << "------------------ \n";
	for (int i=0; i<array.size(); i++)
		out << "[" << i << "] " << array[i] << "\n";
	return out;
}

}

#endif /* PRISM_ARRAY_H_ */
