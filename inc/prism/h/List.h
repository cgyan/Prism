/*
 * List.h
 * v2
 *
 *  Created on: Sep 19, 2016
 *      Author: iainhemstock
 */

/**
 * todo
 *
 * functions to add:
 * -- move constructor and move assignment operator
 * -- TAllocator allocator();
 * -- prism::sort() needs a specialization for List
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
#include <list>
using namespace std;

namespace prism {

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
		out << "ListNode [" << &node << "]";
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
	typedef typename NodeAllocator::pointer 	NodePtr;
	NodeAllocator 								m_nodeAllocator;

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
	deallocateNodes(NodePtr first, NodePtr last) {
		NodePtr currentNode = first;

		while (currentNode != last) {
			NodePtr thisNode = currentNode;
			NodePtr nextNode = thisNode->next;
			deallocateNode(thisNode);
			currentNode = nextNode;
		}
	}
};
/**
 *
 */

//============================================================
// ListData
//============================================================
//template <class T, class Node, class NodeAllocator>
template <class T, class NodeAllocator>
struct ListData : public SharedData {
	typedef typename NodeAllocator::template rebind<T>::other 			TAllocator;
	typedef ListMemory<NodeAllocator> 									Memory;
	typedef typename Memory::NodePtr									NodePtr;
	typedef ListIterator<T,false>										iterator;
	typedef ListIterator<T,true>										const_iterator;

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
		rangeInsert(m_header->next, first, last);
	}

	/**
	 *
	 */
	ListData(const ListData& copy)
	: m_header(0),
	  m_tailer(0),
	  m_nodeCount(0)
	{
		initializeStorage();
		rangeInsert(this->endNode(), const_iterator(copy.beginNode()),
										const_iterator(copy.endNode()));
	}

	/**
	 *
	 */
	~ListData() {
		m_storage.m_nodeAllocator.destroy(m_header);
		m_storage.m_nodeAllocator.destroy(m_tailer);

		m_storage.deallocateNodes(m_header, m_tailer);
		m_storage.deallocateNode(m_tailer);
	}

	/**
	 * The first valid node containing an element.
	 */
	NodePtr
	beginNode() const
	{ return m_header->next; }

	/**
	 *
	 */
	void
	clear_aux()
	{ rangeErase(beginNode(), endNode()); }

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
	 * Decreases the node count by \em amount.
	 */
	void
	decreaseNodeCount(const int amount)
	{ m_nodeCount -= amount; }

	/**
	 *
	 */
	const int
	distanceBetweenNodes(NodePtr first, NodePtr last) {
		int count = 0;
		while (first != last) {
			++count;
			first = first->next;
		}
		return count;
	}

	/**
	 *
	 */
	NodePtr
	endNode() const
	{ return m_tailer; }

	/**
	 *
	 */
	iterator
	eraseNode(const_iterator node) {
		NodePtr previousNode = node.np->previous;
		NodePtr nextNode = node.np->next;

		linkNodes(previousNode, nextNode);

		m_storage.deallocateNode(node.np);
//		NodeAllocTraits::deallocate(m_storage.m_nodeAllocator, node.np);
		decreaseNodeCount(1);

		return iterator(nextNode);
	}

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
		NodePtr newNode = nullptr;

		for (int i=0; i<numElements; i++) {
			newNode = createNode(value);
			insertNode(currentNode, newNode);
			currentNode = newNode;
		}
		increaseNodeCount(numElements);
	}

	/**
	 * Creates the header and tailer nodes and links them together.
	 */
	void
	initializeStorage() {
		m_header = createNode();
		m_tailer = createNode();
		linkNodes(m_header, m_tailer);
		setNodeCount(0);
	}

	/**
	 * Inserts new node before pos.
	 * Returns the last node inserted.
	 */
	iterator
	insert_aux(const_iterator pos, const int count, const T& value) {
		NodePtr newNode = nullptr;
		for (int i=0; i<count; i++) {
			newNode = createNode(value);
			insertNode(pos.np->previous, newNode);
		}
		return iterator(newNode);
	}

	/**
	 *
	 */
	void
	insertAtBack(const T& value) {
		NodePtr newNode = createNode(value);
		insertNode(m_tailer->previous, newNode);
	}

	/**
	 *
	 */
	void
	insertAtFront(const T& value) {
		NodePtr newNode = createNode(value);
		insertNode(m_header, newNode);
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
		increaseNodeCount(1);
	}

	/**
	 *
	 */
	void
	linkNodes(NodePtr node1, NodePtr node2) {
		node1->next = node2;
		node2->previous = node1;
	}

	/**
	 * All nodes except the header and tailer nodes.
	 */
	const int
	nodeCount() const
	{ return m_nodeCount; }

	/**
	 * ForwardIterator could be an iterator of a type other than a ListIterator
	 * i.e. Vector iterator, std::initializer_list etc
	 * Appends the values in the range [first, last] to the end of the list.
	 */
	template <class ForwardIterator>
	void
	rangeAppend(ForwardIterator first, ForwardIterator last)
	{ rangeInsert(m_tailer, first, last); }

	/**
	 * Erases all nodes in the range [first,last] but not including last.
	 * Returns the node that follows the last erased node (could be m_tailer).
	 */
	iterator
	rangeErase(const_iterator first, const_iterator last) {
		const int distance = distanceBetweenNodes(first.np, last.np);
		decreaseNodeCount(distance);
		linkNodes(first.np->previous, last.np);
		m_storage.deallocateNodes(first.np, last.np);

		return iterator(last.np);
	}

	/**
	 * ForwardIterator could be an iterator of a type other than a ListIterator
	 * i.e. Vector iterator, std::initializer_list etc
	 * Inserts the elements from the range [first,last] in this List
	 * starting at the position before \em pos.
	 * Returns a pointer to the first of inserted nodes.
	 */
	template <class ForwardIterator>
	iterator
	rangeInsert(const_iterator pos, ForwardIterator first, ForwardIterator last) {
		NodePtr nodeBeforeInsert = pos.np->previous;
		NodePtr currentNode = pos.np;
		NodePtr newNode = nullptr;

		while (first != last) {
			newNode = createNode(*first);
			insertNode(currentNode->previous, newNode);
			++first;
		}

		return iterator(nodeBeforeInsert->next);
	}

	/**
	 *
	 */
	void
	resize_aux(const int newSize, const T& value) {
		int size = nodeCount();

		if (newSize == size)
			return;

		else if (newSize < size) {
			NodePtr currentNode = beginNode();
			int counter = 0;

			while (counter < newSize) {
				currentNode = currentNode->next;
				++counter;
			}

			rangeErase(currentNode, m_tailer);
		}
		else { // newSize > size
			int numNewNodes = newSize - size;
			insert_aux(m_tailer, numNewNodes, value);
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
	List(const int numElements, const_reference value=T())
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
	: d(new Data(il.begin(), il.end()))
	{}

	/**
	 *
	 */
	List(const List<T,TAllocator>& copy)
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
	append(const_reference value) {
		d.detach();
		d->insertAtBack(value);
	}

	/**
	 *
	 */
	reference
	back() {
		d.detach();
		return *(--end());
	}

	/**
	 *
	 */
	const_reference
	back() const
	{ return *(--end()); }

	/**
	 *
	 */
	iterator
	begin() {
		d.detach();
		return d->beginNode();
	}

	/**
	 *
	 */
	iterator
	begin() const
	{ return d->beginNode(); }

	/**
	 *
	 */
	const_iterator
	cbegin() const
	{ return begin(); }

	/**
	 *
	 */
	iterator
	cend() const
	{ return end(); }

	/**
	 *
	 */
	void
	clear() {
		d.detach();
		d->clear_aux();
	}

	/**
	 *
	 */
	const_iterator
	constBegin() const
	{ return begin(); }

	/**
	 *
	 */
	iterator
	constEnd() const
	{ return end(); }

	/**
	 *
	 */
	const bool
	contains(const_reference value) const
	{ return prism::count(this->begin(), this->end(), value); }

	/**
	 *
	 */
	const int
	count(const_reference value) const
	{ return prism::count(this->begin(), this->end(), value); }

	/**
	 *
	 */
	const bool
	empty()
	{ return d->nodeCount() == 0; }

	/**
	 *
	 */
	iterator
	end() {
		d.detach();
		return d->endNode();
	}

	/**
	 *
	 */
	iterator
	end() const
	{ return d->endNode(); }

	/**
	 *
	 */
	const bool
	endsWith(const_reference value) const
	{ return back() == value; }

	/**
     * This function only erases the element, and that if the element
     * is itself a pointer, the pointed-to memory is not touched in
     * any way.  Managing the pointer is the user's responsibility.
	 */
	iterator
	erase(const_iterator pos) {
		d.detach();
		return d->eraseNode(pos);
	}

	/**
     * This function only erases the element, and that if the element
     * is itself a pointer, the pointed-to memory is not touched in
     * any way.  Managing the pointer is the user's responsibility.
	 */
	iterator
	erase(const_iterator first, const_iterator last) {
		d.detach();
		return d->rangeErase(first.np, last.np);
	}

	/**
	 *
	 */
	reference
	first() {
		d.detach();
		return *begin();
	}

	/**
	 *
	 */
	const_reference
	first() const
	{ return *begin(); }

	/**
	 *
	 */
	reference
	front() {
		d.detach();
		return *begin();
	}

	/**
	 *
	 */
	const_reference
	front() const
	{ return *begin(); }

	/**
	 * Inserts \em value after the value pointed to be \em pos.
	 * @return Returns an iterator that points to the newly inserted value.
	 */
	iterator
	insert(const_iterator insertBefore, const_reference value) {
		d.detach();
		return d->insert_aux(insertBefore, 1, value);
	}

	/**
	 *
	 */
	iterator
	insert(const_iterator insertBefore, const int count, const_reference value) {
		d.detach();
		return d->insert_aux(insertBefore, count, value);
	}

	/**
	 *
	 */
	template <class InputIterator>
	iterator
	insert(const_iterator insertBefore, InputIterator first, InputIterator last) {
		d.detach();
		return d->rangeInsert(insertBefore, first, last);
	}

	/**
	 *
	 */
	iterator
	insert(const_iterator insertBefore, std::initializer_list<T>& il) {
		d.detach();
		return d->rangeInsert(insertBefore, il.begin(), il.end());
	}

	/**
	 *
	 */
	const bool
	isEmpty() const
	{ return d->nodeCount() == 0; }

	/**
	 *
	 */
	reference
	last() {
		d.detach();
		return *(--end());
	}

	/**
	 *
	 */
	const_reference
	last() const
	{ return *(--end()); }

	/**
	 *
	 */
	void
	pop_back() {
		d.detach();
		d->eraseNode(--end());
	}

	/**
	 *
	 */
	void
	pop_front() {
		d.detach();
		d->eraseNode(begin());
	}

	/**
	 *
	 */
	void
	prepend(const_reference value) {
		d.detach();
		d->insertAtFront(value);
	}

	/**
	 *
	 */
	void
	push_back(const_reference value) {
		d.detach();
		d->insertAtBack(value);
	}

	/**
	 *
	 */
	void
	push_front(const_reference value)
	{ d->insertAtFront(value); }



	/**
	 * The remove... family of functions remove the elements based on value whereas
	 * the erase... family of functions remove the elements based on iterators.
	 */
	void
	removeAll(const_reference value) {
		d.detach();
		const_iterator bit = cbegin();
		while (bit != cend()) {
			if (*bit == value) {
				d->eraseNode(bit);
			}
			++bit;
		}
	}

	/**
	 *
	 */
	void
	removeFirst() {
		d.detach();
		erase(begin());
	}

	/**
	 *
	 */
	template <class Predicate>
	void
	removeIf(Predicate pred) {
		d.detach();
		const_iterator bit = cbegin();
		while (bit != cend()) {
			if (pred(*bit)) {
				d->eraseNode(bit);
			}
			++bit;
		}
	}

	/**
	 *
	 */
	void
	removeLast() {
		d.detach();
		erase(--end());
	}

	/**
	 *
	 */
	void
	resize(const int newSize, const_reference value=value_type())
	{ d->resize_aux(newSize, value); }

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
	startsWith(const_reference value)
	{ return first() == value; }

	/**
	 *
	 */
	value_type
	takeFirst() {
		d.detach();
		T ret = first();
		d->eraseNode(begin());
		return ret;
	}

	/**
	 *
	 */
	value_type
	takeLast() {
		d.detach();
		T ret = last();
		d->eraseNode(--end());
		return ret;
	}

	/**
	 *
	 */
	std::list<T>
	toStdList() const {
		std::list<T> list;
		const_iterator bit = cbegin();
		while (bit != cend()) {
			list.push_back(*bit);
			++bit;
		}
		return list;
	}

	/**
	 *
	 */
	const bool
	operator==(const List<T,TAllocator>& rhs) {
		if (this->size() != rhs.size())
			return false;

		return prism::equal(this->begin(), this->end(), rhs.begin());
	}

	/**
	 *
	 */
	const bool
	operator!=(const List<T,TAllocator>& rhs)
	{ return !(*this == rhs); }

	/**
	 *
	 */
	List<T,TAllocator>
	operator+(const List<T,TAllocator>& rhs) {
		d.detach();
		List<T,TAllocator> list(*this);
		list << rhs;
		return list;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator+=(const List<T,TAllocator>& rhs) {
		d.detach();
		return *this << rhs;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator+=(const_reference value) {
		d.detach();
		*this << value;
		return *this;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const_reference value) {
		d.detach();
		d->insertAtBack(value);
		return *this;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator<<(const List<T,TAllocator>& other) {
		d.detach();
		d->rangeAppend(other.begin(), other.end());
		return *this;
	}

	/**
	 *
	 */
	List<T,TAllocator>&
	operator=(const List<T,TAllocator>& rhs) {
		if (this->d != rhs.d)
			this->d = rhs.d;

		return *this;
	}

	/**
	 *
	 */
	friend std::ostream& operator<<(std::ostream& out, const List<T, TAllocator>& list) {
		out << "List [" << &list << "] size=" << list.size() << "\n";
		out << "--- ListData: " << list.d.data() << "\n";
		out << "--- header node: " << list.d->m_header << "\n";
		out << "--- tailer node: " << list.d->m_tailer << "\n";

		int i = 0;
		for (List<T, TAllocator>::const_iterator it = list.cbegin(); it != list.cend(); it++)
			out << "--- [" << i++ << "] " << *it << endl;

		return out;
	}
};

} // end namespace prism



#endif /* PRISM_TMP_LIST_H_ */
