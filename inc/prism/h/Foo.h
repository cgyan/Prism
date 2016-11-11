/*
 * Foo.h
 * v0.*
 *
 *  Created on: Sep 17, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_FOO_H_
#define PRISM_FOO_H_

#include <prism/h/global.h>
#include <prism/h/String.h>
#include <string>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;

PRISM_BEGIN_NAMESPACE

class Foo {
public:
	using StringType = std::string;
//	using StringType = prism::String;
	StringType * name;
	int age;
	char var;
public:
	/*
	 *
	 */
	Foo()
	: name(new StringType),
	  age(0),
	  var(0)
	{}


	/*
	 *
	 */
	Foo(StringType const & name, int const age, const char var)
	: name(new StringType(name)),
	  age(age),
	  var(var)
	{ cout << toString() << endl; }

	/*
	 * This Foo doesn't exist yet so allocates new StringType and takes a copy of rhs's name
	 */
	Foo(Foo const & rhs)
	: name(new StringType(*rhs.name)),
	  age(rhs.age),
	  var(rhs.var)
	{ cout << toString() << endl; }

	/*
	 * This Foo already exists so need to free up its resources before assigning
	 * rhs's resources to it
	 */
	Foo& operator=(const Foo& rhs) {
		if (this != &rhs) {
			delete name;
			name = new StringType(*rhs.name);
			age = rhs.age;
			var = rhs.var;
		}
		cout << toString() << endl;
		return *this;
	}

	/*
	 * This Foo doesn't exist yet but steals the resources from rhs
	 */
//	Foo(Foo&& rhs)
//	: name(nullptr),
//	  age(0)
//	{
//		cout << "move ctor" << *name << "\n";
//		std::swap(name, rhs.name);
//		std::swap(age, rhs.age);
//	}

	/*
	 *
	 */
	~Foo() {
		cout << "dtor: deleting " << endl;
		delete name;
	}

	int const 		getAge() const { return age; }
	StringType 		getName() const { return *name; }
	char			getVar() const { return var; }

	StringType		toString() const {
		std::stringstream ss;
		ss << "Foo: name="<<*name<<" age="<<age<<" var="<<var;
		return StringType(ss.str());
	}

	friend std::ostream& operator<<(std::ostream& out, Foo const & f) {
		out << f.toString();
		return out;
	}
};




PRISM_END_NAMESPACE

#endif /* PRISM_FOO_H_ */












