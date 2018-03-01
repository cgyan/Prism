#ifndef PRISM_ABSTRACT_JSON_VALUE_IMPL_H_
#define PRISM_ABSTRACT_JSON_VALUE_IMPL_H_

#include <prism/global>
#include <prism/JsonObject>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class AbstractJsonValueImpl {
public:
    virtual ~AbstractJsonValueImpl() {}

    virtual double toDouble() const = 0;
    virtual bool toBool() const = 0;
    virtual std::string toString() const = 0;
    virtual JsonObject toObject() const = 0;
    virtual JsonArray toArray() const = 0;

    virtual JsonValue::Type type() const = 0;
    virtual void swap(AbstractJsonValueImpl * other) {}
};

PRISM_END_NAMESPACE

#endif
