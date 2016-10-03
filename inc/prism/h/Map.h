/*
 * Map.h
 * v1
 *
 *  Created on: Oct 2, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_MAP_H_
#define PRISM_MAP_H_
#include <prism/h/functor.h>
#include <prism/h/Allocator.h>
#include <prism/h/pair.h>
#include <prism/h/utility.h>
#include <ostream>
using namespace std;

namespace prism {

/**
 * Returns the node with the lowest value key.
 */
template <class node_pointer>
node_pointer
tree_minimum(node_pointer node) {
	while (node->left != nullptr)
		node = node->left;
	return node;
}

/**
 * Returns the node with the highest value key.
 */
template <class node_pointer>
node_pointer
tree_maximum(node_pointer node) {
	while (node->right != nullptr)
		node = node->right;
	return node;
}

//====================================================================================
// BinarySearchTreeNode
//====================================================================================
template <class Pair> // prism::pair<const Key,T>
struct BSTNode {
	typedef BSTNode*	node_pointer;
	Pair				value;
	node_pointer		parent;
	node_pointer 		left;
	node_pointer 		right;

	BSTNode(const Pair& pair)
	: value(pair),
	  parent(nullptr),
	  left(nullptr),
	  right(nullptr)
	{}
};
//====================================================================================
// BinarySearchTreeIterator
//====================================================================================
template <	class Pair, // prism::pair<const Key,T>
			bool isConst>
struct BSTIterator {
	typedef BSTIterator<Pair, false>				iterator;
	typedef BSTIterator<Pair, true>					const_iterator;
	typedef BSTNode<Pair>*							node_pointer;

	typedef Pair									value_type;
	typedef const value_type						const_reference;
	typedef const value_type*						const_pointer;
	typedef size_t									size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef prism::bidirectional_iterator_tag		iterator_category;
	typedef typename prism::conditional_type<	isConst,
												const value_type*,
												value_type*>
												::type 				pointer;
	typedef typename prism::conditional_type<	isConst,
												const value_type&,
												value_type&>
												::type 				reference;
	typedef typename prism::conditional_type<	isConst,
												const_iterator,
												iterator>
												::type 				Self;

	node_pointer np;

	BSTIterator()
	: np(nullptr)
	{}

	BSTIterator(node_pointer node)
	: np(node)
	{}

	BSTIterator(const iterator& copy)
	: np(copy.np)
	{}

	~BSTIterator()
	{}

	reference
	operator*() const
	{ return np->value; }

	pointer
	operator->() const
	{ return &np->value; }

	// adapted from Introduction to Algorithms (1990, page 292)
	Self&
	operator++() {
		if (np->right != nullptr) {
			np = tree_minimum(np->right);
		}
		else {
			node_pointer parent = np->parent;
			while (parent != nullptr && np == parent->right) {
				np = parent;
				parent = parent->parent;
			}
			np = parent;
		}
		return *this;
	}

	Self
	operator++(int junk) {
		Self tmp(*this);
		this->operator++();
		return tmp;
	}

	// adapted from Introduction to Algorithms (1990, page 292)
	Self&
	operator--() {
		if (np->left != nullptr) {
			np = tree_maximum(np->left);
		}
		else {
			node_pointer parent = np->parent;
			while (parent != nullptr && np == parent->left) {
				np = parent;
				parent = parent->parent;
			}
			np = parent;
		}
		return *this;
	}

	Self
	operator--(int junk) {
		Self tmp(*this);
		this->operator--();
		return tmp;
	}

	Self&
	operator=(const iterator& rhs) {
		if (*this != rhs)
			np = rhs.np;
		return *this;
	}

	const bool
	operator==(const Self& other)
	{ return this->np == other.np; }

	const bool
	operator!=(const Self& other)
	{ return !(*this == other); }
};
//====================================================================================
// Binary Search Tree
//====================================================================================
template <	class Key,
			class Pair, // prism::pair<const Key, T>
			class Compare,
			class Allocator = prism::Allocator<Pair>>
class BinarySearchTree {

};
//====================================================================================
// Map
//====================================================================================
template <	class Key,
			class T,
			class Compare 	= prism::less<Key>,
			class Allocator = prism::Allocator<prism::pair<Key,T>>>
class Map {
public:
	typedef Key 						key_type;
	typedef T 							mapped_type;
	typedef prism::pair<Key,T>			value_type;
	typedef Compare						key_compare;
private:
	typedef BinarySearchTree<Key, value_type, Compare, Allocator> BST;
	BST tree;


};

} // end namespace prism



#endif /* PRISM_MAP_H_ */
