/*
 * List.h
 * v2
 *
 *  Created on: Sep 19, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TMP_LIST_H_
#define PRISM_TMP_LIST_H_

#include <prism/SharedData>
#include <prism/SharedDataPointer>
#include <prism/Allocator>
#include <prism/algorithms>
#include <prism/utilities> // for prism::conditional_type
#include <cstddef> // for std::ptrdiff_t
#include <ostream>
#include <utility> // for std::forward

#include <initializer_list>
using namespace std;

namespace prism {
namespace tmp {

//============================================================
// ListNode
//============================================================
template <class T>
struct ListNode {
	typedef ListNode<T> 	Node;
	T 						value;
	Node* 					next;
	Node* 					previous;

	ListNode()
	: value(),
	  next(0),
	  previous(0)
	{}

	ListNode(const T& value)
	: value(value),
	  next(nullptr),
	  previous(nullptr)
	{}

	friend std::ostream& operator<<(std::ostream& out, ListNode<T>& node) {
		out << "ListNode [" << &node;
		return out;
	}
};

//============================================================
// ListIterator
//============================================================
template <class T, bool isConst>
struct ListIterator {
	typedef T 								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef bidirectional_iterator_tag 		iterator_category;
	typedef ListNode<T>*					NodePtr;
	typedef ListIterator<T, false> 			iterator;
	typedef ListIterator<T, true> 			const_iterator;

	typedef typename prism::conditional_type<isConst, const T*, T*>::type pointer;
	typedef typename prism::conditional_type<isConst, const T&, T&>::type reference;
	typedef typename prism::conditional_type<isConst, const_iterator, iterator>::type Self;

	NodePtr np;

	ListIterator()
	: np(nullptr)
	{}

	ListIterator(NodePtr np)
	: np(np)
	{}

	ListIterator(const iterator& copy)
	: np(copy.np)
	{}

	virtual
	~ListIterator()
	{}

	reference
	operator*()
	{ return np->value; }

	pointer
	operator->()
	{ return &np->value; };

	Self&
	operator++() {
		np = np->next;
		return *this;
	}

	Self
	operator++(int junk) {
		NodePtr tmp = np;
		np = np->next;
		return tmp;
	}

	Self&
	operator--() {
		np = np->previous;
		return *this;
	}

	Self
	operator--(int junk) {
		NodePtr tmp = np;
		np = np->previous;
		return tmp;
	}

	Self&
	operator=(const iterator& other) {
		if (this->np != other.np)
			this->np = other.np;
		return *this;
	}

	const bool
	operator==(const Self& rhs)
	{ return this->np == rhs.np; }

	const bool
	operator!=(const Self& rhs)
	{ return !(*this == rhs); }

	difference_type
	operator-(const Self& rhs)
	{ return this->np - rhs.np; }

	const bool
	operator<(const Self& rhs)
	{ return this->np < rhs.np; }

	const bool
	operator>(const Self& rhs)
	{ return this->np > rhs.np; }

	const bool
	operator<=(const Self& rhs)
	{ return this->np <= rhs.np; }

	const bool
	operator>=(const Self& rhs)
	{ return this->np >= rhs.np; }
};

//============================================================
// ListMemory
//============================================================
template <class NodeAllocator>
struct ListMemory {
	typedef typename NodeAllocator::pointer 					NodePtr;

	NodeAllocator 												m_nodeAllocator;

	/**
	 *
	 */
	NodePtr
	allocateNode()
	{ return m_nodeAllocator.allocate(1); }

	/**
	 *
	 */
	void
	deallocateNode(NodePtr np)
	{ m_nodeAllocator.deallocate(np); }

	/**
	 *
	 */
	void
	destroyNodes(NodePtr first, NodePtr last) {

		NodePtr currentNode = first;

		while (currentNode != last) {
			NodePtr thisNode = currentNode;
			NodePtr nextNode = thisNode->next;
			deallocateNode(thisNode);
			currentNode = nextNode;
		}
	}
};

//============================================================
// ListData
//============================================================
//template <class T, class Node, class NodeAllocator>
template <class T, class NodeAllocator>
struct ListData : public SharedData {
//	typedef typename TAllocator::value_type								T;

	typedef ListMemory<NodeAllocator> 									Memory;
	typedef typename Memory::NodePtr		 							NodePtr;

	Memory		m_storage;
	NodePtr 	m_header;
	NodePtr		m_tailer;
	int 		m_nodeCount;

	/**
	 * Creates an empty list with the header and tailer nodes
	 */
	ListData()
	: m_storage(),
	  m_header(nullptr),
	  m_tailer(nullptr),
	  m_nodeCount(0)
	{ initializeStorage(); }

	/**
	 *
	 */
	ListData(const int numElements, const T& value)
	: m_storage(),
	  m_header(nullptr),
	  m_tailer(nullptr),
	  m_nodeCount(0)
	{
		initializeStorage();
		initializeFill(numElements, value);
		increaseNodeCount(numElements);
	}

	/**
	 *
	 */
	template <class ForwardIterator>
	ListData(ForwardIterator first, ForwardIterator last)
	: m_storage(),
	  m_header(nullptr),
	  m_tailer(nullptr),
	  m_nodeCount(0)
	{
		initializeStorage();
		rangeInsert(m_header, first, last);
		increaseNodeCount(last-first);
	}

	/**
	 *
	 */
	ListData(const std::initializer_list<T>& il)
	: m_storage(),
	  m_header(nullptr),
	  m_tailer(nullptr),
	  m_nodeCount(0)
	{
		initializeStorage();
		rangeInsert(m_header, il.begin(), il.end());
		increaseNodeCount(il.end()-il.begin());
	}

	/**
	 *
	 */
	ListData(const ListData& copy)
	: m_header(0),
	  m_tailer(0),
	  m_nodeCount(copy.m_nodeCount)
	{
		initializeStorage();
		rangeInsert(m_header, copy.begin(), copy.end());
		increaseNodeCount(copy.nodeCount());
	}

	/**
	 *
	 */
	~ListData() {
		m_storage.m_nodeAllocator.destroy(m_header);
		m_storage.m_nodeAllocator.destroy(m_tailer);

		m_storage.destroyNodes(m_header, m_tailer);
		m_storage.deallocateNode(m_tailer);
	}

	/**
	 *
	 */
	void
	appendValue(const T& value) {
		NodePtr newNode = createNode(value);
		insertNode(m_tailer->previous, newNode);
		increaseNodeCount(1);
	}

	/**
	 *
	 */
	NodePtr
	begin() const
	{ return m_header->next; }

	/**
	 *
	 */
	void
	clear() {
		m_storage.destroyNodes(m_header->next, m_tailer);
		m_header->next = m_tailer;
		m_tailer->previous = m_header;
		setNodeCount(0);
	}

	/**
	 *
	 */
	template <typename ...Args>
	NodePtr
	createNode(Args&&... args) {
		NodePtr newNode = m_storage.allocateNode();
		m_storage.m_nodeAllocator.construct(newNode, std::forward<Args>(args)...);
		return newNode;
	}

	/**
	 *
	 */
	void
	decreaseNodeCount(const int amount)
	{ m_nodeCount -= amount; }

	/**
	 *
	 */
	NodePtr
	end() const
	{ return m_tailer; }

	/**
	 *
	 */
	void
	increaseNodeCount(const int amount)
	{ m_nodeCount += amount; }

	/**
	 *
	 */
//	NodeAllocator
//	getNodeAllocator() const
//	{ return m_storage.getNodeAllocator(); }

	/**
	 * Called by ListData(numElements, value) constructor.
	 * The list is empty, only the header and tailer nodes exist.
	 */
	void
	initializeFill(const int numElements, const T& value) {
		NodePtr currentNode = m_header;

		for (int i=0; i<numElements; i++) {
			NodePtr newNode = createNode(value);
			insertNode(currentNode, newNode);
			currentNode = newNode;
		}
	}

	/**
	 * Creates the header and tailer nodes and links them together.
	 */
	void
	initializeStorage() {
		m_header = createNode();
		m_tailer = createNode();
		m_header->next = m_tailer;
		m_tailer->previous = m_header;
		setNodeCount(0);
	}

	/**
	 * Inserts \em newNode after \em pos.
	 * Hooks the new node up in the middle of the previous and the next node.
	 */
	void
	insertNode(NodePtr pos, NodePtr newNode) {
		newNode->previous = pos;
		newNode->next = pos->next;
		pos->next = newNode;
		newNode->next->previous = newNode;
	}

	/**
	 *
	 */
	const int
	nodeCount() const
	{ return m_nodeCount; }

	/**
	 *
	 */
	template <class InputIterator>
	void
	rangeAppend(InputIterator first, InputIterator last) {
		rangeInsert(m_tailer->previous, first, last);
		increaseNodeCount(last-first);
	}

	/**
	 * Erases all nodes in the range [first,last] but not including last.
	 * Returns the node that follows the last erased node (could be m_tailer).
	 */
	NodePtr
	rangeErase(NodePtr first, NodePtr last) {
		NodePtr nodeToErase = first;
		int numErasedNodes = 0;

		while (nodeToErase != last) {
			NodePtr nextNode = nodeToErase->next;
			NodePtr previousNode = nodeToErase->previous;

			previousNode->next = nextNode;
			nextNode->previous = previousNode;

			m_storage.deallocateNode(nodeToErase);
			nodeToErase = nextNode;
			numErasedNodes++;
		}

		decreaseNodeCount(numErasedNodes);
		return last;
	}

	/**
	 * Inserts the elements from the range [first,last] in this List
	 * starting at the position after \em pos.
	 */
	template <class ForwardIterator>
	void
	rangeInsert(NodePtr pos, ForwardIterator first, ForwardIterator last) {
		NodePtr currentNode = pos;

		while (first != last) {
			NodePtr newNode = createNode(*first);
			insertNode(currentNode, newNode);
			++first;
			currentNode = newNode;
		}
	}

	/**
	 *
	 */
	void
	setNodeCount(const int size)
	{ m_nodeCount = size; }
};

//============================================================
// List
//============================================================
template <class T, class TAllocator = prism::Allocator<T>>
class List {
private:
	typedef typename TAllocator::template rebind<ListNode<T>>::other 	NodeAllocator;
	typedef ListData<T, NodeAllocator>									Data;
public:
	typedef typename ListIterator<T,false>::iterator					iterator;
	typedef typename ListIterator<T,true>::const_iterator				const_iterator;
	typedef typename TAllocator::value_type								value_type;
	typedef typename TAllocator::pointer								pointer;
	typedef typename TAllocator::reference								reference;
	typedef typename const_iterator::pointer							const_pointer;
	typedef typename const_iterator::reference							const_reference;
	typedef typename TAllocator::size_type								size_type;
	typedef typename TAllocator::difference_type						difference_type;


private:
	SharedDataPointer<Data> d;
public:
	/**
	 *
	 */
	List()
	: d(new Data)
	{}

	/**
	 *
	 */
	List(const int numElements, const T& value=T())
	: d(new Data(numElements, value))
	{}

	/**
	 *
	 */
	template <class InputIterator>
	List(InputIterator first, InputIterator last)
	: d(new Data(first, last))
	{}

	/**
	 *
	 */
	List(const std::initializer_list<T>& il)
	: d(new Data(il))
	{}

	/**
	 *
	 */
	List(const List& copy)
	: d(copy.d)
	{}

	/**
	 *
	 */
	~List()
	{}

	/**
	 *
	 */
	void
	append(const T& value)
	{ d->appendValue(value); }

	/**
	 *
	 */
	void
	append(const List& list)
	{ d->rangeAppend(list.begin(), list.end()); }

	/**
	 *
	 */
	T&
	back()
	{ return *(--end()); }

	/**
	 *
	 */
	const T&
	back() const
	{ return *(--end()); }

	/**
	 *
	 */
	iterator
	begin()
	{ return d->begin(); }

	/**
	 *
	 */
	iterator
	begin() const
	{ return d->begin(); }

	/**
	 *
	 */
	const_iterator
	cbegin() const
	{ return d->begin(); }

	/**
	 *
	 */
	iterator
	cend() const
	{ return d->end(); }

	/**
	 *
	 */
	void
	clear()
	{ d->clear(); }

	/**
	 *
	 */
	const_iterator
	constBegin() const
	{ return d->begin(); }

	/**
	 *
	 */
	iterator
	constEnd() const
	{ return d->end(); }

	/**
	 *
	 */
	const bool
	contains(const T& value) const
	{ return prism::count(this->begin(), this->end(), value); }

	/**
	 *
	 */
	const int
	count(const T& value) const
	{ return prism::count(this->begin(), this->end(), value); }

	/**
	 *
	 */
	const bool
	empty()
	{ return d->size() == 0; }

	/**
	 *
	 */
	iterator
	end()
	{ return d->end(); }

	/**
	 *
	 */
	iterator
	end() const
	{ return d->end(); }

	/**
	 *
	 */
	const bool
	endsWith(const T& value) const
	{ return back() == value; }

	/**
	 *
	 */
	iterator
	erase(iterator pos)
	{ return d->rangeErase(pos.np, pos.np->next); }

	/**
	 *
	 */
	iterator
	erase(iterator first, iterator last)
	{ return d->rangeErase(first.np, last.np); }

	/**
	 *
	 */
	T&
	first()
	{ return *begin(); }

	/**
	 *
	 */
	const T&
	first() const
	{ return *begin(); }

	/**
	 *
	 */
	T&
	front()
	{ return *begin(); }

	/**
	 *
	 */
	const T&
	front() const
	{ return *begin(); }

	/**
	 *
	 */
	T&
	last()
	{ return *(--end()); }

	/**
	 *
	 */
	const T&
	last() const
	{ return *(--end()); }

	/**
	 *
	 */
	const int
	size() const
	{ return d->nodeCount(); }

	/**
	 *
	 */
	const bool
	startsWith(const T& value)
	{ return first() == value; }

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const T& value) {
		d->appendValue(value);
		return *this;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const List<T,TAllocator>& other) {
		d->rangeAppend(other.begin(), other.end());
		return *this;
	}

	/**
	 *
	 */
	friend std::ostream& operator<<(std::ostream& out, const List<T, TAllocator>& list) {
		out << "List [" << &list << "] size=" << list.size() << "\n";
		out << "--- header node: " << list.d->m_header << "\n";
		out << "--- tailer node: " << list.d->m_tailer << "\n";

		int i = 0;
		for (List<T, TAllocator>::const_iterator it = list.cbegin(); it != list.cend(); it++)
			out << "--- [" << i++ << "] " << *it << endl;

		return out;
	}
};

} // end namespace tmp
} // end namespace prism



#endif /* PRISM_TMP_LIST_H_ */
