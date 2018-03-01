#ifndef PRISM_JSON_VALUE_H_
#define PRISM_JSON_VALUE_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

class AbstractJsonValueImpl;
class JsonObject;
class JsonArray;

class JsonValue {
public:
    enum class Type { Null, Bool, Double, String, Object, Array };
public:
    JsonValue(Type type = Type::Null);
    JsonValue(const int value);
    JsonValue(const double value);
    JsonValue(const bool value);
    JsonValue(const std::string& value);
    JsonValue(const char * value);
    JsonValue(const JsonObject& value);
    JsonValue(const JsonArray& value);
    JsonValue(const JsonValue& copy);
    JsonValue(AbstractJsonValueImpl* impl);
    JsonValue& operator=(const JsonValue& rhs);
    ~JsonValue();

    const bool isNull() const;
    const bool isBool() const;
    const bool isDouble() const;
    const bool isString() const;
    const bool isObject() const;
    const bool isArray() const;

    bool toBool() const;
    double toDouble() const;
    std::string toString() const;
    JsonObject toObject() const;
    JsonArray toArray() const;

    Type type() const;
private:
    std::shared_ptr<AbstractJsonValueImpl> m_impl;
};

const bool operator==(const JsonValue& lhs, const JsonValue& rhs);
const bool operator!=(const JsonValue& lhs, const JsonValue& rhs);
std::ostream& operator<<(std::ostream& out, const JsonValue& jv);

PRISM_END_NAMESPACE

#endif
