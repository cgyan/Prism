#ifndef PRISM_RECT_H_
#define PRISM_RECT_H_

#include <prism/global>
#include <memory>
#include <ostream>

PRISM_BEGIN_NAMESPACE

struct RectData;
class Point;
class Size;

class Rect {
private:
    using RectDataPtr = std::shared_ptr<RectData>;
    RectDataPtr d;
public:
    Rect();
    Rect(const int x, const int y, const int width, const int height);
    Rect(const Point& topLeft, const Point& bottomRight);
    Rect(const Point& topLeft, const Size& size);
    Rect(const Rect& copy);
    Rect& operator=(const Rect& rhs);

    const int x() const;
    const int y() const;
    const int width() const;
    const int height() const;

    Size size() const;
    void setSize(const int width, const int height);

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

    void adjust(const int dx1, const int dy1, const int dx2, const int dy2);
    Rect adjusted(const int dx1, const int dy1, const int dx2, const int dy2) const;

    void moveTop(const int y);
    void moveRight(const int x);
    void moveBottom(const int y);
    void moveLeft(const int x);

    void moveTopLeft(const Point& pos);
    void moveTopRight(const Point& pos);
    void moveBottomRight(const Point& pos);
    void moveBottomLeft(const Point& pos);

    const bool isNull() const;
    const bool isValid() const;

    const bool contains(const Point& pos, const bool precise = false) const;
    const bool contains(const int x, const int y) const;
};

const bool operator==(const Rect& lhs, const Rect& rhs);
const bool operator!=(const Rect& lhs, const Rect& rhs);
std::ostream& operator<<(std::ostream& out, const Rect& r);

PRISM_END_NAMESPACE

#endif // PRISM_RECT_H_
