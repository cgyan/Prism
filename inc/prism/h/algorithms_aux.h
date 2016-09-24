/*
 * algorithms.cpp
 * v1
 *
 *  Created on: Jul 13, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHMS_AUX_H_
#define PRISM_ALGORITHMS_AUX_H_

#include <prism/iterator>
#include <iostream> // todo remove this
#include <cmath>

namespace prism {
// ==================================================================================================
// forward declarations
template <class T>
void swap(T& a, T& b);
template <class RandomAccessIterator>
void p_heapify(RandomAccessIterator node, RandomAccessIterator first, RandomAccessIterator last);
// ==================================================================================================

/**
 * Searches the range \em [first,last] for the first occurrence of
 * two consecutive elements that match.
 * @return Returns an iterator to the first of these two elements, or
 * \em last if no such pair is found.
 */
template <class ForwardIterator>
ForwardIterator
adjacent_find_aux(ForwardIterator first, ForwardIterator last) {
	while (first != last) {
		if (*first == *(first+1))
			return first;
		first++;
	}
	return last;
}

/**
 * Returns true if \em pred returns true for all the elements in the range \em [first,last]
 * or if the range is empty, and false otherwise.
 */
template <class InputIterator, class Predicate>
bool
all_of_aux(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (!pred(*first)) return false;
		first++;
	}
	return true;
}

/**
 * Returns true if \em pred returns true for any of the elements in the range \em [first, last].
 */
template <class InputIterator, class Predicate>
bool
any_of_aux(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (pred(*first)) return true;
		first++;
	}
	return false;
}

/**
 * Copies the elements in the range \em [first,last] into the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator>
OutputIterator
copy_aux(InputIterator first, InputIterator last, OutputIterator otherFirst) {
	while (first != last) {
		*otherFirst = *first;
		first++;
		otherFirst++;
	}
	return otherFirst;
}

/**
 * Copies the elements in the range [first,last] starting from \em last to the range ending
 * at \em otherLast. The elements copied are between \em first and \em last,
 * including \em first but not \em last. \em otherLast should point to the past-the-end
 * position of the destination range.
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward_aux(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 otherLast) {
	while (last != first) {
		*(--otherLast) = *(--last);
	}
	return otherLast;
}

/**
 * Copies the elements in the range \em [first,last] for
 * which \em pred returns true to the range beginning at \em otherFirst.
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator
copy_if_aux(InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred) {
	while (first != last) {
		if (pred(*first)) {
			*otherFirst = *first;
			otherFirst++;
		}
		first++;

	}
	return otherFirst;
}

/**
 * Copies the first \em n elements from the range beginning at \em first
 * into the range beginning at \em otherFirst.
 */
template <class InputIterator, class Size, class OutputIterator>
OutputIterator
copy_n_aux(InputIterator first, Size n, OutputIterator otherFirst) {
	while (n>0) {
	    *otherFirst = *first;
	    ++otherFirst;
	    ++first;
	    --n;
	  }
	return otherFirst;
}

/**
 * Returns the number of elements in the range \em [first,last] that compare equal to \em value.
 */
template <class InputIterator, class T>
int
count_aux(InputIterator first, InputIterator last, const T& value) {
	int c = 0;
	while (first != last) {
		if (*first == value) c++;
		++first;
	}
	return c;
}

/**
 * Returns the number of elements in the range \em [first,last] for which \em pred is true.
 */
template <class InputIterator, class Predicate>
int
count_if_aux(InputIterator first, InputIterator last, Predicate pred) {
	int c = 0;
	while (first != last)  {
		if (pred(*first)) c++;
		first++;
	}
	return c;
}

/**
 * Deletes the elements in the range \em [first, last] by using the c++ delete operator.
 * The element that the iterator points to therefore must be a pointer.
 */
template <class ForwardIterator>
void
delete_range_aux(ForwardIterator first, ForwardIterator last) {
	while (first != last) {
		delete *first;
		first++;
	}
}

/**
 * Compares the elements in the range \em [first1,last1] with those in the
 * range beginning at \em otherFirst, and returns true if all of the
 * elements in both ranges match. \n
 * \note The elements being compared must support operator==().
 */
template <class InputIterator1, class InputIterator2>
bool
equal_aux(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst) {
	while (first != last) {
		if (!(*first == *otherFirst)) return false;
		first++;
		otherFirst++;
	}
	return true;
}

/**
 * Assigns \em value to all the elements in the range \em [first,last].
 */
template <class ForwardIterator, class T>
void
fill_aux(ForwardIterator first, ForwardIterator last, const T& value) {
	while (first != last) {
		*first = value;
		first++;
	}
}

/**
 * Assigns \em value to the first \em n elements of the sequence pointed by \em first.
 */
template <class ForwardIterator, class T>
void
fill_n_aux(ForwardIterator first, int size, const T& value) {
	while (size > 0) {
		*first = value;
		size--;
		first++;
	}
}

/**
 * Returns an iterator to the first element in the range \em [first,last]
 * that compares equal to \em value. If no such element is found, the function returns \em last.
 */
template <class InputIterator, class T>
InputIterator
find_aux(InputIterator first, InputIterator last, const T& value) {
	while (first != last) {
		if (*first == value) return first;
		first++;
	}
	return last;
}

/**
 * Returns an iterator to the first element in the range \em [first,last]
 * for which \em pred returns true. If no such element is found, the function returns \em last.
 */
template <class InputIterator, class Predicate>
InputIterator
find_if_aux(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if(pred(*first)) return first;
		first++;
	}
	return last;
}

/**
 * Returns an iterator to the last element in the range \em [first,last]
 * that compares equal to \em value. The range searched is \em [first,last),
 * which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 * If no match is found then a null pointer is returned instead i.e. p=0;
 */
template <class InputIterator, class T>
InputIterator
find_last_aux(InputIterator first, InputIterator last, const T& value) {
	InputIterator tmp = last;
	while (--last >= first) {
		if (*last == value)
			return last;
	}
	return tmp;
}

/**
 * Applies function \em func to each of the elements in the range \em [first,last].
 */
template <class InputIterator, class Function>
Function
for_each_aux(InputIterator first, InputIterator last, Function func) {
	while (first != last) {
		func(*first);
		first++;
	}
	return func;
}

/**
 * Returns true if the elements in the range \em [first,last] are sorted in
 * ascending order, false otherwise. The range searched is \em [first,last),
 * which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 */
template <class ForwardIterator>
const bool
is_sorted_aux(ForwardIterator first, ForwardIterator last) {
	if (first == last) return true;
	ForwardIterator current = first;

	while (++current != last) {
		if (*current < *first) return false;
		++first;
	}
	return true;
}

/**
 * Rearranges the elements in the range \em [first,last] so that they satisfy
 * the order conditions of a heap.\n
 * The range searched is \em [first,last), which contains all the elements
 * between \em first and \em last, including the element pointed by \em first
 * but not the element pointed by \em last.
 */
template <class RandomAccessIterator>
void
make_heap_aux(RandomAccessIterator first, RandomAccessIterator last) {
	using namespace std;

	int heapSize = last-first;
	RandomAccessIterator node = first + heapSize/2 - 1;

	while (node >= first) {
		p_heapify(node, first, last);
		--node;
	}
}

/**
 * Returns the largest of \em a and \em b.
 * If they are equivalent then \em a is returned.
 */
template <class T>
const T&
max_aux(const T& a, const T& b) {
	if (b > a) return b;
	return a;
}

/**
 * Returns the smallest of \em a and \em b.
 * If they are equivalent then \em a is returned.
 */
template <class T>
const T&
min_aux(const T& a, const T& b) {
	if (b > a) return a;
	return b;
}

/**
 * Returns true if \em pred returns false for all the elements in the range \em [first,last]
 * or if the range is empty, and false otherwise.
 */
template <class InputIterator, class Predicate>
bool
none_of_aux(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (pred(*first)) return false;
		first++;
	}
	return true;
}

/**
 * Transforms the range \em [first,last] into a range with all the elements that
 * compare equal to \em value removed, and returns an iterator to the new end of that range.
 */
template <class ForwardIterator, class T>
ForwardIterator
remove_aux(ForwardIterator first, ForwardIterator last, const T& value) {
  ForwardIterator result = first;
  while (first!=last) {
    if (!(*first == value)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * except those elements that compare equal to \em value.
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
remove_copy_aux(InputIterator first, InputIterator last, OutputIterator otherFirst, const T& value)
{
  while (first!=last) {
    if (!(*first == value)) {
      *otherFirst = *first;
      ++otherFirst;
    }
    ++first;
  }
  return otherFirst;
}

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * except those elements for which \em pred returns true.
 */
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
remove_copy_if_aux(InputIterator first, InputIterator last, OutputIterator otherFirst, UnaryPredicate pred)
{
  while (first!=last) {
    if (!pred(*first)) {
      *otherFirst = *first;
      ++otherFirst;
    }
    ++first;
  }
  return otherFirst;
}

/**
 * Transforms the range \em [first,last] into a range with all the elements for which
 * \em pred returns true removed, and returns an iterator to the new end of that range.
 */
template <class ForwardIterator, class Predicate>
ForwardIterator
remove_if_aux(ForwardIterator first, ForwardIterator last, Predicate pred) {
	ForwardIterator result = first;
	while (first != last) {
		if (!pred(*first)) {
			*result = *first;
			++result;
		}
		++first;
	}
	return result;
}

/**
 * Assigns \em newValue to all the elements in the range \em [first,last]
 * that compare equal to \em oldValue.
 */
template <class ForwardIterator, class T>
void
replace_aux(ForwardIterator first, ForwardIterator last, const T& oldValue, const T& newValue) {
	while (first != last) {
		if (*first == oldValue)
			*first = newValue;
		++first;
	}
}

/**
 * Copies the elements in the range \em [first,last] to the range beginning
 * at \em otherFirst, replacing the appearances of \em oldValue by \em newValue.
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
replace_copy_aux(InputIterator first, InputIterator last, OutputIterator otherFirst,
		const T& oldValue, const T& newValue)
{
	while (first != last) {
		if (*first == oldValue)
			*otherFirst = newValue;
		else
			*otherFirst = *first;
		++first;
		++otherFirst;
	}
	return otherFirst;
}

/**
 * Copies the elements in the range \em [first,last] to the range beginning at \em otherFirst,
 * replacing those for which \em pred returns true by newValue.
 */
template <class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator
replace_copy_if_aux(InputIterator first, InputIterator last, OutputIterator otherFirst,
		Predicate pred, const T& newValue)
{
	while (first != last) {
		if (pred(*first)) *otherFirst = newValue;
		else *otherFirst = *first;
		++first;
		++otherFirst;
	}
	return otherFirst;
}

/**
 * Assigns \em newValue to all the elements in the range \em [first,last]
 * for which \em pred returns true.
 */
template <class ForwardIterator, class Predicate, class T>
void
replace_if_aux(ForwardIterator first, ForwardIterator last, Predicate pred, const T& newValue) {
	while (first != last) {
		if (pred(*first))
			*first = newValue;
		++first;
	}
}

/**
 * Searches the range [first1,last1] for the first occurrence of the sequence
 * defined by [first2,last2], and returns an iterator to its first element,
 * or last1 if no occurrences are found. The range used is [first1,last1],
 * which contains all the elements between first1 and last1, including the
 * element pointed by first1 but not the element pointed by last1.
 */
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
search_aux(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
	if (first2==last2)
		return first1;

	while (first1!=last1) {
		ForwardIterator1 it1 = first1;
		ForwardIterator2 it2 = first2;

		while (*it1==*it2) {
			++it1;
			++it2;
			if (it2==last2) return first1;
			if (it1==last1) return last1;
		}
		++first1;
	}
	return last1;
}

/**
 * Bubble sort for random access iterators
 */
template <class RandomAccessIterator>
void
sort_bubble_aux(RandomAccessIterator first, RandomAccessIterator last,
		prism::random_access_iterator_tag)
{
	RandomAccessIterator thisElement = first;
	RandomAccessIterator nextElement = thisElement+1;
	RandomAccessIterator bit = first;

	bool swapped = false;

	while (bit != last-1) {
		swapped = false;
		while (thisElement != last-1) {

			if (*thisElement > *nextElement) {
				swap(*thisElement, *nextElement);
				swapped = true;
			}
			++thisElement;
			++nextElement;
		}
		if (!swapped) break; // already in sorted order
		thisElement = first;
		nextElement = thisElement+1;
		++bit;
	}
}

/**
 * Bubble sort for bidirectional iterators
 */
template <class BidirectionalIterator>
void
sort_bubble_aux(BidirectionalIterator first, BidirectionalIterator last,
		prism::bidirectional_iterator_tag)
{
	BidirectionalIterator thisElement = first;
	BidirectionalIterator nextElement = ++first;
	--first;
	BidirectionalIterator lastElement = --last;
	++last;
	BidirectionalIterator bit = first;

	bool swapped = false;

	while (bit != lastElement) {
		swapped = false;
		while (thisElement != lastElement) {

			if (*thisElement > *nextElement) {
				swap(*thisElement, *nextElement);
				swapped = true;
			}
			++thisElement;
			++nextElement;
		}
		if (!swapped) break; // already in sorted order
		thisElement = first;
		nextElement = ++thisElement;
		--thisElement;
		++bit;
	}
}

/**
 * Sorts the elements in the range \em [first,last] using the heapsort algorithm. \n
 * The elements are first rearranged so that they satisfy the ordering of a heap (by a
 * call to make_heap()).\n
 * The range used is \em [first,last], which contains all the elements between \em first and \em last,
 * including the element pointed by \em first but not the element pointed by \em last.
 */
template <class RandomAccessIterator>
void
sort_heap_aux(RandomAccessIterator first, RandomAccessIterator last) {
	if (first == last) return;

	make_heap_aux(first, last);

	RandomAccessIterator currentNode = last;

	while (--currentNode >= first) {
		swap(*currentNode, *first);
		p_heapify_aux(first, first, currentNode);
	}
}

/**
 * Quicksort for random access iterators
 */
template <class RandomAccessIterator>
void
sort_quicksort_aux(RandomAccessIterator first, RandomAccessIterator last,
		prism::random_access_iterator_tag it_cat)
{
	RandomAccessIterator wall = first;
	RandomAccessIterator pivot = last - 1;
	RandomAccessIterator cachedFirst = first;

	while (first <= pivot) {

		if (first == pivot)
			swap(*first, *wall);

		else if (*first <= *pivot) {
			swap(*first, *wall);
			++wall;
		}
		++first;
	}

	if (cachedFirst == wall || cachedFirst+1 == wall) {}
	else sort_quicksort_aux(cachedFirst, wall, it_cat);
	if (last - 1 == wall) {}
	else sort_quicksort_aux(wall, last, it_cat);
}

/**
 * Quicksort for bidirectional iterators
 * todo
 * Not a great solution for quicksorting a bidirectional iterator based container!
 * Currently copies the elements into an array, then sorts using the random access
 * quicksort then copies the sorted elements back into the original container.... :-(
 */
template <class BidirectionalIterator>
void
sort_quicksort_aux(BidirectionalIterator first, BidirectionalIterator last,
		prism::bidirectional_iterator_tag)
{
	int count = 0;
	BidirectionalIterator it = first;
	while (it != last) {
		++count;
		++it;
	}

	typedef typename prism::iterator_traits<BidirectionalIterator>::value_type T;
	T * array = new T[count];
	prism::copy_aux(first, last, array);

	prism::sort_quicksort_aux(array, array+count, prism::random_access_iterator_tag());

	count = 0;
	while (first != last) {
		*first = array[count++];
		++first;
	}

	delete array;
}

/**
 * Sorts the elements in the range \em [first,last] in ascending order
 * using the quicksort algorithm. The range used is [first1,last1],
 * which contains all the elements between first1 and last1, including the
 * element pointed by first1 but not the element pointed by last1. \n
 * Currently \em sort() is implemented using the quicksort algorithm which averages
 * a reasonable O(n log(n)) complexity.
 */
template <class BidirectionalIterator>
void
sort_aux(BidirectionalIterator first, BidirectionalIterator last)
{
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	sort_quicksort_aux(first, last, it_cat());
}

/**
 * Exchanges the values of \em a and \em b.
 */
template <class T>
void
swap_aux(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

/**
 * Exchanges the values of each of the elements in the range \em [first1,last1]
 * with those of their respective elements in the range beginning at \em otherFirst.
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
swap_ranges_aux(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	while (first != last) {
		prism::swap(*first, *otherFirst);
		first++;
		otherFirst++;
	}
	return otherFirst;
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
uninitialized_copy_n_aux(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst) {
	for (int i=0; i<size; i++) {

		// the following simplified is:
		//	new (otherFirst) T(first)

		new (static_cast<void*>(&*otherFirst))
				typename prism::iterator_traits<ForwardIterator1>::value_type(*first);
		++first;
		++otherFirst;
	}
	return otherFirst;
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
uninitialized_copy_aux(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	return uninitialized_copy_n_aux(first, last-first, otherFirst);
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
template <class ForwardIterator, class T>
void
uninitialized_fill_n_aux(ForwardIterator first, const int size, const T& value) {
	for (int i=0; i<size; i++) {
		new (static_cast<void*>(&*first)) T(value);
		++first;
	}
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
template <class ForwardIterator, class T>
void
uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value) {
	uninitialized_fill_n_aux(first, last-first, value);
}
// ==================================================================================================
// private
// ==================================================================================================
/**
 * Private recursive function called by make_heap_aux().
 * Compares a node with its two children (if it has any) and ensures that the largest of the three
 * nodes is the parent node.
 */
template <class RandomAccessIterator>
void
p_heapify_aux(RandomAccessIterator node, RandomAccessIterator first, RandomAccessIterator last) {

	int nodeIndex = node-first;
	int leftIndex = 2 * nodeIndex + 1;
	int rightIndex = 2 * nodeIndex + 2;

	RandomAccessIterator leftNode = first + leftIndex;
	RandomAccessIterator rightNode = first + rightIndex;
	RandomAccessIterator largestNode = node;

	if (leftNode < last && *largestNode < *leftNode)
		largestNode = leftNode;

	if (rightNode < last && *largestNode < *rightNode)
		largestNode = rightNode;

	if (node != largestNode) {
		swap(*node, *largestNode);
		p_heapify(largestNode, first, last);
	}

}

} // namespace prism

#endif /* PRISM_ALGORITHMS_AUX_H_ */








