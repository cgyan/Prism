#ifndef PRISM_WIDGET_H_
#define PRISM_WIDGET_H_

#include <prism/global>
#include <string>
#include <memory>

PRISM_BEGIN_NAMESPACE

class Size;
class Point;
class NativeWidget;
class Layout;

class Widget {
public:
    Widget();
    ~Widget();

    const int width() const;
    const int height() const;
    void setWidth(const int width);
    void setHeight(const int height);

    Size size() const;
    void resize(const Size& size);
    void resize(const int width, const int height);

    Size minimumSize() const;
    Size maximumSize() const;
    const int minimumWidth() const;
    const int minimumHeight() const;
    const int maximumWidth() const;
    const int maximumHeight() const;

    void setMinimumSize(const Size& size);
    void setMaximumSize(const Size& size);
    void setMinimumWidth(const int width);
    void setMinimumHeight(const int height);
    void setMaximumWidth(const int width);
    void setMaximumHeight(const int height);

    void setFixedSize(const Size& size);
    void setFixedWidth(const int width);
    void setFixedHeight(const int height);

    std::string title() const;
    void setTitle(const std::string& title);

    const bool isVisible() const;
    const bool isMaximized() const;
    const bool isMinimized() const;

    void setVisible();
    void setMaximized();
    void setMinimized();

    Layout * layout() const;

    void setNativeWidget(NativeWidget * nw);
private:
    struct WidgetImpl;
    std::shared_ptr<WidgetImpl> impl;
};

PRISM_END_NAMESPACE

#endif // PRISM_WIDGET_H_
