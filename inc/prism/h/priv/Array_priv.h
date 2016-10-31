/*
 * Array_priv.h
 * v1
 *
 *  Created on: Oct 27, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ARRAY_PRIV_H_
#define PRISM_ARRAY_PRIV_H_

#include <prism/h/algorithm.h>
#include <prism/h/OutOfBoundsException.h>
#include <memory>

namespace prism {

//=============================================================================================
// ArrayData
//=============================================================================================
template <typename T, size_t Size>
struct Array<T,Size>::ArrayData {
	T array[Size];

	ArrayData() 								= default;
	ArrayData(const ArrayData& copy) 			= default;
	ArrayData(ArrayData&& other) 				= default;
	ArrayData& operator=(const ArrayData& rhs) 	= default;
	ArrayData& operator=(ArrayData&& rhs) 		= default;
	~ArrayData()								= default;

	/*
	 *
	 */
	T&
	ref(const size_t index) {
		return array[index];
	}

	/*
	 *
	 */
	const T&
	ref(const size_t index) const {
		return array[index];
	}

	/*
	 *
	 */
	T*
	data() {
		return &array[0];
	}

	/*
	 *
	 */
	const T*
	data() const {
		return &array[0];
	}
};
//=============================================================================================
// Array
//=============================================================================================
/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
Array()
: d(new ArrayData)
{}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
Array(typename Array<T,Size>::const_reference value)
: d(new ArrayData)
{
	prism::fill(this->begin(), this->end(), value);
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
Array(const std::initializer_list<T> & il)
: d(new ArrayData)
{
	prism::copy(il.begin(), il.end(), this->begin());
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
Array(const Array<T,Size>& copy)
: d(new ArrayData)
{
	prism::copy(copy.data(), copy.data()+Size, this->data());
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
Array(Array<T,Size>&& other)
: d(new ArrayData)
{
	prism::swap(d, other.d);
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>::
~Array() {
	delete d;
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>&
Array<T,Size>::
operator=(const Array<T,Size>& rhs)
{
	Array newArray(rhs);
	prism::swap(this->d, newArray.d);
	return *this;
}

/*
 *
 */
template <typename T, size_t Size>
Array<T,Size>&
Array<T,Size>::
operator=(Array<T,Size>&& rhs)
{
	using prism::swap;
	swap(this->d, rhs.d);
	return *this;
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::reference
Array<T,Size>::
at(const size_t index) {
	if (index < 0 || index >= Size)
		throw prism::OutOfBoundsException(index);
	return d->ref(index);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_reference
Array<T,Size>::
at(const size_t index) const {
	if (index < 0 || index >= Size)
		throw prism::OutOfBoundsException(index);
	return d->ref(index);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::reference
Array<T,Size>::
back() {
	return d->ref(Size-1);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_reference
Array<T,Size>::
back() const {
	return d->ref(Size-1);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::iterator
Array<T,Size>::
begin() noexcept {
	return iterator(d->data());
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
begin() const noexcept {
	return const_iterator(d->data());
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
cbegin() const noexcept {
	return const_iterator(d->data());
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
constBegin() const noexcept {
	return const_iterator(d->data());
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_pointer
Array<T,Size>::
constData() const noexcept {
	return d->data();
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
cend() const noexcept {
	return const_iterator(d->data()+Size);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
constEnd() const noexcept {
	return const_iterator(d->data()+Size);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::pointer
Array<T,Size>::
data() noexcept {
	return d->data();
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_pointer
Array<T,Size>::
data() const noexcept {
	return d->data();
}

/*
 *
 */
template <typename T, size_t Size>
const bool
Array<T,Size>::
empty() const noexcept {
	return Size == 0;
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::iterator
Array<T,Size>::
end() noexcept {
	return iterator(d->data()+Size);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_iterator
Array<T,Size>::
end() const noexcept {
	return const_iterator(d->data()+Size);
}

/*
 *
 */
template <typename T, size_t Size>
void
Array<T,Size>::
fill(const_reference value) {
	prism::fill(this->begin(), this->end(), value);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::reference
Array<T,Size>::
first() {
	return d->ref(0);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_reference
Array<T,Size>::
first() const {
	return d->ref(0);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::reference
Array<T,Size>::
last() {
	return d->ref(Size-1);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_reference
Array<T,Size>::
last() const {
	return d->ref(Size-1);
}

/*
 *
 */
template <typename T, size_t Size>
const typename Array<T,Size>::size_type
Array<T,Size>::
size() const noexcept {
	return Size;
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::reference
Array<T,Size>::
operator[](const size_t index) {
	return d->ref(index);
}

/*
 *
 */
template <typename T, size_t Size>
typename Array<T,Size>::const_reference
Array<T,Size>::
operator[](const size_t index) const {
	return d->ref(index);
}

/*
 *
 */
template <typename T, size_t Size>
void
Array<T,Size>::
swap(Array<T,Size>& other) noexcept {
	using prism::swap;
	swap(d, other.d);
}

/*
 *
 */
template <typename T, size_t Size>
void
swap(Array<T,Size>& a, Array<T,Size>& b) {
	a.swap(b);
}

/*
 *
 */
template <typename T, size_t Size>
const bool
operator==(const Array<T,Size>& a, const Array<T,Size>& b) {
	return prism::equal(a.begin(), a.end(), b.begin());
}

/*
 *
 */
template <typename T, size_t Size>
const bool
operator!=(const Array<T,Size>& a, const Array<T,Size>& b) {
	return !(a==b);
}



} // end namespace prism



#endif /* PRISM_ARRAY_PRIV_H_ */
