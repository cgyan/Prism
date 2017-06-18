#ifndef PRISM_NATIVE_WIDGET_H_
#define PRISM_NATIVE_WIDGET_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class Size;
class Point;

class NativeWidget {
public:
    virtual ~NativeWidget() {}
    virtual Size size() const = 0;
    virtual void setSize(const Size& size) = 0;
    virtual void setSize(const int width, const int height) = 0;
    virtual std::string title() const = 0;
    virtual void setTitle(const std::string& title) = 0;
};

PRISM_END_NAMESPACE

#endif // PRISM_NATIVE_WIDGET_H_
