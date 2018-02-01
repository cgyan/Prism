#ifndef PRISM_JSONARRAY_H_
#define PRISM_JSONARRAY_H_

#include <prism/global>
#include <vector>
#include <memory>

PRISM_BEGIN_NAMESPACE

class JsonValue;
class ostream;

class JsonArray {
public:
    using const_iterator = std::vector<JsonValue>::const_iterator;
public:
    JsonArray();
    JsonArray(std::initializer_list<JsonValue> il);
    JsonArray(const JsonArray& copy);
    JsonArray& operator=(const JsonArray& rhs);

    JsonValue& at(const int index);
    const bool empty() const;
    const int size() const;
    void append(const JsonValue& value);
    void prepend(const JsonValue& value);
    void removeAt(const int index);
    void erase(const_iterator pos);

    const_iterator begin() const;
    const_iterator end() const;

    JsonValue& operator[](const int index);
    friend const bool operator==(const JsonArray& lhs, const JsonArray& rhs);
    friend std::ostream& operator<<(std::ostream& out, const JsonArray& js);
private:
    class JsonArrayImpl;
    std::shared_ptr<JsonArrayImpl> m_impl;
};


PRISM_END_NAMESPACE

#endif
