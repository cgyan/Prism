#ifndef PRISM_POINTF_H_
#define PRISM_POINTF_H_

#include <ostream>

namespace prism {
class Point;

class Pointf
{
private:
	float m_x;
	float m_y;

public:
	Pointf(void);
	Pointf(const float x, const float y);
	Pointf(const Pointf & p);
	virtual ~Pointf(void);

	void reset();
	const bool isReset() const;
	void set(const float x, const float y);
	void setX(const float x);
	void setY(const float y);
	const float x() const;
	const float y() const;
	float & rx();
	float & ry();
	
	Pointf & operator+=(const Pointf & p);
	Pointf & operator-=(const Pointf & p);
	Pointf & operator*=(const float factor);
	Pointf & operator/=(const float divisor);
	Pointf & operator=(const Pointf & p);

	// Related non-members
	friend Pointf operator+(const Pointf & p1, const Pointf & p2);
	friend Pointf operator-(const Pointf & p1, const Pointf & p2);
	friend Pointf operator*(const Pointf & p, const float factor);
	friend Pointf operator*(const float factor, const Pointf & p);
	friend Pointf operator/(const Pointf & p, const float divisor);
	friend bool operator==(const Pointf & p1, const Pointf & p2);
	friend bool operator!=(const Pointf & p1, const Pointf & p2);
	friend std::ostream& operator<<(std::ostream & out, const Pointf & p);
};
}

#endif /* PRISM_POINTF_H_ */
