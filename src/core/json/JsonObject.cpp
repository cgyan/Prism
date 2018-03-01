#include <prism/JsonObject>
#include <prism/AbstractJsonObjectImpl>
#include <prism/algorithm>
#include <map>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonObjectData
//==============================================================================
class JsonObjectImpl : public AbstractJsonObjectImpl {
public:
    JsonObjectImpl() = default;

    template <typename Iter>
    JsonObjectImpl(Iter first, Iter last) {
        for (auto it = first; it != last; ++it)
            insertNewMember((*it).first, (*it).second);
    }

    JsonObjectImpl*
    clone() const override {
        return new JsonObjectImpl(*this);
    }

    const int
    numMembers() const override {
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
    equals(AbstractJsonObjectImpl * rhs) const override {
        JsonObjectImpl * rhsImpl = dynamic_cast<JsonObjectImpl*>(rhs);
        return this->map == rhsImpl->map;
    }
private:
    using Pair = std::pair<std::string, JsonValue>;
    // TODO: use prism::Map when written instead of std::map
    std::map<std::string, JsonValue> map{};
};
//==============================================================================
// JsonObject
//==============================================================================
JsonObject::JsonObject()
: m_impl{new JsonObjectImpl}
{}

JsonObject::JsonObject(std::initializer_list<std::pair<std::string, JsonValue>> il)
: m_impl{new JsonObjectImpl(il.begin(), il.end())}
{}

JsonObject::JsonObject(const JsonObject& copy)
: m_impl{copy.m_impl->clone()}
{}

JsonObject::JsonObject(AbstractJsonObjectImpl * impl)
: m_impl{impl}
{}

JsonObject&
JsonObject::operator=(const JsonObject& rhs) {
    m_impl.reset(rhs.m_impl->clone());
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
    iterator it = find(key);
    return (*it).second;
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
JsonObject::operator==(const JsonObject& rhs) const {
    return m_impl->equals(rhs.m_impl.get());
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
