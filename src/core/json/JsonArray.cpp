#include <prism/global>
#include <prism/JsonArray>
#include <prism/JsonValue>
#include <prism/algorithm>
#include <prism/OutOfBoundsException>
#include <ostream>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonArrayImpl
//==============================================================================
class JsonArray::JsonArrayImpl {
public:
    using iterator = JsonArray::iterator;
    using const_iterator = JsonArray::const_iterator;
public:
    JsonArrayImpl() = default;

    template <typename Iter>
    JsonArrayImpl(Iter first, Iter last) {
        while (first != last)
            m_vec.append(*first++);
    }

    const int
    numElements() const {
        return m_vec.size();
    }

    void
    insert(const_iterator pos, const JsonValue& value) {
        m_vec.insert(pos, value);
    }

    void
    remove(const_iterator pos) {
        m_vec.remove(pos);
    }

    JsonValue&
    elementAt(const int index) {
        return m_vec[index];
    }

    const bool
    containsElements(const JsonValue& value) const {
        return prism::count(m_vec.cbegin(), m_vec.cend(), value);
    }

    iterator
    begin() {
        return m_vec.begin();
    }

    iterator
    end() {
        return m_vec.end();
    }

    const_iterator
    begin() const {
        return m_vec.cbegin();
    }

    const_iterator
    end() const {
        return m_vec.cend();
    }

    void
    swap(JsonArrayImpl& other) {
        prism::swap(this->m_vec, other.m_vec);
    }

    const bool
    operator==(const JsonArrayImpl& rhs) const {
        if (this->m_vec == rhs.m_vec) return true;
        return false;
    }
private:
    prism::Vector<JsonValue> m_vec{};
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
    JsonArrayImpl * newImpl = new JsonArrayImpl(rhs.begin(), rhs.end());
    m_impl.reset(newImpl);
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
    m_impl->insert(end(), value);
}

void
JsonArray::prepend(const JsonValue& value) {
    m_impl->insert(begin(), value);
}

void
JsonArray::insert(JsonArray::const_iterator insertBefore, const JsonValue& value) {
    m_impl->insert(insertBefore, value);
}

void
JsonArray::insert(const int index, const JsonValue& value) {
    m_impl->insert(begin() + index, value);
}

void
JsonArray::removeAt(const int index) {
    m_impl->remove(this->begin() + index);
}

void
JsonArray::remove(JsonArray::const_iterator pos) {
    m_impl->remove(pos);
}

const bool
JsonArray::contains(const JsonValue& value) const {
    return m_impl->containsElements(value);
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
JsonArray::operator==(const JsonArray& rhs) const {
    if (*this->m_impl == *rhs.m_impl) return true;
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
