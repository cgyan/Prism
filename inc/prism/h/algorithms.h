/*
 * Algorithms.h
 * v1
 *
 *  Created on: Sep 17, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHMS_H_
#define PRISM_ALGORITHMS_H_

#include <prism/h/algorithms_aux.h>

namespace prism {

// ==================================================================================================
// forward declarations
//template <class T>
//void swap(T& a, T& b);
//template <class RandomAccessIterator>
//void p_heapify(RandomAccessIterator node, RandomAccessIterator first, RandomAccessIterator last);
// ==================================================================================================

/**
 * Searches the range \em [first,last] for the first occurrence of
 * two consecutive elements that match.
 * @return Returns an iterator to the first of these two elements, or
 * \em last if no such pair is found.
 */
template <class ForwardIterator>
ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last)
{ return adjacent_find_aux(first, last); }

/**
 * Returns true if \em pred returns true for all the elements in the range \em [first,last]
 * or if the range is empty, and false otherwise.
 */
template <class InputIterator, class Predicate>
bool
all_of(InputIterator first, InputIterator last, Predicate pred)
{ return all_of_aux(first, last, pred); }

/**
 * Returns true if \em pred returns true for any of the elements in the range \em [first, last].
 */
template <class InputIterator, class Predicate>
bool
any_of(InputIterator first, InputIterator last, Predicate pred)
{ return any_of_aux(first, last, pred); }

/**
 * Copies the elements in the range \em [first,last] into the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator otherFirst)
{ return copy_aux(first, last, otherFirst); }

/**
 * Copies the elements in the range [first,last] starting from \em last to the range ending
 * at \em otherLast. The elements copied are between \em first and \em last,
 * including \em first but not \em last. \em otherLast should point to the past-the-end
 * position of the destination range.
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first,
				BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast)
{ return copy_backward_aux(first, last, otherLast); }

/**
 * Copies the elements in the range \em [first,last] for
 * which \em pred returns true to the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator
copy_if(InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred)
{ return copy_if_aux(first, last, otherFirst, pred); }

/**
 * Copies the first \em n elements from the range beginning at \em first
 * into the range beginning at \em otherFirst.
 */
template <class InputIterator, class Size, class OutputIterator>
OutputIterator
copy_n(InputIterator first, Size n, OutputIterator otherFirst)
{ return copy_n_aux(first, n, otherFirst); }

/**
 * Returns the number of elements in the range \em [first,last] that compare equal to \em value.
 */
template <class InputIterator, class T>
int
count(InputIterator first, InputIterator last, const T& value)
{ return count_aux(first, last, value); }

/**
 * Returns the number of elements in the range \em [first,last] for which \em pred is true.
 */
template <class InputIterator, class Predicate>
int
count_if(InputIterator first, InputIterator last, Predicate pred)
{ return count_if_aux(first, last, pred); }

/**
 * Deletes the elements in the range \em [first, last] by using the c++ delete operator.
 * The element that the iterator points to therefore must be a pointer.
 */
template <class ForwardIterator>
void
delete_range(ForwardIterator first, ForwardIterator last)
{ delete_range_aux(first, last); }

/**
 * Compares the elements in the range \em [first1,last1] with those in the
 * range beginning at \em otherFirst, and returns true if all of the
 * elements in both ranges match. \n
 * \note The elements being compared must support operator==().
 */
template <class InputIterator1, class InputIterator2>
bool
equal(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst)
{ return equal_aux(first, last, otherFirst); }

/**
 * Assigns \em value to all the elements in the range \em [first,last].
 */
template <class ForwardIterator, class T>
void
fill(ForwardIterator first, ForwardIterator last, const T& value)
{ fill_aux(first, last, value); }

/**
 * Assigns \em value to the first \em n elements of the sequence pointed by \em first.
 */
template <class ForwardIterator, class T>
void
fill_n(ForwardIterator first, int size, const T& value)
{ fill_n_aux(first, size, value); }

/**
 * Returns an iterator to the first element in the range \em [first,last]
 * that compares equal to \em value. If no such element is found, the function returns \em last.
 */
template <class InputIterator, class T>
InputIterator
find(InputIterator first, InputIterator last, const T& value)
{ return find_aux(first, last, value); }

/**
 * Returns an iterator to the first element in the range \em [first,last] for which \em pred returns true.
 * If no such element is found, the function returns \em last.
 */
template <class InputIterator, class Predicate>
InputIterator
find_if(InputIterator first, InputIterator last, Predicate pred)
{ return find_if_aux(first, last, pred); }

/**
 * Returns an iterator to the last element in the range \em [first,last] that compares equal to \em value.
 * The range searched is \em [first,last), which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 * If no match is found then a null pointer is returned instead i.e. p=0;
 */
template <class InputIterator, class T>
InputIterator
find_last(InputIterator first, InputIterator last, const T& value)
{ return find_last_aux(first, last, value); }

/**
 * Applies function \em func to each of the elements in the range \em [first,last].
 */
template <class InputIterator, class Function>
Function
for_each(InputIterator first, InputIterator last, Function func)
{ return for_each_aux(first, last, func); }

/**
 * Returns true if the elements in the range \em [first,last] are sorted in ascending order, false otherwise.
 * The range searched is \em [first,last), which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 */
template <class ForwardIterator>
const bool
is_sorted(ForwardIterator first, ForwardIterator last)
{ return is_sorted_aux(first, last); }

/**
 * Rearranges the elements in the range \em [first,last] so that they satisfy
 * the order conditions of a heap.\n
 * The range searched is \em [first,last), which contains all the elements
 * between \em first and \em last, including the element pointed by \em first
 * but not the element pointed by \em last.
 */
template <class RandomAccessIterator>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last)
{ make_heap_aux(first, last); }

/**
 * Returns the largest of \em a and \em b.
 * If they are equivalent then \em a is returned.
 */
template <class T>
const T&
max(const T& a, const T& b)
{ return max_aux(a, b); }

/**
 * Returns the smallest of \em a and \em b.
 * If they are equivalent then \em a is returned.
 */
template <class T>
const T&
min(const T& a, const T& b)
{ return min_aux(a, b); }

/**
 * Returns true if \em pred returns false for all the elements in the range \em [first,last]
 * or if the range is empty, and false otherwise.
 */
template <class InputIterator, class Predicate>
bool
none_of(InputIterator first, InputIterator last, Predicate pred)
{ return none_of_aux(first, last, pred); }

/**
 * Transforms the range \em [first,last] into a range with all the elements that
 * compare equal to \em value removed, and returns an iterator to the new end of that range.
 */
template <class ForwardIterator, class T>
ForwardIterator
remove(ForwardIterator first, ForwardIterator last, const T& value)
{ return remove_aux(first, last, value); }

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * except those elements that compare equal to \em value.
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
remove_copy (InputIterator first, InputIterator last, OutputIterator otherFirst, const T& value)
{ return remove_copy_aux(first, last, otherFirst, value); }

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * except those elements for which \em pred returns true.
 */
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
remove_copy_if (InputIterator first, InputIterator last, OutputIterator otherFirst, UnaryPredicate pred)
{ return remove_copy_if_aux(first, last, otherFirst, pred); }

/**
 * Transforms the range \em [first,last] into a range with all the elements for which
 * \em pred returns true removed, and returns an iterator to the new end of that range.
 */
template <class ForwardIterator, class Predicate>
ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{ return remove_if_aux(first, last, pred); }

/**
 * Assigns \em newValue to all the elements in the range \em [first,last] that compare equal to \em oldValue.
 */
template <class ForwardIterator, class T>
void
replace(ForwardIterator first, ForwardIterator last, const T& oldValue, const T& newValue)
{ replace_aux(first, last, oldValue, newValue); }

/**
 * Copies the elements in the range \em [first,last] to the range beginning
 * at \em otherFirst, replacing the appearances of \em oldValue by \em newValue.
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
replace_copy(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		const T& oldValue, const T& newValue)
{ return replace_copy_aux(first, last, otherFirst, oldValue, newValue); }

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * replacing those for which \em pred returns true by newValue.
 */
template <class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator
replace_copy_if(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		Predicate pred, const T& newValue)
{ return replace_copy_if_aux(first, last, otherFirst, pred, newValue); }

/**
 * Assigns \em newValue to all the elements in the range \em [first,last] for which \em pred returns true.
 */
template <class ForwardIterator, class Predicate, class T>
void
replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& newValue)
{ replace_if_aux(first, last, pred, newValue); }

/**
 * Searches the range [first1,last1] for the first occurrence of the sequence defined by [first2,last2],
 * and returns an iterator to its first element, or last1 if no occurrences are found.
 * The range used is [first1,last1], which contains all the elements between first1 and last1,
 * including the element pointed by first1 but not the element pointed by last1.
 */
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
search(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, ForwardIterator2 otherLast)
{ return search_aux(first, last, otherFirst, otherLast); }

/**
 * Sorts the elements in the range \em [first, last] in ascending order using the Bubble Sort algorithm. \n
 * The range used is \em [first,last], which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 * \note The objects being sorted must support operator>().
 */
template <class RandomAccessIterator>
void
sort_bubble(RandomAccessIterator first, RandomAccessIterator last)
{ sort_bubble_aux(first, last); }

/**
 * Sorts the elements in the range \em [first,last] using the heapsort algorithm. \n
 * The elements are first rearranged so that they satisfy the ordering of a heap (by a
 * call to make_heap()).\n
 * The range used is \em [first,last], which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 */
template <class RandomAccessIterator>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{ sort_heap_aux(first, last); }

/**
 * Sorts the elements in the range \em [first, last] in ascending order using the Quicksort algorithm. \n
 * The range used is \em [first,last], which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 * \note The objects being sorted must support operator<=().
 */
template <class ForwardIterator>
void
sort_quicksort(ForwardIterator first, ForwardIterator last)
{ sort_quicksort_aux(first, last); }

/**
 * Sorts the elements in the range \em [first,last] in ascending order using the quicksort algorithm.
 * The range used is [first1,last1], which contains all the elements between first1 and last1,
 * including the element pointed by first1 but not the element pointed by last1. \n
 * Currently \em sort() is implemented using the quicksort algorithm which averages
 * a reasonable O(n log(n)) complexity.
 */
template <class ForwardIterator>
void
sort(ForwardIterator first, ForwardIterator last)
{ sort_aux(first, last); }

/**
 * Exchanges the values of \em a and \em b.
 */
template <class T>
void
swap(T& a, T& b)
{ swap_aux(a,b); }

/**
 * Exchanges the values of each of the elements in the range \em [first1,last1]
 * with those of their respective elements in the range beginning at \em otherFirst.
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
swap_ranges(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst)
{ return swap_ranges_aux(first, last, otherFirst); }

/**
 * The range [first,last] represents a block of memory that has been allocated but
 * not initialized i.e. no elements have been constructed.
 * This algorithm takes that memory block and initializes each element by
 * copy-constructing each element in place.
 */
template <class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{ uninitialized_fill_aux(first, last, value); }

/**
 * The range [first,last] represents a block of memory that has been allocated but
 * not initialized i.e. no elements have been constructed.
 * This algorithm takes that memory block and initializes each element by
 * copy-constructing each element in place.
 */
template <class ForwardIterator, class T>
void
uninitialized_fill_n(ForwardIterator first, const int size, const T& value)
{ uninitialized_fill_n_aux(first, size, value); }

/**
 * The range [first,last] represents a block of memory that has been allocated but
 * not initialized i.e. no elements have been constructed yet. This means that the allocated
 * memory cannot be dereferenced yet through an iterator (as in the prism::fill algorithm).
 * This algorithm takes that memory block and initializes each element by
 * copy-constructing each element in place.
 * This algorithm differs from prism::fill because that algorithm dereferences the
 * iterator to assign the new value whereas this algorithm doesn't. It copy-constructs in place instead.
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	return uninitialized_copy_aux(first, last, otherFirst);
}

/**
 * The range [first,last] represents a block of memory that has been allocated but
 * not initialized i.e. no elements have been constructed yet. This means that the allocated
 * memory cannot be dereferenced yet through an iterator (as in the prism::fill algorithm).
 * This algorithm takes that memory block and initializes each element by
 * copy-constructing each element in place.
 * This algorithm differs from prism::fill because that algorithm dereferences the
 * iterator to assign the new value whereas this algorithm doesn't. It copy-constructs in place instead.
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy_n(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst) {
	return uninitialized_copy_n_aux(first, size, otherFirst);
}

} // end namespace prism



#endif /* PRISM_ALGORITHMS_H_ */
