/*
 * Obj.h
 * v0.*
 *
 *  Created on: Sep 17, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_OBJ_H_
#define PRISM_OBJ_H_

#include <iostream>

namespace prism {

class Obj {
private:
	int* p;
public:
	Obj()
	: p(0) {
		std::cout << "Obj::constructor [" << this << "]";
		std::cout << (*this) << std::endl;
	}

	Obj(int i)
	: p(new int(i))
	{
		std::cout << "Obj::constructor [" << this << "] with i=" << i;
		std::cout << *this << std::endl;
	}

	Obj(const Obj& copy)
	: p(0) {
		if (copy.p) p = new int(*copy.p);
		else p = 0;
		std::cout << "Obj::copy_constructor [" << this << "]";
		std::cout << *this << std::endl;

	}

	~Obj() {
		std::cout << "Obj::destructor [" << this << "]";
		std::cout << *this << std::endl;
		if (p) delete p;
	}

	friend ostream& operator<<(ostream& out, const Obj& o) {
//		out << "Obj[" << &o << "] o.p:" << o.p << " ";
		if (o.p) out << " *p:" << *(o.p);
		else out << " p:0";
		return out;
	}
};

} // end namepsace prism

#endif /* PRISM_OBJ_H_ */
