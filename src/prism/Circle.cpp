/*
 * Circle.cpp
 * v0.1
 *
 *
 *  Created on: Jul 3, 2016
 *      Author: iainhemstock
 */

#include <prism/Circle>
#include <prism/Pointf>
#include <prism/Mathf>
#include <prism/Algorithms>
#include <cmath>
#include <iostream>

namespace prism {

using namespace prism;

/**
 * Creates a unit circle i.e. a circle with a radius of 1.
 */
Circle::Circle()
	: m_radius(1), m_x(0), m_y(0), m_angleMode(DEGREES)
{}

/**
 * Creates a circle with a radius of \em radius and its centre (x,y) set to 0.
 */
Circle::Circle(const float radius)
	: m_radius(radius), m_x(0), m_y(0), m_angleMode(DEGREES)
{}

/**
 * Creates a unit circle with a radius of 1 and its centre point set to \em (x,y).
 */
Circle::Circle(const float x, const float y)
	: m_radius(1), m_x(x), m_y(y), m_angleMode(DEGREES)
{}

/**
 * Creates a circle with a radius of \em radius and its centre point
 * set to \em (x,y).
 */
Circle::Circle(const float radius, const float x, const float y)
	: m_radius(radius), m_x(x), m_y(y), m_angleMode(DEGREES)
{}

/**
 * Creates a circle with a radius of \em radius and its centre point set to \em position.
 */
Circle::Circle(const float radius, const Pointf &position)
	: m_radius(radius), m_x(position.x()), m_y(position.y()), m_angleMode(DEGREES)
{}

/**
 * Creates a copy of the circle \em copy.
 */
Circle::Circle(const Circle &copy)
	: m_radius(copy.m_radius), m_x(copy.m_x), m_y(copy.m_y), m_angleMode(copy.m_angleMode)
{}

/**
* Destroys this circle
 */
Circle::~Circle() {}

/**
 * Returns the angle of the coordinate \em (x,y).\n
 * \note The angle will be expressed either in degrees or radians depending on
 * which mode is set in setAngleMode(). By default DEGREES mode is set.
 *
 * @return Returns the angle of the coordinate \em (x,y).
 * \image html circle_angle.png
 */
const float Circle::angle(const float x, const float y) const {
	// the inverse tangent of 'opposite' over 'adjacent' (soh cah TOA)
	return (m_angleMode == DEGREES)
			? atan2f(y,x) * 180/PI
			: atan2f(y,x);
}

/**
 * This is an overloaded function.\n
 * Returns the angle of the Pointf \em position.\n
 * \note The angle will be expressed either in degrees or radians depending on
 * which mode is set in setAngleMode(). By default DEGREES mode is set.
 *
 * @return Returns the angle of the Pointf \em position.
 */
const float Circle::angle(const Pointf &position) const {
	return angle(position.x(), position.y());
}

/**
 * @return Returns Circle::DEGREES or Circle::RADIANS depending on which mode is set.
 * By default a circle is set to DEGREES mode.
 */
Circle::AngleMode Circle::angleMode() const {
	return m_angleMode;
}

/**
 * An arc is the section of the circumference that sits between two points.\n
 * The major arc can be found by subtracting the minor arc length from the circumference.
 * @return Returns the length of the minor arc between the points \em p1 and \em p2.
 * \image html circle_arclength.png
 */
const float Circle::arcLength(const Pointf &p1, const Pointf &p2) const {
	float theta = centralAngle(p1,p2);

	if (m_angleMode == DEGREES) // degree formula
		return theta * (PI/180) * m_radius;
	else // radian formula
		return theta * m_radius;
}

/**
 * @return Returns the area of the circle.
 */
const float Circle::area() const {
	return PI * pow(m_radius, 2);
}

/**
 * @return Returns the y-coordinate of the bottom edge of the circle.
 */
const float Circle::bottom() const {
	return m_y+m_radius;
}

/**
 * @return Returns true if the circle contains (or is on the circumference)
 * the point \em (x,y), false otherwise.
 */
const bool Circle::contains(const float x, const float y) const {
	return this->contains(Pointf(x,y));
}

/**
 * This is an overloaded function.\n
 * @return Returns true if the circle contains (or is on the circumference)
 * the point \em position, false otherwise.
 */
const bool Circle::contains(const Pointf &position) const {
	Pointf p = position - this->centre();
	float x = p.x();
	float y = p.y();
	float distance = sqrt(x*x + y*y);

	return distance <= m_radius;
}

/**
 * This is an overloaded function.
 * @return Returns true if the circle contains (or is on the circumference)
 * the circle represented by \em otherCircle, false otherwise.
 */
const bool Circle::contains(const Circle &otherCircle) const {
	Pointf p = otherCircle.centre() - this->centre();
	float distance = sqrt(p.x()*p.x() + p.y()*p.y());

	return distance + otherCircle.radius() <= this->m_radius;
}

/**
 * @return Returns the circumference of the circle.
 */
const float Circle::circumference() const {
	return 2*PI*m_radius;
}

/**
 * A central angle is formed by two radii extending from the centre point
 * of the circle to the circumference.\n
 * The angle will be expressed either in degrees or radians depending on
 * which mode is set in setAngleMode(). By default DEGREES mode is set.
 * \note Note that the smallest angle will be returned and is always positive \n
 * i.e. if moving in one direction from point to point around the circle gives an angle of 270º and
 * moving in the opposite direction gives an angle of 90º then 90º is returned.\n
 *
 * @return Returns the central angle formed by two points on the circumference.
 * \image html circle_centralangle.png
 */
const float Circle::centralAngle(const Pointf &p1, const Pointf &p2) const {
	// uses the Law Of Cosines formula - c^2 = a^2 + b^2 - 2ab * cos(theta)
	// where a and b are the sides next to theta (the angle we are trying to find)
	// and also are radius of the circle.
	// Finally, c is the distance between the points p1 and p2.
	// So after calculating c we just solve for theta.

	Pointf p = p2-p1;
	float cLength = sqrt(pow(p.x(),2) + pow(p.y(),2));
	float cLengthSquared = pow(cLength, 2);
	float twoRadiusSquared = 2 * pow(m_radius, 2);

	float radianTheta = acosf((cLengthSquared - twoRadiusSquared) / twoRadiusSquared);
	float degreeTheta = radianTheta * (180 / PI);

	return (m_angleMode == DEGREES) ? 180-degreeTheta : PI-radianTheta;
}

/**
 * @return Returns a Pointf representing the centre point of the circle.
 */
Pointf Circle::centre() const {
	return Pointf(m_x, m_y);
}

/**
 * @return Returns the diameter of the circle.
 */
const float Circle::diameter() const {
	return 2*m_radius;
}

/**
 * Extracts the radius and centre x and y coordinates and assigns
 * them to \em radius, \em x and \em y.
 */
void Circle::getCircle(float *radius, float *x, float *y) {
	*radius = m_radius;
	*x = m_x;
	*y = m_y;
}

/**
 * @return Returns true if this circle intersects with \em otherCircle, false otherwise.
 */
const bool Circle::intersects(const Circle &otherCircle) const {
	Pointf p = otherCircle.centre() - this->centre();
	float distance = sqrt(p.x()*p.x() + p.y()*p.y());

	return distance < (this->m_radius + otherCircle.radius());
}

/**
 * A valid circle is one which has a radius larger than 0.
 * @return Returns true if the circle is valid, false otherwise.
 */
const bool Circle::isValid() const {
	return m_radius > 0;
}

/**
 * @return Returns the x-coordinate of the left edge of the circle.
 */
const float Circle::left() const {
	return m_x-m_radius;
}

/**
 * Moves the circle on the y-axis so that its bottom-most point sits at \em y.
 */
void Circle::moveBottom(const float y) {
	m_y = y-m_radius;
}

/**
 * Moves the centre point of the circle to \em (x,y).
 */
void Circle::moveCentre(const float x, const float y) {
	m_x = x;
	m_y = y;
}

/**
 * This is an overloaded function.\n
 * Moves the centre point of the circle to \em position.
 */
void Circle::moveCentre(const Pointf &position) {
	moveCentre(position.x(), position.y());
}

/**
 * Moves the circle on the x-axis so that its left-most point sits at \em x;
 */
void Circle::moveLeft(const float x) {
	m_x = x+m_radius;
}

/**
 * Moves the circle on the x-axis so that its right-most point sits at \em x;
 */
void Circle::moveRight(const float x) {
	m_x = x-m_radius;
}

/**
 * Moves the circle so that its top-most point sits at \em y.
 */
void Circle::moveTop(const float y) {
	m_y = y+m_radius;
}

/**
 * If a circle has a negative value for a radius it can be normalised so that
 * its radius is positive again by flipping the negative value to a positive one.
 * For e.g. a radius of -5 will become 5 after normalisation.
 * @return Returns a normalised copy of this circle.
 */
Circle Circle::normalised() const {
	Circle c(*this);

	if (m_radius < 0)
		c.setRadius(m_radius * -1);

	return c;
}

/**
 * @return Returns the (x,y) coordinate on the circumference at an angle of \em angle.
 * The angle argument can either be in degrees or radians depending on which mode is
 * set in setAngleMode().
 *
 * \image html circle_point.png
 */
Pointf Circle::point(const float angle) const {
	Pointf p;
	float theta = angle;

	if (m_angleMode == DEGREES)
		theta = angle*PI/180;

	p.setX((cos(theta) * m_radius) + m_x);
	p.setY((sin(theta) * m_radius) + m_y);

	return p;
}

/**
 * This calculates \em divisions amount of evenly spaced points around the circumference
 * in a clockwise direction. \n
 * For example, passing in 12 as the argument means that the
 * vector will contain 12 evenly spaced points exactly like the notches on a clock face.
 *
 * @return A vector containing \em divisions amount of points.
 * \image html circle_points.png
 */
prism::Vector<Pointf> Circle::points(const int divisions) const {

	prism::Vector<Pointf> v;
	v.reserve(divisions);

    float increment = 360 / divisions;
    float theta = 0;
    float px = 0;
    float py = 0;

    for (int i=0; i<divisions; i++) {
        px = (cos(theta*PI/180) * m_radius) + m_x;
        py = (sin(theta*PI/180) * m_radius) + m_y;
        theta += increment;

        v.push_back(Pointf(px, py));
    }

	return v;
}

/**
 * @return Returns the radius of the circle.
 */
const float Circle::radius() const {
	return m_radius;
}

/**
 * @return Returns the x-coordinate of the right edge of the circle.
 */
const float Circle::right() const {
	return m_x+m_radius;
}

/**
 * A sector visually is like a slice of pizza. Its base is the centre point of the circle with
 * two radii extending from the centre to the circumference.\n
 * The major sector area can be found by subtracting the area of the minor sector
 * from the total area of the circle.
 *
 * @return Returns the area of the minor sector formed by the centre point of the circle and points \em p1 and \em p2
 * located on the circumference.
 * \image html circle_sectorarea.png
 */
const float Circle::sectorArea(const Pointf &p1, const Pointf &p2) const {
	float theta = centralAngle(p1,p2);

	// degree formula
	if (m_angleMode == DEGREES)
		return theta/360 * PI * pow(m_radius,2);

	// radian formula
	return  theta/2 * pow(m_radius,2);
}

/**
 * A segment is formed by drawing a line (known as a chord) from one point on the circumference
 * to another point (effectively splitting the circle in two). \n
 * The area of the major segment can be found by subtracting the minor segment area
 * from the total area of the circle.
 *
 * @return Returns the area of the minor segment formed by the points \em p1 and \em p2. \n
 * \image html circle_segmentarea.png
 */
const float Circle::segmentArea(const Pointf &p1, const Pointf &p2) const {
	float theta = centralAngle(p1,p2);

	if (m_angleMode == DEGREES)
		theta = theta*PI/180; // converts theta from degrees to radians

	return pow(m_radius,2)/2 * (theta-sin(theta));
}

/**
 * Sets the angle mode of the circle to work with degrees or radians.
 * By default the circle is set to DEGREES mode.
 * The mode can be changed by passing in Circle::DEGREES or Circle::RADIANS.
 */
void Circle::setAngleMode(Circle::AngleMode mode) {
	m_angleMode = mode;
}

/**
 * Sets the radius to \em radius and positions the
 * centre of the circle at \em (x,y).
 */
void Circle::setCircle(const float radius, const float x, const float y) {
	m_radius = radius;
	m_x = x;
	m_y = y;
}

/**
 * This is an overloaded function.\n
 * Sets the radius to \em radius and positions the
 * centre of the circle at \em position.
 */
void Circle::setCircle(const float radius, const Pointf &position) {
	m_radius = radius;
	m_x = position.x();
	m_y = position.y();
}

/**
 * Sets the diameter of the circle to \em diameter.
 */
void Circle::setDiameter(const float diameter) {
	m_radius = diameter/2;
}

/**
 * Sets the radius of the circle to \em radius.
 */
void Circle::setRadius(const float radius) {
	m_radius = radius;
}

/**
 * Sets the centre of the circle to \em x in the x-axis.
 */
void Circle::setX(const float x) {
	m_x = x;
}

/**
 * Sets the centre of the circle to \em y in the y-axis.
 */
void Circle::setY(const float y) {
	m_y = y;
}

/**
 * @return Returns the y-coordinate of the top edge of the circle.
 */
const float Circle::top() const {
	return m_y-m_radius;
}

/**
 * Translates the circle relative to its current position
 * by \em dx on the x-axis and \em dy on the y-axis.
 */
void Circle::translate(const float dx, const float dy) {
	m_x += dx;
	m_y += dy;
}

/**
 * This is an overloaded function.\n
 * Translates the circle relative to its current position
 * by the amount of \em offset.
 */
void Circle::translate(const Pointf &offset) {
	translate(offset.x(), offset.y());
}

/**
 * @return Returns a copy of this circle which has been translated relative to
 * its current position by \em dx and \em dy.
 */
Circle Circle::translated(const float dx, const float dy) const {
	Circle c(*this);
	c.translate(dx, dy);
	return c;
}

/**
 * This is an overloaded function.\n
 * @return Returns a copy of this circle which has been translated relative to
 * its current position by \em offset.
 */
Circle Circle::translated(const Pointf &offset) const {
	Circle c(*this);
	c.translate(offset.x(), offset.y());
	return c;
}

/**
 * A unit circle is one which has a radius of 1.
 * @return Returns a copy of this circle which has been converted to a unit circle.
 * This does not affect the circle's position as it retains its (x,y) coordinates.
 */
Circle Circle::unit() const {
	if (m_radius == 1)
		return Circle(*this);

	Circle c(*this);
	c.setRadius(1);

	return c;
}

/**
 * @return Returns a new bounding circle that contains this circle
 * and \em otherCircle.
 */
Circle Circle::united(const Circle &otherCircle) const {

	Circle boundingCircle;
	boundingCircle.m_x = ((otherCircle.m_x - this->m_x) / 2) + this->m_x;
	boundingCircle.m_y = ((otherCircle.m_y - this->m_y) / 2) + this->m_y;

	Pointf p = otherCircle.centre() - boundingCircle.centre();
	float distance = sqrt(p.x()*p.x() + p.y()*p.y());

	boundingCircle.m_radius = distance + prism::max(this->m_radius, otherCircle.m_radius);

	return boundingCircle;
}

/**
 * @return Returns the centre of the circle in the x-axis.
 */
const float Circle::x() const {
	return m_x;
}

/**
 * @return Returns the centre of the circle in the y-axis.
 */
const float Circle::y() const {
	return m_y;
}

/**
 * Assigns \em other to this circle.
 */
Circle& Circle::operator =(const Circle &other) {
	m_radius = other.m_radius;
	m_x = other.m_x;
	m_y = other.m_y;
	m_angleMode = other.m_angleMode;

	return *this;
}

/* ========================================================
 * Related non-members
 * ======================================================*/
/**
 * @return Returns true if both circles have the same radius and (x,y) centre point, false otherwise.
 */
const bool operator==(const Circle &c1, const Circle &c2) {
	return c1.m_radius == c2.m_radius && c1.m_x == c2.m_x && c1.m_y == c2.m_y;
}

/**
 * @return Returns true if both circles are not equal, false otherwsie.
 */
const bool operator!=(const Circle &c1, const Circle &c2) {
	return !(c1==c2);
}

/**
 * @return Returns true if \em c1 has a smaller radius than \em c2, false otherwise.
 */
const bool operator<(const Circle &c1, const Circle &c2) {
	return c1.m_radius < c2.m_radius;
}

/**
 * @return Returns true if \em c1 has a greater radius than \em c2, false otherwise.
 */
const bool operator>(const Circle &c1, const Circle &c2) {
	return !(c1<c2);
}

/**
 * Allows an instance of Circle to be written to the ostream and returns a reference to the ostream.
 */
std::ostream& operator<<(std::ostream &out, const Circle &c) {
	out << "Circle [" << &c << "]: radius=" << c.m_radius << ", centreX=" << c.m_x << ", centreY=" << c.m_y;
	return out;
}

} /* namespace prism */