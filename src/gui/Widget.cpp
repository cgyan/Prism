#include <prism/Widget>
#include <prism/Size>
#include <prism/Point>

PRISM_BEGIN_NAMESPACE

Size
Widget::size() const {
    return Size(m_width, m_height);
}

void
Widget::resize(const int width, const int height) {
    m_width = width;
    m_height = height;
}

std::string
Widget::title() const {
    return "Default Window Title";
}

Point
Widget::position() const {
    return Point(m_x,m_y);
}

void
Widget::setPosition(const Point& pos) {
    m_x = pos.x();
    m_y = pos.y();
}

PRISM_END_NAMESPACE
