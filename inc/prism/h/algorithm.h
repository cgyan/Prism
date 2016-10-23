/*
 * algorithm.h
 * v1
 *
 *  Created on: Sep 17, 2016
 *      Author: iainhemstock
 */

// todo in documentation state whether an algorithm modifies the input or not

///
/// @file 					algorithm.h
///
/// @brief 					Algorithms for use with the Prism containers.
///
/// 						There are numerous algorithms presented here that can be used in
///							conjunction with the Prism containers.
///
/// @since 					1.0.0

#ifndef PRISM_ALGORITHM_H_
#define PRISM_ALGORITHM_H_

namespace prism {

/// @brief 					Finds two consecutive matching elements in a range.
///
/// 						Searches the range @em [first,last] for the first
///							occurrence of two consecutive elements that match.
///
///							The range is @em [first,last],
///							which contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param[in] first 		The iterator pointing to the start of the range
/// @param[in] last 		The iterator pointing to the end of the range
///
/// @return 				Returns an iterator to the first of these two elements, or
/// 						@em last if no such pair is found.
///
/// @since 					1.0.0
template <class ForwardIterator>
ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last);

/// @brief 					Checks if all the elements match a condition in a range
///
/// 						Each element in the range @em [first,last] is
///							matched against the condition in @em pred.
///
///							The range is @em [first,last],
///							which contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in] first 		An iterator pointing to the first element in the range
/// @param [in] last 		An iterator pointing to the position after the last element in the
///							range
/// @param [in] pred 		A unary function that returns true or false
///
/// @return 				Returns true if the predicate returns true for all of the elements
///							in the range or false otherwise.
///
/// Example usage
/// @code
/// bool isEven(const int n) { return n % 2 == 0; }
///
/// int a[5] = {2,4,6,8,10};
/// bool allEven = prism::all_of(a, a+5, isEven);
/// cout << allEven;
///
/// output: 1
/// @endcode
///
/// @see 					any_of()
///
/// @since 					1.0.0
template <class InputIterator, class UnaryPredicate>
bool
all_of(InputIterator first, InputIterator last, UnaryPredicate pred);

/// @brief 					Checks if any elements match a condition in a range
///
/// 						Each element in the range @em [first,last] is
///							checked against the condition in <em><b>pred</b></em> until one of
///							them matches.
///
///							The range is @em [first,last],
///							which contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in] first 		An iterator pointing to the first element in the range
/// @param [in] last 		An iterator pointing to the position past the last element in the
///							range
/// @param [in] pred 		A unary function that returns true or false
///
/// @return 				Returns true if any of the elements match the condition in
///							@em pred or false otherwise
///
/// Example usage
/// @code
/// bool isEven(const int n) { return n % 2 == 0; }
///
/// int a[5] = {1,3,5,8,9};
/// bool anyEven = prism::any_of(a, a+5, isEven);
/// cout << anyEven;
///
/// output: 1
/// @endcode
///
/// @see 					all_of()
///
/// @since 					1.0.0
template <class InputIterator, class UnaryPredicate>
bool
any_of(InputIterator first, InputIterator last, UnaryPredicate pred);

/// @brief 					Copies the elements from one range to another range
///
/// 						Copies the elements in the range @em [first,last]
///							and places them at the range beginning from
///							@em otherFirst
///
///							The range is @em [first,last],
///							which contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in] first 		An iterator pointing to the first element in the range to be copied
/// @param [in] last 		An iterator pointing to the position after the last element in the
///							range to be copied
/// @param [in] otherFirst	An iterator pointing to the start of the range where the copies
///							will be placed.
///
/// @return					An iterator pointing to the end of the destination range
///
/// @code
/// 						int a[5] = {1,2,3,4,5};
///							int b[5];
///
///							prism::copy(a, a+5, b);
///							// b == [1,2,3,4,5]
/// @endcode
///
/// @see 					copy_backward(), copy_if(), copy_n()
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator otherFirst);



/// @brief					Copies a range to another range backwards
///
///							Copies the elements in the range @em [first,last] starting from
///							@em last to the range ending at @em otherLast.

///							The elements copied are between @em first and @em last, including
///							@em first but not @em last. @em otherLast should point to the
///							past-the-end position of the destination range.
///
/// @param [in] first		An iterator that points to the start of the range to be copied
/// @param [in] last		An iterator that points to the position after the last element
///							to be copied
/// @param [in] otherLast	An iterator that points to the position after where the copied range
///							should finish
///
/// @return					An iterator that points to the first element of the copied range in
///							the destination range
///
/// @since 					1.0.0
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first,
				BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast);



/// @brief					Copies elements from a range to another range only if they meet
///							a condition
///
///							Each element from the range @em [first,last] is matched against
///							the condition in @em pred which if true the element is copied
///							across to the range beginning at @em otherFirst.
///
///							The range is @em [first,last],
///							which contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in] first		An iterator that points to the first element in the range to be
///							copied from
/// @param [in] last		An iterator that points to the position after the last element in
///							the range to be copied from
/// @param [in] otherFirst	An iterator that points to the start of the destination range
/// @param [in] pred		A unary function that returns true or false
///
/// @return					An iterator that is one position past the last inserted element in
///							the destination range
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
copy_if(InputIterator first,
		InputIterator last,
		OutputIterator otherFirst,
		UnaryPredicate pred);

/// @brief 					Copies a specified number of elements from one range to another range
///
///							Copies @em n amount of elements from the range beginning at @em
///							first to the range beginning at @em otherFirst
///
/// @param [in]	first		An iterator that points to the first element in the range to be
///							copied
/// @param [in] n			The number of elements to be copied
/// @param [in] otherFirst	An iterator that points to the start of the destination range
///
/// @return					An iterator that is one position past the last inserted element in
///							the destination range
///
/// @since 					1.0.0
template <class InputIterator, class Size, class OutputIterator>
OutputIterator
copy_n(InputIterator first, Size n, OutputIterator otherFirst);

/// @brief 					Counts the number of occurrences of a value in a range.
///
///							Searches the range @em [first,last] and counts
///							the number of occurrences of elements matching
///							@em value.
///
///							The range is @em [first,last], which
///							contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in]	first		An iterator that points to the start of the range to be searched
/// @param [in] last		An iterator that points to the position after the last element to
///							be searched
/// @param [in] value		The value that each element will be compared to
///
/// @return					The number of times that @em value appears in
///							the range
///
/// @since 					1.0.0
template <class InputIterator, class T>
int
count(InputIterator first, InputIterator last, const T& value);

/// @brief 					Counts the number of occurrences of a value that meets a condition
///							in a range
///
///							Iterates through the range @em [first,last] and
///							compares each element to the predicate @em pred.
///							If @em pred returns true for that element then
///							it will be counted.
///
///							The range is @em [first,last], which
///							contains all the elements  between @em first
///							and @em last, including the element pointed to
///							by @em first but not the element pointed to by
///							@em last.
///
/// @param [in]	first		An iterator that points to the start of the range to be counted
/// @param [in]	last		An iterator that points to the position after the last element of
///							the range to be counted
/// @param [in] pred		A unary function that returns true or false
///
/// @return					The number of elements that match the condition in
///							@em pred
///
/// @since 					1.0.0
template <class InputIterator, class UnaryPredicate>
int
count_if(InputIterator first, InputIterator last, UnaryPredicate pred);

/// @brief 					Compares two ranges for equality
///
///							Compares all the elements in the range [first,last] against the
///							elements in the range beginning from @ otherFirst. Comparison is
///							made using operator==() so the element must support that operator.
///
/// @param [in]	first		An iterator that points to the start of the first range
/// @param [in]	last		An iterator that points to the position after the last element of
///							the first range
/// @param [in]	otherFirst	An iterator that points to the start of the second range
///
/// @return					If each element from the first range matches the corresponding
///							element in the second range then @em true is returned and @em false
///							otherwise.
///
/// @since 					1.0.0
template <class InputIterator1, class InputIterator2>
bool
equal(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst);

/// @brief 					Fills a range with a value
///
///							Assigns @em value to each element in the range [first,last].
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to one position past the last element in
///							the range
/// @param [in] value		The value to be assigned
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
void
fill(ForwardIterator first, ForwardIterator last, const T& value);

/// @brief 					Assigns a value to a specified number of elements in a range
///
///							Assigns @em value to the first @size elements starting from @em first
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] size		The number of assignments to take place
/// @param [in]	value		The value to be assigned
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
void
fill_n(ForwardIterator first, int size, const T& value);

/// @brief 					Finds a value in a range
///
///							Searches the range [first,last] for the first value equal to
///							@em value. Comparison is made using operator==() so the element
///							must support that operator.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position after the last element in
///							the range
/// @param [in] value		The value to be found
///
/// @return					An iterator that points to the found value or @em last if no element
///							is found.
///
/// @since 					1.0.0
template <class InputIterator, class T>
InputIterator
find(InputIterator first, InputIterator last, const T& value);

/// @brief 					Finds the first value in a range for which a predicate returns true
///
///							Searches the range [first,last] to find the first element for which
///							@em pred returns true.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in]	first		An iterator that points to the first element in the range
/// @param [in]	last		An iterator that points to the position after the last element of
///							the range
/// @param [in] pred		A unary function that returns true or false
///
/// @return					An iterator that points to the first found element for which
///							@em pred return true or @em last if no element is found
///
/// @since 					1.0.0
template <class InputIterator, class UnaryPredicate>
InputIterator
find_if(InputIterator first, InputIterator last, UnaryPredicate pred);

/// @brief 					Finds the last value in a range that matches a specified value
///
///							Searches the range [first,last] for the last occurrence of @em value
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element of
///							the range
/// @param [in] value		The value to be found
///
/// @return					An iterator that points to the found element or @em last if no
///							element is found
///
/// @since 					1.0.0
template <class InputIterator, class T>
InputIterator
find_last(InputIterator first, InputIterator last, const T& value);

/// @brief 					Calls a function for each element in a range.
///
///							For all elements in a range [first,last] a function @em func is
///							called where each element is passed into the function as an
///							argument.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] func		The function to be called for each element
///
/// @return					The function @em func
///
/// @since 					1.0.0
template <class InputIterator, class UnaryFunction>
UnaryFunction
for_each(InputIterator first, InputIterator last, UnaryFunction func);

/// @brief 					Checks if a range is sorted in ascending order
///
///							Checks the elements in a range [first,last] to see if they are
///							arranged in ascending order. The element type must support
///							operator<().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] func		A unary function that takes an argument from the range [frst,last]
///
/// @return					True if the range is sorted in ascending order or false otherwise
///
/// @since 					1.0.0
template <class ForwardIterator>
const bool
is_sorted(ForwardIterator first, ForwardIterator last);

/// @brief					Rearranges a range into a heap order
///
///							todo WRITE A BETTER EXPLANATION OF WHAT A HEAP IS
///							Transforms a range [first,last] in such a way that it forms a heap.
///							This makes retrieving the element with the highest value very fast.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class RandomAccessIterator>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last);

/// @brief 					Determines which value is greater
///
///							Compares the values @em a and @em b to find out which one has the
///							greater value
///
/// @param [in] a			The first value
/// @param [in] b			The second value
///
/// @return					@em a or @em b, whichever is the greater value
///
/// @since 					1.0.0
template <class T>
const T&
max(const T& a, const T& b);

/// @brief 					Determines which value is lesser
///
///							Compares the values @em a and @em b to find out which one has the
///							lesser value
///
/// @param [in] a			The first value
/// @param [in] b			The second value
///
/// @return					@em a or @em b, whichever is the lesser value
///
/// @since 					1.0.0
template <class T>
const T&
min(const T& a, const T& b);

/// @brief 					Checks elements in a range to see if they don't match a condition
///
///							Each element in the range [first,last] is checked to make sure it
///							doesn't match the condition in @em pred.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] pred		A unary predicate that returns true or false
/// @return					True if @em pred returns false for all elements or if the range is
///							empty, false otherwise
///
/// @since 					1.0.0
template <class InputIterator, class UnaryPredicate>
bool
none_of(InputIterator first, InputIterator last, UnaryPredicate pred);

/// @brief					Removes all elements that equal a value in a range
///
///							Transforms a range [first,last] into a range where all elements
///							that equal @em value are removed. The element type must support
///							operator==().
///
///							The order of the elements not removed are preserved but note that
///							any element between the returned iterator and @em last are
///							still valid but in an unspecified state.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in]	value		The value to be removed
///
/// @return					An iterator that points to the position after the new end of the
///							range
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
ForwardIterator
remove(ForwardIterator first, ForwardIterator last, const T& value);

/// @brief 					Copies elements from a range that don't match a value into another
///							range
///
///							Iterates through a range [first,last] and copies each element that
///							doesn't match @em value into the range beginning at @em otherFirst.
///							The element type must support operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the destination range
/// @param [in] value		The value for each element to be compared to
///
/// @return					An iterator that points to the position after the last element
///							copied into the destination range
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator, class T>
OutputIterator
remove_copy (InputIterator first, InputIterator last,
		OutputIterator otherFirst, const T& value);

/// @brief 					Copies elements from a range for which a predicate returns false
///							into another range
///
///							Iterates through a range [first,last] and copies all elements
///							(except those for which @em pred returns true) into the range
///							beginning at @em otherFirst. The element type must support
///							operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the destination range
/// @param [in] pred		A unary function that returns true or false
///
/// @return					An iterator that points to the position after the last element
///							copied into the destination range
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
remove_copy_if (InputIterator first, InputIterator last,
		OutputIterator otherFirst, UnaryPredicate pred);

/// @brief					Removes all elements from a range for which a predicate returns true
///
///							Transforms the range [first,last] into a range where each element
///							for which @em pred returns true is removed.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] pred		A unary function that returns true or false
///
/// @return					An iterator that points to the position after the new end of the
///							range
///
/// @since 					1.0.0
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred);

/// @brief 					Replaces all occurrences of a value with a new value in a range
///
///							Iterates through the range [first,last] and replaces each occurrence
///							of @em oldValue with @em newValue. The element type must support
///							operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] oldValue	The value to be replaced
/// @param [in] newValue	The new value that replaces the old value
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
void
replace(ForwardIterator first, ForwardIterator last,
		const T& oldValue, const T& newValue);

/// @brief 					Copies the elements from one range to another range replacing
///							one value with another value.
///
///							Iterates through the range [first,last] and copies each element
///							into the range beginning at @em otherFirst whilst replacing all
///							occurrences of @em oldValue with @em newValue in the destination
///							range. The element type must support operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the destination range
/// @param [in] oldValue	The value to be replaced
/// @param [in] newValue	The new value that replaces the old value
///
/// @return					An iterator that points to the position after the last element
///							copied into the destination range
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator, class T>
OutputIterator
replace_copy(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		const T& oldValue, const T& newValue);

/// @brief 					Copies the elements from one range to another range replacing
///							each element that a predicate returns true for with a new value
///
///							Iterates through the range {first,last] and copies each element into
///							the destination range beginning at @em otherFirst replacing any value
///							with @em newValue for which @em pred returns true.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the destination range
/// @param [in] pred		A unary function that returns true or false
/// @param [in] newValue	The new value that replaces the old value
///
/// @return					An iterator that points to the position after the last element
///							copied into the destination range
///
/// @since 					1.0.0
template <class InputIterator, class OutputIterator, class UnaryPredicate, class T>
OutputIterator
replace_copy_if(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		UnaryPredicate pred, const T& newValue);

/// @brief 					Assigns a new value to all elements for which a predicate returns
///							true
///
///							Iterates through the range [first,last] and replaces any element
///							for which the predicate @em pred returns true with @em newValue.
///							The element type must support operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] pred		A unary function that returns true or false
/// @param [in] newValue	The new value that replaces the old value
///
/// @return					Nothing
///
/// @since	 				1.0.0
template <class ForwardIterator, class UnaryPredicate, class T>
void
replace_if(ForwardIterator first, ForwardIterator last,
		UnaryPredicate pred, const T& newValue);

/// @brief 					Searches a range for a sub-range
///
///							Iterates through the range [first,last] searching for the sub-range
///							defined by the range [otherFirst,otherLast]. The element type must
///							support operator==().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last. Likewise
///							for the range [otherFirst,otherLast].
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the other range
/// @param [in] otherLast	An iterator that points to the position past the last element in
///							the other range
///
/// @return					An iterator that points to the first element of the matching
///							sub-range in the source range or @em last if no sub-range is found
///
/// @since 					1.0.0
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
search(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, ForwardIterator2 otherLast);

/// @brief 					Sorts the elements in a range in ascending order
///
///							Sorts the elements in the range [first,last] in ascending order
///							using the bubble sort algorithm. The element type must support
///							operator>().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class BidirectionalIterator>
void
sort_bubble(BidirectionalIterator first, BidirectionalIterator last);

/// @brief 					Sorts the elements in a range in ascending order
///
///							Sorts the elements in the range [first,last] in ascending order
///							using the heap sort algorithm. The element type must support
///							operator<().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class RandomAccessIterator>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last);

/// @brief 					Sorts the elements in a range in ascending order
///
///							Sorts the elements in the range [first,last] in ascending order
///							using the quick sort algorithm. The element type must support
///							operator<=().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class BidirectionalIterator>
void
sort_quicksort(BidirectionalIterator first, BidirectionalIterator last);

/// @brief 					Sorts the elements in a range in ascending order
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class BidirectionalIterator>
void
sort(BidirectionalIterator first, BidirectionalIterator last);

/// @brief 					Swaps the values of two variables
///
///							After running this function @em a will equal @em b's old value and
///							@em b will equal @em a's old value. The element type must support
///							operator=()
///
/// @param [in] a			The first value
/// @param [in] b			The second value
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class T>
void
swap(T& a, T& b);

/// @brief 					Swaps the elements in two ranges
///
///							All of the elements in the range [first,last] are swapped with the
///							elements in the range beginning from @em otherFirst. The element
///							type must support operator=().
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of the other range
///
/// @return					An iterator that points to the position after the last element
///							swapped into the destination range
///
/// @since 					1.0.0
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
swap_ranges(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst);

/// @brief 					Fills an uninitialized range with a value
///
///							The range [first,last] represents a block of memory that has been
///							allocated but not initialized i.e. no elements have been constructed.
///							This algorithm takes that memory block and initializes each element
///							by copy-constructing each element in place.
///
///							The range is @em [first,last], which contains all the elements
///							between @em first and @em last, including the element pointed to
///							by @em first but not the element pointed to by @em last.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] value		The value to be assigned to the range
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last,
						const T& value);

/// @brief 					Fills the first number of elements in an uninitialized range with a
///							value
///
///							The range starting at @em first represents a block of memory that
///							has been allocated but not initialized i.e. no elements have been
///							constructed. This algorithm takes that memory block and initializes
///							each element by copy-constructing each element in place.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] size		The number of elements to fill-initialize
/// @param [in] value		The value to fill-initialize with
///
/// @return					Nothing
///
/// @since 					1.0.0
template <class ForwardIterator, class T>
void
uninitialized_fill_n(ForwardIterator first, const int size, const T& value);

/// @brief 					Copies a range into an uninitialized range
///
///							The range [first,last] represents a block of memory that has been
///							allocated but not initialized i.e. no elements have been constructed
///							yet. This means that the allocated memory cannot be dereferenced
///							yet through an iterator (as in the prism::copy algorithm). This
///							algorithm takes that memory block and initializes each element by
///							copy-constructing each element in place. This algorithm differs
///							from prism::copy because that algorithm dereferences the iterator
///							to assign the new value whereas this algorithm doesn't. It
///							copy-constructs in place instead.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] last		An iterator that points to the position past the last element in
///							the range
/// @param [in] otherFirst	An iterator that points to the start of an uninitialized range
///
/// @return					An iterator that points to the position after the last element
///							copied to the destination range
///
/// @since 					1.0.0
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst);

/// @brief 					Copies a number of elements from a range into an uninitialized range
///
///							The range beginning at @em first represents a block of memory that
///							has been allocated but not initialized i.e. no elements have been
///							constructed yet. This means that the allocated memory cannot be
///							dereferenced yet through an iterator (as in the prism::fill
///							algorithm). This algorithm takes that memory block and initializes
///							each element by copy-constructing each element in place. This
///							algorithm differs from prism::fill because that algorithm
///							dereferences the iterator to assign the new value  whereas this
///							algorithm doesn't. It copy-constructs in place instead.
///
/// @param [in] first		An iterator that points to the start of the range
/// @param [in] size		The number of elements to copy-initialize
/// @param [in] otherFirst	An iterator that points to the start of an uninitialized range
///
/// @return					An iterator that points to the position after the last element
///							copied to the destination range
///
/// @since 					1.0.0
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy_n(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst);

} // end namespace prism

#include <prism/h/priv/algorithm_priv.h>

#endif /* PRISM_ALGORITHM_H_ */
