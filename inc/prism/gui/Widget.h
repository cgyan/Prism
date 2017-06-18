#ifndef PRISM_WIDGET_H_
#define PRISM_WIDGET_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class Size;
class Point;

//==============================================================================
// Widget
//==============================================================================
class Widget {
public:
    Widget();
    ~Widget();

    Size size() const;
    void resize(const Size& size);
    void resize(const int width, const int height);

    std::string title() const;
    void setTitle(const std::string& title);

    Point pos() const;
    void setPos(const Point& pos);
private:
    int m_width{600};
    int m_height{400};
    int m_x{0};
    int m_y{0};
    std::string m_title{"Default Window Title"};
};

PRISM_END_NAMESPACE

#endif // PRISM_WIDGET_H_
