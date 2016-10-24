/*
 * VersionTest.cpp
 * v1
 *
 *  Created on: Oct 13, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/Version>

namespace prism {
namespace test {

class VersionTest : public ::testing::Test {

};

/**
 * Test: Version()
 */
TEST_F(VersionTest, defaultCtor) {
	Version v;

	ASSERT_TRUE(v.major() == 0);
	ASSERT_TRUE(v.minor() == 0);
	ASSERT_TRUE(v.patch() == 0);
	ASSERT_TRUE(v.name() == "");
	ASSERT_EQ(v.string(), "0.0.0");
}

/**
 * Test: Version(maj)
 */
TEST_F(VersionTest, ctor_maj) {
	Version v(1);

	ASSERT_TRUE(v.major() == 1);
	ASSERT_TRUE(v.minor() == 0);
	ASSERT_TRUE(v.patch() == 0);
	ASSERT_TRUE(v.name() == "");
	ASSERT_EQ(v.string(), "1.0.0");
}

/**
 * Test: Version(maj, min)
 */
TEST_F(VersionTest, ctor_maj_min) {
	Version v(1,2);

	ASSERT_TRUE(v.major() == 1);
	ASSERT_TRUE(v.minor() == 2);
	ASSERT_TRUE(v.patch() == 0);
	ASSERT_TRUE(v.name() == "");
	ASSERT_EQ(v.string(), "1.2.0");
}

/**
 * Test: Version(maj, min, patch)
 */
TEST_F(VersionTest, ctor_maj_min_patch) {
	Version v(1,2,3);

	ASSERT_TRUE(v.major() == 1);
	ASSERT_TRUE(v.minor() == 2);
	ASSERT_TRUE(v.patch() == 3);
	ASSERT_TRUE(v.name() == "");
	ASSERT_EQ(v.string(), "1.2.3");
}

/**
 * Test: Version(maj, min, patch, name)
 */
TEST_F(VersionTest, ctor_maj_min_patch_name) {
	Version v(1,2,3,"alpha");

	ASSERT_TRUE(v.major() == 1);
	ASSERT_TRUE(v.minor() == 2);
	ASSERT_TRUE(v.patch() == 3);
	ASSERT_TRUE(v.name() == "alpha");
	ASSERT_EQ(v.string(), "1.2.3.alpha");
}

/**
 * Test: Version(copy)
 */
TEST_F(VersionTest, ctor_copy) {
	Version v(1,2,3,"alpha");
	Version copy(v);

	ASSERT_TRUE(copy.major() == 1);
	ASSERT_TRUE(copy.minor() == 2);
	ASSERT_TRUE(copy.patch() == 3);
	ASSERT_TRUE(copy.name() == "alpha");
	ASSERT_EQ(copy.string(), "1.2.3.alpha");
}

/**
 * Test: operator=(rhs)
 */
TEST_F(VersionTest, op_assignment) {
	Version v(1,2,3,"alpha");
	Version copy = v;

	ASSERT_TRUE(copy.major() == 1);
	ASSERT_TRUE(copy.minor() == 2);
	ASSERT_TRUE(copy.patch() == 3);
	ASSERT_TRUE(copy.name() == "alpha");
	ASSERT_EQ(copy.string(), "1.2.3.alpha");
}

/**
 * Test: major()
 */
TEST_F(VersionTest, major) {
	Version v(1,2,3,"alpha");

	ASSERT_TRUE(v.major() == 1);
	ASSERT_FALSE(v.minor() == 1);
	ASSERT_FALSE(v.patch() == 1);
}

/**
 * Test: minor()
 */
TEST_F(VersionTest, minor) {
	Version v(1,2,3,"alpha");

	ASSERT_TRUE(v.minor() == 2);
	ASSERT_FALSE(v.major() == 2);
	ASSERT_FALSE(v.patch() == 2);
}

/**
 * Test: patch()
 */
TEST_F(VersionTest, patch) {
	Version v(1,2,3,"alpha");

	ASSERT_TRUE(v.patch() == 3);
	ASSERT_FALSE(v.major() == 3);
	ASSERT_FALSE(v.minor() == 3);
}

/**
 * Test: name()
 */
TEST_F(VersionTest, name) {
	Version v(1,2,3,"alpha");
	ASSERT_TRUE(v.name() == "alpha");
}

/**
 * Test: string()
 */
TEST_F(VersionTest, string) {
	Version v(1,2,3,"alpha");
	ASSERT_TRUE(v.string() == "1.2.3.alpha");
}

/**
 * Test: operator==()
 */
TEST_F(VersionTest, op_equality) {
	Version v(1,2,3,"alpha");
	Version v2(1,2,3,"alpha");
	Version v3(3,2,1,"beta");

	ASSERT_TRUE(v == v2);
	ASSERT_FALSE(v == v3);
}

/**
 * Test: operator!=()
 */
TEST_F(VersionTest, op_inequality) {
	Version v(1,2,3,"alpha");
	Version v2(1,2,3,"alpha");
	Version v3(3,2,1,"beta");

	ASSERT_FALSE(v != v2);
	ASSERT_TRUE(v != v3);
}

/**
 * Test: operator<()
 */
TEST_F(VersionTest, op_less) {
	Version v(1,2,3,"alpha");
	Version v2(1,2,3,"alpha");
	Version v3(3,2,3,"alpha");

	ASSERT_FALSE(v < v2);
	ASSERT_TRUE(v < v3);
}

/**
 * Test: operator<=()
 */
TEST_F(VersionTest, op_lessEqual) {
	Version v(1,1,1);
	Version v2(1,1,2);
	Version v3(1,2,2);
	Version v4(2,2,2);
	Version v5(1,1,1);

	ASSERT_TRUE(v <= v2);
	ASSERT_TRUE(v <= v3);
	ASSERT_TRUE(v <= v4);
	ASSERT_TRUE(v <= v5);

	ASSERT_FALSE(v2 <= v);
	ASSERT_FALSE(v3 <= v);
	ASSERT_FALSE(v4 <= v);
}

/**
 * Test: operator>()
 */
TEST_F(VersionTest, op_greater) {
	Version v(1,1,1,"alpha");
	Version v2(1,1,2,"alpha");
	Version v3(1,2,2,"alpha");

	ASSERT_TRUE(v3 > v2);
	ASSERT_TRUE(v3 > v);
}

/**
 * Test: operator>=()
 */
TEST_F(VersionTest, op_greaterEqual) {
	Version v(1,1,1);
	Version v2(1,1,2);
	Version v3(1,2,2);
	Version v4(2,2,2);
	Version v5(1,1,1);

	ASSERT_FALSE(v >= v2);
	ASSERT_FALSE(v >= v3);
	ASSERT_FALSE(v >= v4);

	ASSERT_TRUE(v >= v5);
	ASSERT_TRUE(v2 >= v);
	ASSERT_TRUE(v3 >= v);
	ASSERT_TRUE(v4 >= v);
}

} // end namespace test
} // end namespace prism















