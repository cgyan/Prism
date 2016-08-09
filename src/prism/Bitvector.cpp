/*
 * Bitvector.cpp
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#include <prism/Bitvector.h>
#include <prism/algorithms>
#include <iostream>
using namespace std;//todo remove this

namespace prism {

/**
 * Creates a new Bitvector that contains \em nBits.
 */
Bitvector::Bitvector(const int nBits)
	: d(new BitvectorData)
{
	int usiBits = sizeof(unsigned short int) * 8;
	int nBytes;

	if (nBits % usiBits == 0) nBytes = nBits / usiBits;
	else nBytes = nBits / usiBits + 1;
}

/**
 * Destroys this Bitvector
 */
Bitvector::~Bitvector() {
	delete d;
}

/**
 *
 */
void Bitvector::reserve(const int nBytes) {
	if (nBytes > d->storage.finish - d->storage.start) {
		unsigned short int * newStorage = new unsigned short int[nBytes];
		prism::copy(d->storage.start, d->storage.end, newStorage);

		int size = d->storage.end-d->storage.start;
		delete []d->storage.start;
		d->storage.start = newStorage;
		d->storage.end = d->storage.start + size;
		d->storage.end = d->storage.start + nBytes;

	}
}

/**
 * @return Returns the number of bits
 */
const int Bitvector::size() const {
	return 1;
}

} /* namespace prism */
