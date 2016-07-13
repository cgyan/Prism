/*
 * _DequeData.h
 * v0.2
 *
 *  Created on: Feb 2, 2015
 *      Author: iainhemstock
 *
 *  begin.current always points to the first element in the deque.
 *  end.current always points to the imaginary element one past the last element in the deque.
 */

#ifndef DEQUEDATA_H_
#define DEQUEDATA_H_

#include <ostream>
#include <algorithm>
#include "_DequeIterator.h"

namespace prism {
namespace containers {

using namespace std; // todo remove this
using namespace prism::containers;

// \cond DO_NOT_DOCUMENT
template <class T>
class DequeData {
	typedef 	DequeIterator<T>	iterator;
public:
	T** 		map;
	int			mapSize;
	iterator	firstChunk; 	// points to first chunk in map
	iterator	lastChunk;	 	// points to last chunk in map
	enum		{ CHUNK_SIZE = 8 };
public:
				DequeData();
				DequeData(const int numElements);
	T*			allocateChunk() const;
	T**			allocateMap(const int size) const;
	void		createChunks(T** begin, T** end);
	void		deallocateChunk(T* chunk);
	void		deallocateMap();
	void		destroyChunks(T** begin, T** end);
	void		initializeMap(const int numElements);
	void		reallocateMap(const int numChunks);
	void		reserveMapAtFront(const int numChunks);

	void		debugMap() const;
};
// \endcond

// todo remove all the following code into a .tcc file
//#include "DequeData.tcc"
template <class T>
DequeData<T>::DequeData()
: map(0), mapSize(0) {
	initializeMap(0);
}

/**
 *
 */
template <class T>
DequeData<T>::DequeData(const int numElements)
: map(0), mapSize(0) {
	initializeMap(numElements);
}

/**
 *
 */
template <class T>
T* DequeData<T>::allocateChunk() const {
	return new T[CHUNK_SIZE];
}

/**
 *
 */
template <class T>
T** DequeData<T>::allocateMap(const int size) const {
	return new T*[size];
}

/**
 *
 */
template <class T>
void DequeData<T>::createChunks(T** begin, T** end) {
	T** c = begin;
	while (c != end)
		*c++ = allocateChunk();
}

/**
 *
 */
template <class T>
void DequeData<T>::deallocateChunk(T* chunk) {
	delete chunk;
}

/**
 *
 */
template <class T>
void DequeData<T>::deallocateMap() {
	T** b = map;
	T** e = map + mapSize;
	destroyChunks(b, e);
	delete []map;
}

/**
 *
 */
template <class T>
void DequeData<T>::destroyChunks(T** begin, T** end) {
	while (begin != end)
		deallocateChunk(*begin++);
}

/**
 *
 */
template <class T>
void DequeData<T>::initializeMap(const int numElements) {
	int numChunks = numElements / CHUNK_SIZE + 1;
	mapSize = numChunks;
	map = allocateMap(mapSize);

	T** beginChunk = map;
	T** endChunk = beginChunk + numChunks;
	createChunks(beginChunk, endChunk);

	firstChunk.setChunk(beginChunk);
	lastChunk.setChunk(endChunk-1);
	firstChunk.current = firstChunk.begin;
	lastChunk.current = lastChunk.begin + numElements % CHUNK_SIZE;

}

/**
 *
 */
template <class T>
void DequeData<T>::reallocateMap(const int numChunks) {
	T** newMap = allocateMap(mapSize+numChunks);

	T** beginChunk = newMap;
	T** endChunk = beginChunk + numChunks;
	createChunks(beginChunk, endChunk);

	std::copy(map, map+mapSize, newMap+numChunks);

	deallocateMap();
	map = newMap;
	mapSize += numChunks;
}

/**
 *
 */
template <class T>
void DequeData<T>::reserveMapAtFront(const int numChunks) {
	reallocateMap(numChunks);
}

/**
 *
 */
template <class T>
void DequeData<T>::debugMap() const {
	std::cout << "-----------------------------\n";
	std::cout << "Deque map [" << this->map << "] size:" << this->mapSize << "\n";
	std::cout << "-----------------------------\n";
	for (int i=0; i<this->mapSize; i++)
		std::cout << "-- [" << i << "] " << this->map[i] << "\n";
	std::cout << "-----------------------------\n";
}


}
}




#endif /* DEQUEDATA_H_ */
