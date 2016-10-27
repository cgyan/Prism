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
	typedef const T* 						const_pointer;
	typedef const T& 						const_reference;
	typedef size_t 							size_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef random_access_iterator_tag		iterator_category;
	typedef SequenceIterator<T,false> 		iterator;
	typedef SequenceIterator<T,true>		const_iterator;

private:
	struct ArrayData;
	ArrayData * d;

private:
	///
	/// @brief 				This constructor is made private so that it cannot be called
	///						externally.
	///
	/// @since 				1.0.0
	Array();

public:
	///
	/// @brief 				Creates an array of size \em size and fills each element with
	///						default-constructed values.
	///
	/// @param [in] size	The number of default initialized elements to initialize the
	///						array with
	///
	/// @since				1.0.0
	///
	Array(const int size);

	///
	/// @brief				Creates an array of size \em size and fills each element with
	///						\em value.
	///
	/// @param [in] size	The number of elements to initialize the array with
	/// @param [in] value	The value to initialize all new elements with
	///
	/// @since 				1.0.0
	///
	Array(const int size, const T & value);

	///
	/// @brief				Creates an array populated from the elements of the initializer list.
	///
	/// @param [in] il		An initializer list to initialize the array with
	///
	/// @since 				1.0.0
	///
	Array(std::initializer_list<T> il);

	///
	/// @brief				Copy-constructs this array from another array
	///
	/// @param [in] copy	The array to make copy into this array
	///
	/// @since				1.0.0
	Array(const Array<T> & copy);

	///
	/// @brief				Destroys this array. If the elements are pointers then it is the
	///						user's responsibility to destroy the memory they point to.
	///
	/// @since				1.0.0
	///
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
	const int		lastIndexOf(const T & value, int index=-1) const;
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

} // end namespace prim

#include <prism/h/priv/Array_priv.h>

#endif /* PRISM_ARRAY_H_ */
