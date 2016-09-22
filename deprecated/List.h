/*
 * List.h
 * v1
 *
 *  Created on: Jan 10, 2015
 *      Author: iainhemstock
 *
 *  List is a template-based container where each value is "linked" to the following value.
 *  It is implemented as a doubly linked list.
 */

/*
 * todo add support for move constructor
 */

#ifndef PRISM_LIST_H_
#define PRISM_LIST_H_

#include <prism/Iterator> // for bidirectional_iterator_tag
#include <prism/algorithms>
#include <ostream>
#include <forward_list>

namespace prism {
//
/****************************************************************************************************************
 * Special iterator for the List container (implemented as a bidirectional iterator.
 * A list contains a linked list of nodes and each node contains the actual values
 * stored by the user. As such the iterator needs to return that value and not the
 * node as that is part of the private implementation.
 ****************************************************************************************************************/
// \cond DO_NOT_DOCUMENT
template <class Node, class T>
struct ListIterator {
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;
	typedef bidirectional_iterator_tag 	iterator_category;
	typedef std::ptrdiff_t 				difference_type;

										Node * node;
										ListIterator() : node(0) {}
										ListIterator(Node * node) : node(node) {}
										ListIterator(const ListIterator & copy) { node = copy.node; }
	reference 							operator*() { return node->value; }
	pointer 							operator->() { return &node->value; }
	ListIterator & 						operator++() { node = node->next; return *this; }
	ListIterator   						operator++(int junk) { Node * n = node; node = node->next; return n; }
	ListIterator & 						operator--() { node = node->prev; return *this; }
	ListIterator  						operator--(int junk) { Node * n = node; node = node->prev; return n; }
	ListIterator & 						operator=(const ListIterator & rhs) { node = rhs.node; return *this;}
	bool 								operator!=(const ListIterator & rhs) { return node != rhs.node; }
	bool 								operator==(const ListIterator & rhs) const { return node == rhs.node; }

	// Related non-members
	friend inline difference_type 		operator-(const ListIterator & lhs, const ListIterator & rhs) { return lhs.node - rhs.node; }
	friend inline const bool 			operator<(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 			operator>(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 			operator<=(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 			operator>=(const ListIterator & lhs, const ListIterator & rhs) { return lhs-rhs >= 0; }
};
// \endcond
/****************************************************************************************************************
 * Const List iterator
 ****************************************************************************************************************/
// \cond DO_NOT_DOCUMENT
template <class Node, class T>
struct ListConstIterator {
	typedef const T						value_type;
	typedef const T&					reference;
	typedef const T*					pointer;
	typedef bidirectional_iterator_tag 	iterator_category;
	typedef std::ptrdiff_t 				difference_type;

										Node * node;
										ListConstIterator() : node(0) {}
										ListConstIterator(Node * node) : node(node) {}
										ListConstIterator(const ListConstIterator & copy) { node = copy.node; }
	reference 							operator*() { return node->value; }
	pointer 							operator->() { return &node->value; }
	ListConstIterator & 				operator++() { node = node->next; return *this; }
	ListConstIterator   				operator++(int junk) { Node * n = node; node = node->next; return n; }
	ListConstIterator & 				operator--() { node = node->prev; return *this; }
	ListConstIterator 	 				operator--(int junk) { Node * n = node; node = node->prev; return n; }
	ListConstIterator & 				operator=(const ListConstIterator & rhs) { node = rhs.node; return *this;}
	bool 								operator!=(const ListConstIterator & rhs) { return node != rhs.node; }
	bool 								operator==(const ListConstIterator & rhs) const { return node == rhs.node; }

	// Related non-members
	friend inline difference_type 		operator-(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs.node - rhs.node; }
	friend inline const bool 			operator<(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs < 0; }
	friend inline const bool 			operator>(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs > 0; }
	friend inline const bool 			operator<=(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs <= 0; }
	friend inline const bool 			operator>=(const ListConstIterator & lhs, const ListConstIterator & rhs) { return lhs-rhs >= 0; }
};
// \endcond
/****************************************************************************************************************
 *
 ****************************************************************************************************************/
// \cond DO_NOT_DOCUMENT
template <class T>
struct ListNode {
	T value;
	ListNode * next;
	ListNode * prev;
	ListNode(const T & value=T()) : value(value), next(0), prev(0) {}
};
// \endcond

/****************************************************************************************************************
 *
 ****************************************************************************************************************/
template <class T>
class List {
	typedef ListNode<T>	Node;
public:
	typedef ListIterator<Node, T> 				iterator;
	typedef ListConstIterator<Node, T> 			const_iterator;
	typedef typename iterator::reference		reference;
	typedef typename const_iterator::reference	const_reference;
	typedef typename iterator::pointer			pointer;
	typedef typename const_iterator::pointer	const_pointer;
	typedef typename iterator::value_type		value_type;
	typedef typename iterator::difference_type	difference_type;
	typedef int									size_type;

protected:
	Node * 					m_header; // Imaginary node before the first node
	Node *					m_tailer; // Imaginary node following the last node
	int 					m_size;
public:
							List();
							List(std::initializer_list<T> il);
							List(const List<T> & copy);
	virtual 				~List();
	iterator 				append(const T & value);
	T& 						back();
	const T& 				back() const;
	iterator 				begin();
	const_iterator 			begin() const;
	const_iterator			cbegin() const;
	const_iterator			cend() const;
	const_iterator 			constBegin() const;
	const_iterator 			constEnd() const;
	const bool				contains(const T & value) const;
	const int				count(const T & value) const;
	void 					clear();
	const bool				empty() const;
	iterator 				end();
	const_iterator 			end() const;
	const bool				endsWith(const T & value) const;
	iterator 				erase(iterator pos);
	T&						first();
	const T&				first() const;
	T& 						front();
	const T& 				front() const;
	iterator 				insert(const iterator & pos, const T & value);
	const bool 				isEmpty() const;
	T&						last();
	const T&				last() const;
	void					pop_back();
	void					pop_front();
	void 					push_back(const T & value);
	void 					push_front(const T & value);
	iterator 				prepend(const T & value);
	void					removeAll(const T & value);
	void					removeFirst();
	void					removeFirstOf(const T & value);
	void 					removeLast();
	const int 				size() const;
	const bool				startsWith(const T & value) const;
	std::forward_list<T> 	toStdForwardList() const;

	List<T>& 				operator<<(const T & value);
	List<T>&				operator<<(const List<T> & list);
	const bool				operator==(const List<T> & rhs) const;
	const bool				operator!=(const List<T> & rhs) const;
	List<T>&				operator=(const List<T> & rhs);
	List<T>					operator+(const List<T> & rhs) const;
	List<T>&				operator+=(const List<T> & rhs);
	List<T>&				operator+=(const T & value);

	static List<T>			fromStdForwardList(const std::forward_list<T> & fl);

};

/**
 * Constructs an empty list.
 */
template <class T>
List<T>::List() : m_header(new Node()), m_tailer(new Node()), m_size(0) {
	m_header->next = m_tailer;
	m_tailer->prev = m_header;
}

/**
 * Constructs a list from the elements contained in the initializer list.
 */
template <class T>
List<T>::List(std::initializer_list<T> il)
	: m_header(new Node()), m_tailer(new Node()), m_size(0)
{
	m_header->next = m_tailer;
	m_tailer->prev = m_header;

	for (auto it = il.begin(); it != il.end(); it++)
		insert(--end(), *it);
}

/**
 * Copy-constructs a new list from \em copy.
 */
template <class T>
List<T>::List(const List<T> & copy) : m_header(new Node()), m_tailer(new Node()), m_size(0) {
	m_header->next = m_tailer;
	m_tailer->prev = m_header;

	const_iterator itCopy = copy.constBegin();
	iterator itThis = begin();
	while (itCopy != copy.constEnd()) {
		itThis = append(*itCopy);
		itCopy++;
	}
}

/**
 * Destroys this list.
 */
template <class T>
List<T>::~List<T>() {
	clear();

	delete m_header;
	delete m_tailer;
}

/**
 * Appends \em value at the end of this list.
 * Returns an iterator pointing to the item just inserted.
 */
template <class T>
typename List<T>::iterator List<T>::append(const T & value) {
	return insert(--end(), value);
}

/**
 * Returns a reference to the last item in the list. Added for STL-compatibility.
 */
template <class T>
T & List<T>::back() {
	const_iterator it = --constEnd();
	return it.node->value;
}

/**
 * Returns a const reference to the last item in the list. Added for STL-compatibility.
 */
template <class T>
const T & List<T>::back() const {
	const_iterator it = --constEnd();
	return it.node->value;
}

/**
 * Returns an iterator to the first item in the list. If the list is empty then the returned iterator is equal to end().
 */
template <class T>
typename List<T>::iterator List<T>::begin() {
	return iterator(m_header->next);
}

/**
 * Returns an iterator to the first item in the list. If the list is empty then the returned iterator is equal to end().
 */
template <class T>
typename List<T>::const_iterator List<T>::begin() const {
	return const_iterator(m_header->next);
}

/**
 * Returns a const_iterator that points to the first item in the list.
 */
template <class T>
typename List<T>::const_iterator List<T>::cbegin() const {
	return const_iterator(m_header->next);
}

/**
 * Returns an iterator to the imaginary position one past the last item.
 * This iterator should not be dereferenced.
 */
template <class T>
typename List<T>::const_iterator List<T>::cend() const {
	return const_iterator(m_tailer);
}

/**
 * Removes every item from this list.
 */
template <class T>
void List<T>::clear() {
	while (m_header->next != m_tailer) {
		erase(begin());
	}
}

/**
 * Returns a const_iterator that points to the first item in the list.
 */
template <class T>
typename List<T>::const_iterator List<T>::constBegin() const {
	return const_iterator(m_header->next);
}

/**
 * Returns an iterator to the imaginary position one past the last item.
 * This iterator should not be dereferenced.
 */
template <class T>
typename List<T>::const_iterator List<T>::constEnd() const {
	return const_iterator(m_tailer);
}

/**
 * Returns true if this list contains \em value, false otherwise.
 * The value type should have an implementation of operator==().
 */
template <class T>
const bool List<T>::contains(const T & value) const {
	const_iterator it = constBegin();
	while (it != constEnd()) {
		if (it.node->value == value) {
			return true;
		}
		it++;
	}
	return false;
}

/**
 * Counts and returns the number of occurrences of \em value in this list.
 * The value type should have an implementation of operator==().
 */
template <class T>
const int List<T>::count(const T & value) const {
	int i = 0;
	const_iterator it = constBegin();
	while (it != constEnd()) {
		if (it.node->value == value) i++;
		it++;
	}
	return i;
}

/**
 * Returns true if the list contains no items, false otherwise.
 * Equivalent to isEmpty(). Added for STL-compatibility.
 */
template <class T>
const bool List<T>::empty() const {
	return isEmpty();
}

/**
 * Returns an iterator to the imaginary position one past the last item.
 * This iterator should not be dereferenced.
 */
template <class T>
typename List<T>::iterator List<T>::end() {
	return iterator(m_tailer);
}

/**
 * Returns a const_iterator to the imaginary item one past the last item.
 */
template <class T>
typename List<T>::const_iterator List<T>::end() const {
	return const_iterator(m_tailer);
}

/**
 * Returns true if the list is not empty and the last item is equal to \em value, false otherwise.
 * The value type should have an implementation of operator==().
 */
template <class T>
const bool List<T>::endsWith(const T & value) const {
	if (m_header->next == m_tailer) return false; // empty list
	if (back() == value) return true;
	return false;
}

/**
 * Removes the item from the list pointed to by \em pos.
 * If \em pos is equal to end() then nothing is removed and \em pos is returned.
 * Otherwise an iterator to the item after the one just removed is returned instead which could be
 * equal to end() if the list is now empty.
 */
template <class T>
typename List<T>::iterator List<T>::erase(iterator pos) {
	if (pos.node == m_header || pos.node == m_tailer) return pos;

	Node* nbefore = pos.node->prev;
	Node* nafter = pos.node->next;

	nbefore->next = nafter;
	nafter->prev = nbefore;

	delete pos.node;
	m_size--;

	return iterator(nafter);
}

/**
 * Returns a reference to the first item in the list.
 * Equivalent to front().
 */
template <class T>
T & List<T>::first() {
	return m_header->next->value;
}

/**
 * Returns a const reference to the first item in the list.
 * Equivalent to front().
 */
template <class T>
const T & List<T>::first() const {
	return m_header->next->value;
}

/**
 * Returns a reference to the first item in the list. Added for STL-compatibility.
 * Equivalent to first().
 */
template <class T>
T & List<T>::front() {
	return m_header->next->value;
}

/**
 * Returns a const reference to the first item in the list. Added for STL-compatibility.
 * Equivalent to first().
 */
template <class T>
const T & List<T>::front() const {
	return m_header->next->value;
}

/**
 * Inserts \em value at one position after the item at \em pos.
 * Returns an iterator to the item just inserted.
 */
template <class T>
typename List<T>::iterator List<T>::insert(const iterator & pos, const T & value) {
	Node* n = new Node(value);
	Node* nbefore = pos.node;
	Node* nafter = nbefore->next;

	n->next = nafter;
	n->prev = nbefore;
	nbefore->next = n;
	nafter->prev = n;

	m_size++;
	return iterator(n);
}

/**
 * Returns true if the list contains no items, false otherwise.
 */
template <class T>
const bool List<T>::isEmpty() const {
	return m_header->next == m_tailer;
}

/**
 * Returns a reference to the last item in the list. Equivalent to back();
 */
template <class T>
T & List<T>::last() {
	return back();
}

/**
 * Returns a const reference to the last item in the list. Equivalent to back();
 */
template <class T>
const T & List<T>::last() const {
	return back();
}

/**
 * Removes the last item in the list. Equivalent to removeLast(). Added for STL-compatibility.
 */
template <class T>
void List<T>::pop_back() {
	erase(--end());
}

/**
 * Removes the first item in the list. Equivalent to removeFirst(). Added for STL-compatibility.
 */
template <class T>
void List<T>::pop_front() {
	erase(begin());
}

/**
 * Adds \em value to the start of the list.
 * Returns an iterator to the item just inserted.
 */
template <class T>
typename List<T>::iterator List<T>::prepend(const T & value) {
	return insert(--begin(), value);
}

/**
 * Appends \em value to the end of the list and is equivalent to append(). Added for STL-compatibility.
 */
template <class T>
void List<T>::push_back(const T & value) {
	insert(--end(), value);
}

/**
 * Prepends \em value at the beginning of the list and is equivalent to prepend(). Added for STL-compatibility.
 */
template <class T>
void List<T>::push_front(const T & value) {
	insert(--begin(), value);
}

/**
 * Removes all occurrences of \em value from the list. To remove all items from the list use clear().
 * The value type should have an implementation of operator==().
 */
template <class T>
void List<T>::removeAll(const T & value) {
	iterator it = begin();
	while (it != end()) {
		if (it.node->value == value) erase(iterator(it.node));
		it++;
	}
}

/**
 * Removes the first item in the list. Equivalent to pop_front().
 */
template <class T>
void List<T>::removeFirst() {
	pop_front();
}

/**
 * Removes the first occurrence of \em value from the list.
 * The value type should have an implementation of operator==().
 */
template <class T>
void List<T>::removeFirstOf(const T & value) {
	iterator it = begin();
	while (it != end()) {
		if (it.node->value == value) {
			erase(it);
			break;
		}
		it++;
	}
}

/**
 * Removes the last item in the list. Equivalent to pop_back().
 */
template <class T>
void List<T>::removeLast() {
	pop_back();
}

/**
 * Returns the number of items contained in the list.
 */
template <class T>
const int List<T>::size() const {
	return m_size;
}

/**
 * Returns true if the list is not empty and the first item equals \em value.
 */
template <class T>
const bool List<T>::startsWith(const T & value) const {
	if (m_header->next == m_tailer) return false; // empty list?
	if (m_header->next->value != value) return false;
	return true;

}

/**
 * Creates and returns a std::forward_list containing the items from this list.
 */
template <class T>
std::forward_list<T> List<T>::toStdForwardList() const {
	std::forward_list<T> fl;
	typename std::forward_list<T>::iterator itFl = fl.before_begin();
	const_iterator itThis = constBegin();

	while (itThis != constEnd()) {
		itFl = fl.insert_after(itFl, *itThis++);
	}

	return fl;
}

/**
 * Appends \em value to the end of the list. Equivalent to append() and is useful to chain appends together
 * i.e. list << 1 << 2 << 3 etc.
 */
template <class T>
List<T> & List<T>::operator<<(const T& value) {
	append(value);
	return *this;
}

/**
 * Appends the items in \em list to the end of this list.
 * Returns a reference to this list.
 */
template <class T>
List<T> & List<T>::operator <<(const List<T> & list) {
	*this += list;
}

/**
 * Returns true if this list is equal to the other list \em rhs.
 * They are considered equal if they are the same size and have the same values in the same order.
 */
template <class T>
const bool List<T>::operator==(const List<T> & rhs) const {
	if (m_size != rhs.size()) return false;

	const_iterator thisIt = constBegin();
	const_iterator rhsIt = rhs.constBegin();

	while (thisIt != constEnd()) {
		if (*thisIt++ != *rhsIt++) return false;
	}
	return true;
}

/**
 * Returns true if this list is equal to the other list \em rhs.
 * They are considered equal if they are the same size and have the same values in the same order.
 */
template <class T>
const bool List<T>::operator!=(const List<T> & rhs) const {
	return !(*this==rhs);
}

/**
 * Assigns the list \em rhs to this list.
 * Returns a reference to this list.
 */
template <class T>
List<T> & List<T>::operator=(const List<T> & rhs) {
	if (m_header != rhs.m_header) { // don't assign to self
		*this = List<T>(rhs);
	}
}

/**
 * Creates and returns a new list that starts with this list followed by the list \em rhs.
 */
template <class T>
List<T> List<T>::operator+(const List<T> & rhs) const {
	List<T> list = List<T>(*this);
	const_iterator itRhs = rhs.constBegin();

	while (itRhs != rhs.constEnd()) {
		list.insert(--list.end(), itRhs.node->value);
		itRhs++;
	}
	return list;
}

/**
 * Appends the contents of the list \em rhs to the end of this list.
 * Returns a reference to this list.
 */
template <class T>
List<T> & List<T>::operator +=(const List<T> & rhs) {
	const_iterator itRhs = rhs.constBegin();
	while (itRhs != rhs.end()) {
		insert(--end(), itRhs.node->value);
		itRhs++;
	}
	return *this;
}

/**
 * Appends \em value to the end of the list.
 * Returns a reference to this list.
 */
template <class T>
List<T> & List<T>::operator +=(const T & value) {
	insert(--end(), value);
}

/**
 * Static method that creates and returns a new list from a std::forward_list.
 */
template <class T>
List<T> List<T>::fromStdForwardList(const std::forward_list<T> & fl) {
	List<T> list;
	typename std::forward_list<T>::const_iterator it = fl.cbegin();

	while (it != fl.cend())
		list.append(*it++);

	return list;
}

/**
 * Outputs a human-friendly summary of \em list to the stream \em out.
 */
template <class T>
std::ostream & operator<<(std::ostream & out, const List<T> & list) {
	typename List<T>::const_iterator it = list.constBegin();
	int i = 0;

//	out << "------------------ \n";
	out << "List (" << &list << ") size:" << list.size() << "\n";
//	out << "------------------ \n";

	if (list.isEmpty()) out << "(empty)" << std::endl;

	while (it != list.constEnd()) {
		out << "-- [" << i++ << "] " << *it;
		out << std::endl;
		it++;
	}
//	out << "------------------ \n";
	return out;
}

}

#endif /* PRISM_LIST_H_ */
