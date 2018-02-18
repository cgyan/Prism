#ifndef PRISM_ABSTRACT_JSON_VALUE_IMPL_H_
#define PRISM_ABSTRACT_JSON_VALUE_IMPL_H_

#include <prism/global>
#include <prism/JsonObject>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class AbstractJsonValueImpl {
public:
    virtual ~AbstractJsonValueImpl() {}

    virtual double toDouble() const { return double{}; };
    virtual bool toBool() const { return bool{}; }
    virtual std::string toString() const { return std::string{}; }
    virtual JsonObject toObject() const {return JsonObject{};  }
    virtual JsonArray toArray() const { return JsonArray{}; }

    virtual JsonValue::Type type() const { return JsonValue::Type::Null; }
    virtual void swap(AbstractJsonValueImpl * other) {}
};

PRISM_END_NAMESPACE

#endif
