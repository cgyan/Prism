#include <prism/JsonObject>
#include <prism/JsonValue>
#include <map>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonObjectData
//==============================================================================
class JsonObject::JsonObjectData {
private:
    using Pair = std::pair<std::string, JsonValue>;
    // TODO: use prism::Map when written instead of std::map
    std::map<std::string, JsonValue> map;
public:
    JsonObjectData() = default;

    template <typename Iter>
    JsonObjectData(Iter first, Iter last) {
        for (auto it = first; it != last; ++it)
            insertNewMember((*it).first, (*it).second);
    }

    const int
    numMembers() {
        return map.size();
    }

    void
    insertNewMember(const std::string& key, const JsonValue& value) {
        map[key] = value;
    }

    void
    removeMember(const std::string& key) {
        map.erase(key);
    }

    JsonValue&
    value(const std::string& key) {
        return map[key];
    }

    std::list<std::string>
    keys() const {
        std::list<std::string> ret;
        for (auto cit = map.cbegin(); cit != map.cend(); ++cit) {
            ret.push_back((*cit).first);
        }
        return ret;
    }

    const bool
    containsKey(const std::string& key) {
        JsonObject::iterator it = findMember(key);
        if (it == end()) return false;
        return true;
    }

    JsonObject::iterator
    findMember(const std::string& key) {
        return map.find(key);
    }

    JsonObject::iterator
    begin() {
        return map.begin();
    }

    JsonObject::iterator
    end() {
        return map.end();
    }

    const bool
    operator==(const JsonObjectData& rhs) {
        return this->map == rhs.map;
    }
};
//==============================================================================
// JsonObject
//==============================================================================
JsonObject::JsonObject()
    : m_impl{new JsonObjectData}
{}

JsonObject::JsonObject(std::initializer_list<std::pair<std::string, JsonValue>> il)
    : m_impl{new JsonObjectData(il.begin(), il.end())}
{}

JsonObject::JsonObject(const JsonObject& copy)
: m_impl{new JsonObjectData(copy.begin(), copy.end())}
{}

JsonObject&
JsonObject::operator=(const JsonObject& rhs) {
    m_impl.reset(new JsonObjectData(rhs.begin(), rhs.end()));
    return *this;
}

void
JsonObject::insert(const std::string& key, const JsonValue& value) {
    m_impl->insertNewMember(key, value);
}

void
JsonObject::remove(const std::string& key) {
    m_impl->removeMember(key);
}

void
JsonObject::erase(JsonObject::iterator it) {
    m_impl->removeMember((*it).first);
}

const int
JsonObject::size() const {
    return m_impl->numMembers();
}

const bool
JsonObject::empty() const {
    if (size() == 0) return true;
    return false;
}

const bool
JsonObject::contains(const std::string& key) const {
    return m_impl->containsKey(key);
}

JsonValue&
JsonObject::operator[](const std::string& key) {
    return m_impl->value(key);
}

std::list<std::string>
JsonObject::keys() const {
    return m_impl->keys();
}

JsonObject::iterator
JsonObject::find(const std::string& key) {
    return m_impl->findMember(key);
}

JsonObject::iterator
JsonObject::begin() {
    return m_impl->begin();
}

JsonObject::const_iterator
JsonObject::begin() const {
    return m_impl->begin();
}

JsonObject::const_iterator
JsonObject::cbegin() const {
    return m_impl->begin();
}

JsonObject::iterator
JsonObject::end() {
    return m_impl->end();
}

JsonObject::const_iterator
JsonObject::end() const {
    return m_impl->end();
}

JsonObject::const_iterator
JsonObject::cend() const {
    return m_impl->end();
}

const bool
JsonObject::operator==(const JsonObject& rhs) {
    return *this->m_impl == *rhs.m_impl;
}

std::ostream&
operator<<(std::ostream& out, const JsonObject& jo) {
    out << "JsonObject [" << &jo << "] \n";
    for (auto it = jo.begin(); it != jo.end(); ++it) {
        out << "\t" << (*it).first;
        JsonValue jv = (*it).second;
        if (jv.type() == JsonValue::Type::Null) out << " Null \n";
        else if (jv.type() == JsonValue::Type::Double) out << jv.toDouble() << " \n";
        else if (jv.type() == JsonValue::Type::Bool) out << jv.toBool() << " \n";
        // else if (jv.type() == JsonValue::Type::String) out << "String" << " \n";
        // else if (jv.type() == JsonValue::Type::Object) out << " Object \n";
        // else if (jv.type() == JsonValue::Type::Array) out << " Array \n";
    }
    return out;
}

PRISM_END_NAMESPACE
