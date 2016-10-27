/*
 * Array_priv.h
 * v1
 *
 *  Created on: Oct 24, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ARRAY_PRIV_H_
#define PRISM_ARRAY_PRIV_H_

#include <prism/h/algorithm.h>

namespace prism {
//=============================================================================================
// ArrayData
//=============================================================================================
template <class T>
struct Array<T>::ArrayData {
	T * m_array;
	int m_size;

	ArrayData()
	: m_array(nullptr),
	  m_size(0)
	{}

	ArrayData(const int size)
	: m_array(new T[size]),
	  m_size(size)
	{
		prism::fill(m_array, m_array+m_size, T());
	}

	ArrayData(const int size, const T& value)
	: m_array(new T[size]),
	  m_size(size)

	{
		prism::fill(m_array, m_array+size, value);
	}

	ArrayData(std::initializer_list<T> il)
	: m_array(new T[il.size()]),
	  m_size(il.size())
	{
		prism::copy(il.begin(), il.end(), m_array);
	}

	~ArrayData() {
		delete [] m_array;
		m_array = nullptr;
		m_size = 0;
	}
};
//=============================================================================================
// Array
//=============================================================================================
/**
 *
 */
template <class T>
Array<T>::Array()
	: d(nullptr)
{}

/**
 *
 */
template <class T>
Array<T>::Array(const int size)
	: d(new ArrayData(size))
{}

/**
 *
 */
template <class T>
Array<T>::Array(const int size, const T & value)
	: d(new ArrayData(size, value))
{}

/**
 *
 */
template <class T>
Array<T>::Array(std::initializer_list<T> il)
	: d(new ArrayData(il))
{}

/**
 *
 */
template <class T>
Array<T>::Array(const Array<T> & copy)
	: d(new ArrayData)
{
	d->m_array = new T[copy.size()];
	d->m_size = copy.d->m_size;
	prism::copy(copy.begin(), copy.end(), this->begin());
}

/**
 *
 */
template <class T>
Array<T>::~Array()
{ delete d; }

/**
 * Returns a reference to the value stored in the array at the index \em i.
 * This method performs bounds checking on \em i.
 */
template <class T>
T & Array<T>::at(const int i)  {
	if (i < 0 || i >= d->m_size) std::cerr << "[Array] index is out of bounds" << std::endl;
	else return d->m_array[i];
}

/**
 * Returns a const reference to the value stored in the array at the index \em i.
 * This method performs bounds checking on \em i.
 */
template <class T>
const T & Array<T>::at(const int i) const {
	if (i < 0 || i >= d->m_size) std::cerr << "[Array] index is out of bounds" << std::endl;
	else return d->m_array[i];
}

/**
 * Returns a reference to the last element in the array.
 * Equivalent to last().
 */
template <class T>
T & Array<T>::back() {
	return d->m_array[d->m_size-1];
}

/**
 * Returns a const reference to the last element in the array.
 * Equivalent to last().
 */
template <class T>
const T & Array<T>::back() const {
	return d->m_array[d->m_size-1];
}

/**
 * Returns an iterator which points to the first element in the array.
 */
template <class T>
typename Array<T>::iterator Array<T>::begin() {
	return iterator(d->m_array);
}

/**
 * Returns a const_iterator to the first element in the array.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::begin() const {
	return const_iterator(d->m_array);
}

/**
 * Returns a const_iterator to the first element in the array.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::constBegin() const {
	return const_iterator(d->m_array);
}

/**
 * Returns a const pointer to the internal array data.
 */
template <class T>
const T * Array<T>::constData() const {
	return d->m_array;
}

/**
 * Returns a const_iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::constEnd() const {
	return const_iterator(d->m_array+d->m_size);
}

/**
 * Returns true if the array contains \em value, false otherwise.
 */
template <class T>
const bool Array<T>::contains(const T & value) const {
	const_iterator it = prism::find(begin(), end(), value);
	return (it == end()) ? false : true;
}

/**
 * Returns the number of times that \em value appears in the array.
 */
template <class T>
const int Array<T>::count(const T & value) const {
	return prism::count(begin(), end(), value);
}

/**
 * Returns a pointer to the internal array data.
 */
template <class T>
T * Array<T>::data() {
	return d->m_array;
}

/**
 * Returns a const_pointer to the internal array data.
 */
template <class T>
const T * Array<T>::data() const {
	return d->m_array;
}

/**
 * Returns an iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::iterator Array<T>::end() {
	return iterator(d->m_array+d->m_size);
}

/**
 * Returns a const_iterator to the imaginary element that follows the last element in the array.
 * As such this should never be dereferenced.
 */
template <class T>
typename Array<T>::const_iterator Array<T>::end() const {
	return iterator(d->m_array+d->m_size);
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
	auto it = prism::find(this->begin() + index, this->end(), value);
	return (it == this->end())
			? -1
			: it - this->begin();
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
const int Array<T>::lastIndexOf(const T & value, int index) const {
	auto bit = this->begin();
	auto eit = (index == -1) ? this->end() : this->begin() + index;

	auto it = prism::find_last(bit, eit, value);

	return (it == eit)
			? -1
			: it - this->begin();
}

/**
 * Returns the number of elements in the array.
 * Equivalent to size().
 */
template <class T>
const int Array<T>::length() const {
	return d->m_size;
}

/**
 * Returns a new array that is a subsection of this array. The new array starts from \em index
 * in this array. If \em length is -1 then all elements after \em index are copied over
 * otherwise \em length elements are copied instead.
 */
template <class T>
Array<T> Array<T>::mid(const int index, const int length) const {
	int subLength = (length == -1) ? this->size() - index : length;
	Array<T> sub(subLength);
	prism::copy_n(this->begin() + index, subLength, sub.begin());

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
	return d->m_size;
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
	return d->m_array[index];
}

/**
 * Returns a reference to the element stored at \em index.
 */
template <class T>
T & Array<T>::operator [](const int index) {
	return d->m_array[index];
}

/**
 * Returns a const reference to the element stored at \em index.
 */
template <class T>
const T & Array<T>::operator [](const int index) const {
	return d->m_array[index];
}

/**
 * Compares this array with \em rhs to see if they are equal to each other.
 * They are considered equal if they have the same length and the same values in the same order.
 */
template <class T>
const bool Array<T>::operator==(const Array<T> & rhs) const {
	if (d->m_size != rhs.size())
		return false;

	return prism::equal(this->begin(), this->end(), rhs.begin());
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

} // end namespace prism



#endif /* PRISM_ARRAY_PRIV_H_ */
