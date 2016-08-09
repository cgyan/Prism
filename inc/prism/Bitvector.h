/*
 * Bitvector.h
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_BITVECTOR_H_
#define PRISM_BITVECTOR_H_

namespace prism {

struct BitvectorData {
	struct memory  {
		unsigned short int * start; // unsigned short int is 16 bits each
		unsigned short int * end;
		unsigned short int * finish;
		memory() : start(0), end(0), finish() {}
		~memory() { delete []start; start=0; end=0; finish=0; }
	};
	memory storage;
};
/*!
 * This is the class description for the Bitvector.
 */
class Bitvector {
private:
	BitvectorData * d;
private:
	Bitvector() : d(new BitvectorData) {}
	void reserve(const int nBytes);
public:
	Bitvector(const int nBits);
	virtual ~Bitvector();

	const int size() const;
};

} /* namespace prism */

#endif /* PRISM_BITVECTOR_H_ */











