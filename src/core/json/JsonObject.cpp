#include <prism/JsonObject>
#include <prism/AbstractJsonObjectImpl>
#include <prism/Pair>
#include <prism/algorithm>
#include <map>

PRISM_BEGIN_NAMESPACE

//==============================================================================
// JsonObjectData
//==============================================================================
class JsonObjectImpl : public AbstractJsonObjectImpl {
public:
    using iterator = JsonObject::iterator;
    using const_iterator = JsonObject::const_iterator;
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
        return m_map.size();
    }

    void
    insertNewMember(const std::string& key, const JsonValue& value) {
        if (!m_memberOrder.contains(key)) {
            m_memberOrder << key;
        }
        m_map[key] = value;
        assert(m_memberOrder.size() == m_map.size());
    }

    void
    removeMember(const std::string& key) {
        m_memberOrder.removeAll(key);
        m_map.erase(key);
        assert(m_memberOrder.size() == m_map.size());
    }

    prism::Vector<std::string>
    keys() const {
        return m_memberOrder;
    }

    const bool
    containsKey(const std::string& key) {
        if (m_memberOrder.contains(key)) return true;
        return false;
    }

    JsonObject::iterator
    findMember(const std::string& key) {
        const int index = m_memberOrder.indexOf(key);
        return iterator(&m_memberOrder, &m_map, index);
    }

    JsonObject::iterator
    begin() {
        return iterator(&m_memberOrder, &m_map, 0);
    }

    JsonObject::iterator
    end() {
        return iterator(&m_memberOrder, &m_map, m_map.size());
    }

    const bool
    equals(AbstractJsonObjectImpl * rhs) const override {
        JsonObjectImpl * rhsImpl = dynamic_cast<JsonObjectImpl*>(rhs);
        return this->m_memberOrder == rhsImpl->m_memberOrder && this->m_map == rhsImpl->m_map;
    }
private:
    // using Pair = std::pair<std::string, JsonValue>;
    // TODO: use prism::Map when written instead of std::map
    prism::Vector<std::string> m_memberOrder;
    std::map<std::string, JsonValue> m_map{};
};
//==============================================================================
// JsonObject
//==============================================================================
JsonObject::JsonObject()
: m_impl{new JsonObjectImpl}
{}

JsonObject::JsonObject(std::initializer_list<prism::Pair<std::string, JsonValue>> il)
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

prism::Vector<std::string>
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
