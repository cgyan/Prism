/*
 * Console.h
 * v0.*
 *
 *  Created on: Jul 21, 2016
 *      Author: iainhemstock
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <prism/String>

namespace prism {

class Console;

template <class T>
void output(const T& value) {
	std::cout << value;
}

class Console {
public:
	Console & operator<<(const int i) { output(i); return *this; }
	Console & operator<<(const float f) { output(f); return *this; }
	Console & operator<<(const String & str) { output(str); return *this; }
	Console & operator<<(const char * str) { output(str); return *this; }

	template <class T>
	friend Console & operator<<(Console & c, const T& value) {
		c << value;
		return c;
	}
};

Console console() { return Console(); }

}



#endif /* CONSOLE_H_ */
