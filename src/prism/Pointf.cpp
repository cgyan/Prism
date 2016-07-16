#include <prism/Pointf>
#include <prism/Point>

namespace prism {

/**
 * Default constructor
 */
Pointf::Pointf(void)
	: m_x(0), m_y(0)
{}

/**
 * Constructor override
 */
Pointf::Pointf(const float x, const float y)
	: m_x(x), m_y(y)
{}

/**
 *
 */
Pointf::Pointf(const Pointf & p) {
	m_x = p.m_x;
	m_y = p.m_y;
}

/**
 * Virtual destructor
 */
Pointf::~Pointf(void)
{}

/**
 * Resets this Pointf back to x=y=0
 */
void Pointf::reset() {
	m_x = m_y = 0;
}

/**
 * Returns true if x=0 and y=0, false if not
 */
const bool Pointf::isReset() const {
	return (m_x == 0) && (m_y == 0);
}

/**
 * Convenience method that sets x and y simultaineously
 */
void Pointf::set(const float x, const float y) {
	m_x = x;
	m_y = y;
}

/**
 * Sets the x component
 */
void Pointf::setX(const float x) {
	set(x, m_y);
}

/**
 * Sets the y component
 */
void Pointf::setY(const float y) {
	set(m_x, y);
}

/**
 * Returns the x component
 */
const float Pointf::x() const {
	return m_x;
}

/**
 * Returns the y component
 */
const float Pointf::y() const {
	return m_y;
}

/**
 * Returns a reference to the x component allowing direct manipulation
 * i.e. Pointf.rx() += 5
 */
float & Pointf::rx() {
	return m_x;
}

/**
 * Returns a reference to the y component allowing direct manipulation
 * i.e. Pointf.ry() += 5
 */
float & Pointf::ry() {
	return m_y;
}

/**
 * Returns a reference to this Pointf after adding p to it
 */
Pointf & Pointf::operator+=(const Pointf & p) {
	m_x += p.m_x;
	m_y += p.m_y;
	return *this;
}

/**
 * Returns a reference to this Pointf after subtracting p from it
 */
Pointf & Pointf::operator-=(const Pointf & p) {
	m_x -= p.m_x;
	m_y -= p.m_y;
	return *this;
}

/**
 * Multiplies this Pointf's components by the given factor 
 * and returns a reference to this Pointf.
 */
Pointf & Pointf::operator*=(const float factor) {
	m_x *= factor;
	m_y *= factor;
	return *this;
}

/**
 * Multiplies this Pointf's coordinates by the given factor 
 * and returns a reference to this Pointf
 */
Pointf & Pointf::operator/=(const float divisor) {
	if (divisor == 0) {
		this->reset();
	}
	else {
		m_x /= divisor;
		m_y /= divisor;
	}
	return *this;
}

/**
 *
 */
Pointf & Pointf::operator=(const Pointf & p) {
	m_x = p.m_x;
	m_y = p.m_y;
	return *this;
}

// ============================================================
// Related non-members
// ============================================================
/**
 * Returns an ostream object that allows this object to printed with std::cout
 */
std::ostream & operator<<(std::ostream & out, const Pointf & p) {
	// std::fixed has to be added here as otherwise very small values for x and y
	// are printed in scientific notation e.g. 1.2345e-06
	out << std::fixed << "Pointf: [" << &p << "] x=" << p.m_x << " y=" << p.m_y;
	return out;
}

/** 
 * Returns a Pointf object that is the sum of the components of p1 and p2
 */
Pointf operator+(const Pointf & p1, const Pointf & p2) {
	return Pointf(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

/** 
 * Returns a Pointf object that is formed by subtracting the components of p2 from p1
 */
Pointf operator-(const Pointf & p1, const Pointf & p2) {
	return Pointf(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

/**
 * Returns a Pointf object that is formed by multiplying the components of p by the float factor
 */
Pointf operator*(const Pointf & p, const float factor) {
	return Pointf(p.m_x * factor, p.m_y * factor);
}

/**
 *
 */
Pointf operator*(const float factor, const Pointf & p) {
	return p*factor;
}

/**
 * Returns a Pointf object that is formed by dividing the components of p by divisor
 */
Pointf operator/(const Pointf & p, const float divisor) {
	if (divisor == 0) return Pointf();
	return Pointf(p.m_x / divisor, p.m_y / divisor);
}

/**
 * Returns true if x and y of p1 and p2 are equal, false if not
 */
bool operator==(const Pointf & p1, const Pointf & p2) {
	return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
}

/**
 * Returns true if x or y of p1 and p2 are not equal, false if not
 */
bool operator!=(const Pointf & p1, const Pointf & p2) {
	return (p1.m_x != p2.m_x) || (p1.m_y != p2.m_y);
}

}
