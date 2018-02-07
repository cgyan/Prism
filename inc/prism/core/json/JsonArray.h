#ifndef PRISM_JSONARRAY_H_
#define PRISM_JSONARRAY_H_

#include <prism/global>
#include <prism/Vector>
#include <memory>

PRISM_BEGIN_NAMESPACE

class JsonValue;
class ostream;

class JsonArray {
public:
    using iterator = prism::Vector<JsonValue>::iterator;
    using const_iterator = prism::Vector<JsonValue>::const_iterator;
public:
    JsonArray();
    JsonArray(std::initializer_list<JsonValue> il);
    JsonArray(const JsonArray& copy);
    JsonArray& operator=(const JsonArray& rhs);

    JsonValue& at(const int index);
    const int size() const;
    const bool empty() const;
    void insert(const_iterator insertBefore, const JsonValue& value);
    void insert(const int index, const JsonValue& value);
    void append(const JsonValue& value);
    void prepend(const JsonValue& value);
    void remove(const_iterator pos);
    void removeAt(const int index);
    const bool contains(const JsonValue& value) const;

    const_iterator begin() const;
    const_iterator end() const;

    JsonValue& operator[](const int index);
    const bool operator==(const JsonArray& rhs) const;
    friend std::ostream& operator<<(std::ostream& out, const JsonArray& js);
private:
    class JsonArrayImpl;
    std::shared_ptr<JsonArrayImpl> m_impl;
};



PRISM_END_NAMESPACE

#endif
