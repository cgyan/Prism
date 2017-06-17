#ifndef PRISM_WIDGET_H_
#define PRISM_WIDGET_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class Size;
class Point;

class Widget {
public:
    Size size() const;
    void resize(const int width, const int height);

    std::string title() const;

    Point position() const;
    void setPosition(const Point& pos);
private:
    int m_width{600};
    int m_height{400};
    int m_x{0};
    int m_y{0};
};

PRISM_END_NAMESPACE

#endif // PRISM_WIDGET_H_
