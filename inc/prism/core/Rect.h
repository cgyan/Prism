#ifndef PRISM_RECT_H_
#define PRISM_RECT_H_

#include <prism/global>
#include <prism/Point>
#include <prism/Size>

PRISM_BEGIN_NAMESPACE

class Rect {
private:
    Point m_topLeft;
    Point m_bottomRight;
public:
    Rect();
    Rect(const Point& topLeft, const Size& size);

    const int x() const;
    const int y() const;

    const int top() const;
    const int right() const;
    const int bottom() const;
    const int left() const;

    Point centre() const;
    Point topLeft() const;
    Point topRight() const;
    Point bottomLeft() const;
    Point bottomRight() const;

    void setTopLeft(const Point& pos);
    void setTopRight(const Point& pos);
    void setBottomRight(const Point& pos);
    void setBottomLeft(const Point& pos);

    const int width() const;
    const int height() const;
    Size size() const;

    void moveRight(const int x);
};

PRISM_END_NAMESPACE

#endif // PRISM_RECT_H_
