/*
 * AbstractTree.h
 * v1
 *
 *  Created on: Oct 9, 2016
 *      Author: iainhemstock
 */

#ifndef ABSTRACTTREE_H_
#define ABSTRACTTREE_H_

namespace prism {

//====================================================================================
// AbstractTree
//====================================================================================
template <	class Key,
			class Value,
			class AssociativeIterator,
			class Compare = prism::less<Key>,
			class Allocator = prism::Allocator<std::pair<Key,Value>>>
class AbstractTree {
public:
	typedef Key 					KeyType;
	typedef Value 					ValueType;
	typedef Compare					KeyCompareType;
	typedef AssociativeIterator 	iterator;
	typedef Allocator 				AllocType;

	virtual ~AbstractTree()
	{}

	virtual iterator 		begin() = 0;
	virtual iterator 		begin() const = 0;
	virtual void 			clear() = 0;
	virtual iterator 		end() = 0;
	virtual iterator 		end() const = 0;
	virtual void 			erase(const Key& key) = 0;
	virtual const bool 		empty() const = 0;
	virtual iterator 		find(const Key& key) const = 0;
	virtual iterator 		insert(const Key& key, const Value& value) = 0;
	virtual iterator 		insertUnique(const Key& key, const Value& value) = 0;
	virtual KeyCompareType 	keyCompare() const = 0;
	virtual iterator 		lowerBound(const Key& key) const = 0;
	virtual const int 		size() const = 0;
	virtual iterator 		upperBound(const Key& key) const = 0;
	virtual ValueType& 		operator[](const Key& key) = 0;
};

}  // end namespace prism



#endif /* ABSTRACTTREE_H_ */
