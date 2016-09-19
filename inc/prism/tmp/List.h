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
#include <prism/utilities> // for prism::conditional_type
#include <ostream>
#include <cstddef> // for std::ptrdiff_t
using namespace std;

namespace prism {
namespace tmp {

//============================================================
// ListIterator
//============================================================
template <class T, class Node, bool isConst=true>
struct ListIterator {

	typedef T 								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef bidirectional_iterator_tag 		iterator_category;
	typedef ListIterator<T, Node, false> 	iterator;
	typedef ListIterator<T, Node, true> 	const_iterator;
	typedef typename prism::conditional_type<isConst, const T*, T*>::type pointer;
	typedef typename prism::conditional_type<isConst, const T&, T&>::type reference;
	typedef typename prism::conditional_type<isConst, const_iterator, iterator>::type Self;

	Node* np;

	ListIterator()
	: np(nullptr)
	{}

	ListIterator(Node* np)
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
		Node* tmp = np;
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
		Node* tmp = np;
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
// ListNode
//============================================================
template <class T>
struct ListNode {
	typedef ListNode<T> 	Node;
	T 						value;
	Node* 					next;
	Node* 					previous;

	ListNode()
	: value(T()),
	  next(0),
	  previous(0)
	{}

	ListNode(const T& value)
	: value(value),
	  next(nullptr),
	  previous(nullptr)
	{}
};

//============================================================
// ListMemory
//============================================================
template <class T, class Node, class NodeAllocator>
struct ListMemory {
	typedef typename NodeAllocator::pointer 			NodePtr;
	typedef typename NodeAllocator::reference			reference;
	typedef typename NodeAllocator::const_pointer		const_pointer;
	typedef typename NodeAllocator::const_reference		const_reference;
	typedef ListIterator<T, Node, false>				iterator;
	typedef ListIterator<T, Node, true>					const_iterator;

	NodeAllocator m_nodeAllocator;

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
	destroyNodes(iterator first, iterator last) {
		while (first != last) {
			deallocateNode(first.np);
			++first;
		}
	}
};

//============================================================
// ListData
//============================================================
template <class T, class Node, class NodeAllocator>
struct ListData : public SharedData {
	typedef ListMemory<T, Node, NodeAllocator> 			Memory;
	typedef typename NodeAllocator::pointer 			NodePtr;
	typedef typename NodeAllocator::reference			reference;
	typedef typename NodeAllocator::const_pointer		const_pointer;
	typedef typename NodeAllocator::const_reference		const_reference;
	typedef ListIterator<T, Node, false>				iterator;
	typedef ListIterator<T, Node, true>					const_iterator;

	Memory	m_storage;
	NodePtr m_header;
	NodePtr	m_tailer;
	int 	m_size;

	/**
	 *
	 */
	ListData()
	: m_header(0),
	  m_tailer(0),
	  m_size(0)
	{
		initializeStorage();
	}

	/**
	 *
	 */
	ListData(const ListData& copy)
	: m_header(0),
	  m_tailer(0),
	  m_size(copy.m_size)
	{
		initializeStorage();
		// copy data from copy to this
	}

	/**
	 *
	 */
	~ListData() {
		iterator begin(m_header);
		iterator end(m_tailer);
		++end;
		m_storage.destroyNodes(begin, end);
	}

	/**
	 *
	 */
	NodePtr
	createHeaderOrTailerNode() {
		NodePtr node = m_storage.allocateNode();
		m_storage.m_nodeAllocator.construct(node);
		return node;
	}

	/**
	 *
	 */
	NodePtr
	createNode(const T& value=T()) {
		NodePtr node = m_storage.allocateNode();
		m_storage.m_nodeAllocator.construct(node, value);
		return node;
	}

	/**
	 *
	 */
	void
	destroyElements(iterator first, iterator last) {
		while (first != last) {
			m_storage.m_nodeAllocator.destroy(&*first);
			++first;
		}
	}

	/**
	 *
	 */
	NodeAllocator
	getNodeAllocator() const
	{ return m_storage.m_nodeAllocator; }

	/**
	 *
	 */
	void
	initializeStorage() {
		m_header = createHeaderOrTailerNode();
		m_tailer = createHeaderOrTailerNode();
		m_header->next = m_tailer;
		m_tailer->previous = m_header;
	}

	/**
	 *
	 */
	const int
	size() const
	{ return m_size; }
};

//============================================================
// List
//============================================================
template <class T, class Alloc = prism::Allocator<T>>
class List {
public:
	typedef ListNode<T>										Node;
	typedef typename Alloc::template rebind<Node>::other 	NodeAllocator;
	typedef ListData<T, Node, NodeAllocator>				Data;
	typedef ListIterator<T, Node,false> 					iterator;
	typedef ListIterator<T, Node, true> 					const_iterator;
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
	const int
	size() const {
		return d->size();
	}

	/**
	 *
	 */
	friend std::ostream& operator<<(std::ostream& out, const List<T, Alloc>& list) {
		out << "List [" << &list << "] size=" << list.size() << "\n";
		out << "--- header node: " << list.d->m_header << "\n";
		out << "--- tailer node: " << list.d->m_tailer << "\n";


		return out;
	}
};

} // end namespace tmp
} // end namespace prism



#endif /* PRISM_TMP_LIST_H_ */
