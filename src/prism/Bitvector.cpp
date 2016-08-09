/*
 * Bitvector.cpp
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#include <prism/Bitvector.h>
#include <prism/algorithms>
#include <prism/OutOfBoundsException>
#include <iostream>
using namespace std;//todo remove this

namespace prism {

/**
 * Creates a new Bitvector that contains \em nBits. \n
 * More precisely the bitvector will contain enough bytes to represent the requested
 * number of bits. i.e. internally the storage is represented in unsigned short ints
 * which are 16 bits each so its size will always be a multiple of 16. If a Bitvector
 * with 10 bits is requested then the Bitvector will have a size of 16, if 23 bits
 * are requested then Bitvector will have a size of 32 etc.
 */
Bitvector::Bitvector(const int nBits)
	: d(new BitvectorData)
{
	d->storage.nBits = nBits;
	int usiBits = sizeof(unsigned short int) * 8;
	int nBytes;

	if (nBits % usiBits == 0) nBytes = nBits / usiBits;
	else nBytes = nBits / usiBits + 1;

	reserve(nBytes);
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
const bool Bitvector::get(const int pos) const {
	if (rangeCheck(pos)) {

	}
	else
		throw OutOfBoundsException(pos);
}

/**
 *
 */
const bool Bitvector::rangeCheck(const int n) const {
	if (n < 0 || n > d->storage.nBits) return false;
	return true;
}

/**
 * @return Returns the number of bits in the Bitvector.
 */
const int Bitvector::size() const {
	return d->storage.nBits;
}

/**
 *
 */
void Bitvector::reserve(const int nBytes) {
	if (nBytes > d->storage.finish - d->storage.start) {
		unsigned short int * newStorage = new unsigned short int[nBytes];
		prism::copy(d->storage.start, d->storage.finish, newStorage);

		delete []d->storage.start;
		d->storage.start = newStorage;
		d->storage.finish = d->storage.start + nBytes;

	}
}

} /* namespace prism */
