/*
 * ReverseIteratorTest.cpp
 * v1
 *
 *  Created on: 3 Dec 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/Iterator>
#include <prism/String>

namespace prism {
namespace test {

class ReverseIteratorTest : public ::testing::Test {
public:
	using reverse_iterator = ReverseIterator<String::iterator>;
	String str;
	reverse_iterator rbit; // begin iter
	reverse_iterator reit; // end iter
public:
	ReverseIteratorTest()
	: str("abcdefg"),
	  rbit(str.end()),
	  reit(str.begin())
	{}
};

/**
 * Test: ReverseIterator()
 */
TEST_F(ReverseIteratorTest, default_ctor) {
	EXPECT_TRUE(typeid(decltype(rbit.base()))
			== typeid(String::iterator));
}

/**
 * Test: base()
 */
TEST_F(ReverseIteratorTest, base) {
	EXPECT_TRUE(typeid(decltype(rbit.base()))
			== typeid(String::iterator));
}

/**
 * Test: operatror*()
 */
TEST_F(ReverseIteratorTest, dereference_this_iter) {
	EXPECT_TRUE(*rbit == 'g');
	EXPECT_FALSE(*rbit == 'a');
	EXPECT_FALSE(*rbit == 'b');
	EXPECT_FALSE(*rbit == 'c');
	EXPECT_FALSE(*rbit == 'd');
	EXPECT_FALSE(*rbit == 'e');
	EXPECT_FALSE(*rbit == 'f');
}

/**
 * Test: operator+(numSteps)
 */
TEST_F(ReverseIteratorTest, advance_copy_of_iter_num_steps) {
	reverse_iterator ri = rbit + 3;
	EXPECT_EQ('g', *rbit); // rbit should not be modified
	EXPECT_EQ('d', *ri);
	EXPECT_NE('a', *ri);
	EXPECT_NE('b', *ri);
	EXPECT_NE('c', *ri);
	EXPECT_NE('e', *ri);
	EXPECT_NE('f', *ri);
}

/**
 * Test: operator++()
 */
TEST_F(ReverseIteratorTest, advance_this_iter_one_step) {
	++rbit;
	EXPECT_EQ('f', *rbit);
}

/**
 * Test: operator++(int junk)
 */
TEST_F(ReverseIteratorTest, advance_copy_of_iter_one_step) {
	EXPECT_EQ('g', *rbit++);
	EXPECT_EQ('f', *rbit);
}

/**
 * Test: operator+=(int steps)
 */
TEST_F(ReverseIteratorTest, advance_this_iter_num_steps) {
	rbit = rbit += 4;
	EXPECT_EQ('c', *rbit);
	EXPECT_NE('a', *rbit);
	EXPECT_NE('b', *rbit);
	EXPECT_NE('d', *rbit);
	EXPECT_NE('e', *rbit);
	EXPECT_NE('f', *rbit);
	EXPECT_NE('g', *rbit);
}

/**
 * Test: operator-(numSteps)
 */
TEST_F(ReverseIteratorTest, decrement_copy_of_iter_num_steps) {
	reverse_iterator it = reit - 5;
	EXPECT_EQ('e', *it);
	EXPECT_NE('a', *it);
	EXPECT_NE('b', *it);
	EXPECT_NE('c', *it);
	EXPECT_NE('d', *it);
	EXPECT_NE('f', *it);
	EXPECT_NE('g', *it);
}

/**
 * Test: operator--()
 */
TEST_F(ReverseIteratorTest, decrement_this_iter_one_step) {
	--reit;
	EXPECT_EQ('a', *reit);
}

/**
 * Test: operator--(int junk)
 */
TEST_F(ReverseIteratorTest, decrement_copy_of_iter_one_step) {
	--reit;
	EXPECT_EQ('a', *reit--);
	EXPECT_EQ('b', *reit);
}

/**
 * Test: operator-=(int steps)
 */
TEST_F(ReverseIteratorTest, decrement_this_iter_num_steps) {
	reit -= 2;
	EXPECT_EQ('b', *reit);
}

/**
 * Test: operator[](int offset)
 */
TEST_F(ReverseIteratorTest, access_element_at_offset) {
	EXPECT_EQ('d', rbit[3]);

	// now move the iterator and access the offset value again
	// it should now have changed
	++rbit;
	EXPECT_EQ('c', rbit[3]);
}

/**
 * Test: operator==(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_equal_to_iter_B) {
	EXPECT_TRUE(rbit == rbit);
	EXPECT_FALSE(rbit == reit);
}

/**
 * Test: operator!=(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_not_equal_to_iter_B) {
	EXPECT_FALSE(rbit != rbit);
	EXPECT_TRUE(rbit != reit);
}

/**
 * Test: operator<(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_less_than_iter_B) {
	EXPECT_TRUE(rbit < reit);
	EXPECT_FALSE(reit < rbit);
}

/**
 * Test: operator<=(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_less_than_or_equal_to_iter_B) {
	reverse_iterator it(str.end());
	it += 4; // it == 'c'

	EXPECT_TRUE(rbit <= reit);
	EXPECT_TRUE(rbit <= it);
	rbit += 4;
	EXPECT_TRUE(rbit <= it); // rbit should be equal to it
	++rbit;
	EXPECT_FALSE(rbit <= it); // rbit should be one place after it
}

/**
 * Test: operator>(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_greater_than_iter_B) {
	EXPECT_TRUE(reit > rbit);
	reit = rbit;
	EXPECT_FALSE(reit > rbit);
}

/**
 * Test: operator>=(rev_iter a, rev_iter b)
 */
TEST_F(ReverseIteratorTest, iter_A_greater_than_or_equal_to_iter_B) {
	reverse_iterator it = reit - 5; // it == 'f'
	EXPECT_TRUE(reit >= rbit);
	EXPECT_TRUE(reit >= it);
	reit -= 5;
	EXPECT_TRUE(reit >= it);
	--reit;
	EXPECT_FALSE(reit >= it);
}

} // end namespace test
} // end namespace prism


















