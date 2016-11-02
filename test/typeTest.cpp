/*
 * typeTest.cpp
 * v1
 *
 *  Created on: Nov 2, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/type>

namespace prism {
namespace test {

class typeTest : public ::testing::Test {

};

/*
 * Test: conditional_type<>
 * -- using two fundamental types
 */
TEST_F(typeTest, conditional_type_fundamental) {
	typedef int	T1;
	typedef char T2;
	typename prism::conditional_type<true, T1, T2>::type IntType;
	typename prism::conditional_type<false, T1, T2>::type CharType;

	ASSERT_TRUE(typeid(IntType) 	== typeid(int));
	ASSERT_TRUE(typeid(CharType) 	== typeid(char));
	ASSERT_FALSE(typeid(CharType) 	== typeid(int));
	ASSERT_FALSE(typeid(IntType) 	== typeid(char));
}

/*
 * Test: conditional_type<>
 * -- using two non member pointer types
 */
TEST_F(typeTest, conditional_type_nonmember_pointers) {
	typedef int* T1;
	typedef char* T2;
	typename prism::conditional_type<true,T1,T2>::type IntPtrType;
	typename prism::conditional_type<false,T1,T2>::type CharPtrType;

	ASSERT_TRUE(typeid(IntPtrType) == typeid(int*));
	ASSERT_TRUE(typeid(CharPtrType) == typeid(char*));
	ASSERT_FALSE(typeid(CharPtrType) == typeid(int*));
	ASSERT_FALSE(typeid(IntPtrType) == typeid(char*));
}

/*
 * Test: conditional_type<>
 * -- using two union types
 */
TEST_F(typeTest, conditional_type_unions) {
	union U1 {};
	union U2 {};
	typename prism::conditional_type<true,U1,U2>::type UType1;
	typename prism::conditional_type<false,U1,U2>::type UType2;

	ASSERT_TRUE(typeid(UType1) == typeid(U1));
	ASSERT_TRUE(typeid(UType2) == typeid(U2));
	ASSERT_FALSE(typeid(UType2) == typeid(U1));
	ASSERT_FALSE(typeid(UType1) == typeid(U2));
}

/*
 * Test: conditional_type<>
 * -- using two enum types
 */
TEST_F(typeTest, conditional_type_enums) {
	enum E1 {};
	enum E2 {};
	typename prism::conditional_type<true,E1,E2>::type EType1;
	typename prism::conditional_type<false,E1,E2>::type EType2;

	ASSERT_TRUE(typeid(EType1) == typeid(E1));
	ASSERT_TRUE(typeid(EType2) == typeid(E2));
	ASSERT_FALSE(typeid(EType2) == typeid(E1));
	ASSERT_FALSE(typeid(EType1) == typeid(E2));
}

/*
 * Test: conditional_type<>
 * -- using two member pointer types
 * -- TMemPtr and UMemPtr are pointer types to member functions (T::x() and
 * -- U::x() respectively).
 */
TEST_F(typeTest, conditional_type_member_pointers) {
	class T { public: int x() {return 1;}; };
	class U { public: int x() {return 2;}; };
	typedef int (T::*TMemPtr)(void);
	typedef int (U::*UMemPtr)(void);
	T t;
	U u;

	typedef typename prism::conditional_type<true,TMemPtr,UMemPtr>::type P1;
	typedef typename prism::conditional_type<false,TMemPtr,UMemPtr>::type P2;

	P1 p1 = &T::x; // p1 == pointer to member function T::x()
	P2 p2 = &U::x; // p2 == pointer to member function U::x()

	ASSERT_EQ(1, (t.*p1)());
	ASSERT_EQ(2, (u.*p2)());
	ASSERT_TRUE(typeid(TMemPtr) == typeid(P1));
	ASSERT_TRUE(typeid(UMemPtr) == typeid(P2));
	ASSERT_FALSE(typeid(UMemPtr) == typeid(P1));
	ASSERT_FALSE(typeid(TMemPtr) == typeid(P2));
}

/*
 * Test: conditional_type<>
 * -- using two array types
 */
TEST_F(typeTest, conditional_type_arrays) {
	typedef prism::conditional_type<true, char[1],int[1]>::type CharArrayType;
	typedef prism::conditional_type<false, char[1],int[1]>::type IntArrayType;

	// CharTypeArray holds 1 char so should be the size of 1 char
	// IntTypeArray holds 1 int so should be the size of 1 int
	ASSERT_EQ(sizeof(CharArrayType), sizeof(char));
	ASSERT_EQ(sizeof(IntArrayType), sizeof(int));
}

} // end namespace test
} // end namespace prism













