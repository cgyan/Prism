/*
 * SharedDataPointerTest.cpp
 * v0.*
 *
 *  Created on: Aug 13, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/SharedDataPointer>
#include <prism/SharedData>
#include <iostream>
using namespace std;

namespace prism {
namespace test {

class SharedDataPointerTest : public ::testing::Test {

};

class Dummy : public SharedData {
private:
	int m_index;
public:
//	~Dummy() { cout << "Dummy destructing!" << endl; }
	void setIndex(const int i) { m_index = i; }
	const int index() const { return m_index; }
};

/**
 * Test: constructor
 */
TEST_F(SharedDataPointerTest, constructor) {
	SharedDataPointer<Dummy> p;
	ASSERT_TRUE(p.isNull());
	ASSERT_TRUE(p.data() == 0);
	ASSERT_TRUE(p.constData() == 0);
	ASSERT_FALSE(p.isShareable());
	ASSERT_FALSE(p.isShared());
	ASSERT_EQ(p.refCount(), 0);
}

/**
 * Test: constructor_pointer_arg
 */
TEST_F(SharedDataPointerTest, constructor_pointer_arg)
{
	Dummy * pd = new Dummy;
	SharedDataPointer<Dummy> p(pd);

	ASSERT_FALSE(p.isNull());
	ASSERT_TRUE(p.data() == pd);
	ASSERT_TRUE(p.constData() == pd);
	ASSERT_TRUE(p.isShareable());
	ASSERT_FALSE(p.isShared());
	ASSERT_EQ(p.refCount(), 1);
}

/**
 * Test: constData()
 */
TEST_F(SharedDataPointerTest, constData)
{
	Dummy * pd = new Dummy;
	SharedDataPointer<Dummy> p(pd);

	ASSERT_TRUE(p.constData() == pd);
}

/**
 * Test: data()
 */
TEST_F(SharedDataPointerTest, data)
{
	Dummy * pd = new Dummy;
	SharedDataPointer<Dummy> p(pd);

	ASSERT_TRUE(p.data() == pd);
}

/**
 * Test: detach()
 */
TEST_F(SharedDataPointerTest, detach)
{
	SharedDataPointer<Dummy> p1(new Dummy);
	SharedDataPointer<Dummy> p2 = p1;

	p1->setIndex(10);

	ASSERT_TRUE(p1->index() == 10);
	ASSERT_TRUE(p2->index() == 10);

	p1.detach();
	p1->setIndex(1234);

	ASSERT_TRUE(p1->index() == 1234);
	ASSERT_TRUE(p2->index() == 10);
}

/**
 * Test: isNull()
 */
TEST_F(SharedDataPointerTest, isNull)
{
	SharedDataPointer<Dummy> p1;
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_TRUE(p1.isNull());

	p1 = p2;

	ASSERT_FALSE(p1.isNull());
	ASSERT_FALSE(p2.isNull());

}

/**
 * Test: isShareable()
 */
TEST_F(SharedDataPointerTest, isShareable)
{
	SharedDataPointer<Dummy> p1;
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_FALSE(p1.isShareable());

	p1 = p2;

	ASSERT_TRUE(p1.isShareable());

	p1.setUnshareable();

	ASSERT_FALSE(p1.isShareable());
}

/**
 * Test: isShared()
 */
TEST_F(SharedDataPointerTest, isShared)
{
	SharedDataPointer<Dummy> p1;
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_FALSE(p1.isShared());

	p1 = p2;

	ASSERT_TRUE(p1.isShared());

	p1.setUnshareable();

	ASSERT_FALSE(p1.isShareable());
}

/**
 * Test: refCount()
 */
TEST_F(SharedDataPointerTest, refCount)
{
	SharedDataPointer<Dummy> p1(new Dummy);
	ASSERT_EQ(p1.refCount(), 1);

	SharedDataPointer<Dummy> p2 = p1;
	ASSERT_EQ(p1.refCount(), 2);
	ASSERT_EQ(p2.refCount(), 2);

	p1.detach();
	ASSERT_EQ(p1.refCount(), 1);
	ASSERT_EQ(p2.refCount(), 1);

}

/**
 * Test: setUnshareable()
 */
TEST_F(SharedDataPointerTest, setUnshareable)
{
	SharedDataPointer<Dummy> p(new Dummy);
	ASSERT_TRUE(p.isShareable());

	p.setUnshareable();
	ASSERT_FALSE(p.isShareable());
}

/**
 * Test: operator!()
 */
TEST_F(SharedDataPointerTest, opNot)
{
	SharedDataPointer<Dummy> p1;
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_TRUE(!p1);

	p1 = p2;
	ASSERT_FALSE(!p1);
}

/**
 * Test: operator!=()
 */
TEST_F(SharedDataPointerTest, opNotEquals)
{
	SharedDataPointer<Dummy> p1(new Dummy);
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_TRUE(p1 != p2);

	SharedDataPointer<Dummy> p3 = p2;

	ASSERT_FALSE(p3 != p2);
}

/**
 * Test: operator==()
 */
TEST_F(SharedDataPointerTest, opEqualsEquals)
{
	SharedDataPointer<Dummy> p1(new Dummy);
	SharedDataPointer<Dummy> p2(new Dummy);

	ASSERT_FALSE(p1 == p2);

	SharedDataPointer<Dummy> p3 = p2;

	ASSERT_TRUE(p3 == p2);
}

} // end namespace test
} // end namespace prism







