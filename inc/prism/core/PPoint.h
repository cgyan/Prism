#ifndef PRISM_PPOINT_H_
#define PRISM_PPOINT_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

class PPoint {
private:
    int m_x;
    int m_y;
public:
    PPoint(const int x=0, const int y=0);

    const int x() const;
    void setX(const int x);
    const int y() const;
    void setY(const int y);
    void set(const int x, const int y);
    void reset();
};

const bool operator==(const PPoint& lhs, const PPoint& rhs);
const bool operator!=(const PPoint& lhs, const PPoint& rhs);

PRISM_END_NAMESPACE

#endif // PRISM_PPOINT_H_
