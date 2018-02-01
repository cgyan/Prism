#include <prism/global>
#include <prism/JsonArray>
#include <prism/JsonValue>
#include <prism/OutOfBoundsException>
#include <ostream>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonArrayImpl
//==============================================================================
class JsonArray::JsonArrayImpl {
public:
    using const_iterator = std::vector<JsonValue>::const_iterator;
public:
    JsonArrayImpl() = default;

    template <typename Iter>
    JsonArrayImpl(Iter first, Iter last) {
        while (first != last)
            m_vec.push_back(*first++);
    }

    const int
    numElements() const {
        return m_vec.size();
    }

    void
    insertAtEnd(const JsonValue& value) {
        m_vec.push_back(value);
    }

    void
    insert(const_iterator pos, const JsonValue& value) {
        m_vec.insert(pos, value);
    }

    void
    erase(const_iterator pos) {
        m_vec.erase(pos);
    }

    JsonValue&
    elementAt(const int index) {
        return m_vec[index];
    }

    const_iterator
    begin() const {
        return m_vec.cbegin();
    }

    const_iterator
    end() const {
        return m_vec.cend();
    }

    const bool
    operator==(const JsonArrayImpl& rhs) {
        if (this->m_vec == rhs.m_vec) return true;
        return false;
    }
private:
    std::vector<JsonValue> m_vec{};
};
//==============================================================================
// JsonArray
//==============================================================================
JsonArray::JsonArray()
: m_impl{new JsonArray::JsonArrayImpl}
{}

JsonArray::JsonArray(std::initializer_list<JsonValue> il)
: m_impl{new JsonArray::JsonArrayImpl(il.begin(), il.end())}
{}

JsonArray::JsonArray(const JsonArray& copy)
: m_impl{new JsonArray::JsonArrayImpl(copy.begin(), copy.end())}
{}

JsonArray&
JsonArray::operator=(const JsonArray& rhs) {
    m_impl.reset(new JsonArrayImpl(rhs.begin(), rhs.end()));
    return *this;
}

JsonValue&
JsonArray::at(const int index) {
    if (index >= m_impl->numElements())
        throw prism::OutOfBoundsException(index);
    return m_impl->elementAt(index);
}

const bool
JsonArray::empty() const {
    return size() == 0;
}

const int
JsonArray::size() const {
    return m_impl->numElements();
}

void
JsonArray::append(const JsonValue& value) {
    m_impl->insertAtEnd(value);
}

void
JsonArray::prepend(const JsonValue& value) {
    m_impl->insert(begin(), value);
}

void
JsonArray::removeAt(const int index) {
    m_impl->erase(this->begin() + index);
}

void
JsonArray::erase(JsonArray::const_iterator pos) {
    m_impl->erase(pos);
}

JsonArray::const_iterator
JsonArray::begin() const {
    return m_impl->begin();
}

JsonArray::const_iterator
JsonArray::end() const {
    return m_impl->end();
}

JsonValue&
JsonArray::operator[](const int index) {
    return m_impl->elementAt(index);
}

const bool
operator==(const JsonArray& lhs, const JsonArray& rhs) {
    if (*lhs.m_impl == *rhs.m_impl) return true;
    return false;
}

std::ostream&
operator<<(std::ostream& out, const JsonArray& jv) {
    out << "JsonArray [" << &jv << "] = ";
    for (auto it = jv.begin(); it != jv.end(); ++it) {
        out << *it << ", ";
    }
    return out;
}

PRISM_END_NAMESPACE
