#ifndef PRISM_SIZE_H_
#define PRISM_SIZE_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

struct SizeData;

class Size {
private:
    using SizeDataPtr = std::shared_ptr<SizeData>;
    SizeDataPtr d;
public:
    Size(const int width = 0, const int height = 0);
    virtual ~Size();

    const int width() const;
    const int height() const;

    void setWidth(const int width);
    void setHeight(const int height);

    void set(const int width, const int height);
    void reset();
    const bool isReset() const;
    const bool isValid() const;

    void transpose();
    Size transposed() const;

    void scale(const int widthFactor, const int heightFactor);
    void scale(const Size& size);
    Size scaled(const int widthFactor, const int heightFactor) const;
    Size scaled(const Size& size) const;

    Size& operator+=(const Size& rhs);
    Size& operator-=(const Size& rhs);
    Size& operator*=(const int factor);
    Size& operator/=(const int factor);
};

const bool operator==(const Size& lhs, const Size& rhs);
const bool operator!=(const Size& lhs, const Size& rhs);
Size operator+(const Size& lhs, const Size& rhs);
Size operator-(const Size& lhs, const Size& rhs);
Size operator*(const Size& size, const int factor);
Size operator*(const int factor, const Size& size);
Size operator/(const Size& size, const int factor);

PRISM_END_NAMESPACE

#endif // PRISM_SIZE_H_
