/*
 * algorithm_priv.h
 * v1
 *
 *  Created on: Sep 28, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALGORITHM_PRIV_H_
#define PRISM_ALGORITHM_PRIV_H_

#include <prism/iterator>
#include <iostream> // todo remove this
#include <cmath>


namespace prism {

//============================================================================================
// private stuff
//============================================================================================
namespace priv {

/**
 * Private recursive function called by make_heap().
 * Compares a node with its two children (if it has any) and ensures that the largest of the three
 * nodes is the parent node.
 */
template <class RandomAccessIterator>
void
heapify(RandomAccessIterator node, RandomAccessIterator first, RandomAccessIterator last) {

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
		priv::heapify(largestNode, first, last);
	}

}

/**
 * Bubble sort for random access iterators
 */
template <class RandomAccessIterator>
void
sort_bubble(RandomAccessIterator first, RandomAccessIterator last,
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
sort_bubble(BidirectionalIterator first, BidirectionalIterator last,
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
 * Quicksort for random access iterators
 */
template <class RandomAccessIterator>
void
sort_quicksort(RandomAccessIterator first, RandomAccessIterator last,
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
	else sort_quicksort(cachedFirst, wall, it_cat);
	if (last - 1 == wall) {}
	else sort_quicksort(wall, last, it_cat);
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
sort_quicksort(BidirectionalIterator first, BidirectionalIterator last,
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
	prism::copy(first, last, array);

	priv::sort_quicksort(array, array+count, prism::random_access_iterator_tag());

	count = 0;
	while (first != last) {
		*first = array[count++];
		++first;
	}

	delete array;
}

/**
 *
 */
template <class BidirectionalIterator>
void
sort_quicksort(BidirectionalIterator first, BidirectionalIterator last) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	sort_quicksort(first, last, it_cat());
}

} // end namespace priv
//============================================================================================
// public implementations
//============================================================================================
/**
 *
 */
template <class ForwardIterator>
ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last){
	while (first != last) {
		if (*first == *(first+1))
			return first;
		first++;
	}
	return last;
}

/**
 *
 */
template <class InputIterator, class Predicate>
bool
all_of(InputIterator first, InputIterator last, Predicate pred){
	while (first != last) {
		if (!pred(*first)) return false;
		first++;
	}
	return true;
}

/**
 *
 */
template <class InputIterator, class Predicate>
bool
any_of(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (pred(*first)) return true;
		first++;
	}
	return false;
}

/**
 *
 */
template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator otherFirst) {
	while (first != last) {
		*otherFirst = *first;
		first++;
		otherFirst++;
	}
	return otherFirst;
}

/**
 *
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first,
				BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast) {
	while (last != first) {
		*(--otherLast) = *(--last);
	}
	return otherLast;
}

/**
 *
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator
copy_if(InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred) {
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
 *
 */
template <class InputIterator, class Size, class OutputIterator>
OutputIterator
copy_n(InputIterator first, Size n, OutputIterator otherFirst) {
	while (n>0) {
	    *otherFirst = *first;
	    ++otherFirst;
	    ++first;
	    --n;
	  }
	return otherFirst;
}

/**
 *
 */
template <class InputIterator, class T>
int
count(InputIterator first, InputIterator last, const T& value) {
	int c = 0;
	while (first != last) {
		if (*first == value) c++;
		++first;
	}
	return c;
}

/**
 *
 */
template <class InputIterator, class Predicate>
int
count_if(InputIterator first, InputIterator last, Predicate pred) {
	int c = 0;
	while (first != last)  {
		if (pred(*first)) c++;
		first++;
	}
	return c;
}

/**
 *
 */
template <class InputIterator1, class InputIterator2>
bool
equal(InputIterator1 first, InputIterator1 last, InputIterator2 otherFirst) {
	while (first != last) {
		if (!(*first == *otherFirst)) return false;
		first++;
		otherFirst++;
	}
	return true;
}

/**
 *
 */
template <class ForwardIterator, class T>
void
fill(ForwardIterator first, ForwardIterator last, const T& value) {
	while (first != last) {
		*first = value;
		first++;
	}
}

/**
 *
 */
template <class ForwardIterator, class T>
void
fill_n(ForwardIterator first, int size, const T& value) {
	while (size > 0) {
		*first = value;
		size--;
		first++;
	}
}

/**
 *
 */
template <class InputIterator, class T>
InputIterator
find(InputIterator first, InputIterator last, const T& value) {
	while (first != last) {
		if (*first == value) return first;
		first++;
	}
	return last;
}

/**
 *
 */
template <class InputIterator, class Predicate>
InputIterator
find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if(pred(*first)) return first;
		first++;
	}
	return last;
}

/**
 *
 */
template <class InputIterator, class T>
InputIterator
find_last(InputIterator first, InputIterator last, const T& value) {
	InputIterator tmp = last;
	while (--last >= first) {
		if (*last == value)
			return last;
	}
	return tmp;
}

/**
 *
 */
template <class InputIterator, class Function>
Function
for_each(InputIterator first, InputIterator last, Function func) {
	while (first != last) {
		func(*first);
		first++;
	}
	return func;
}

/**
 *
 */
template <class ForwardIterator>
const bool
is_sorted(ForwardIterator first, ForwardIterator last) {
	if (first == last) return true;
	ForwardIterator current = first;

	while (++current != last) {
		if (*current < *first) return false;
		++first;
	}
	return true;
}

/**
 *
 */
template <class RandomAccessIterator>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last) {
	using namespace std;

	int heapSize = last-first;
	RandomAccessIterator node = first + heapSize/2 - 1;

	while (node >= first) {
		priv::heapify(node, first, last);
		--node;
	}
}

/**
 *
 */
template <class T>
const T&
max(const T& a, const T& b) {
	if (b > a) return b;
	return a;
}

/**
 *
 */
template <class T>
const T&
min(const T& a, const T& b) {
	if (b > a) return a;
	return b;
}

/**
 *
 */
template <class InputIterator, class Predicate>
bool
none_of(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last) {
		if (pred(*first)) return false;
		first++;
	}
	return true;
}

/**
 *
 */
template <class ForwardIterator, class T>
ForwardIterator
remove(ForwardIterator first, ForwardIterator last, const T& value) {
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
 *
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
remove_copy (InputIterator first, InputIterator last, OutputIterator otherFirst, const T& value)
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
 *
 */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator
remove_copy_if (InputIterator first, InputIterator last, OutputIterator otherFirst, Predicate pred)
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
 *
 */
template <class ForwardIterator, class Predicate>
ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{
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
 *
 */
template <class ForwardIterator, class T>
void
replace(ForwardIterator first, ForwardIterator last, const T& oldValue, const T& newValue) {
	while (first != last) {
		if (*first == oldValue)
			*first = newValue;
		++first;
	}
}

/**
 *
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator
replace_copy(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
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
 *
 */
template <class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator
replace_copy_if(InputIterator first, InputIterator last,
		OutputIterator otherFirst,
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
 *
 */
template <class ForwardIterator, class Predicate, class T>
void
replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& newValue) {
	while (first != last) {
		if (pred(*first))
			*first = newValue;
		++first;
	}
}

/**
 *
 */
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
search(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, ForwardIterator2 otherLast)
{
	if (otherFirst==otherLast)
		return first;

	while (first!=last) {
		ForwardIterator1 it1 = first;
		ForwardIterator2 it2 = otherFirst;

		while (*it1==*it2) {
			++it1;
			++it2;
			if (it2==otherLast) return first;
			if (it1==last) return last;
		}
		++first;
	}
	return last;
}



/**
 *
 */
template <class RandomAccessIterator>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
	if (first == last) return;

	make_heap(first, last);

	RandomAccessIterator currentNode = last;

	while (--currentNode >= first) {
		swap(*currentNode, *first);
		p_heapify(first, first, currentNode);
	}
}



/**
 *
 */
template <class BidirectionalIterator>
void
sort(BidirectionalIterator first, BidirectionalIterator last) {
	typedef typename prism::iterator_traits<BidirectionalIterator>::iterator_category it_cat;
	priv::sort_quicksort(first, last, it_cat());
}

/**
 *
 */
template <class T>
void
swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
swap_ranges(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	while (first != last) {
		prism::swap(*first, *otherFirst);
		first++;
		otherFirst++;
	}
	return otherFirst;
}

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
	uninitialized_fill_n(first, last-first, value);
}

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill_n(ForwardIterator first, const int size, const T& value) {
	for (int i=0; i<size; i++) {
		new (static_cast<void*>(&*first)) T(value);
		++first;
	}
}

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	return uninitialized_copy_n(first, last-first, otherFirst);
}

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy_n(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst) {
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

} // end namespace prism


#endif // PRISM_ALGORITHM_PRIV_H_









