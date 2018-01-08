#include <prism/Widget>
#include <prism/gui/NativeWidget.h>
#include <prism/Size>
#include <prism/Point>

PRISM_BEGIN_NAMESPACE

//==============================================================================
// WidgetImpl
//==============================================================================
struct Widget::WidgetImpl {
    std::shared_ptr<NativeWidget> native;
    bool visible{false};
    bool maximized{false};
    bool minimized{false};
    Size minimumSize{0,0};
    Size maximumSize{16777215, 16777215};

    const bool canResizeWidth(const int newWidth) {
        if (newWidth < minimumSize.width() || newWidth > maximumSize.width()) return false;
        return true;
    }

    const bool canResizeHeight(const int newHeight) {
        if (newHeight < minimumSize.height() || newHeight > maximumSize.height()) return false;
        return true;
    }
};
//==============================================================================
// Widget
//==============================================================================
Widget::Widget()
:   impl{new WidgetImpl}
{}

Widget::~Widget() {
    //
}

void
Widget::resize(const Size& size) {
    resize(size.width(), size.height());
}

void
Widget::resize(const int width, const int height) {
    if (impl->canResizeWidth(width))
        impl->native->setSize(Size(width, this->height()));
    else {
        (width < impl->minimumSize.width())
            ? impl->native->setSize(impl->minimumSize.width(), this->height())
            : impl->native->setSize(impl->maximumSize.width(), this->height());
    }

    if (impl->canResizeHeight(height))
        impl->native->setSize(Size(this->width(), height));
    else {
        (height < impl->minimumSize.height())
            ? impl->native->setSize(this->width(), impl->minimumSize.height())
            : impl->native->setSize(this->width(), impl->maximumSize.height());
    }
}

const int
Widget::width() const {
    return impl->native->size().width();
}

void
Widget::setWidth(const int width) {
    resize(width, height());
}

const int
Widget::height() const {
    return impl->native->size().height();
}

void
Widget::setHeight(const int height) {
    resize(width(), height);
}

Size
Widget::size() const {
    return impl->native->size();
}

const int
Widget::minimumWidth() const {
    return impl->minimumSize.width();
}

void
Widget::setMinimumWidth(const int width) {
    impl->minimumSize.setWidth(width);
}

const int
Widget::minimumHeight() const {
    return impl->minimumSize.height();
}

void
Widget::setMinimumHeight(const int height) {
    impl->minimumSize.setHeight(height);
}

const int
Widget::maximumWidth() const {
    return impl->maximumSize.width();
}

void
Widget::setMaximumWidth(const int width) {
    impl->maximumSize.setWidth(width);
}

const int
Widget::maximumHeight() const {
    return impl->maximumSize.height();
}

void
Widget::setMaximumHeight(const int height) {
    impl->maximumSize.setHeight(height);
}

Size
Widget::minimumSize() const {
    return Size(impl->minimumSize.width(), impl->minimumSize.height());
}

void
Widget::setMinimumSize(const Size& size) {
    setMinimumWidth(size.width());
    setMinimumHeight(size.height());
}

Size
Widget::maximumSize() const {
    return Size(impl->maximumSize.width(), impl->maximumSize.height());
}

void
Widget::setMaximumSize(const Size& size) {
    setMaximumWidth(size.width());
    setMaximumHeight(size.height());
}

void
Widget::setFixedWidth(const int width) {
    impl->minimumSize.setWidth(width);
    impl->maximumSize.setWidth(width);
}

void
Widget::setFixedHeight(const int height) {
    impl->minimumSize.setHeight(height);
    impl->maximumSize.setHeight(height);
}

void
Widget::setFixedSize(const Size& size) {
    setFixedWidth(size.width());
    setFixedHeight(size.height());
}

std::string
Widget::title() const {
    return impl->native->title();
}

void
Widget::setTitle(const std::string& title) {
    impl->native->setTitle(title);
}

const bool
Widget::isVisible() const {
    return impl->visible;
}

void
Widget::setVisible() {
    impl->visible = true;
}

const bool
Widget::isMaximized() const {
    return impl->maximized;
}

void
Widget::setMaximized() {
    impl->maximized = true;
}

const bool
Widget::isMinimized() const {
    return impl->minimized;
}

void
Widget::setMinimized() {
    impl->minimized = true;
}

void
Widget::setNativeWidget(NativeWidget * nw) {
    impl->native.reset(nw);
}

Layout *
Widget::layout() const {
    return nullptr;
}

PRISM_END_NAMESPACE
