/*
 * algorithm_priv.h
 * v1
 *
 *  Created on: Sep 28, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHM_PRIV_H_
#define PRISM_ALGORITHM_PRIV_H_

#include <prism/h/algorithm_aux.h>

namespace prism {

/**
 *
 */
template <class ForwardIterator>
ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last)
{ return adjacent_find_aux(first, last); }

/**
 *
 */
template <class InputIterator, class Predicate>
bool
all_of(InputIterator first, InputIterator last, Predicate pred)
{ return all_of_aux(first, last, pred); }

/**
 *
 */
template <class InputIterator, class Predicate>
bool
any_of(InputIterator first, InputIterator last, Predicate pred)
{ return any_of_aux(first, last, pred); }

/**
 *
 */
template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator otherFirst)
{ return copy_aux(first, last, otherFirst); }

/**
 *
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first,
				BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast)
{ return copy_backward_aux(first, last, otherLast); }

/**
 *
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator
copy_if(InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred)
{ return copy_if_aux(first, last, otherFirst, pred); }

/**
 *
 */
template <class InputIterator, class Size, class OutputIterator>
OutputIterator
copy_n(InputIterator first, Size n, OutputIterator otherFirst)
{ return copy_n_aux(first, n, otherFirst); }

/**
 *
 */
template <class InputIterator, class T>
int
count(InputIterator first, InputIterator last, const T& value)
{ return count_aux(first, last, value); }

/**
 *
 */
template <class InputIterator, class Predicate>
int
count_if(InputIterator first, InputIterator last, Predicate pred)
{ return count_if_aux(first, last, pred); }

/**
 *
 */
template <class ForwardIterator>
void
delete_range(ForwardIterator first, ForwardIterator last)
{ delete_range_aux(first, last); }

/**
 *
 */
template <class InputIterator1, class InputIterator2>
bool
equal(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst)
{ return equal_aux(first, last, otherFirst); }

/**
 *
 */
template <class ForwardIterator, class T>
void
fill(ForwardIterator first, ForwardIterator last, const T& value)
{ fill_aux(first, last, value); }

/**
 *
 */
template <class ForwardIterator, class T>
void
fill_n(ForwardIterator first, int size, const T& value)
{ fill_n_aux(first, size, value); }

/**
 *
 */
template <class InputIterator, class T>
InputIterator
find(InputIterator first, InputIterator last, const T& value)
{ return find_aux(first, last, value); }

/**
 *
 */
template <class InputIterator, class Predicate>
InputIterator
find_if(InputIterator first, InputIterator last, Predicate pred)
{ return find_if_aux(first, last, pred); }

/**
 *
 */
template <class InputIterator, class T>
InputIterator
find_last(InputIterator first, InputIterator last, const T& value)
{ return find_last_aux(first, last, value); }

/**
 *
 */
template <class InputIterator, class Function>
Function
for_each(InputIterator first, InputIterator last, Function func)
{ return for_each_aux(first, last, func); }

/**
 *
 */
template <class ForwardIterator>
const bool
is_sorted(ForwardIterator first, ForwardIterator last)
{ return is_sorted_aux(first, last); }

/**
 *
 */
template <class RandomAccessIterator>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last)
{ make_heap_aux(first, last); }

/**
 *
 */
template <class T>
const T&
max(const T& a, const T& b)
{ return max_aux(a, b); }

/**
 *
 */
template <class T>
const T&
min(const T& a, const T& b)
{ return min_aux(a, b); }

/**
 *
 */
template <class InputIterator, class Predicate>
bool
none_of(InputIterator first, InputIterator last, Predicate pred)
{ return none_of_aux(first, last, pred); }

/**
 *
 */
template <class ForwardIterator, class T>
ForwardIterator
remove(ForwardIterator first, ForwardIterator last, const T& value)
{ return remove_aux(first, last, value); }

/**
 *
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
remove_copy (InputIterator first, InputIterator last, OutputIterator otherFirst, const T& value)
{ return remove_copy_aux(first, last, otherFirst, value); }

/**
 *
 */
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
remove_copy_if (InputIterator first, InputIterator last, OutputIterator otherFirst, UnaryPredicate pred)
{ return remove_copy_if_aux(first, last, otherFirst, pred); }

/**
 *
 */
template <class ForwardIterator, class Predicate>
ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{ return remove_if_aux(first, last, pred); }

/**
 *
 */
template <class ForwardIterator, class T>
void
replace(ForwardIterator first, ForwardIterator last, const T& oldValue, const T& newValue)
{ replace_aux(first, last, oldValue, newValue); }

/**
 *
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
replace_copy(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		const T& oldValue, const T& newValue)
{ return replace_copy_aux(first, last, otherFirst, oldValue, newValue); }

/**
 *
 */
template <class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator
replace_copy_if(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
		Predicate pred, const T& newValue)
{ return replace_copy_if_aux(first, last, otherFirst, pred, newValue); }

/**
 *
 */
template <class ForwardIterator, class Predicate, class T>
void
replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& newValue)
{ replace_if_aux(first, last, pred, newValue); }

/**
 *
 */
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
search(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, ForwardIterator2 otherLast)
{ return search_aux(first, last, otherFirst, otherLast); }

/**
 *
 */
template <class BidirectionalIterator>
void
sort_bubble(BidirectionalIterator first, BidirectionalIterator last) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	sort_bubble_aux(first, last, it_cat());
}

/**
 *
 */
template <class RandomAccessIterator>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{ sort_heap_aux(first, last); }

/**
 *
 */
template <class BidirectionalIterator>
void
sort_quicksort(BidirectionalIterator first, BidirectionalIterator last) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	sort_quicksort_aux(first, last, it_cat());
}

/**
 *
 */
template <class BidirectionalIterator>
void
sort(BidirectionalIterator first, BidirectionalIterator last) {
	sort_aux(first, last);
}

/**
 *
 */
template <class T>
void
swap(T& a, T& b)
{ swap_aux(a,b); }

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
swap_ranges(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst)
{ return swap_ranges_aux(first, last, otherFirst); }

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{ uninitialized_fill_aux(first, last, value); }

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill_n(ForwardIterator first, const int size, const T& value)
{ uninitialized_fill_n_aux(first, size, value); }

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst)
{ return uninitialized_copy_aux(first, last, otherFirst); }

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy_n(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst)
{ return uninitialized_copy_n_aux(first, size, otherFirst); }

} // end namespace prism


#endif // PRISM_ALGORITHM_PRIV_H_









