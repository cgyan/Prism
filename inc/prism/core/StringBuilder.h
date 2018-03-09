#ifndef PRISM_STRING_BUILDER_H_
#define PRISM_STRING_BUILDER_H_

#include <prism/global>
#include <memory>
class string;

PRISM_BEGIN_NAMESPACE

class StringBuilderImpl;

class StringBuilder {
public:
    StringBuilder();
    StringBuilder(const std::string& string);

    void clear();
    const int size() const;
    const bool empty() const;
    const std::string toString() const;

    void append(const char c);
    void append(const char * string);
    void append(const std::string& string);
    void append(const bool b);
    void append(const int i);
    void append(const double d);

    void prepend(const char c);
    void prepend(const char * string);
    void prepend(const std::string& string);
    void prepend(const bool b);
    void prepend(const int i);
    void prepend(const double d);
private:
    std::shared_ptr<StringBuilderImpl> m_impl;
};

PRISM_END_NAMESPACE

#endif
