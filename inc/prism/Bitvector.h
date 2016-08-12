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
#include <ostream>

namespace prism {

struct BitvectorData {
	struct memory  {
		unsigned long long int * start; // unsigned long long ints are 64 bits each
		unsigned long long int * finish;
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
public://todo back to private
	BitvectorData * d;
public:
	Bitvector();
	Bitvector(const int nBits);
	Bitvector(const String & bitString);
	Bitvector(const Bitvector & copy);
	virtual ~Bitvector();

	const bool		all() const;
	const bool		any() const;
	const int		count() const;
	void			flip(int bit);
	void			flipAll();
	const bool 		get(int bit) const;
	const bool		none() const;
	void			resetAll();
	void 			set(int bit, const bool b=true);
	void			setAll();
	const int 		size() const;
	String			string() const;
	unsigned long long int		ull() const;

	bool			operator[](const int bit);
	const bool		operator[](const int bit) const;
	Bitvector 		operator<<(const int pos) const;
	Bitvector 		operator>>(const int pos) const;
	Bitvector &		operator<<=(const int pos);
	Bitvector &		operator>>=(const int pos);
	Bitvector 		operator~() const;
	Bitvector &		operator&=(const Bitvector & other);
	Bitvector &		operator|=(const Bitvector & other);
	Bitvector &		operator^=(const Bitvector & other);
	Bitvector & 	operator=(const Bitvector & other);

	// related non members
	friend Bitvector		operator&(const Bitvector & bv1, const Bitvector & bv2);
	friend Bitvector		operator|(const Bitvector & bv1, const Bitvector & bv2);
	friend Bitvector		operator^(const Bitvector & bv1, const Bitvector & bv2);
	friend const bool		operator==(const Bitvector & bv1, const Bitvector & bv2);
	friend const bool		operator!=(const Bitvector & bv1, const Bitvector & bv2);
	friend std::ostream & 	operator<<(std::ostream & out, const Bitvector &bv);

private:
	const int	numBytes(const int nBits) const;
	const bool 	rangeCheck(const int n) const;
	void 		reserve(const int nBytes);
};

} /* namespace prism */

#endif /* PRISM_BITVECTOR_H_ */











