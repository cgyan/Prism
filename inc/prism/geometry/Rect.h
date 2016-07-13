/*
 * Rect.h
 * v0.1
 *
 *  Created on: Jul 1, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_RECT_H_
#define PRISM_RECT_H_

#include <ostream>

namespace prism {

class Point;
class Size;

class Rect {
private:
	int x1;
	int y1;
	int x2;
	int y2;

public:
	Rect();
	Rect(const int x, const int y, const int width, const int height);
	Rect(const Point &topLeft, const Point &bottomRight);
	Rect(const Point &topLeft, const Size &size);
	Rect(const Rect &copy);
	virtual ~Rect();

	void		adjust(const int dx1, const int dy1, const int dx2, const int dy2);
	Rect		adjusted(const int dx1, const int dy1, const int dx2, const int dy2) const;
	const int	bottom() const;
	Point		bottomLeft() const;
	Point		bottomRight() const;
	Point		centre() const;
	const bool	contains(const Point &point) const;
	const bool	contains(const int x, const int y) const;
	const bool	contains(const Rect &rect) const;
	void		getCoordinates(int *x1, int *y1, int *x2, int *y2) const;
	void		getRect(int *x, int *y, int *width, int *height) const;
	const int 	height() const;
	Rect		intersected(const Rect &rect) const;
	const bool	intersects(const Rect &rect) const;
	const bool	isEmpty() const;
	const bool	isNull() const;
	const bool	isValid() const;
	const int	left() const;
	void		moveBottom(const int y);
	void		moveBottomLeft(const Point &position);
	void 		moveBottomRight(const Point &position);
	void		moveCentre(const int x, const int y);
	void		moveCentre(const Point &position);
	void		moveLeft(const int x);
	void		moveRight(const int x);
	void		moveTo(const int x, const int y);
	void		moveTo(const Point &position);
	void 		moveTop(const int y);
	void		moveTopLeft(const Point &position);
	void		moveTopRight(const Point &position);
	Rect		normalised() const;
	const int	right() const;
	void		setBottom(const int y);
	void		setBottomLeft(const Point &position);
	void		setBottomRight(const Point &position);
	void		setCoordinates(const int x1, const int y1, const int x2, const int y2);
	void 		setHeight(const int height);
	void		setLeft(const int x);
	void		setRect(const int x, const int y, const int width, const int height);
	void		setRight(const int x);
	void 		setSize(const Size &size);
	void		setTop(const int y);
	void		setTopLeft(const Point &position);
	void		setTopRight(const Point &position);
	void 		setX(const int x);
	void 		setY(const int y);
	void 		setWidth(const int width);
	Size 		size() const;
	const int	top() const;
	Point		topLeft() const;
	Point		topRight() const;
	void		translate(const int dx, const int dy);
	void		translate(const Point &offset);
	Rect		translated(const int dx, const int dy) const;
	Rect		translated(const Point &offset) const;
	Rect		transposed() const;
	Rect 		united(const Rect &rect) const;
	const int 	width() const;
	const int 	x() const;
	const int 	y() const;

	Rect & operator=(const Rect & rect);

	// related non-members
	friend const bool operator==(const Rect &r1, const Rect &r2);
	friend const bool operator!=(const Rect &r1, const Rect &r2);
	friend std::ostream& operator<<(std::ostream &out, const Rect &rect);
};

} /* namespace prism */

#endif /* PRISM_RECT_H_ */
