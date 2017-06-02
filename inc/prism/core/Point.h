#ifndef PRISM_POINT_H_
#define PRISM_POINT_H_

#include <ostream>

namespace prism {
class Point
{
private:
	int m_x;
	int m_y;

public:
	Point(void);
	Point(const int x, const int y);
	Point(const Point & copy);
	~Point(void);

	void 		reset();
	const bool 	isReset() const;
	void 		set(const int x, const int y);
	void 		setX(const int x);
	void 		setY(const int y);
	const int 	x() const;
	const int 	y() const;
	int & 		rx();
	int & 		ry();
	
	Point & operator=(const Point & p);
	Point & operator+=(const Point & p);
	Point & operator-=(const Point & p);
	Point & operator*=(const float factor);
	Point & operator*=(const int factor);
	Point & operator/=(const float divisor);
	Point & operator/=(const int divisor);

	// Related non-members
	friend std::ostream& operator<<(std::ostream & out, const Point & p);
	friend Point operator+(const Point & p1, const Point & p2);
	friend Point operator-(const Point & p1, const Point & p2);
	friend Point operator*(const Point & p, const int factor);
	friend Point operator*(const Point & p, const float factor);
	friend Point operator*(const int factor, const Point & p);
	friend Point operator*(const float factor, const Point & p);
	friend Point operator/(const Point & p, const float divisor);
	friend bool operator==(const Point & p1, const Point & p2);
	friend bool operator!=(const Point & p1, const Point & p2);
	
};
}


#endif /* PRISM_POINT_H_ */
