/*
 * Rect.cpp
 * v0.1
 *
 *  Created on: Jul 1, 2016
 *      Author: iainhemstock
 */

#include <prism/Rect>
#include <prism/Size>
#include <prism/Point>
#include <iostream>
#include <cmath>
#include <prism/Algorithms>

namespace prism {

/**
 * Creates a rectangle with x=y=width=height=0.
 * \em isEmpty() and \em isNull() will return true in this state whilst
 * \em isValid() will return false.
 */
Rect::Rect()
	: x1(0), y1(0), x2(0), y2(0)
{}

/**
 * Creates a rectangle positioning the top left corner at (x,y) and
 * having \em width and \em height.
 */
Rect::Rect(const int x, const int y, const int width, const int height)
	: x1(x), y1(y), x2(x+width), y2(y+height)
{}

/**
 * Creates a rectangle positioning its top left corner at \em topLeft
 * and its bottom right corner positioned at \em bottomRight.
 */
Rect::Rect(const Point &topLeft, const Point &bottomRight)
	: x1(topLeft.x()), y1(topLeft.y()), x2(bottomRight.x()), y2(bottomRight.y())
{}

/**
 * Creates a rectangle positioning its top left corner at \em topLeft
 * and its width and height set to \em size.
 */
Rect::Rect(const Point &topLeft, const Size &size)
	: x1(topLeft.x()), y1(topLeft.y()), x2(x1+size.width()), y2(y1+size.height())
{}

/**
 * Copy constructor makes a copy of \em copy.
 */
Rect::Rect(const Rect &copy)
	: x1(copy.x1), y1(copy.y1), x2(copy.x2), y2(copy.y2)
{}

/**
 * Destroys the rectangle.
 */
Rect::~Rect() {}

/**
 * Adds dx1, dy1, dx2 and dy2 to the existing coordinates of the rectangle.
 */
void Rect::adjust(const int dx1, const int dy1, const int dx2, const int dy2) {
	this->x1 += dx1;
	this->y1 += dy1;
	this->x2 += dx2;
	this->y2 += dy2;
}

/**
 * Returns a copy of this rectangle which has added dx1, dy1, dx2 and dy2
 * to the existing coordinates of the rectangle.
 */
Rect Rect::adjusted(const int dx1, const int dy1, const int dx2, const int dy2) const {
	Rect r(*this);
	r.adjust(dx1, dy1, dx2, dy2);

	return r;
}

/**
 * Returns the y-coordinate of the rectangle's bottom edge.
 */
const int Rect::bottom() const {
	return y2;
}

/**
 * Returns the coordinate of the bottom left of the rectangle.
 */
Point Rect::bottomLeft() const {
	return Point(x1, y2);
}

/**
 * Returns the coordinate of the bottom right of the rectangle.
 */
Point Rect::bottomRight() const {
	return Point(x2, y2);
}

/**
 * Returns the coordinate of the centre point of the rectangle.
 */
Point Rect::centre() const {
	return Point((x2-x1)/2+x1, (y2-y1)/2+y1);
}

/**
 * Returns true if \em point is within or on the rectangle's boundary, false otherwise.
 */
const bool Rect::contains(const Point &point) const {
	if (point.x() >= left() && point.x() <= right()
			&& point.y() >= top() && point.y() <= bottom()) {
		return true;
	}
	return false;
}



/**
 * Returns true if (x,y) is within or on the rectangle's boundary, false otherwise.
 */
const bool Rect::contains(const int x, const int y) const {
	return contains(Point(x,y));
}

/**
 * Returns true if \em rect is contained within or on the rectangle's boundary, false otherwise.
 */
const bool Rect::contains(const Rect &rect) const {
	if (rect.left() >= left() && rect.right() <= right()
			&& rect.top() >= top() && rect.bottom() <= bottom()) {
		return true;
	}
	return false;
}

/**
 * Extracts the coordinates of the rectangle and assigns them to
 * (x1,y1)(x2,y2).
 */
void Rect::getCoordinates(int *x1, int *y1, int *x2, int *y2) const {
	*x1 = this->x1;
	*y1 = this->y1;
	*x2 = this->x2;
	*y2 = this->y2;
}

/**
 * Extracts the top left corner coordinates and width and height of this
 * rectangle and assigns them to (x,y) and \em width and \em height.
 */
void Rect::getRect(int *x, int *y, int *width, int *height) const {
	*x = this->left();
	*y = this->top();
	*width = this->width();
	*height = this->height();
}

/**
 * Returns the height of the rectangle.
 */
const int Rect::height() const {
	return y2-y1;
}

/**
 * Returns a rectangle that represents the overlapping portion
 * of this rectangle and \em rect. If the two rectangles are not
 * intersected then this rectangle is returned instead.
 */
Rect Rect::intersected(const Rect &rect) const {
	Rect r;

	if (this->intersects(rect)) {

		int nleft = prism::max(left(),rect.left());
		int nright = prism::min(right(),rect.right());
		int nbottom = prism::min(bottom(),rect.bottom());
		int ntop = prism::max(top(),rect.top());

		r.setLeft(nleft);
		r.setRight(nright);
		r.setBottom(nbottom);
		r.setTop(ntop);

		return r;
	}

	return r = *this;
}

/**
 * Returns true if \em rect intersects this rectangle, false otherwise.
 * Note that a rectangle must intersect by at least 1 pixel in order for it
 * to be considered intersecting. Edges that sit on top of each are not
 * considered to be intersecting.
 */
const bool Rect::intersects(const Rect &rect) const {
	if (left() < rect.right() && right() > rect.left() &&
			top() < rect.bottom() && bottom() > rect.top()) {
		return true;
	}
	return false;
}

/**
 * An empty rectangle is one where its width or height (or both) are zero or less.
 * Returns true if it is an empy rectangle, false otherwise.
 */
const bool Rect::isEmpty() const {
	return (x2-x1) < 1 || (y2-y1) < 1;
}

/**
 * A null rectangle is one where the width and height are both equal to zero.
 * Returns true if it is a null rectangle, false otherwise.
 */
const bool Rect::isNull() const {
	return (x2-x1) == 0 && (y2-y1) == 0;
}

/**
 * A valid rectangle is one where its width and height are at least 1 or greater.
 * Returns true if this is a valid rectangle, false otherwise.
 */
const bool Rect::isValid() const {
	return x2>x1 && y2>y1;
}

/**
 * Returns the x-coordinate of the rectangle's left edge.
 */
const int Rect::left() const {
	return x1;
}

/**
 * Moves the rectangle downwards so that its bottom edge is positioned at \em y.
 * This does not affect the width and height.
 */
void Rect::moveBottom(const int y) {
	int distance = y-y2;
	y1+=distance;
	y2+=distance;
}

/**
 *
 */
void Rect::moveBottomLeft(const Point &position) {
	moveLeft(position.x());
	moveBottom(position.y());
}

/**
 *
 */
void Rect::moveBottomRight(const Point &position) {
	moveRight(position.x());
	moveBottom(position.y());
}

/**
 * Moves the rectangle placing its centre at (x,y).
 * This does not affect the width and height.
 */
void Rect::moveCentre(const int x, const int y) {
	moveCentre(Point(x,y));
}

/**
 * Moves the rectangle placing its centre point at \em position.
 * This does not affect the width and height.
 */
void Rect::moveCentre(const Point &position) {
	int w = width();
	int h = height();

	x1 = position.x() - w/2;
	y1 = position.y() - h/2;
	x2 = (position.x() + w) - (w/2);
	y2 = (position.y() + h) - h/2;
}

/**
 * Moves the rectangle to the left so that its left edge is positioned at \em x.
 * This does not affect the width and height.
 */
void Rect::moveLeft(const int x) {
	int distance = x1-x;
	x1-=distance;
	x2-= distance;
}

/**
 * Moves the rectangle to the right so that its right edge is positioned at \em x.
 * This does not affect the width and height.
 */
void Rect::moveRight(const int x) {
	int distance = x-x2;
	x1+=distance;
	x2+=distance;
}

/**
 * Moves the rectangle so that its top left corner will be located at (x,y).
 * The width and height will still be the same as before the rectangle was moved.
 */
void Rect::moveTo(const int x, const int y) {
	moveTo(Point(x,y));
}

/**
 * Moves the rectangle so that its top left corner will be located at \em position.
 * The width and height will still be the same as before the rectangle was moved.
 */
void Rect::moveTo(const Point &position) {
	int w = x2-x1;
	int h = y2-y1;

	x1 = position.x();
	y1 = position.y();
	x2 = x1+w;
	y2 = y1+h;
}

/**
 * Moves the rectangle upwards so that its top edge is positioned at \em y.
 * This does not affect the width and height.
 */
void Rect::moveTop(const int y) {
	int distance = y1-y;
	y1-=distance;
	y2-= distance;
}

/**
 * Moves the rectangle so that its top left corner is positioned at \em position.
 * This does not affect the width and height.
 */
void Rect::moveTopLeft(const Point &position) {
	moveLeft(position.x());
	moveTop(position.y());
}

/**
 * Moves the rectangle so that its top right corner is positioned at \em position.
 * This does not affect the width and height.
 */
void Rect::moveTopRight(const Point &position) {
	moveRight(position.x());
	moveTop(position.y());
}

/**
 * If a rectangle has a negative width or height it can normalised by
 * swapping the left and right edges around and/or the top and bottom edges around as necessary.
 * Returns a new normalised rectangle.
 */
Rect Rect::normalised() const {
	Rect r(*this);

	if (width() < 0) {
		int temp = r.x1;
		r.x1 = r.x2;
		r.x2 = temp;
	}
	if (height() < 0) {
		int temp = y1;
		r.y1 = r.y2;
		r.y2 = temp;
	}

	return r;
}

/**
 * Returns the x-coordinate of the rectangle's right edge.
 */
const int Rect::right() const {
	return x2;
}

/**
 * Sets the bottom edge of the rectangle to \em y which will potentially
 * affect the overall height but will not effect the top edge in any way.
 */
void Rect::setBottom(const int y) {
	y2 = y;
}

/**
 * Sets the bottom left corner of the rectangle to \em bottomLeft.
 * It may change the width and height of the rectangle
 * but the top right corner will not move.
 */
void Rect::setBottomLeft(const Point &position) {
	x1 = position.x();
	y2 = position.y();
}

/**
 * Sets the bottom right corner of the rectangle to \em bottomRight.
 * It may change the width and height of the rectangle
 * but the top left corner will not move.
 */
void Rect::setBottomRight(const Point &position) {
	x2 = position.x();
	y2 = position.y();
}

/**
 * Sets the coordinates of this rectangle's top left corner to (x1,y1)
 * and the bottom right corner to (x2,y2).
 */
void Rect::setCoordinates(const int x1, const int y1, const int x2, const int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

/**
 * Sets the height of the rectangle.
 */
void Rect::setHeight(const int height) {
	y2 = y1 + height;
}

/**
 * Sets the left side of the rectangle to \em x which will potentially
 * alter the width of the rectangle but will not affect the right edge in any way.
 */
void Rect::setLeft(const int x) {
	x1 = x;
}

/**
 *
 */
void Rect::setRect(const int x, const int y, const int width, const int height) {
	x1 = x;
	y1 = y;
	x2 = x1+width;
	y2 = y1+height;
}

/**
 * Sets the right side of the rectangle to \em x which will potentially
 * alter the width of the rectangle but will not affect the left edge in any way.
 */
void Rect::setRight(const int x) {
	x2 = x;
}

/**
 * Sets the rectangle's size to \em size.
 */
void Rect::setSize(const Size &size) {
	x2 = x1+size.width();
	y2 = y1+size.height();
}

/**
 * Sets the top edge of the rectangle to \em y which will potentially
 * affect the height of the rectangle but will not affect the bottom edge in any way.
 */
void Rect::setTop(const int y) {
	y1 = y;
}

/**
 * Sets the top left corner of the rectangle to \em topLeft.
 * It may change the width and height of the rectangle
 * but the bottom right corner will not move.
 */
void Rect::setTopLeft(const Point &position) {
	x1 = position.x();
	y1 = position.y();
}

/**
 * Sets the top right corner of the rectangle to \em topRight.
 * It may change the width and height of the rectangle
 * but the bottom left corner will not move.
 */
void Rect::setTopRight(const Point &position) {
	x2 = position.x();
	y1 = position.y();
}

/**
 * Sets the x-coordinate of the rectangle.
 */
void Rect::setX(const int x) {
	x1 = x;
}

/**
 * Sets the y-coordinate of the rectangle.
 */
void Rect::setY(const int y) {
	y1 = y;
}

/**
 * Sets the width of the rectangle.
 */
void Rect::setWidth(const int width) {
	x2 = x1+width;
}

/**
 * Returns a Size object representing the size of this rectangle.
 */
Size Rect::size() const {
	return Size(x2-x1, y2-y1);
}

/**
 * Returns the y-coordinate of the rectangle's top edge.
 */
const int Rect::top() const {
	return y1;
}

/**
 * Returns the top left coordinate of the rectangle.
 */
Point Rect::topLeft() const {
	return Point(x1,y1);
}

/**
 * Returns the coordinate of the top right of the rectangle.
 */
Point Rect::topRight() const {
	return Point(x2,y1);
}

/**
 * Translates the rectangle relative to its current position
 * by the amount of \em dx on the x-axis and by the amount of
 * \em dy on the y-axis.
 */
void Rect::translate(const int dx, const int dy) {
	x1+=dx;
	y1+=dy;
	x2+=dx;
	y2+=dy;
}

/**
 * Translates the rectangle relative to its current position
 * by the amount of \em offset.
 */
void Rect::translate(const Point &offset) {
	x1+=offset.x();
	y1+=offset.y();
	x2+=offset.x();
	y2+=offset.y();
}

/**
 * Returns a copy of this rectangle that has been translated relative
 * to its current position by the amount of \em dx on the x-axis and
 * by the amount of dy on the y-axis.
 */
Rect Rect::translated(const int dx, const int dy) const {
	Rect r(*this);
	r.translate(dx,dy);

	return r;
}

/**
 * Returns a copy of this rectangle that has been translated relative
 * to its current position by the amount of \em offset.
 */
Rect Rect::translated(const Point &offset) const {
	Rect r(*this);
	r.translate(offset);

	return r;
}

/**
 * Returns a new rectangle with the same top left corner but
 * with the width and height swapped around.
 */
Rect Rect::transposed() const {
	return Rect(x1,y1,height(),width());
}

/**
 * Returns a new bounding rectangle that contains both this rectangle and \em rect.
 */
Rect Rect::united(const Rect &rect) const {
	Rect r;

	if (this->contains(rect))
		r = *this;
	else if (rect.contains(*this))
		r = rect;
	else {
		r.setLeft(prism::min(this->left(), rect.left()));
		r.setTop(prism::min(this->top(), rect.top()));
		r.setRight(prism::max(this->right(), rect.right()));
		r.setBottom(prism::max(this->bottom(), rect.bottom()));
	}

	return r;
}

/**
 * Returns the width of the rectangle.
 */
const int Rect::width() const {
	return x2-x1;
}


/**
 * Returns the x-coordinate of the rectangle's left edge.
 */
const int Rect::x() const {
	return x1;
}

/**
 * Returns the y-coordinate of the rectangle's top edge.
 */
const int Rect::y() const {
	return y1;
}

/**
 * Assignment constructor
 */
Rect & Rect::operator=(const Rect & rect) {
	x1 = rect.x1;
	y1 = rect.y1;
	x2 = rect.x2;
	y2 = rect.y2;

	return *this;
}

/**
 * =====================================================================
 * Related non-members
 * =====================================================================
 */
/**
 * Returns true if the rectangles \em r1 and \em r2 are equal, false otherwise.
 */
const bool operator==(const Rect &r1, const Rect &r2) {
	return r1.x1 == r2.x1 && r1.y1 == r2.y1 && r1.x2 == r2.x2 && r1.y2 == r2.y2;
}

/**
 * Returns true if the rectangles \em r1 and \em r2 are not equal, false otherwise.
 */
const bool operator!=(const Rect &r1, const Rect &r2) {
	return !(r1==r2);
}

/**
 * Allows an instance of Rect to be written to the ostream and returns a reference to the ostream.
 */
std::ostream& operator<<(std::ostream &out, const Rect &rect) {
	out << "Rect [" << &rect << "]: (x=" << rect.x1 << ", y=" << rect.y1
			<< ", width=" << rect.width() << ", height=" << rect.height()
			<< ", left=" << rect.left() << ", top=" << rect.top() << ", right=" << rect.right() << ", bottom=" << rect.bottom() << ")";
	return out;
}

} /* namespace prism */
