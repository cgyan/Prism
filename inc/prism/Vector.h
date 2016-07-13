/*
 * Vector.h
 * v0.1
 *
 *  Created on: Jan 16, 2015
 *      Author: iainhemstock
 */

/*
 * todo add support for initializer list constructor and move constructor
 * i.e. array<int> a = {1,2,3.4};
 */

#ifndef PRISM_VECTOR_H_
#define PRISM_VECTOR_H_

#include <iostream>
#include <vector>
#include <initializer_list>
#include <prism/Iterator>
#include <prism/List>
#include <prism/OutOfBoundsException>

namespace prism {

/******************************************************************************
 * VectorData
 *****************************************************************************/
// \cond DO_NOT_DOCUMENT
template <class T>
struct VectorData {
	struct memory {
		T* start;	// the start of the storage
		T* end; 	// one position after the last value
		T* finish; 	// the end of the storage
		const int exponent;
		memory() : start(0), end(0), finish(0), exponent(2) {}
		~memory() { delete [] start; start=0; end=0; finish=0; }
	};
	memory storage;
};
// \endcond
/******************************************************************************
 * Vector
 *****************************************************************************/
template <class T>
class Vector {
public:
	typedef RandomAccessIterator<T> 			iterator;
	typedef RandomAccessConstIterator<T>		const_iterator;
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
					Vector(const Vector<T>& copy);
					~Vector();
	void			append(const T& value);
	T&				at(const int index);
	const T&		at(const int index) const;
	reference		back();
	const_reference	back() const;
	iterator		begin();
	const_iterator	begin() const;
	const int		capacity() const;
	const_iterator	cbegin() const;
	const_iterator	cend() const;
	void			clear();
	const_iterator	constBegin() const;
	const T *		constData() const;
	const_iterator	constEnd() const;
	const bool		contains(const T& value) const;
	const int		count(const T& value) const;
	T *				data();
	const T * 		data() const;
	const bool		empty() const;
	iterator		end();
	const_iterator	end() const;
	const bool		endsWith(const T& value) const;
	iterator		erase(iterator pos);
	iterator		erase(iterator from, iterator to);
	void			fill(const T& value);
	T&				first();
	const T&		first() const;
	reference		front();
	const_reference	front() const;
	const int		indexOf(const T& value, const int from=0) const;
	void			insert(const int index, const T& value);
	void			insert(const int index, const int count, const T& value);
	iterator		insert(iterator insertBefore, const T& value);
	iterator		insert(iterator insertBefore, const int count, const T& value);
	const bool		isEmpty() const;
	T&				last();
	const T&		last() const;
	const int		lastIndexOf(const T& value, const int from=-1) const;
	Vector<T>		mid(const int startIndex, const int count=-1);
	void			pop_back();
	void			pop_front();
	void 			prepend(const T& value);
	void			push_back(const T& value);
	void			push_front(const T& value);
	void			remove(const int index);
	void			remove(const int index, const int count);
	void			removeAll(const T& value);
	void			removeFirst();
	void			removeLast();
	void			replace(const int index, const T& value);
	void 			reserve(const int newCapacity);
	const int		size() const;
	void			squeeze();
	const bool		startsWith(const T& value) const;
	List<T>			toList() const;
	std::vector<T>	toStdVector() const;

	static Vector<T>	fromList(const List<T>& list);
	static Vector<T>	fromStdVector(const std::vector<T>& stdVec);

	T&				operator[](const int index);
	const T&		operator[](const int index) const;
	Vector<T>&		operator<<(const T& value);
	Vector<T>& 		operator<<(const Vector<T> & rhs);
	Vector<T>&	 	operator=(const Vector<T> & rhs);
	const bool 		operator==(const Vector<T> & rhs) const;
	const bool 		operator!=(const Vector<T> & rhs) const;
	Vector<T> 		operator+(const Vector<T> & rhs) const;
	Vector<T> & 	operator+=(const Vector<T> & rhs);

	friend std::ostream& operator<<(std::ostream & out, const Vector<T> & v) {
		out << "Vector (" << &v << ", size=" << v.size() << ", capacity=" << v.capacity() /* << ", VectorData (&=" << v.d.data()*/ << ")\n";
		for (int i=0; i<v.size(); i++) out << "-- [" << i << "] " << *(v.d->storage.start+i) << "\n";
		return out;
	}
private:
	VectorData<T> * d;
private:
	const bool rangeCheck(const int index) const;
};

/**
 * Creates an empty vector.
 */
template <class T>
Vector<T>::Vector() : d(new VectorData<T>()) {

}

/**
 * Creates a vector containing \em size elements setting each value to its
 * default constructed value i.e. T() if a value is not provided.
 * If a value is provided then each element is set to \em value.
 */
template <class T>
Vector<T>::Vector(const int size, const T& value) : d(new VectorData<T>()) {
	reserve(size);
	insert(0, size, value);
}

/**
 * Copy-constructs a new vector that will contain all of the elements from \em copy.
 */
template <class T>
Vector<T>::Vector(const Vector<T>& copy) : d(new VectorData<T>()) {
	reserve(copy.capacity());

	const_iterator it = copy.cbegin();
	for (int i=0; i<copy.size(); i++)
		d->storage.start[i] = *it++;

	d->storage.end = d->storage.start + copy.size();
	d->storage.finish = d->storage.start + copy.capacity();
}

/**
 * Destroys this vector.
 */
template <class T>
Vector<T>::~Vector() {
	delete d;
}

/**
 * Appends \em value to the end of the vector.
 */
template <class T>
void Vector<T>::append(const T& value) {
	insert(end(), 1, value);
}

// todo add bounds checking to index
/**
 * Returns a reference to the element at \em index.
 * \em index must be 0<=index<size().
 */
template <class T>
T& Vector<T>::at(const int index) {
	if (!rangeCheck(index))
		throw prism::OutOfBoundsException(index);

	return this->operator[](index);
}

// todo add bounds checking to index
/**
 * Returns a const reference to the element at \em index.
 * \em index must be 0<=index<size().
 */
template <class T>
const T& Vector<T>::at(const int index) const {
	if (!rangeCheck(index))
		throw prism::OutOfBoundsException(index);

	return this->operator[](index);
}

/**
 * Returns a reference to the last element in the vector.
 */
template <class T>
typename Vector<T>::reference Vector<T>::back() {
	return *(d->storage.end-1);
}

/**
 * Returns a const reference to the last element in the vector.
 */
template <class T>
typename Vector<T>::const_reference Vector<T>::back() const {
	return *(d->storage.end-1);
}

/**
 * Returns an iterator that points to the first element in the vector.
 */
template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
	return iterator(d->storage.start);
}

/**
 * Returns a const iterator that points to the first element in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
	return const_iterator(d->storage.start);
}

/**
 * Returns the capacity of the vector.
 */
template <class T>
const int Vector<T>::capacity() const {
	return d->storage.finish - d->storage.start;
}

/**
 * Returns a const iterator that points to the first element in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const {
	return const_iterator(d->storage.start);
}

/**
 * Returns a const iterator that points to the imaginary element one after the last value in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::cend() const {
	return const_iterator(d->storage.end);
}

/**
 * Removes all elements from the vector leaving a size of 0.
 * The capacity however remains unchanged although can shrunk using squeeze() if required.
 */
template <class T>
void Vector<T>::clear() {
	erase(begin(), end());
}

/**
 * Returns a const iterator that points to the first element in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::constBegin() const {
	return const_iterator(d->storage.start);
}

/**
 * Returns a const pointer to the underlying array data.
 */
template <class T>
const T * Vector<T>::constData() const {
	return d->storage.start;
}

/**
 * Returns a const iterator that points to the imaginary element one after the last value in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::constEnd() const {
	return const_iterator(d->storage.end);
}

/**
 * Returns true if the vector contains one or more occurrences of \em value and false otherwise.
 * The vector's value type must support operator==().
 */
template <class T>
const bool Vector<T>::contains(const T& value) const {
	const_iterator it = cbegin();
	while (it != cend()) {
		if (*it++ == value) return true;
	}
	return false;
}

/**
 * Counts and returns the number of occurrences of /em value in the vector.
 * The vector's value type must support operator==().
 */
template <class T>
const int Vector<T>::count(const T& value) const {
	const_iterator it = cbegin();
	int c = 0;
	while (it != cend()) {
		if (*it++ == value) c++;
	}
	return c;
}

/**
 * Returns a pointer to the underlying array data.
 */
template <class T>
T * Vector<T>::data() {
	return d->storage.start;
}

/**
 * Returns a const pointer to the underlying array data.
 */
template <class T>
const T * Vector<T>::data() const {
	return d->storage.start;
}

/**
 * Returns true if this vector contains no elements i.e. size of 0 and false otherwise.
 * Equivalent to isEmpty().
 */
template <class T>
const bool Vector<T>::empty() const {
	return size() == 0;
}

/**
 * Returns an iterator to the imaginary element one position after the last value in the vector.
 */
template <class T>
typename Vector<T>::iterator Vector<T>::end() {
	return iterator(d->storage.end);
}

/**
 * Returns a const iterator to the imaginary element one position after the last value in the vector.
 */
template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const {
	return const_iterator(d->storage.end);
}

/**
 * Returns true if the vector is not empty and its last element is equal to \em value and false otherwise.
 * The vector's value type must support operator==().
 */
template <class T>
const bool Vector<T>::endsWith(const T& value) const {
	if (isEmpty()) return false;
	return back() == value;
}

/**
 * Erases the element pointed to by \em pos. Returns an iterator to the next position (which could be end()).
 */
template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
	return erase(pos, pos+1);
}

/**
 * Erases the elements pointed to by the iterator range of \em from and \em to.
 * Every element from \em from up to (but not including \em to) is erased.
 * Returns an iterator to the first element after the erased elements (could be equal to end()).
 */
template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator from, iterator to) {
	int count = to-from;
	int endIndex = to - begin();
	int s = size();
	int returnIndex = from - begin();

	for (int i=endIndex; i<s; i++) {
		d->storage.start[i-count] = d->storage.start[i];
	}
	d->storage.end -= count;

	return iterator(d->storage.start+returnIndex);
}

/**
 * Assigns \em value to every element in the vector.
 */
template <class T>
void Vector<T>::fill(const T& value) {
	iterator it = begin();
	while (it != end())
		*it++ = value;
}

/**
 * Returns a reference to the first element in the vector.
 */
template <class T>
T& Vector<T>::first() {
	return d->storage.start[0];
}

/**
 * Returns a const reference to the first element in the vector.
 */
template <class T>
const T& Vector<T>::first() const {
	return d->storage.start[0];
}

/**
 * Creates and returns a vector that contains all the items from \em list.
 */
template <class T>
Vector<T> Vector<T>::fromList(const List<T>& list) {
	Vector<T> v;
	v.reserve(list.size());

	typename List<T>::const_iterator it = list.cbegin();
	while (it != list.cend())
		v.append(*it++);

	return v;
}

/**
 * Creates and returns a vector of the same size and capacity and comprises the elements from the std::vector \em stdVec.
 */
template <class T>
Vector<T> Vector<T>::fromStdVector(const std::vector<T>& stdVec) {
	Vector<T> v;
	v.reserve(stdVec.capacity());

	for (int i=0; i<stdVec.size(); i++)
		v.append(stdVec.at(i));

	return v;
}

/**
 * Returns a reference to the first element in the vector.
 */
template <class T>
typename Vector<T>::reference Vector<T>::front() {
	return d->storage.start[0];
}

/**
 * Returns a const reference to the first element in the vector.
 */
template <class T>
typename Vector<T>::const_reference Vector<T>::front() const {
	return d->storage.start[0];
}

/**
 * Searches the vector starting from index \em from (default is 0 if not specified) and returns the index
 * of the first occurrence of \em value if found. Returns -1 otherwise.
 * The vector's value type must support operator==().
 */
template <class T>
const int Vector<T>::indexOf(const T& value, const int from) const {
	int s = size();
	for (int i=from; i<s; i++)
		if (d->storage.start[i] == value) return i;
	return -1;
}

/**
 * Inserts \em value at index \em index.
 */
template <class T>
void Vector<T>::insert(const int index, const T& value) {
	insert(index, 1, value);
}

/**
 * Inserts \em count copies of \em value starting at \em index..
 */
template <class T>
void Vector<T>::insert(const int index, const int count, const T& value) {
	insert(iterator(d->storage.start+index), count, value);
}

/**
 * todo bounds check index
 * Inserts \em count copies of \em value in front of the position represented by the iterator \em insertBefore.
 */
template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator insertBefore, const int count, const T& value) {
	int j = size()-1;
	int insertIndex = insertBefore - begin();

	// need to reallocate more space?
	if (size() + count > capacity()) {
		int newCapacity = (capacity() + count) * d->storage.exponent;
		reserve(newCapacity);
	}

	for (int i=j; i>=insertIndex; i--)
		d->storage.start[i+count] = d->storage.start[i];

	for (int j=0; j<count; j++) {
		d->storage.start[insertIndex+j] = T(value);
		d->storage.end++;
	}

	return iterator(d->storage.start+insertIndex);
}

/**
 * Inserts \em value in front of the position represented by the iterator \em insertBefore.
 */
template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator insertBefore, const T& value) {
	return insert(insertBefore, 1, value);
}

/**
 * Returns true if this vector contains no elements i.e. size of 0 and false otherwise.
 * Equivalent to empty().
 */
template <class T>
const bool Vector<T>::isEmpty() const {
	return size() == 0;
}

/**
 * Returns a reference to the last element in the vector.
 */
template <class T>
T& Vector<T>::last() {
	return back();
}

/**
 * Returns a const reference to the last element in the vector.
 */
template <class T>
const T& Vector<T>::last() const {
	return back();
}

/**
 * Returns the index of the last occurrence of \em value in the vector. It searches backwards from index \em from.
 * If /em from is -1 (the default) then the search starts from the last element.
 * Returns -1 if there is no match found.
 * The vector's value type must support operator==().
 */
template <class T>
const int Vector<T>::lastIndexOf(const T& value, const int from) const {
	int index = size()-1;
	if (from != -1) index = from;

	for (int i=index; i>= 0; i--)
		if (d->storage.start[i] == value) return i;

	return -1;
}

/**
 * Creates and returns a new vector containing \em count elements from this vector starting from \em index.
 * If \em count is -1 (the default) then all elements after \em index are copied across.
 * It performs a bounds check so if \em startIndex + \em count goes past the end of the vector's storage
 * then all the elements from \em startIndex up to and including the final element are copied over.
 */
template <class T>
Vector<T> Vector<T>::mid(const int startIndex, const int count) {
	int subLength = count;
	bool copyAllAfterIndex = (subLength == -1);
	bool outOfBounds = (startIndex + subLength >= size());

	if (copyAllAfterIndex || outOfBounds)
		subLength = size() - startIndex;

	Vector<T> sub;
	sub.reserve(subLength);

	for (int i=startIndex; i<startIndex+subLength; i++)
		sub.append(d->storage.start[i]);

	return sub;
}

/**
 * Removes the last element from the vector.
 */
template <class T>
void Vector<T>::pop_back() {
	erase(end()-1, end());
}

/**
 * Removes the first element from the vector.
 */
template <class T>
void Vector<T>::pop_front() {
	erase(begin(), begin()+1);
}

/**
 * Inserts \em value at the start of the vector.
 */
template <class T>
void Vector<T>::prepend(const T& value) {
	insert(begin(), 1, value);
}

/**
 * Appends \em value at the end of the vector.
 */
template <class T>
void Vector<T>::push_back(const T& value) {
	insert(end(), 1, value);
}

/**
 * Adds \em value at the start of the vector.
 */
template <class T>
void Vector<T>::push_front(const T& value) {
	insert(begin(), 1, value);
}

/**
 * Private method that checks that the index is within bounds.
 * Returns false if the index is invalid, true otherwise.
 */
template <class T>
const bool Vector<T>::rangeCheck(const int index) const {
	if (index < 0 || index >= size()) return false;
	return true;
}

/**
 * Removes the element at \em index.
 */
template <class T>
void Vector<T>::remove(const int index) {
	erase(begin()+index);
}

/**
 * Removes \em count elements starting from \em index.
 */
template <class T>
void Vector<T>::remove(const int index, const int count) {
	iterator from = begin()+index;
	iterator to = from + count;
	erase(from, to);
}

/**
 * Removes all occurrences of \em value from the vector.
 * The vector's value type must support operator==().
 */
template <class T>
void Vector<T>::removeAll(const T & value) {
	iterator it = begin();
	while (it != end()) {
		if (*it == value)
			it = erase(it);
		else it++;
	}
}

/**
 * Removes the first element of the vector.
 */
template <class T>
void Vector<T>::removeFirst() {
	erase(begin(), begin()+1);
}

/**
 * Removes the last element of the vector.
 */
template <class T>
void Vector<T>::removeLast() {
	erase(end()-1, end());
}

/**
 * Replaces the value at \em index with \em value.
 * \em index must be 0<=index>size().
 */
template <class T>
void Vector<T>::replace(const int index, const T& value) {
	d->storage.start[index] = value;
}

/**
 * Reserves enough memory for the vector to contain \em newCapacity elements i.e. newCapacity * sizeof(T).
 * The capacity can only grow and will not lessen even if clear() or erase() is called. Only squeeze() can
 * alter the capacity to a lower amount. If \em newCapacity is less than or equal to the current capacity then
 * nothing changes. Any existing elements in the vector are not affected by this function.
 */
template <class T>
void Vector<T>::reserve(const int newCapacity) {
	if (newCapacity <= capacity()) return;

	T * newStorage = new T[newCapacity];
	int s = size();

	for (int i=0; i<s; i++)
		newStorage[i] = d->storage.start[i];

	delete [] d->storage.start;
	d->storage.start = newStorage;
	d->storage.end = d->storage.start + s;
	d->storage.finish = d->storage.start + newCapacity;
}

/**
 * Returns the number of elements currently stored in the vector.
 */
template <class T>
const int Vector<T>::size() const {
	return d->storage.end - d->storage.start;
}

/**
 * Destroys any unused memory currently held by this vector. For example, if the vector has a capacity
 * of 10 and a size of 4, squeeze() will release the extra memory of the capacity resulting in a capacity and size of 4.
 * If size() and capacity() are already equal then nothing happens.
 */
template <class T>
void Vector<T>::squeeze() {
	if (size() == capacity()) return;
	int s = size();

	T * array = new T[size()];
	const_iterator it = cbegin();
	for (int i=0; i<s; i++)
		array[i] = *it++;

	delete [] d->storage.start;
	d->storage.start = array;
	d->storage.end = d->storage.start + s;
	d->storage.finish = d->storage.start + s;
}

/**
 * Returns true if the vector is not empty and its first element is equal to \em value and false otherwise.
 */
template <class T>
const bool Vector<T>::startsWith(const T& value) const {
	if (isEmpty()) return false;
	return first() == value;
}

/**
 * Creates and returns a List containing all the elements from this vector.
 */
template <class T>
List<T> Vector<T>::toList() const {
	List<T> list;
	const_iterator it = cbegin();

	while (it != cend())
		list.append(*it++);

	return list;
}

/**
 * Creates an returns a std::vector containing all the elements from this vector.
 */
template <class T>
std::vector<T> Vector<T>::toStdVector() const {
	std::vector<T> v;
	v.reserve(capacity());

	const_iterator it = cbegin();
	while (it != cend())
		v.push_back(*it++);

	return v;
}

/**
 * Returns a reference to the element at \em index.
 * \em index must be 0<=index<size().
 */
template <class T>
T& Vector<T>::operator [](const int index) {
	return d->storage.start[index];
}

/**
 * Returns a reference to the element at \em index.
 * \em index must be 0<=index<size().
 */
template <class T>
const T& Vector<T>::operator [](const int index) const {
	return d->storage.start[index];
}

/**
 * Appends \em value to the end of the vector. Equivalent to append().
 */
template <class T>
Vector<T>& Vector<T>::operator<<(const T& value) {
	insert(end(), value);
	return *this;
}

/**
 * Appends the contents of the \em rhs vector onto the end of this vector.
 * Returns a reference to this vector.
 */
template <class T>
Vector<T>& Vector<T>::operator<<(const Vector<T>& rhs) {
	const_iterator it = rhs.cbegin();
	while (it != rhs.cend())
		append(*it++);

	return *this;
}

/**
 * Assignment operator assigns all of the elements from the vector \em rhs to this vector.
 * Returns a reference to this vector.
 */
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
	if (rhs.capacity() != 0) {
		T * array = new T[rhs.capacity()];
		for (int i=0; i<rhs.size(); i++)
			array[i] = rhs[i];

		delete [] d->storage.start;
		d->storage.start = array;
		d->storage.end = d->storage.start + rhs.size();
		d->storage.finish = d->storage.start + rhs.capacity();
	}
	return *this;
}

/**
 * Compares this vector with \em rhs and if both have the same number of elements in the same order then they are considered equal.
 * Returns true if they are equal or false otherwise.
 */
template <class T>
const bool Vector<T>::operator==(const Vector<T>& rhs) const {
	if (size() != rhs.size()) return false;

	const_iterator itThis = cbegin();
	const_iterator itRhs = rhs.cbegin();

	while (itThis != cend())
		if (*itThis++ != *itRhs++) return false;

	return true;
}

/**
 * Compares this vector with \em rhs and if both have the same number of elements in the same order then they are considered equal.
 * Returns true if they are equal or false otherwise.
 */
template <class T>
const bool Vector<T>::operator!=(const Vector<T>& rhs) const {
	return !(*this == rhs);
}

/**
 * Creates and returns a new vector that contains all of the elements from this vector followed by the elements from \em rhs.
 */
template <class T>
Vector<T> Vector<T>::operator+(const Vector<T> & rhs) const {
	Vector<T> v(*this);
	v << rhs;
	return v;
}

/**
 * Appends the contents of \em rhs onto the end of this vector.
 * Returns a reference to this vector.
 */
template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T> & rhs) {
	*this << rhs;
	return *this;
}

}



#endif /* PRISM_VECTOR_H_ */
