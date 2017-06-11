#ifndef PRISM_RECT_H_
#define PRISM_RECT_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

struct RectData;
class Point;
class Size;
class ostream;

class Rect {
public:
    Rect();
    Rect(const Point& topLeft, const Size& size);
    Rect(const Point& topLeft, const Point& bottomRight);
    Rect(const int x, const int y, const int width, const int height);
    Rect(const Rect& copy);
    Rect& operator=(const Rect& rhs);

    void set(const Point& topLeft, const Size& size);
    void set(const int x, const int y, const int width, const int height);

    const int x() const;
    const int y() const;
    void setX(const int x);
    void setY(const int y);

    const int width() const;
    const int height() const;
    void setWidth(const int width);
    void setHeight(const int height);

    Size size() const;
    void setSize(const int width, const int height);

    Point centre() const;

    const int top() const;
    const int right() const;
    const int bottom() const;
    const int left() const;

    Point topLeft() const;
    Point topRight() const;
    Point bottomLeft() const;
    Point bottomRight() const;

    void setTop(const int y);
    void setRight(const int x);
    void setBottom(const int y);
    void setLeft(const int x);

    void setTopLeft(const Point& pos);
    void setTopRight(const Point& pos);
    void setBottomRight(const Point& pos);
    void setBottomLeft(const Point& pos);

    void adjust(const int dx1, const int dy1, const int dx2, const int dy2);
    Rect adjusted(const int dx1, const int dy1, const int dx2, const int dy2) const;

    void moveCentre(const Point& pos);
    void moveCentre(const int x, const int y);

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
    const bool contains(const int x, const int y, const bool = false) const;
    const bool contains(const Rect& rect, const bool precise = false) const;

    Rect transposed() const;
    Rect normalised() const;

    void translate(const int dx, const int dy);
    void translate(const Point& offset);
    Rect translated(const int dx, const int dy) const;
    Rect translated(const Point& offset) const;

    const bool intersects(const Rect& r) const;
    static Rect intersected(const Rect& r1, const Rect& r2);

    static Rect united(const Rect& r1, const Rect& r2);
private:
    using RectDataPtr = std::shared_ptr<RectData>;
    RectDataPtr d;
};

const bool operator==(const Rect& lhs, const Rect& rhs);
const bool operator!=(const Rect& lhs, const Rect& rhs);
std::ostream& operator<<(std::ostream& out, const Rect& r);

PRISM_END_NAMESPACE

#endif // PRISM_RECT_H_
