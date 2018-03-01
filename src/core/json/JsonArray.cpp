#include <prism/global>
#include <prism/JsonArray>
#include <prism/AbstractJsonArrayImpl>
#include <prism/JsonValue>
#include <prism/algorithm>
#include <prism/OutOfBoundsException>
#include <prism/Vector>
#include <ostream>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonArrayImpl
//==============================================================================
class JsonArrayImpl : public AbstractJsonArrayImpl {
public:
    using iterator = JsonArray::iterator;
    using const_iterator = JsonArray::const_iterator;
public:
    JsonArrayImpl() = default;

    template <typename Iter>
    JsonArrayImpl(Iter first, Iter last) {
        m_vec.reserve(last - first);
        while (first != last)
            m_vec.append(*first++);
    }

    JsonArrayImpl*
    clone() const override {
        return new JsonArrayImpl(*this);
    }

    const int
    numElements() const override {
        return m_vec.size();
    }

    void
    insert(const_iterator pos, const JsonValue& value) override {
        m_vec.insert(pos, value);
    }

    void
    remove(const_iterator pos) override {
        m_vec.remove(pos);
    }

    const bool
    containsElement(const JsonValue& value) const override {
        return prism::count(m_vec.cbegin(), m_vec.cend(), value);
    }

    iterator
    begin() override {
        return m_vec.begin();
    }

    iterator
    end() override {
        return m_vec.end();
    }
private:
    prism::Vector<JsonValue> m_vec{};
};
//==============================================================================
// JsonArray
//==============================================================================
JsonArray::JsonArray()
: m_impl{new JsonArrayImpl}
{}

JsonArray::JsonArray(std::initializer_list<JsonValue> il)
: m_impl{new JsonArrayImpl(il.begin(), il.end())}
{}

JsonArray::JsonArray(const JsonArray& copy)
: m_impl{copy.m_impl->clone()}
{}

JsonArray::JsonArray(AbstractJsonArrayImpl * impl)
: m_impl{impl}
{}

JsonArray&
JsonArray::operator=(const JsonArray& rhs) {
    m_impl.reset(rhs.m_impl->clone());
    return *this;
}

JsonValue&
JsonArray::at(const int index) {
    if (index >= m_impl->numElements())
        throw prism::OutOfBoundsException(index);
    return *(m_impl->begin() + index);
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
    return m_impl->containsElement(value);
}

void
JsonArray::swap(JsonArray& other) {
    std::swap(this->m_impl, other.m_impl);
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
    return *(m_impl->begin() + index);
}

const bool
JsonArray::operator==(const JsonArray& rhs) const {
    return prism::equal(this->begin(), this->end(), rhs.begin());
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
