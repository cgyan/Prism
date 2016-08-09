/*
 * Bitvector.h
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_BITVECTOR_H_
#define PRISM_BITVECTOR_H_

#include <prism/String>

namespace prism {

struct BitvectorData {
	struct memory  {
		unsigned short int * start; // unsigned short int is 16 bits each
		unsigned short int * finish;
		int nBits;
		memory() : start(0), finish(0), nBits(0) {}
		~memory() { delete []start; start=0; finish=0; nBits=0; }
	};
	memory storage;
};
/*!
 * This is the class description for the Bitvector.
 */
class Bitvector {
private:
	BitvectorData * d;
public:
	Bitvector();
	Bitvector(const int nBits);
	virtual ~Bitvector();

	const bool 	get(const int pos) const;
	void		reset();
	void		set();
	void 		set(const int pos, const bool b=true);
	const int 	size() const;
	String		toString() const;

private:
	const bool 	rangeCheck(const int n) const;
	void 		reserve(const int nBytes);
};

} /* namespace prism */

#endif /* PRISM_BITVECTOR_H_ */











