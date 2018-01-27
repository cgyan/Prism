#include <prism/global>
#include <prism/JsonValue>
#include <prism/JsonObject>
#include <prism/InvalidConversionException>

PRISM_BEGIN_NAMESPACE

struct JsonValue::JsonValueData {
    Type m_type;

    union {
        bool m_boolValue;
        double m_doubleValue;
        JsonArray m_arrayValue;
        JsonObject m_objectValue;
        std::string m_stringValue;
    };

    JsonValueData() {}

    ~JsonValueData() {
        if (m_type == JsonValue::Type::String) destroyString();
        else if (m_type == JsonValue::Type::Object) destroyObject();
        else if (m_type == JsonValue::Type::Array) destroyArray();
    }

    void destroyString() {
        using namespace std;
        m_stringValue.~string();
    }

    void destroyObject() {
        m_objectValue.~JsonObject();
    }

    void destroyArray() {
        m_arrayValue.~JsonArray();
    }

    const std::string toString(const char * cstr) {
        char c = cstr[0];
        int i = 0;
        while (c != '\0') {
            c = cstr[++i];
        }
        return std::string(cstr, cstr + i);
    }

    void setString(const std::string& value) {
        using namespace std;
        new(&m_stringValue) string(value);
    }

    void setObject(const JsonObject& value) {
        new(&m_objectValue) JsonObject(value);
    }

    void setArray(const JsonArray& value) {
        new(&m_arrayValue) JsonArray(value);
    }

    void setBool(const bool value) {
        m_boolValue = value;
    }

    void setDouble(const double value) {
        m_doubleValue = value;
    }

    void setType(JsonValue::Type type) {
        m_type = type;
    }
};

JsonValue::JsonValue(JsonValue::Type type)
    : data{new JsonValueData}
{
    data->setType(type);
}

JsonValue::JsonValue(const double value)
    : data{new JsonValueData}
{
    data->setType(Type::Double);
    data->setDouble(value);
}

JsonValue::JsonValue(const bool value)
    : data{new JsonValueData}
{
    data->setType(Type::Bool);
    data->setBool(value);
}

JsonValue::JsonValue(const char * cstr)
    : data{new JsonValueData}
{
    *this = JsonValue(data->toString(cstr));
}

JsonValue::JsonValue(const std::string& value)
    : data{new JsonValueData}
{
    data->setType(Type::String);
    data->setString(value);
}

JsonValue::JsonValue(const JsonObject& value)
    : data{new JsonValueData}
{
    data->setType(Type::Object);
    data->setObject(value);
}

JsonValue::JsonValue(const JsonArray& value)
    : data{new JsonValueData}
{
    data->setType(Type::Array);
    data->setArray(value);
}

JsonValue::JsonValue(const JsonValue& copy)
    : data{new JsonValueData}
{
    switch (copy.type()) {
        case JsonValue::Type::Null: *this = JsonValue(JsonValue::Type::Null); break;
        case JsonValue::Type::Bool: *this = JsonValue(copy.toBool()); break;
        case JsonValue::Type::Double: *this = JsonValue(copy.toDouble()); break;
        case JsonValue::Type::String: *this = JsonValue(copy.toString()); break;
        case JsonValue::Type::Object: *this = JsonValue(copy.toObject()); break;
        case JsonValue::Type::Array: *this = JsonValue(copy.toArray()); break;
    }
}

JsonValue&
JsonValue::operator=(const JsonValue& rhs) {
    using Type = JsonValue::Type;
    if (this->isString() && rhs.isString()) {
        data->m_stringValue = rhs.toString();
        return *this;
    }
    else if (this->isObject() && rhs.isObject()) {
        data->m_objectValue = rhs.toObject();
        return *this;
    }
    else if (this->isArray() && rhs.isArray()) {
        data->m_arrayValue = rhs.toArray();
        return *this;
    }

    if (this->isString()) data->destroyString();
    else if (this->isObject()) data->destroyObject();
    else if (this->isArray()) data->destroyArray();

    switch (rhs.type()) {
        case Type::Null: break;
        case Type::Bool: data->setBool(rhs.toBool()); break;
        case Type::Double: data->setDouble(rhs.toDouble()); break;
        case Type::String: data->setString(rhs.toString()); break;
        case Type::Object: data->setObject(rhs.toObject()); break;
        case Type::Array: data->setArray(rhs.toArray()); break;
    }

    data->setType(rhs.type());
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
    if (isDouble()) return data->m_doubleValue;
    throw prism::InvalidConversionException("Invalid conversion to double");
}

bool
JsonValue::toBool() const {
    if (isBool()) return data->m_boolValue;
    throw prism::InvalidConversionException("Invalid conversion to bool");
}

std::string
JsonValue::toString() const {
    if (isString()) return data->m_stringValue;
    throw prism::InvalidConversionException("Invalid conversion to string");
}

JsonArray
JsonValue::toArray() const {
    if (isArray()) return data->m_arrayValue;
    throw prism::InvalidConversionException("Invalid conversion to array");
}

JsonObject
JsonValue::toObject() const {
    if (isObject()) return data->m_objectValue;
    throw prism::InvalidConversionException("Invalid conversion to object");
}

JsonValue::Type
JsonValue::type() const {
    return data->m_type;
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

PRISM_END_NAMESPACE
