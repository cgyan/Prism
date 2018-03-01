#include <prism/global>
#include <prism/JsonValue>
#include <prism/AbstractJsonValueImpl>
#include <prism/JsonObject>
#include <prism/JsonArray>
#include <prism/algorithm>
#include <prism/InvalidConversionException>
#include <string>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonValueImpl
//==============================================================================
class JsonValueImpl : public AbstractJsonValueImpl {
public:
    JsonValueImpl(JsonValue::Type type);
    JsonValueImpl(const double value);
    JsonValueImpl(const bool value);
    JsonValueImpl(const std::string& value);
    JsonValueImpl(const JsonObject& value);
    JsonValueImpl(const JsonArray& value);
    JsonValueImpl(const JsonValueImpl& copy);
    ~JsonValueImpl();

    double toDouble() const override;
    bool toBool() const override;
    std::string toString() const override;
    JsonObject toObject() const override;
    JsonArray toArray() const override;

    JsonValue::Type type() const override;
    void swap(AbstractJsonValueImpl * other) override;
private:
    void constructString(const std::string& value);
    void constructObject(const JsonObject& value);
    void constructArray(const JsonArray& value);
    void destroyString();
    void destroyObject();
    void destroyArray();
private:
    JsonValue::Type m_type;
    union {
        bool m_boolValue;
        double m_doubleValue;
        std::string m_stringValue;
        JsonObject m_objectValue;
        JsonArray m_arrayValue;
    };
};

JsonValueImpl::JsonValueImpl(JsonValue::Type type) {
    m_type = type;
}

JsonValueImpl::JsonValueImpl(const double value) {
    m_type = JsonValue::Type::Double;
    m_doubleValue = value;
}

JsonValueImpl::JsonValueImpl(const bool value) {
    m_type = JsonValue::Type::Bool;
    m_boolValue = value;
}

JsonValueImpl::JsonValueImpl(const std::string& value) {
    m_type = JsonValue::Type::String;
    constructString(value);
}

JsonValueImpl::JsonValueImpl(const JsonObject& value) {
    m_type = JsonValue::Type::Object;
    constructObject(value);
}

JsonValueImpl::JsonValueImpl(const JsonArray& value) {
    m_type = JsonValue::Type::Array;
    constructArray(value);
}

JsonValueImpl::JsonValueImpl(const JsonValueImpl& copy) {
    switch (copy.type()) {
        case JsonValue::Type::Null:
            break;
        case JsonValue::Type::Bool:
            m_boolValue = copy.m_boolValue;
            break;
        case JsonValue::Type::Double:
            m_doubleValue = copy.m_doubleValue;
            break;
        case JsonValue::Type::String:
            constructString(copy.m_stringValue);
            break;
        case JsonValue::Type::Object:
            constructObject(copy.m_objectValue);
            break;
        case JsonValue::Type::Array:
            constructArray(copy.m_arrayValue);
            break;
    }
    m_type = copy.m_type;
}

JsonValueImpl::~JsonValueImpl() {
    using Type = JsonValue::Type;
    if (type() == Type::String) destroyString();
    else if (type() == Type::Object) destroyObject();
    else if (type() == Type::Array) destroyArray();
}

void
JsonValueImpl::constructString(const std::string& value) {
    new (&m_stringValue) std::string(value);
}

void
JsonValueImpl::constructObject(const JsonObject& value) {
    new (&m_objectValue) JsonObject(value);
}

void
JsonValueImpl::constructArray(const JsonArray& value) {
    new (&m_arrayValue) JsonArray(value);
}

void
JsonValueImpl::destroyString() {
    using namespace std;
    m_stringValue.~string();
}

void
JsonValueImpl::destroyObject() {
    m_objectValue.~JsonObject();
}

void
JsonValueImpl::destroyArray() {
    m_arrayValue.~JsonArray();
}

double
JsonValueImpl::toDouble() const {
    return m_doubleValue;
}

bool
JsonValueImpl::toBool() const {
    return m_boolValue;
}

std::string
JsonValueImpl::toString() const {
    return m_stringValue;
}

JsonObject
JsonValueImpl::toObject() const {
    return m_objectValue;
}

JsonArray
JsonValueImpl::toArray() const {
    return m_arrayValue;
}

JsonValue::Type
JsonValueImpl::type() const {
    return m_type;
}

void
JsonValueImpl::swap(AbstractJsonValueImpl * other) {
    JsonValueImpl * otherImpl = dynamic_cast<JsonValueImpl*>(other);
    using Type = JsonValue::Type;
    switch (other->type()) {
        case Type::Null:
            break;
        case Type::Bool:
            prism::swap(m_boolValue, otherImpl->m_boolValue);
            break;
        case Type::Double:
            prism::swap(m_doubleValue, otherImpl->m_doubleValue);
            break;
        case Type::String:
            prism::swap(m_stringValue, otherImpl->m_stringValue);
            break;
        case JsonValue::Type::Object:
            prism::swap(m_objectValue, otherImpl->m_objectValue);
            break;
        case JsonValue::Type::Array:
            prism::swap(m_arrayValue, otherImpl->m_arrayValue);
            break;
    }
    prism::swap(m_type, otherImpl->m_type);
}
//==============================================================================
// JsonValue
//==============================================================================
JsonValue::JsonValue(JsonValue::Type type)
: m_impl{new JsonValueImpl(type)}
{}

JsonValue::JsonValue(const int value)
: m_impl{new JsonValueImpl(static_cast<double>(value))}
{}

JsonValue::JsonValue(const double value)
: m_impl{new JsonValueImpl(value)}
{}

JsonValue::JsonValue(const bool value)
: m_impl{new JsonValueImpl(value)}
{}

JsonValue::JsonValue(const std::string& value)
: m_impl{new JsonValueImpl(value)}
{}

JsonValue::JsonValue(const char* value)
: m_impl{new JsonValueImpl(std::string{value})}
{}

JsonValue::JsonValue(const JsonObject& value)
: m_impl{new JsonValueImpl(value)}
{}

JsonValue::JsonValue(const JsonArray& value)
: m_impl{new JsonValueImpl(value)}
{}

JsonValue::JsonValue(const JsonValue& copy) {
    switch (copy.type()) {
        case Type::Null: m_impl.reset(new JsonValueImpl(Type::Null)); break;
        case Type::Bool: m_impl.reset(new JsonValueImpl(copy.toBool())); break;
        case Type::Double: m_impl.reset(new JsonValueImpl(copy.toDouble())); break;
        case Type::String: m_impl.reset(new JsonValueImpl(copy.toString())); break;
        case Type::Object: m_impl.reset(new JsonValueImpl(copy.toObject())); break;
        case Type::Array: m_impl.reset(new JsonValueImpl(copy.toArray())); break;
    }
}

JsonValue::JsonValue(AbstractJsonValueImpl* impl)
{
    m_impl.reset(impl);
}

JsonValue&
JsonValue::operator=(const JsonValue& rhs) {
    std::shared_ptr<AbstractJsonValueImpl> copyRhsImpl = rhs.m_impl;
    copyRhsImpl.swap(this->m_impl);
    return *this;
}

JsonValue::~JsonValue()
{}

const bool
JsonValue::isNull() const {
    return type() == Type::Null;
}

const bool
JsonValue::isDouble() const {
    return type() == Type::Double;
}

const bool
JsonValue::isBool() const {
    return type() == Type::Bool;
}

const bool
JsonValue::isString() const {
    return type() == Type::String;
}

const bool
JsonValue::isObject() const {
    return type() == Type::Object;
}

const bool
JsonValue::isArray() const {
    return type() == Type::Array;
}

double
JsonValue::toDouble() const {
    if (isDouble()) return m_impl->toDouble();
    throw prism::InvalidConversionException("Invalid conversion to double");
}

bool
JsonValue::toBool() const {
    if (isBool()) return m_impl->toBool();
    throw prism::InvalidConversionException("Invalid conversion to bool");
}

std::string
JsonValue::toString() const {
    if (isString()) return m_impl->toString();
    throw prism::InvalidConversionException("Invalid conversion to string");
}

JsonObject
JsonValue::toObject() const {
    if (isObject()) return m_impl->toObject();
    throw prism::InvalidConversionException("Invalid conversion to object");
}

JsonArray
JsonValue::toArray() const {
    if (isArray()) return m_impl->toArray();
    throw prism::InvalidConversionException("Invalid conversion to array");
}

JsonValue::Type
JsonValue::type() const {
    return m_impl->type();
}

const bool
operator==(const JsonValue& lhs, const JsonValue& rhs) {
    using Type = JsonValue::Type;
    if (lhs.type() != rhs.type()) return false;
    switch(lhs.type()) {
        case Type::Null: return true; break;
        case Type::Bool: if (lhs.toBool() == rhs.toBool()) {return true;} break;
        case Type::Double: if (lhs.toDouble() == rhs.toDouble()) {return true;} break;
        case Type::String: if (lhs.toString() == rhs.toString()) {return true;} break;
        case Type::Object: if (lhs.toObject() == rhs.toObject()) {return true;} break;
        case Type::Array: if (lhs.toArray() == rhs.toArray()) {return true;} break;
    }
    return false;
}

const bool
operator!=(const JsonValue& lhs, const JsonValue& rhs) {
    return !(lhs == rhs);
}

std::ostream&
operator<<(std::ostream& out, const JsonValue& jv) {
    using Type = JsonValue::Type;
    switch(jv.type()) {
        case Type::Null: out << "Null"; break;
        case Type::Bool: out << jv.toBool(); break;
        case Type::Double: out << jv.toDouble(); break;
        case Type::String: out << jv.toString(); break;
        case Type::Object: out << "Object"; break;
        case Type::Array: out << "Array"; break;
    }
    return out;
}

PRISM_END_NAMESPACE
