#ifndef PRISM_ABSTRACT_JSON_ARRAY_IMPL_H_
#define PRISM_ABSTRACT_JSON_ARRAY_IMPL_H_

#include <prism/global>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class AbstractJsonArrayImpl {
public:
    virtual ~AbstractJsonArrayImpl() {}

    virtual AbstractJsonArrayImpl* clone() const = 0;
    virtual const int numElements() const = 0;
    virtual void insert(JsonArray::const_iterator pos, const JsonValue& value) = 0;
    virtual void remove(JsonArray::const_iterator pos) = 0;
    virtual const bool containsElement(const JsonValue& value) const = 0;
    virtual JsonArray::iterator begin() = 0;
    virtual JsonArray::iterator end() = 0;
};

PRISM_END_NAMESPACE

#endif
