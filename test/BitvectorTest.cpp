/*
 * BitvectorTest.cpp
 * v0.*
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Bitvector>
#include <iostream> // todo remove this
using namespace std; // todo remove this

namespace prism {

class BitvectorTest : public ::testing::Test {
};

/**
 * Test: Bitvector(nBits)
 */
TEST_F(BitvectorTest, constructor) {
	Bitvector bv;
}

/**
 * Test: constructor(nBits)
 */
TEST_F(BitvectorTest, constructor_nBits) {
	Bitvector bv(20);

	ASSERT_TRUE(bv.size() == 20);
}

/**
 * Test: Bitvector(string)
 */
TEST_F(BitvectorTest, constructor_string) {
	String s = "11110000111100001111"; // 20 digits
	Bitvector bv(s);
	ASSERT_TRUE(bv.toString() == "11110000111100001111");
}

/**
 * Test: Bitvector(copy)
 */
TEST_F(BitvectorTest, copyConstructor) {
	Bitvector bv(8);
	bv.set(0);
	bv.set(2);
	bv.set(4);
	bv.set(7);

	Bitvector copy(bv);
	ASSERT_EQ(copy.toString(), "10010101");
}

/**
 * Test: all()
 */
TEST_F(BitvectorTest, all) {
	Bitvector bv("0000");
	ASSERT_FALSE(bv.all());
	bv.set(1);
	ASSERT_FALSE(bv.all());
	bv.setAll();
	ASSERT_TRUE(bv.all());
}

/**
 * Test: any()
 */
TEST_F(BitvectorTest, any) {
	Bitvector bv("0000");
	ASSERT_FALSE(bv.any());
	bv.set(1);
	ASSERT_TRUE(bv.any());
}

/**
 * Test: count()
 */
TEST_F(BitvectorTest, count) {
	Bitvector bv("111100001111");
	ASSERT_EQ(bv.count(), 8);
	bv.setAll();
	ASSERT_EQ(bv.count(), 12);
	bv.resetAll();
	ASSERT_EQ(bv.count(), 0);
}

/**
 * TEST: flip(bit)
 */
TEST_F(BitvectorTest, flip) {
	Bitvector bv("11100100011101010");
	bv.flip(0);
	bv.flip(1);
	bv.flip(12);

	ASSERT_EQ(bv.get(0), 1);
	ASSERT_EQ(bv.get(1), 0);
	ASSERT_EQ(bv.get(12), 1);
}

/**
 * Test: flipAll()
 */
TEST_F(BitvectorTest, flipAll) {
	Bitvector bv("11100100011101010");
	bv.flipAll();

	ASSERT_EQ(bv.toString(), "00011011100010101");
}

/**
 * Test: get(pos)
 */
TEST_F(BitvectorTest, get) {
	Bitvector bv(6);
	bv.set(0);
	bv.set(2);
	bv.set(4);

	ASSERT_TRUE(bv.get(0));
	ASSERT_TRUE(bv.get(2));
	ASSERT_TRUE(bv.get(4));
	ASSERT_FALSE(bv.get(1));
	ASSERT_FALSE(bv.get(3));
	ASSERT_FALSE(bv.get(5));
}

/**
 * Test: none()
 */
TEST_F(BitvectorTest, none) {
	Bitvector bv("111000110010");
	ASSERT_FALSE(bv.none());
	bv.resetAll();
	ASSERT_TRUE(bv.none());
}

/**
 * Test: resetAll()
 */
TEST_F(BitvectorTest, resetAll) {
	Bitvector bv(8);
	bv.set(0);
	bv.set(2);
	bv.set(4);
	bv.set(7);

	bv.resetAll();
	ASSERT_EQ(bv.toString(), "00000000");
}

/**
 * Test: setAll()
 */
TEST_F(BitvectorTest, setAll) {
	Bitvector bv(8);
	bv.setAll();
	ASSERT_EQ(bv.toString(), "11111111");
}

/**
 * Test: set(pos, bool)
 */
TEST_F(BitvectorTest, set_pos_bool) {
	Bitvector bv(20);
	bv.set(1, true);
	bv.set(6);
	bv.set(19);

	ASSERT_FALSE(bv.get(0));
	ASSERT_TRUE(bv.get(1));
	ASSERT_FALSE(bv.get(2));
	ASSERT_FALSE(bv.get(3));
	ASSERT_FALSE(bv.get(4));
	ASSERT_FALSE(bv.get(5));
	ASSERT_TRUE(bv.get(6));
	ASSERT_FALSE(bv.get(7));
	ASSERT_FALSE(bv.get(8));
	ASSERT_FALSE(bv.get(9));
	ASSERT_FALSE(bv.get(10));
	ASSERT_FALSE(bv.get(11));
	ASSERT_FALSE(bv.get(12));
	ASSERT_FALSE(bv.get(13));
	ASSERT_FALSE(bv.get(14));
	ASSERT_FALSE(bv.get(15));
	ASSERT_FALSE(bv.get(16));
	ASSERT_FALSE(bv.get(17));
	ASSERT_FALSE(bv.get(18));
	ASSERT_TRUE(bv.get(19));
}

/**
 * Test: size()
 * Bitvector uses unsigned short ints as the internal storage
 * that are 16 bits each.
 */
TEST_F(BitvectorTest, size) {
	Bitvector bv(16);
	ASSERT_EQ(bv.size(), 16);
	Bitvector bv2(17);
	ASSERT_EQ(bv2.size(), 17);
}

/**
 * Test: toString()
 */
TEST_F(BitvectorTest, toString) {
	Bitvector bv(8);
	bv.setAll();

	ASSERT_EQ(bv.toString(), "11111111");

	bv.set(0, false);
	bv.set(4, false);

	ASSERT_EQ(bv.toString(), "11101110");
}

/**
 * Test: operator[]()
 */
TEST_F(BitvectorTest, opBrackets) {
	Bitvector bv("111100001010");
	ASSERT_EQ(bv[0], 0);
	ASSERT_EQ(bv[1], 1);
	ASSERT_EQ(bv[2], 0);
	ASSERT_EQ(bv[3], 1);
	ASSERT_EQ(bv[4], 0);
	ASSERT_EQ(bv[5], 0);
	ASSERT_EQ(bv[6], 0);
	ASSERT_EQ(bv[7], 0);
	ASSERT_EQ(bv[8], 1);
	ASSERT_EQ(bv[9], 1);
	ASSERT_EQ(bv[10], 1);
	ASSERT_EQ(bv[11], 1);
}

/**
 * Test: const operator[]()
 */
TEST_F(BitvectorTest, opConstBrackets) {
	const Bitvector bv("111100001010");
	ASSERT_EQ(bv[0], 0);
	ASSERT_EQ(bv[1], 1);
	ASSERT_EQ(bv[2], 0);
	ASSERT_EQ(bv[3], 1);
	ASSERT_EQ(bv[4], 0);
	ASSERT_EQ(bv[5], 0);
	ASSERT_EQ(bv[6], 0);
	ASSERT_EQ(bv[7], 0);
	ASSERT_EQ(bv[8], 1);
	ASSERT_EQ(bv[9], 1);
	ASSERT_EQ(bv[10], 1);
	ASSERT_EQ(bv[11], 1);
}

/**
 * Test: operator<<(pos)
 */
TEST_F(BitvectorTest, opShiftLeft) {

	Bitvector bv("00000000000000000000000000001111"); // 32 digits

	bv = bv << 1;
	ASSERT_TRUE(bv.toString() == "00000000000000000000000000011110");

	bv = bv << 30;
	ASSERT_TRUE(bv.toString() == "10000000000000000000000000000000");
}

/**
 * Test: operator>>(pos)
 */
TEST_F(BitvectorTest, opShiftRight) {

	Bitvector bv("11110000000000000000000000001111"); // 32 digits

	bv = bv >> 1;
	cout << bv.toString() << endl;
	ASSERT_TRUE(bv.toString() == "01111000000000000000000000000111");

	bv = bv >> 2;
	ASSERT_TRUE(bv.toString() == "00011110000000000000000000000001");
}

/**
 * Test: operator<<=(pos)
 */
TEST_F(BitvectorTest, opShiftLeftEquals) {

	Bitvector bv("00000000000000000000000000001111"); // 32 digits

	bv <<= 1;
	ASSERT_TRUE(bv.toString() == "00000000000000000000000000011110");

	bv <<= 30;
	ASSERT_TRUE(bv.toString() == "10000000000000000000000000000000");
}

/**
 * Test: operator>>=(pos)
 */
TEST_F(BitvectorTest, opShiftRightEquals) {

	Bitvector bv("11110000000000000000000000001111"); // 32 digits

	bv >>= 1;
	ASSERT_TRUE(bv.toString() == "01111000000000000000000000000111");

	bv >>= 2;
	ASSERT_TRUE(bv.toString() == "00011110000000000000000000000001");
}

/**
 * Test: operator~()
 */
TEST_F(BitvectorTest, opBitwiseNOT) {
	Bitvector bv("111011001000");
	bv = ~bv;

	ASSERT_EQ(bv.toString(), "000100110111");
}

/**
 * Test: operator&=()
 */
TEST_F(BitvectorTest, opBitwiseANDEquals) {
	Bitvector bv1("110010101111");
	Bitvector bv2("101010101010");
	bv1 &= bv2;

	ASSERT_EQ(bv1.toString(), "100010101010");
}

/**
 * Test: operator|=()
 */
TEST_F(BitvectorTest, opBitwiseOREquals) {
	Bitvector bv1("110010101111");
	Bitvector bv2("101010101010");
	bv1 |= bv2;

	ASSERT_EQ(bv1.toString(), "111010101111");
}

/**
 * Test: operator^=()
 */
TEST_F(BitvectorTest, opBitwiseXOREquals) {
	Bitvector bv1("110010101111");
	Bitvector bv2("101010101010");
	bv1 ^= bv2;

	ASSERT_EQ(bv1.toString(), "011000000101");
}

/**
 * Test: assignment operator
 */
TEST_F(BitvectorTest, opAssignment) {
	Bitvector bv1("11110000111100001111");
	Bitvector bv2 = bv1;

	ASSERT_TRUE(bv2.toString() == "11110000111100001111");
	ASSERT_TRUE(bv2.size() == 20);
}

/**
 * Test: operator&(Bitvector1, Bitvector2)
 */
TEST_F(BitvectorTest, opBitwiseAND) {
	Bitvector bv1("11100100011100101001"); // 20 digits
	Bitvector bv2("00111001010100110001");
	Bitvector bv3 = bv1 & bv2;

	ASSERT_EQ(bv3.toString(), "00100000010100100001");
}

/**
 * Test: operator|(Bitvector1, Bitvector2)
 */
TEST_F(BitvectorTest, opBitwiseOR) {
	Bitvector bv1("11100100011100101001"); // 20 digits
	Bitvector bv2("00111001010100110001");
	Bitvector bv3 = bv1 | bv2;

	ASSERT_EQ(bv3.toString(), "11111101011100111001");
}

/**
 * Test: operator^(Bitvector1, Bitvector2)
 */
TEST_F(BitvectorTest, opBitwiseXOR) {
	Bitvector bv1("11100100011100101001"); // 20 digits
	Bitvector bv2("00111001010100110001");

	Bitvector bv3 = bv1 ^ bv2;

	ASSERT_EQ(bv3.toString(), "11011101001000011000");
}

/**
 * Test: operator==()
 */
TEST_F(BitvectorTest, opEqualsEquals) {
	Bitvector bv1(8);
	bv1.setAll();
	Bitvector bv2(bv1);
	Bitvector bv3(12);

	ASSERT_TRUE(bv1 == bv2);
	ASSERT_FALSE(bv1 == bv3);
}

/**
 * Test: operator!=()
 */
TEST_F(BitvectorTest, opNotEquals) {
	Bitvector bv1(8);
	bv1.setAll();
	Bitvector bv2(bv1);
	Bitvector bv3(12);

	ASSERT_FALSE(bv1 != bv2);
	ASSERT_TRUE(bv1 != bv3);
}

}















