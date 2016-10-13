/*
 * BinarySearchTree.h
 * v1
 *
 *  Created on: Oct 9, 2016
 *      Author: iainhemstock
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <prism/h/functor.h>
#include <prism/h/Allocator.h>
#include <prism/h/pair.h>
#include <prism/h/utility.h>
#include <prism/h/iterator.h>
#include <prism/h/AbstractTree.h>
#include <ostream>
#include <cstddef> // for std::ptrdiff_t

namespace prism {

/**
 *
 */
template <class NodePointer>
void
printTree(NodePointer p, int indent=0) {
    if(p != nullptr) {
        if(p->right)
        	printTree(p->right, indent+4);

        if (indent)
            std::cout << std::setw(indent) << ' ';

        if (p->right)
        	std::cout<<" /\n" << std::setw(indent) << ' ';

		std::cout<< p->value.first << "\n ";

        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            printTree(p->left, indent+4);
        }
    }
}


//====================================================================================
// BinarySearchTreeNode
//====================================================================================
template <class Key, class Value>
struct BSTNode {
	typedef BSTNode*		node_pointer;
	prism::pair<Key,Value>	value;
	node_pointer			parent;
	node_pointer 			left;
	node_pointer 			right;

	BSTNode()
	: value(),
	  parent(nullptr),
	  left(nullptr),
	  right(nullptr)
	{}

	BSTNode(const Key& key, const Value& value)
	: value(prism::pair<Key,Value>(key,value)),
	  parent(nullptr),
	  left(nullptr),
	  right(nullptr)
	{}
};
//====================================================================================
// BinarySearchTreeMemory
//====================================================================================
template <	class Key,
			class Value,
			class NodeAllocator>
struct BSTMemory {
	typedef BSTNode<Key,Value> 	Node;
	typedef Node* 				node_pointer;

	NodeAllocator				alloc;

	node_pointer
	allocateNode()
	{ return alloc.allocate(1); }

	void
	deallocateNode(node_pointer node)
	{ alloc.deallocate(node); }
};
//====================================================================================
// BinarySearchTreeData
//====================================================================================
template <	class Key,
			class Value,
			class Compare, // defaults to prism::less<Key>
			class NodeAllocator>
struct BSTData {
private:
	typedef BSTMemory<Key,Value,NodeAllocator>				Memory;
	typedef BSTNode<Key,Value> 								Node;
	typedef Node* 											node_pointer;
public:
	typedef AssociativeIterator<Key,Value,Node,false>		iterator;
	typedef AssociativeIterator<Key,Value,Node,true>		const_iterator;
public:
	node_pointer 	m_root;
	int 			m_nodecount;
	Memory			m_storage;
	Compare			m_keyCompare;
public:
	/**
	 *
	 */
	BSTData()
	: m_root(nullptr),
	  m_nodecount(0)
	{}

	/**
	 *
	 */
	~BSTData() {
		if (m_root != nullptr)
			delete m_root;
	}

	/**
	 *
	 */
	iterator
	begin() const
	{ return minimumNodeInSubTree(m_root); }

	/**
	 *
	 */
	void
	clear() {
		node_pointer node = m_root;
		while (node != nullptr) {
			erase(node);
			node = m_root;
		}
	}

	/**
	 *
	 */
	template <typename ...Args>
	node_pointer
	createNode(Args&&... args) {
		node_pointer newNode = m_storage.allocateNode();
		m_storage.alloc.construct(newNode, std::forward<Args>(args)...);
		return newNode;
	}

	/**
	 *
	 */
	void
	destroyNode(node_pointer node) {
		m_storage.alloc.destroy(node);
		m_storage.deallocateNode(node);
	}

	/**
	 *
	 */
	void
	decrementNodeCount()
	{ --m_nodecount; }

	/**
	 *
	 */
	iterator
	end() const
	{ return m_root->parent; }

	/**
	 *
	 */
	void
	erase(const Key& key) {
		node_pointer node = findNode(key);
		erase(node);
	}

	/**
	 *
	 */
	void
	erase(node_pointer node) {
		if (node->left == nullptr) {

		}
		else if (node->right == nullptr) {

		}


		destroyNode(node);
		decrementNodeCount();

//		node_pointer y = nullptr;
//
//		if (z->left == nullptr)
//			transplant(z,z->right);
//		else if (z->right == nullptr)
//			transplant(z,z->left);
//		else {
//			y = minimumNodeInSubTree(z->right);
//			if (y->parent != z) {
//				transplant(y,y->right);
//				y->right = z->right;
//				y->right->parent = y;
//			}
//			else {
//				transplant(z,y);
//				y->left = z->left;
//				y->left->parent = y;
//			}
//		}
//		destroyNode(z);
//		decrementNodeCount();
	}

	/**
	 *
	 */
//	void
//	erase(node_pointer node) {
//		if (node != nullptr) {
//			// if the node has 0 children
//			if (node->left == nullptr && node->right == nullptr) {
//				if (node->parent->left == node)
//					node->parent->left = nullptr;
//				else
//					node->parent->right = nullptr;
//			}
//			// if the node only has a right child
//			else if (node->left != nullptr && node->right == nullptr) {
//				node_pointer rightChild = node->right;
//
//				if (node->parent->left == node)
//					node->parent->left = rightChild;
//				else
//					node->parent->right = rightChild;
//			}
//			// if the node only has a left child
//			else if (node->right != nullptr && node->left == nullptr) {
//				node_pointer leftChild = node->left;
//
//				if (node->parent->left == node)
//					node->parent->left = leftChild;
//				else
//					node->parent->right = leftChild;
//			}
//			// two children
//			else {
//				node_pointer tmp = minimumNodeInSubTree(node->right);
//				node->value = tmp->value;
//				if (tmp->parent->left == tmp)
//					tmp->parent->left = nullptr;
//				else
//					tmp->parent->right = nullptr;
//				node = tmp;
//			}
//		}
//		destroyNode(node);
//		decrementNodeCount();
//	}

	/**
	 * Returns an iterator to the node containing \em key or an iterator
	 * pointing to \em end() if a matching key is not found.
	 */
	iterator
	find(const Key& key)
	{ return findNode(key); }

	/**
	 *
	 */
	node_pointer
	findNode(const Key& key) {
		node_pointer currentNode = m_root;

		while (currentNode != nullptr && currentNode->value.first != key) {
			if (m_keyCompare(key, currentNode->value.first))
				currentNode = currentNode->left;
			else
				currentNode = currentNode->right;
		}
		return currentNode;
	}

	/**
	 *
	 */
	void
	incrementNodeCount()
	{ ++m_nodecount; }

	/**
	 *
	 */
	iterator
	insert(const Key& key, const Value& value) {
		node_pointer newNode = createNode(key,value);
		node_pointer currentNode = m_root;
		node_pointer parentNode = nullptr;

		while (currentNode != nullptr) {
			parentNode = currentNode;
			if (m_keyCompare(key, currentNode->value.first))
				currentNode = currentNode->left;
			else
				currentNode = currentNode->right;
		}

		newNode->parent = parentNode;

		if (parentNode == nullptr)
			m_root = newNode;
		else if (m_keyCompare(key, parentNode->value.first))
			parentNode->left = newNode;
		else parentNode->right = newNode;

		incrementNodeCount();

		return iterator(newNode);
	}

	/**
	 *
	 */
	int
	nodeCount() const
	{ return m_nodecount; }

	/**
	 *
	 */
	void
	transplant(node_pointer u, node_pointer v) {
		if (u->parent == nullptr)
			m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != nullptr)
			v->parent = u->parent;
	}
};

//====================================================================================
// Binary Search Tree
//====================================================================================
template <	class Key,
			class Value,
			class Compare = prism::less<Key>,
			class Allocator = prism::Allocator<prism::pair<Key,Value>>>
class BinarySearchTree
		: protected AbstractTree<	Key,
		  	  	  	  	  	  	  	Value,
		  	  	  	  	  	  	  	AssociativeIterator<	Key,
		  	  	  	  	  	  	  							Value,
		  	  	  	  	  	  	  							BSTNode<Key,Value>,
		  	  	  	  	  	  	  							false>,
		  	  	  	  	  	  	  	Compare,
		  	  	  	  	  	  	  	Allocator> {
private:
	typedef typename Allocator::template
			rebind<BSTNode<Key,Value>>::other 			NodeAllocator;
	typedef BSTData<Key,Value,Compare,NodeAllocator>	Data;
	typedef BSTNode<Key,Value>							Node;
	typedef Key&										key_reference;
	typedef const Key&									const_key_reference;
public:
	typedef AssociativeIterator<Key,Value,Node,false>	iterator;
	typedef AssociativeIterator<Key,Value,Node,true>	const_iterator;
	typedef Value*										pointer;
	typedef const Value*								const_pointer;
	typedef Value&										reference;
	typedef const Value&								const_reference;
	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;
public:
	Data * d;
public:

	/**
	 *
	 */
	BinarySearchTree()
	: d(new Data)
	{}

	/**
	 *
	 */
	~BinarySearchTree()
	{ if (d != nullptr) delete d; }

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
	void
	clear()
	{ d->clear(); }

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
	void
	erase(const_key_reference key)
	{ d->erase(key); }

	/**
	 *
	 */
	const bool
	empty() const
	{ return d->nodeCount() == 0; }

	/**
	 *
	 */
	iterator
	find(const_key_reference key) const
	{ return d->find(key); }

	/**
	 *
	 */
	iterator
	insert(const_key_reference key, const_reference value)
	{ return d->insert(key,value); }

	/**
	 *
	 */
	iterator
	insertUnique(const_key_reference key, const_reference value) {

	}

	/**
	 *
	 */
	Compare
	keyCompare() const {
		return d->m_keyCompare;
	}

	/**
	 *
	 */
	iterator
	lowerBound(const_key_reference key) const {

	}

	/**
	 *
	 */
	const int
	size() const
	{ return d->nodeCount(); }

	/**
	 *
	 */
	iterator
	upperBound(const_key_reference key) const {

	}

	/**
	 *
	 */
	reference
	operator[](const_key_reference key) {
		iterator it = d->find(key);
		if (it == end())
			it = d->insert(key, Value());
		return it->second;
	}

	/**
	 *
	 */
	friend
	std::ostream&
	operator<<(std::ostream& out, const BinarySearchTree<Key,Value,Compare,Allocator>& t) {
		out << "BinarySearchTree [" << &t << "] ";
		out << "size: " << t.size() << "\n";
		out << "---------------------------------------------\n";
		printTree(t.d->m_root);
		return out;
	}
};

} // end namespace prism



#endif /* BINARYSEARCHTREE_H_ */
