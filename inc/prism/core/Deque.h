/*
 * Deque.h
 * v1
 *
 *  Created on: Aug 23, 2016
 *      Author: iainhemstock
 */

/*TODO
	Functions to add:
		static Deque<T, Alloc> fromList(const List<T>& list);
		void squeeze();
		iterator insert(const_iterator insertBefore, std::initializer_list<T>& il)
*/

#ifndef PRISM_DEQUE_H_
#define PRISM_DEQUE_H_

#include <prism/core/List.h>
#include <prism/Allocator>
#include <prism/SharedDataPointer>
#include <deque>

namespace prism {

template <class T, class TAllocator>
struct DequeData;

static const int prism_deque_bucket_size = 20;

//================================================================================
// Deque
//================================================================================
template <class T, class TAllocator = prism::Allocator<T>>
class Deque {
public:
	typedef DequeData<T, TAllocator>				Data;
	typedef typename Data::iterator					iterator;
	typedef typename Data::const_iterator			const_iterator;
	typedef typename TAllocator::value_type			value_type;
	typedef typename TAllocator::difference_type	difference_type;
	typedef typename TAllocator::pointer			pointer;
	typedef typename TAllocator::reference			reference;
	typedef typename TAllocator::const_pointer		const_pointer;
	typedef typename TAllocator::const_reference	const_reference;
	typedef typename iterator::iterator_category 	iterator_category;
private:
	SharedDataPointer<Data> d;
public:
	/**
	 * Creates an empty Deque.
	 */
	Deque();

	/**
	 * Creates a Deque that contains \em size amount of elements
	 * initialized to \em value.
	 */
	Deque(const int size, const_reference value=T());

	/**
	 *
	 */
	template <class ForwardIterator>
	Deque(ForwardIterator first, ForwardIterator last);

	/**
	 * Creates a Deque and assigns the elements in the initializer list
	 * to the Deque.
	 */
	Deque(std::initializer_list<T> list);

	/**
	 * Creates a new Deque which is a copy of \em copy.
	 */
	Deque(const Deque<T, TAllocator>& copy);

	/**
	 * Destroys this Deque.
	 */
	~Deque();

	/**
	 *
	 */
	TAllocator
	allocator() const;

	/**
	 *
	 */
	void
	append(const_reference value);

	/**
	 * @return Returns a reference to the the element at index \em i.
	 * @exception Throws an OutOfBoundsException if \em i is less than 0 or
	 * greater than or equal to \em size().
	 */
	reference
	at(const int i);

	/**
	 * @return Returns a const reference to the the element at index \em i.
	 * @exception Throws an OutOfBoundsException if \em i is less than 0 or
	 * greater than or equal to \em size().
	 */
	const_reference
	at(const int i) const;

	/**
	 * @return Returns a reference to the last element in the Deque.
	 */
	reference
	back();

	/**
	 * @return Returns a const reference to the last element in the Deque.
	 */
	const_reference
	back() const;;

	/**
	 * @return Returns an iterator that points to the first element in the Deque.
	 */
	iterator
	begin();

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	begin() const;

	/**
	 * @return Returns the capacity of the Deque.
	 */
	const int
	capacity() const;

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	cbegin() const;

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	cend() const;

	/**
	 * Clears all elements from the Deque so that its size is 0. \n
	 * Note that this does not affect the capacity.
	 */
	void
	clear();

	/**
	 * @return Returns a const_iterator that points to the first element in the Deque.
	 */
	const_iterator
	constBegin() const;

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	constEnd() const;

	/**
	 * @return Returns true if the Deque contains \em value, false otherwise.
	 */
	const bool
	contains(const_reference value) const;

	/**
	 *
	 */
	const int
	count(const_reference value) const;

	/**
	 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
	 */
	const bool
	empty() const;

	/**
	 * @return Returns an iterator that points to one position past the last element in the Deque.
	 */
	iterator
	end();

	/**
	 * @return Returns a const_iterator that points to one position past the last element in the Deque.
	 */
	const_iterator
	end() const;

	/**
	 *
	 */
	const bool
	endsWith(const_reference value) const;

	/**
	 *
	 */
	iterator
	erase(iterator pos);

	/**
	 * @return Returns an iterator to the new position of the element that follows the
	 * last element erased.
	 * \code
	 * Deque<int> d({1,2,3,4,5,6});
	 * iterator it = d.erase(d.begin()+2, d.begin()+5);
	 * // *it == 6 since the integers 3, 4 and 5 were erased
	 * \endcode
	 */
	iterator
	erase(iterator first, iterator last);

	/**
	 * Sets each element in the Deque to \em value.
	 */
	void
	fill(const_reference value);

	/**
	 * @return Returns a reference to the first element in the Deque.
	 */
	reference
	first();

	/**
	 * @return Returns a const reference to the first element in the Deque.
	 */
	const_reference
	first() const;

	/**
	 * @return Returns a reference to the first element in the Deque.
	 */
	reference
	front();

	/**
	 * @return Returns a const reference to the first element in the Deque.
	 */
	const_reference
	front() const;

	/**
	 * Searches for the first index starting from index \em from that contains \em value.
	 * @return Returns the index of of the first occurrence of \em value or -1 if \em value
	 * does not occur in the Deque.
	 */
	const int
	indexOf(const_reference value, const int from=0) const;

	/**
	 *
	 */
	void
	insert(const int index, const_reference value);

	/**
	 *
	 */
	void
	insert(const int index, const int count, const_reference value);

	/**
	 *
	 */
	iterator
	insert(iterator insertBefore, const_reference value);

	/**
	 *
	 */
	iterator
	insert(iterator insertBefore, const int count, const_reference value);

	/**
	 * @return Returns true if the Deque is empty i.e. size == 0, false otherwise.
	 */
	const bool
	isEmpty() const;

	/**
	 * @return Returns a reference to the last element in the Deque.
	 */
	reference
	last();

	/**
	 * @return Returns a const reference to the last element in the Deque.
	 */
	const_reference
	last() const;

	/**
	 *
	 */
	const int
	lastIndexOf(const_reference value, int from=-1) const;

	/**
	 *
	 */
	Deque<T, TAllocator>
	mid(const int startIndex, const int count) const;

	/**
	 *
	 */
	void
	pop_back();

	/**
	 *
	 */
	void
	pop_front();

	/**
	 *
	 */
	void
	prepend(const_reference value);

	/**
	 *
	 */
	void
	push_back(const_reference value);

	/**
	 *
	 */
	void
	push_front(const_reference value);

	/**
	 *
	 */
	void
	remove(const int index);

	/**
	 *
	 */
	void
	remove(const int index, const int count);

	/**
	 *
	 */
	void
	removeAll(const_reference value);

	/**
	 *
	 */
	void
	removeFirst();

	/**
	 *
	 */
	void
	removeLast();

	/**
	 *
	 */
	void
	replace(const int index, const_reference value);

	/**
	 *
	 */
	void
	resize(const int newSize, const_reference value=T());

	/**
	 * @return Returns the number of elements currently in the Deque.
	 */
	const int
	size() const;

	/**
	 *
	 */
//	void
//	squeeze() {
//		d->reduceMemoryUse();
//	}

	/**
	 *
	 */
	const bool
	startsWith(const_reference value) const;

	/**
	 *
	 */
	List<T>
	toList() const;

	/**
	 *
	 */
	std::deque<T>
	toStdDeque() const;

	/**
	 * @return Returns a reference to the element at index \em i.
	 * \note Note that no bounds checking is performed on \em i.
	 */
	reference
	operator [](const int i);

	/**
	 * @return Returns a const reference to the element at index \em i.
	 * \note Note that no bounds checking is performed on \em i.
	 */
	const_reference
	operator [](const int i) const;

	/**
	 *
	 */
	Deque<T, TAllocator>&
	operator=(const Deque<T, TAllocator>& rhs);

	/**
	 *
	 */
	const bool
	operator==(const Deque<T, TAllocator>& rhs) const;

	/**
	 *
	 */
	const bool
	operator!=(const Deque<T, TAllocator>& rhs) const;

	/**
	 *
	 */
	Deque<T, TAllocator>
	operator+(const Deque<T, TAllocator>& rhs);

	/**
	 *
	 */
	Deque<T, TAllocator>&
	operator+=(const Deque<T, TAllocator>& rhs);

	/**
	 *
	 */
	Deque<T, TAllocator>&
	operator<<(const_reference value);

	/**
	 *
	 */
	Deque<T, TAllocator>&
	operator<<(const Deque<T, TAllocator>& rhs);

	/**
	 *
	 */
	friend std::ostream&
	operator<<(std::ostream& out, const Deque<T, TAllocator>& d) {
		out << "Deque [" << &d << "]\n"
				"----size:           " << d.size() << "\n" <<
				"----capacity:       " << d.capacity() << "\n" <<
				"----numBuckets:     " << d.d->storage.numBuckets() << std::endl;
		out << "----storage.start:  [" << d.d->storage.start << "]" << std::endl;
		out << "----storage.finish: [" << d.d->storage.finish << "]" << std::endl;
		out << "----begin:\n" <<
			   "      [buckets address: " << d.d->begin.buckets << "]\n" <<
			   "      [buckets index: " << d.d->begin.buckets-d.d->storage.start << "] \n" <<
			   "      [bucket address: " << d.d->begin.start << "]\n" <<
			   "      [current index:" << d.d->begin.current-d.d->begin.start << "]\n";
		out << "----end: \n" <<
			   "      [buckets address: " << d.d->end.buckets << "] \n" <<
			   "      [buckets index:" << d.d->end.buckets-d.d->storage.start << "] \n" <<
			   "      [bucket address: " << d.d->end.start << "] \n" <<
			   "      [current index:" << d.d->end.current-d.d->end.start << "]\n";

		int startIndex = (d.d->begin.buckets - d.d->storage.start) *
							prism_deque_bucket_size
							+ d.d->begin.current - d.d->begin.start;

		const_iterator cit = d.cbegin();

		for (int i=0; i<d.capacity(); i++) {
			if (i % prism_deque_bucket_size == 0) {
				out << "---------------------------------" << std::endl;
				out << "Bucket " << (cit.buckets-d.d->storage.start) << ": \n" <<
						"--- storage address: " << cit.buckets << "\n" <<
						"--- bucket address:  " << *cit.buckets << std::endl;
				out << "---------------------------------" << std::endl;
			}

			if (i < startIndex || i >= startIndex+d.size())
				out << "[-] *" << std::endl;
			else
				out << "[" << (cit-d.cbegin()) << "] " << *cit++ << std::endl;
		}

		return out;
	}

}; // class Deque

} // namespace prism

#include <prism/core/priv/Deque_priv.h>

#endif // PRISM_DEQUE_H
