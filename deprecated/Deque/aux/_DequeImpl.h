/*
 * _DequeImpl.h
 * v0.2
 *
 *  Created on: Feb 22, 2015
 *      Author: iainhemstock
 */

#ifndef DEQUEIMPL_H_
#define DEQUEIMPL_H_

#include "_DequeIterator.h"
#include "_DequeData.h"

namespace prism {
namespace containers {

// \cond DO_NOT_DOCUMENT
template <class T>
class DequeImpl {
public:
	typedef DequeIterator<T>	iterator;

					DequeImpl();
					DequeImpl(const int size, const T& value);
					~DequeImpl();
	void 			fillInitialize(const int size, const T& value);
	void			insertInBack(const int count, const T& value);
	void 			insertInFront(const int count, const T& value);
	void			insertInMiddle(iterator before, const int count, const T& value);
	const bool 		rangeCheckOk(const int index) const;
public:
	DequeData<T>	*data;
};
// \endcond

/**
 *
 */
template <class T>
DequeImpl<T>::DequeImpl()
: data(new DequeData<T>) {

}

/**
 *
 */
template <class T>
DequeImpl<T>::DequeImpl(const int size, const T& value)
: data(new DequeData<T>(size)) {
	fillInitialize(size, value);
}

/**
 *
 */
template <class T>
DequeImpl<T>::~DequeImpl() {
	delete data;
}

/**
 *
 */
template <class T>
void DequeImpl<T>::fillInitialize(const int size, const T& value) {
	// todo make this function generic again instead of using int
	iterator begin = data->firstChunk;
	iterator end = data->lastChunk;

	int i = 0;
	while (begin != end) {
		*begin = i++;
		++begin;
	}
}

/**
 *
 */
template <class T>
void DequeImpl<T>::insertInBack(const int count, const T& value) {

}

/**
 *
 */
template <class T>
void DequeImpl<T>::insertInFront(const int count, const T& value) {
	cout << "inserting in front" << endl;
	// is there space in the current chunk to add 'count' values?
	int numSpacesAtFrontOfChunk = data->firstChunk.current - data->firstChunk.begin;
	if (numSpacesAtFrontOfChunk < count) {
		int numChunks = (count - numSpacesAtFrontOfChunk) / data->CHUNK_SIZE + 1;
		data->reserveMapAtFront(numChunks);


	}
}

/**
 *
 */
template <class T>
void DequeImpl<T>::insertInMiddle(iterator before, const int count, const T& value) {

}

/**
 *
 */
template <class T>
const bool DequeImpl<T>::rangeCheckOk(const int index) const {
	return index >= 0 && index < (data->lastChunk - data->firstChunk);
}

}
}



#endif /* DEQUEIMPL_H_ */
