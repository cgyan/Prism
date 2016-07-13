/*
 * Deque.h
 * v0.1
 *
 * DO NOT USE THIS FILE
 * IT IS INCOMPLETE AND DOESN'T WORK!
 *
 *  Created on: Jan 25, 2015
 *      Author: iainhemstock
 *
 *  - Complexity:
 *  	- O(1) for push_back, push_front, pop_back and pop_front
 *  	- O(1) for random access via operator[]
 *  	- no more than N/2 shifts for insertions/deletions on a N-sized deque
 *  - Block size set to 7 by default
 *  - firstIndex set to the middle of the default block namely index 3 (i.e. 7/2) so that the first element added goes into the middle of the first block
 *  - blocks is a vector that contains pointers to numerous vectors of seven elements each.
 *  - T has to have a public constructor i.e. T()
 *  - Insertions/deletions will require no more than N/2 shifts on a N-sized deque because shifts take place from the point of insertion/deletion
 *    all the way to nearest end of the deque - the front or the back whichever is closest.
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include <ostream>
#include "Vector.h"
#include "OutOfBoundsException.h"

// todo remove this
using namespace std;

namespace prism {
namespace containers {

/******************************************************************************
 * DequeData
 *****************************************************************************/
template <class T>
struct DequeData {
	Vector<Vector<T>*> 	blocks;
	const int 			blockSize;
	int 				firstBlock;
	int 				firstIndex; // will be the middle index of the first block initially by default
	int					size;
	DequeData() : blockSize(7), firstBlock(0), firstIndex(blockSize/2+1), size(0) {}
	~DequeData() { for(int i=0; i<blocks.size(); i++) delete blocks.at(i); }
};

/******************************************************************************
 * Deque
 *****************************************************************************/
template <class T>
class Deque {
private:
	DequeData<T> *d;
private:
	struct 		Storage { int block; int index;
				friend std::ostream& operator<<(ostream& out, const Storage& s) { out << "Storage: block:" << s.block << " index:" << s.index << endl; return out; }
	};
	void 		findBlockAndIndex(int index, Storage& pos) const;
public:
				Deque();
				~Deque();
	T& 			at(const int index);
	const T& 	at(const int index) const;
	void 		insert(const int index, const int count, const T& value);
	const int 	size() const;
	/**
	 *
	 */
	friend std::ostream& operator<<(std::ostream& out, const Deque<T>& deque) {
		out << "--------------------------------------------- \n";
		out << "Deque(" << &deque << ") size:" << deque.d->size << " blocks:" << deque.d->blocks.size() << " firstBlock:" << deque.d->firstBlock << " firstIndex:" << deque.d->firstIndex << " blockSize:" << deque.d->blockSize << "\n";
		for (int i=0; i<deque.d->blocks.size(); i++) {
			cout << "- Block " << i << " (" << &deque.d->blocks.at(i) << "): \n";
			for (int j=0; j<deque.d->blocks[i]->size(); j++) {
				out << "-- [" << j << "] " << deque.d->blocks[i]->at(j);
				out << endl;
			}
		}
		out << "--------------------------------------------- \n";
		return out;
	}
};

/**
 * Constructs an empty deque.
 */
template <class T>
Deque<T>::Deque() : d(new DequeData<T>) {

}

/**
 * Destroys this deque and all of its elements.
 */
template <class T>
Deque<T>::~Deque() {
	delete d;
}

/**
 * Returns the element stored at \em index.
 */
template <class T>
T& Deque<T>::at(const int index) {
//	cout << "at(" << index << ")" << endl;
	if (index < 0 || index >= d->size)
		throw prism::exceptions::OutOfBoundsException(index);

	Storage storage;
	findBlockAndIndex(index, storage);
	return (*d->blocks[storage.block])[storage.index];
}

/**
 * Returns the element stored at \em index.
 */
template <class T>
const T& Deque<T>::at(const int index) const {
	if (index < 0 || index >= d->size)
		throw prism::exceptions::OutOfBoundsException(index);

	Storage storage;
	findBlockAndIndex(index, storage);
	return (*d->blocks[storage.block])[storage.index];
}

/**
 * Given an index number this function finds the correct block/index and assigns them to \em pos.
 */
template <class T>
void Deque<T>::findBlockAndIndex(int index, Storage& storage) const {
	// if index is within the first block ...
	if (index < d->blockSize-d->firstIndex) {
		storage.block = d->firstBlock;
		storage.index = index + d->firstIndex;
	}
	// ... otherwise ...
	else {
		index -= d->blockSize-d->firstIndex;
		++storage.block;
		int k = index/d->blockSize;
		storage.block += k;
		storage.index = index - k*d->blockSize;
	}
}

/**
 * todo add support for potential failure of new operator
 * todo currently only adds one value rather than 'count' amount
 * Inserts \em count copies of \em value starting from \em index.
 */
template <class T>
void Deque<T>::insert(const int index, const int count, const T& value) {

	if (index < 0 || index > d->size)
		throw prism::exceptions::OutOfBoundsException(index);

	// IF NO BLOCKS EXIST YET
	if (d->blocks.size() == 0 && d->blocks.capacity() == 0) {
		d->blocks.reserve(1);
		d->blocks.push_back(new Vector<T>(d->blockSize));
	}

	//--------------------------------------------------
	// INSERT AT FRONT
	//--------------------------------------------------
	if (index == 0) {
		cout << "inserting at front" << endl;
		int storageIndex = d->firstIndex - count;
		if (storageIndex < 0) {
			storageIndex = d->blockSize + storageIndex;
			d->firstIndex = storageIndex;

			if (d->firstBlock == 0)
				d->blocks.push_front(new Vector<T>(d->blockSize));
			else d->firstBlock--;
		}

		Vector<T> *block = d->blocks[d->firstBlock];
		for (int c=count; c>0; c--)
			block->replace(d->firstIndex-c, value);

		d->size += count;
		d->firstIndex-= count;


//	if (index == 0) {
//		if (d->firstIndex-count >= 0)  {// then there is already room to prepend value in this block
//			Vector<T> *block = d->blocks[d->firstBlock];
//			for (int c=count; c>0; c--)
//				block->replace(d->firstIndex-c, value);
//			d->size += count;
//			d->firstIndex -= count;
//		}
//		else if (d->firstBlock != 0) { // there is no room at the front of this block so need to prepend a new block
//			Vector<T> *block = new Vector<T>(d->blockSize);
//			d->blocks.push_front(block);
//			for (int c=count; c>0; c++)
//				block->replace(d->blockSize-1, value);
//
//			d->firstBlock = 0;
//			d->firstIndex = d->blockSize-1;
//			d->size++;
//		}



	}
	//--------------------------------------------------
	// INSERT AT BACK
	//--------------------------------------------------
	else if (index == d->size) {
		Storage storage;
		findBlockAndIndex(index-1, storage);

		Vector<T> *block = d->blocks[storage.block];
		if (storage.index + 1 >= block->size()) { // then there is no more space in this block so need to append a new block
			Vector<T> *block = new Vector<T>(d->blockSize);
			d->blocks.push_back(block);
			block->replace(0, value);
			d->size++;
		}
		else { // there is room in this current block
			block->replace(storage.index+1, value);
			d->size++;
		}
	}
	//--------------------------------------------------
	// INSERT IN MIDDLE
	//--------------------------------------------------
	else {
		Storage storage;
		findBlockAndIndex(index, storage);

//		bool indexIsNearerFrontOfDeque = storage.index < (d->blockSize/2);
		bool indexIsNearerFrontOfDeque = index < d->size/2;
		if (indexIsNearerFrontOfDeque) {

			//  if there is room in the current block
			if (d->firstIndex != 0)
				d->firstIndex--;

			// if there is isn't room in the current block
			else {
				// if the first block is the first block in the vector
				if (d->firstBlock == 0) {
					d->blocks.push_front(new Vector<T>(d->blockSize));
					d->firstBlock = 0;
					d->firstIndex = d->blockSize-1;
				}
				// there is already a block unused before the current one
				else {
					d->firstBlock--;
					d->firstIndex = d->blockSize-1;
				}
			}

			d->size++;

			for (int i=0; i<index; i++)
				at(i) = at(i+1);

			at(index) = value;
		}
		// index is nearer the rear
		else {
			Storage storage;
			findBlockAndIndex(d->size-1, storage);

			// there isn't any room at the end of the current block
			if (storage.index == d->blockSize-1) {
				if (storage.block == d->blocks.size()-1)
					d->blocks.push_back(new Vector<T>(d->blockSize));
			}

			d->size++;

			for (int i=d->size-1; i>=index; i--) {
				Storage s1;
				Storage s2;
				findBlockAndIndex(i, s1);
				findBlockAndIndex(i-1, s2);
				Vector<T> *v1 = d->blocks[s1.block];
				Vector<T> *v2 = d->blocks[s2.block];
				v1->replace(s1.index, v2->at(s2.index));
			}

			at(index) = value;
		}
	}
}

/**
 * Returns the number of elements contained in this deque.
 */
template <class T>
const int Deque<T>::size() const {
	return d->size;
}



}
}



#endif /* DEQUE_H_ */
