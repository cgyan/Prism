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
#include <prism/Allocator>
#include <cmath>
#include <iostream> // todo remove this

namespace prism {

//============================================================================================
// private definitions
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
		std::random_access_iterator_tag)
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
		std::bidirectional_iterator_tag)
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
		std::random_access_iterator_tag it_cat)
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
		std::bidirectional_iterator_tag)
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

	priv::sort_quicksort(array, array+count, std::random_access_iterator_tag());

	count = 0;
	while (first != last) {
		*first = array[count++];
		++first;
	}

	delete[] array;
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
// public definitions
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
template <bool IsPod>
struct Copy {
	template <typename InputIterator, typename OutputIterator>
	static OutputIterator
	copy(InputIterator first, InputIterator last, OutputIterator otherFirst) {
		using value_type = typename prism::iterator_traits<InputIterator>::value_type;
		const int numElements = prism::distance(first, last);
		const size_t numBytes = numElements * sizeof(value_type);
		memmove(&*otherFirst, &*first, numBytes);
		return otherFirst + numElements;
	}
};

/**
 *
 */
template <>
struct Copy<false> {
	template <typename InputIterator, typename OutputIterator>
	static OutputIterator
	copy(InputIterator first, InputIterator last, OutputIterator otherFirst) {
		while (first != last)
			*otherFirst++ = *first++;
		return otherFirst;
	}
};

/**
 *
 */
template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator otherFirst) {
	using value_type = typename prism::iterator_traits<InputIterator>::value_type;
	return Copy<std::is_pod<value_type>::value>::copy(first, last, otherFirst);
}

/**
 *
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first,
				BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast) {
	auto current = last;
	while (current != first)
		*(--otherLast) = *(--current);
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
		++first;
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
		++first;
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
template <typename ForwardIterator1, typename ForwardIterator2>
const bool
lexicographical_compare(ForwardIterator1 first1, ForwardIterator1 last1,
						ForwardIterator2 first2, ForwardIterator2 last2) {
	while (first1 != last1) {
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
		++first1;
		++first2;
	}
	return first2 != last2;
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
template <typename InputIterator, typename OutputIterator>
OutputIterator
move(InputIterator first, InputIterator last, OutputIterator otherFirst) {
	auto current = first;
	for (; current != last; ++current, ++otherFirst)
		*otherFirst = std::move(*current);
	return otherFirst;
}

/**
 *
 */
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2
move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
				BidirectionalIterator2 otherLast) {
	auto current = last;
	while (current != first)
		*(--otherLast) = std::move(*--current);
	return otherLast;
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
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
remove_copy_if (InputIterator first, InputIterator last,
					OutputIterator otherFirst, UnaryPredicate pred)
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
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
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
#include <iostream>
/**
 *
 */
template <class T>
void
swap(T& a, T& b) {
	T temp = std::move(a);
	a = std::move(b);
	b = std::move(temp);
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
template <typename ForwardIterator1, typename ForwardIterator2, typename Allocator>
ForwardIterator2
uninitialized_copy_alloc(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, Allocator& alloc);

///
///
///
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2
uninitialized_move_backwards(BidirectionalIterator1 first,
								BidirectionalIterator1 last,
								BidirectionalIterator2 otherLast);

///
///
///
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator2
uninitialized_move(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst);

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
	prism::Allocator<T> alloc;
	uninitialized_fill_alloc(first, last, value, alloc);
}

/**
 *
 */
template <class ForwardIterator, class T>
void
uninitialized_fill_n(ForwardIterator first, const int size, const T& value) {
	prism::Allocator<T> alloc;
	uninitialized_fill_alloc(first, first + size, value, alloc);
}

/**
 *
 */
template <typename ForwardIterator, typename T, typename Allocator>
void
uninitialized_fill_alloc(ForwardIterator first, ForwardIterator last,
		const T& value, Allocator& alloc) {
	using alloc_traits = prism::AllocatorTraits<Allocator>;
	auto current = first;
	try {
		for (; current != last; current++)
			alloc_traits::construct(alloc, &*current, value);
	}
	catch(...) {
		for (auto it = first; it != current; it++)
			(&*it)->~T();
		throw;
	}
}

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	using value_type = typename prism::iterator_traits<ForwardIterator1>::value_type;
	prism::Allocator<value_type> alloc;
	return uninitialized_copy_alloc(first, last, otherFirst, alloc);
}

/**
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2
uninitialized_copy_n(ForwardIterator1 first, const int size, ForwardIterator2 otherFirst) {
	return uninitialized_copy(first, first + size, otherFirst);
}

/**
 *
 */
template <typename ForwardIterator1, typename ForwardIterator2, typename Allocator>
ForwardIterator2
uninitialized_copy_alloc(ForwardIterator1 first, ForwardIterator1 last,
		ForwardIterator2 otherFirst, Allocator& alloc) {
	using alloc_traits = prism::AllocatorTraits<Allocator>;
	using value_type = typename prism::iterator_traits<ForwardIterator1>::value_type;
	auto current = first;
	try {
		for (; current != last; ++current, ++otherFirst)
			alloc_traits::construct(alloc, &*otherFirst, value_type(*current));
	}
	catch(...) {
		for (auto it = first; it != current; it++)
			(&*it)->~value_type();
		throw;
	}
	return otherFirst;
}

/**
 *
 */
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator2
uninitialized_move(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 otherFirst) {
	using value_type = typename prism::iterator_traits<ForwardIterator1>::value_type;
	auto current = first;
	try {
		for (; current != last; current++, otherFirst++)
			::new (static_cast<void*>(&*otherFirst)) value_type(std::move(*current));
	}
	catch(...) {
		for (auto it = first; it != current; it++)
			(&*it)->~value_type();
		throw;
	}
	return otherFirst;
}

/**
 *
 */
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2
uninitialized_move_backwards(BidirectionalIterator1 first,
								BidirectionalIterator1 last,
								BidirectionalIterator2 otherLast)
{
	using value_type = typename prism::iterator_traits<BidirectionalIterator1>::value_type;
	auto current = last;
	try {
		while (current != first)
			::new (static_cast<void*>(&*--otherLast)) value_type(std::move(*--current));
	}
	catch(...) {
		auto it = last;
		while (it != current)
			(&*--it)->~value_type();
		throw;
	}
	return otherLast;
}

} // end namespace prism


#endif // PRISM_ALGORITHM_PRIV_H_
