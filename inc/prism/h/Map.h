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
#include <prism/h/BinarySearchTree.h>
using namespace std;

namespace prism {

//====================================================================================
// Map
//====================================================================================
template <	class Key,
			class T,
			class Compare 	= prism::less<Key>,
			class Allocator = prism::Allocator<prism::pair<Key,T>>,
			class Tree 		= prism::BinarySearchTree<Key,T,Compare,Allocator>>
class Map {
public:
	typedef Key 						key_type;
	typedef T 							mapped_type;
	typedef prism::pair<Key,T>			value_type;
	typedef Compare						key_compare;
private:
	Tree tree;


};

} // end namespace prism



#endif /* PRISM_MAP_H_ */
