/*
 * StringTest.cpp
 * v0.*
 *
 *  Created on: Jul 23, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <string>
#include <prism/String>

using namespace prism;

class StringTest : public String, public ::testing::Test {

};

/**
 *
 */
TEST_F(StringTest, constructorDefault) {
	String s;
	ASSERT_EQ(s, "");
	ASSERT_EQ(s.size(), 0);
	ASSERT_EQ(s.capacity(), 0);
}

/**
 *
 */
TEST_F(StringTest, constructorCString) {
	const char cs[] = "test";
	String s(cs);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 *
 */
TEST_F(StringTest, constructorStdString) {
	std::string ss = "test";
	String s(ss);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 *
 */
TEST_F(StringTest, constructorChar) {
	char c = 'f';
	String s(c);
	ASSERT_EQ(s, c);
	ASSERT_EQ(s.size(), 1);
	ASSERT_EQ(s.capacity(), 1);
}

/**
 *
 */
TEST_F(StringTest, constructorNumChars) {
	char c = '*';
	String s(5, c);
	ASSERT_EQ(s, "*****");
	ASSERT_EQ(s.size(), 5);
	ASSERT_EQ(s.capacity(), 5);
}

/**
 *
 */
TEST_F(StringTest, constructorCopy) {
	String first("test");
	String copy(first);
	ASSERT_EQ(copy, "test");
	ASSERT_EQ(copy.size(), 4);
	ASSERT_EQ(copy.capacity(), 4);
}

/**
 *
 */
TEST_F(StringTest, reserveNewString) {
	String s;
	s.reserve(15);
	ASSERT_EQ(s, "");
	ASSERT_EQ(s.capacity(), 15);
	ASSERT_EQ(s.size(), 0);
}

/**
 *
 */
TEST_F(StringTest, reserveMoreExistingString) {
	String s("test");
	s.reserve(8);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 8);
}

/**
 * String::reserve() can only increase the capacity.
 * Any call to reserve() with a value less than the current capacity
 * should be ignored.
 */
TEST_F(StringTest, reserveLessExistingString) {
	String s("test");
	s.reserve(2);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Calling String::resize(arg) on a new empty string should set both the
 * size and capacity to arg and init each character to a space.
 */
TEST_F(StringTest, resizeNewString) {
	String s;
	s.resize(5);
	ASSERT_EQ(s, "     "); // 5 single spaces
	ASSERT_EQ(s.size(), 5);
	ASSERT_EQ(s.capacity(), 5);
}

/**
 * Calling String::resize(arg) on an existing string where arg is lower
 * than the current size those characters are removed but the capacity
 * remains unchanged.
 */
TEST_F(StringTest, resizeLowerExistingString) {
	String s("test");
	s.resize(2);
	ASSERT_EQ(s, "te");
	ASSERT_EQ(s.size(), 2);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Calling String::resize(arg) on an existing string where arg is greater
 * than the current size will increase the string's size to arg setting the
 * new characters to ' '. This test will force an increase of the capacity
 * from 4 to 8.
 */
TEST_F(StringTest, resizeGreaterExistingString) {
	String s("test");
	s.resize(8);
	ASSERT_EQ(s, "test    "); // "test" followed by four spaces
	ASSERT_EQ(s.size(), 8);
	ASSERT_EQ(s.capacity(), 8);
}

/**
 * Calling String::resize(arg) on an existing string where arg is the same value
 * as the string's size will change nothing.
 */
TEST_F(StringTest, resizeToSameSizeExistingString) {
	String s("test");
	s.resize(4);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * On an empty string calling String::insert(iterator, str) should increase
 * the capacity to accommodate str. The capacity should equal the size.
 */
TEST_F(StringTest, insertBeginNewStringIterator) {
	String s;
	s.insert(s.end(), "test");
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 *
 */
TEST_F(StringTest, insertBeginExistingStringIterator) {
	String s("millor");
	s.insert(s.begin(), "cala");
	ASSERT_EQ(s, "calamillor");
	ASSERT_EQ(s.size(), 6);
	ASSERT_EQ(s.capacity(), 12);
}




