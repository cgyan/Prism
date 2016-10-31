/*
 * Array.h
 * v1
 *
 *  Created on: Oct 27, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ARRAY_H_
#define PRISM_ARRAY_H_

#include <prism/h/iterator.h>
#include <initializer_list>
#include <stddef.h>
#include <ostream>

namespace prism {
//============================================================
// Array
//============================================================
/// @class 	Array prism/h/Array.h prism/Array
///
/// @brief 	A fixed size sequence based container
///
/// 		More detailed description here
///
/// @since	1.0.0
template <typename T, size_t Size>
class Array {
public:
	typedef T 							value_type;
	typedef T* 							pointer;
	typedef T& 							reference;
	typedef const T* 					const_pointer;
	typedef const T& 					const_reference;
	typedef std::ptrdiff_t 				difference_type;
	typedef size_t 						size_type;
	typedef SequenceIterator<T,false> 	iterator;
	typedef SequenceIterator<T,true> 	const_iterator;
public:
	///
	/// @brief 				Constructs an array to a size of the template argument @em size.
	///
	///						If the value type is a class then the default constructor is called
	///						for each element whereas if it is a fundamental type the elements
	///						are not initialized.
	///
	/// @since 				1.0.0
	explicit Array();

	///
	/// @brief 				Constructs an array to a size of the template argument @em size amd
	///						fills it with a given value.
	///
	/// @since 				1.0.0
	explicit Array(const_reference value);

	///
	/// @brief				Constructs an array from the elements in an initializer list
	///
	/// @since				1.0.0
	explicit Array(const std::initializer_list<T>& il);

	///
	/// @brief				Copy-constructs this array from another array
	///
	/// @param [in] copy	The array to make copy into this array
	///
	/// @since				1.0.0
	explicit Array(const Array<T,Size> & copy);

	///
	/// @brief				Move-constructs an array using the elements from @em other
	///
	/// @param other		An array where the elements are moved into this array
	///
	/// @since 				1.0.0
	explicit Array(Array<T,Size>&& other);

	///
	/// @brief				Assigns another array to this array
	///
	/// @param other		The array to assign to this array
	///
	/// @return				A reference to this array
	///
	/// @since				1.0.0
	Array<T,Size>&
	operator=(const Array<T,Size>& rhs);

	///
	/// @brief				Moves the contents of another array into this array
	///
	/// @param other		The array to move its contents from
	///
	/// @return				A reference to this array
	///
	/// @since				1.0.0
	Array<T,Size>&
	operator=(Array<T,Size>&& rhs);

	///
	/// @brief				Destroys this array. If the elements are pointers then it is the
	///						user's responsibility to destroy the memory they point to.
	///
	/// @since				1.0.0
	///
	virtual ~Array();

	///
	/// @brief				Accesses the element at the given index
	///
	/// @param index		The index of the element to be accessed
	///
	/// @throws				Throws an OutOfBoundsException if @em index is less than 0 or
	///						greater than / equal to the array's size
	///
	/// @return				A reference to the element at the given index
	///
	/// @since 				1.0.0
	reference
	at(const size_type index);

	///
	/// @brief				Accesses the element at the given index
	///
	/// @param index		The index of the element to be accessed
	///
	/// @return				A const reference to the element at the given index
	///
	/// @since				1.0.0
	const_reference
	at(const size_type index) const;

	///
	/// @brief				Accesses the last element
	///
	/// @return				A reference to the last element
	///
	/// @since				1.0.0
	reference
	back();

	///
	/// @brief				Accesses the last element
	///
	/// @return				A const reference to the last element
	///
	/// @since				1.0.0
	const_reference
	back() const;

	///
	/// @brief				An iterator that points to the first element
	///
	/// @return				An iterator that points to the first element
	///
	/// @since				1.0.0
	iterator
	begin() noexcept;

	///
	/// @brief				A const iterator that points to the first element
	///
	/// @return				A const iterator that points to the first element
	///
	/// @since				1.0.0
	const_iterator
	begin() const noexcept;

	///
	/// @brief				A const iterator that points to the first element
	///
	/// @return				A const iterator that points to the first element
	///
	/// @since				1.0.0
	const_iterator
	cbegin() const noexcept;

	///
	/// @brief				A const iterator that points to the first element
	///
	/// @return				A const iterator that points to the first element
	///
	/// @since				1.0.0
	const_iterator
	constBegin() const noexcept;

	///
	/// @brief				Gets a pointer to the underlying data
	///
	/// @return				A const pointer to the start of the underlying data
	///
	/// @since				1.0.0
	const_pointer
	constData() const noexcept;

	///
	/// @brief				A const iterator that points to the position past the last element
	///
	/// @return				A const iterator that points to the position past the last element
	///
	/// @since				1.0.0
	const_iterator
	cend() const noexcept;

	///
	/// @brief				A const iterator that points to the position past the last element
	///
	/// @return				A const iterator that points to the position past the last element
	///
	/// @since				1.0.0
	const_iterator
	constEnd() const noexcept;

	///
	/// @brief				Gets a pointer to the start of the underlying data
	///
	/// @return				A pointer to the start of the underlying data
	///
	/// @since				1.0.0
	pointer
	data() noexcept;

	///
	/// @brief				Gets a const pointer to the start of the underlying data
	///
	/// @return				A const pointer to the start of the underlying data
	///
	/// @since				1.0.0
	const_pointer
	data() const noexcept;

	///
	/// @brief				Checks if the array is empty or not
	///
	/// @return				Returns true if the array size is 0 or false otherwise
	///
	/// @since				1.0.0
	const bool
	empty() const noexcept;

	///
	/// @brief				An iterator that points to the position past the last element
	///
	/// @return				An iterator that points to the position past the last element
	///
	/// @since				1.0.0
	iterator
	end() noexcept;

	///
	/// @brief				A const iterator that points to the position past the last element
	///
	/// @return				A const iterator that points to the position past the last element
	///
	/// @since				1.0.0
	const_iterator
	end() const noexcept;

	///
	/// @brief				Fills the array with a given value
	///
	/// @param value		The value to fill the array with
	///
	/// @return				Nothing
	///
	/// @since				1.0.0
	void
	fill(const_reference value);

	///
	/// @brief				Accesses the first element
	///
	/// @return				A reference to the first element
	///
	/// @since				1.0.0
	reference
	first();

	///
	/// @brief				Accesses the first element
	///
	/// @return				A const reference to the first element
	///
	/// @since				1.0.0
	const_reference
	first() const;

	///
	/// @brief				Accesses the last element
	///
	/// @return				A reference to the last element
	///
	/// @since				1.0.0
	reference
	last();

	///
	/// @brief				Accesses the last element
	///
	/// @return				A const reference to the last element
	///
	/// @since				1.0.0
	const_reference
	last() const;

	///
	/// @brief				The number of elements in the array
	///
	/// @return				The size of the array i.e. the number of elements stored
	///
	/// @since				1.0.0
	const size_type
	size() const noexcept;
//
	///
	/// @brief				Swaps the elements of the two arrays
	///
	///						At the end of the function the contents of this array will be in
	///						the other array and the contents of the other array will be in
	///						this array.
	///
	/// @param other		The array to swap contents with
	///
	/// @return
	///
	/// @since				1.0.0
	void
	swap(Array<T,Size>& other) noexcept;

	///
	/// @brief				Accesses the element at a given index
	///
	/// @param index		The index of the element to be accessed
	///
	/// @return				A reference to the element at the given index
	///
	/// @since				1.0.0
	reference
	operator[](const size_type index);

	///
	/// @brief				Accesses the element at a given index
	///
	/// @param index		The index of the element to be accessed
	///
	/// @return				A const reference to the element at the given index
	///
	/// @since				1.0.0
	const_reference
	operator[](const size_type index) const;

private:
	struct ArrayData;
	ArrayData * d;
}; // end class Array
//=============================================================================================
// Related non-members
//=============================================================================================
///
/// @brief				Compares two arrays for equality
///
/// @param lhs			The first array
/// @param rhs			The second array
///
/// @return				Returns true if the arrays are equal or false otherwise. Two arrays are
///						equivalent if they have the same size and the same elements in the
///						same order
///
/// @since				1.0.0
template <typename T, size_t size>
const bool
operator==(const Array<T,size>& lhs, const Array<T,size>& rhs);

///
/// @brief				Compares two arrays for inequality
///
/// @param lhs			The first array
/// @param rhs			The second array
///
/// @return				Returns true if the arrays are not equal or false otherwise. Two arrays
///						are equivalent if they have the same size and the same elements in the
///						same order
///
/// @since				1.0.0
template <typename T, size_t size>
const bool
operator!=(const Array<T,size>& lhs, const Array<T,size>& rhs);

///
/// @brief				Swaps the contents of two arrays
///
/// @param a			The first array
/// @param b			The second array
///
/// @return				Nothing
///
/// @since				1.0.0
template <typename T, size_t Size>
void swap(Array<T,Size>& a, Array<T,Size>& b);

} // end namespace prism

#include <prism/h/priv/Array_priv.h>

#endif /* PRISM_ARRAY_H_ */
