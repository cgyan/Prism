#include <prism/Widget>
#include <prism/Size>
#include <prism/Point>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// Widget
//==============================================================================
Widget::Widget()
{}

Widget::~Widget() {
    //
}

Size
Widget::size() const {
    return Size(m_width, m_height);
}

void
Widget::resize(const Size& size) {
    m_width = size.width();
    m_height = size.height();
}

void
Widget::resize(const int width, const int height) {
    resize(Size(width, height));
}

std::string
Widget::title() const {
    return m_title;
}

void
Widget::setTitle(const std::string& title) {
    m_title = title;
}

Point
Widget::pos() const {
    return Point(m_x, m_y);
}

void
Widget::setPos(const Point& pos) {
    m_x = pos.x();
    m_y = pos.y();
}

PRISM_END_NAMESPACE
