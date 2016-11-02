/*
 * CircleTest.cpp
 * v1
 *
 *  Created on: Oct 29, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/Circle>
#include <prism/Pointf>

namespace prism {
namespace test {

class CircleTest : public ::testing::Test {
protected:
	Circle defaultCircle;
};

/**
 * Test: Circle()
 */
TEST_F(CircleTest, ctor) {
	ASSERT_EQ(1, defaultCircle.radius());
	ASSERT_EQ(0, defaultCircle.x());
	ASSERT_EQ(0, defaultCircle.y());
	ASSERT_EQ(Circle::DEGREES, defaultCircle.angleMode());
}

/**
 * Test: ctor(radius)
 */
TEST_F(CircleTest, ctor_radius) {
	Circle c(10);

	ASSERT_EQ(10, c.radius());
	ASSERT_EQ(0, c.x());
	ASSERT_EQ(0, c.y());
	ASSERT_EQ(Circle::DEGREES, c.angleMode());
}

/**
 * Test: ctor(x,y)
 */
TEST_F(CircleTest, ctor_x_y) {
	Circle c(20,30);

	ASSERT_EQ(1, c.radius());
	ASSERT_EQ(20, c.x());
	ASSERT_EQ(30, c.y());
	ASSERT_EQ(Circle::DEGREES, c.angleMode());
}

/**
 * Test: ctor(radius,x,y)
 */
TEST_F(CircleTest, ctor_radius_x_y) {
	Circle c(100,20,30);

	ASSERT_EQ(100, c.radius());
	ASSERT_EQ(20, c.x());
	ASSERT_EQ(30, c.y());
	ASSERT_EQ(Circle::DEGREES, c.angleMode());
}

/**
 * Test: ctor(radius,position)
 */
TEST_F(CircleTest, ctor_radius_position) {
	Circle c(100,Pointf(20,30));

	ASSERT_EQ(100, c.radius());
	ASSERT_EQ(20, c.x());
	ASSERT_EQ(30, c.y());
	ASSERT_EQ(Circle::DEGREES, c.angleMode());
}

/**
 * Test: Circle(copy)
 */
TEST_F(CircleTest, copy_ctor) {
	Circle a(10,50,55);
	Circle b(a);

	// check a hasn't been modified
	ASSERT_EQ(10, a.radius());
	ASSERT_EQ(50, a.x());
	ASSERT_EQ(55, a.y());

	ASSERT_EQ(10, b.radius());
	ASSERT_EQ(50, b.x());
	ASSERT_EQ(55, b.y());
}

/**
 * Test: angle()
 */
TEST_F(CircleTest, angle) {
	Circle c;

	int angle = c.angle(1,0);
	ASSERT_EQ(0, angle);

	angle = c.angle(0,1);
	ASSERT_EQ(90, angle);

	angle = c.angle(-1,0);
	ASSERT_EQ(180, angle);

	angle = c.angle(0,-1);
	ASSERT_EQ(-90, angle);
}

/**
 * Test: angle(point
 */
TEST_F(CircleTest, angle_point) {
	Circle c;

	int angle = c.angle(Pointf(1,0));
	ASSERT_EQ(0, angle);

	angle = c.angle(Pointf(0,1));
	ASSERT_EQ(90, angle);

	angle = c.angle(Pointf(-1,0));
	ASSERT_EQ(180, angle);

	angle = c.angle(Pointf(0,-1));
	ASSERT_EQ(-90, angle);
}

/**
 * Test: angleMode()
 */
TEST_F(CircleTest, angleMode) {
	ASSERT_EQ(Circle::DEGREES, defaultCircle.angleMode());
}

/**
 * Test: arcLength()
 */
TEST_F(CircleTest, arcLength) {
	Pointf p1(1,0);
	Pointf p2(0,1);
	float arcLength = defaultCircle.arcLength(p1,p2);

	ASSERT_FLOAT_EQ(1.5707939, arcLength);
}

/**
 * Test: area()
 */
TEST_F(CircleTest, area) {
	ASSERT_FLOAT_EQ(3.1415901, defaultCircle.area());
}

/**
 * Test: bottom()
 */
TEST_F(CircleTest, bottom) {
	// x and y == 0, radius == 10
	Circle c(10);
	ASSERT_EQ(10, c.bottom());

	// x and y == 50, radius == 10
	Circle d(10, Pointf(50,50));
	ASSERT_EQ(60, d.bottom());

}

/**
 * Test: centralAngle()
 */
TEST_F(CircleTest, centralAngle) {
	Circle c;
	Pointf x(1,0);
	Pointf y(0,1);

	// degrees
	ASSERT_EQ(90, c.centralAngle(x,y));

	// radians
	c.setAngleMode(Circle::RADIANS);
	ASSERT_EQ(Circle::PI/2, c.centralAngle(x,y));
}

/**
 * Test: centre()
 */
TEST_F(CircleTest, centre) {
	ASSERT_EQ(Pointf(0,0), defaultCircle.centre());

	Circle c(100,50); // x=100, y=50
	ASSERT_EQ(Pointf(100,50), c.centre());
}

} // end namespace test
} // end namespace prism















