#ifndef PRISM_SIZE_H_
#define PRISM_SIZE_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

struct SizeData;

class PSize {
private:
    using SizeDataPtr = std::shared_ptr<SizeData>;
    SizeDataPtr d;
public:
    PSize(const int width = 0, const int height = 0);
    virtual ~PSize();

    const int width() const;
    const int height() const;

    void setWidth(const int width);
    void setHeight(const int height);

    void set(const int width, const int height);
    void reset();
    const bool isReset() const;
    const bool isValid() const;

    void transpose();
    PSize transposed() const;

    void scale(const int widthFactor, const int heightFactor);
    void scale(const PSize& size);
    PSize scaled(const int widthFactor, const int heightFactor) const;
    PSize scaled(const PSize& size) const;

    PSize& operator+=(const PSize& rhs);
    PSize& operator-=(const PSize& rhs);
    PSize& operator*=(const PSize& rhs);
    PSize& operator/=(const PSize& rhs);
};

const bool operator==(const PSize& lhs, const PSize& rhs);
const bool operator!=(const PSize& lhs, const PSize& rhs);
PSize operator+(const PSize& lhs, const PSize& rhs);
PSize operator-(const PSize& lhs, const PSize& rhs);
PSize operator*(const PSize& size, const int factor);
PSize operator*(const int factor, const PSize& size);
PSize operator/(const PSize& size, const int factor);

PRISM_END_NAMESPACE

#endif // PRISM_SIZE_H_
