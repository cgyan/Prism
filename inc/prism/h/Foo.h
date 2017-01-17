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

/*
 	-fno-elide-constructors
 	By default the compiler is allowed to perform copy elision which optimizes away unnecessary
 	calls to constructors. To turn off this optimization use this flag in the g++ statement

	Foo f("Harley");	// calls Foo(name)
	Foo g(f);			// calls Foo ctor
	Foo h = f;			// calls Foo ctor

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimizatio: only calls Foo(name)
	Foo i = Foo("Davidson");

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimizatio: only calls Foo(name)
	Foo j(Foo("Davidson"));

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimization: same
	Foo k(std::move(Foo("Davidson")));
 */

PRISM_BEGIN_NAMESPACE

class Foo {
public:
	using StringType = std::string;
//	using StringType = prism::String;
	StringType * name;
public:
	/*
	 *
	 */
	Foo() noexcept
	: name(nullptr)
	{}


	/*
	 *
	 */
	explicit Foo(StringType const & name)
	: name(new StringType(name))
	{cout << "Foo(name)\n";}

	// =======================================================================================
	// COPY SEMANTICS
	// =======================================================================================
	/*
	 * This Foo doesn't exist yet so allocates new StringType and takes a copy of rhs's name
	 * rhs.name will be a valid pointer to a StringType object but may be an empty string
	 */
	Foo(Foo const & rhs)
	: name(nullptr)
	{
		cout << "Foo::Foo(Foo const&)\n";
		if (rhs.name != nullptr)
			name = new StringType(*rhs.name);
	}

	/*
	 * This Foo already exists so need to free up its resources before assigning
	 * rhs's resources to it
	 */
	Foo& operator=(Foo const & rhs) {
		cout << "Foo::operator=(Foo const&)\n";
		if (this != &rhs) {
			delete name;
			name = nullptr;
			if (rhs.name != nullptr)
				name = new StringType(*rhs.name);
		}
		return *this;
	}
	// =======================================================================================
	// MOVE SEMANTICS
	// =======================================================================================
	/*
	 * This Foo doesn't exist yet but will steal the resources from rhs instead of initializing
	 * its own resources
	 */
	Foo(Foo&& rhs) noexcept
	: name(nullptr)
	{
		cout << "Foo::Foo(Foo&&)\n";
		this->name = rhs.name;
		rhs.name = nullptr;
	}

	/*
	 * This Foo aready exists. this->name might be null or points to a StringType object
	 * Existing dynamic resources should be released prior to assignment
	 */
	Foo& operator=(Foo&& rhs) noexcept {
		cout << "Foo::operator=(Foo&&)\n";
		this->name = rhs.name;
		rhs.name = nullptr;
		return *this;
	}

	/*
	 *
	 */
	~Foo() noexcept {
		cout << "~Foo()\n";
		delete name;
	}

	StringType 		getName() const noexcept{ return *name; }

	friend std::ostream& operator<<(std::ostream& out, Foo const & f) {
		out << "Foo [" << &f << "] name=" << f.getName();
		return out;
	}
};




PRISM_END_NAMESPACE

#endif /* PRISM_FOO_H_ */












