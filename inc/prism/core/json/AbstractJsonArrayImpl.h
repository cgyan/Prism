#ifndef PRISM_ABSTRACT_JSON_ARRAY_IMPL_H_
#define PRISM_ABSTRACT_JSON_ARRAY_IMPL_H_

#include <prism/global>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class AbstractJsonArrayImpl {
public:
    virtual ~AbstractJsonArrayImpl() {}

    virtual const int numElements() const { return int{}; }
    virtual void insert(JsonArray::const_iterator pos, const JsonValue& value) {}
    virtual void remove(JsonArray::const_iterator pos) {}
    virtual const bool containsElement(const JsonValue& value) const { return bool{}; }
    virtual JsonArray::iterator begin() { return JsonArray::iterator{}; }
    virtual JsonArray::iterator end() { return JsonArray::iterator{}; }
};

PRISM_END_NAMESPACE

#endif
