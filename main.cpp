/*
 * main.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <forward_list>
//#include <algorithm>
#include <prism/Array>
#include <prism/Stack>
#include <prism/List>
#include <prism/Queue>
#include <prism/Vector>
#include <prism/Iterator>
#include <prism/Point>
#include <prism/Pointf>
#include <prism/OutOfBoundsException>
#include <prism/SharedPointer>
#include <prism/Fraction>
#include <prism/Mathf>
#include <prism/Size>
#include <prism/Rect>
#include <prism/Circle>
#include <prism/String>
#include <prism/Char>
#include <prism/Algorithms>

using namespace prism;
using namespace std;

bool isOdd(int n) { return n%2 == 1; }
bool isEven(int n) { return n%2 == 0; }
bool isNegative(int n) { return n<0; }
void print(int n) { cout << n << endl; }

int main(int argc, char * argv[]) {
//	::testing::InitGoogleTest(&argc, argv);


//	String s("Cala Bona in Majorca");
//	s.replace(15, 1, Char('l'));
//
//	cout << s;

	Char c('s');
	String s("I see sea ships on the sea shore");
	s.replace("sea", '*');

	cout << s; // outputs: "I see ocean ships on the ocean shore"


//	return RUN_ALL_TESTS();
	return 0;
}

















