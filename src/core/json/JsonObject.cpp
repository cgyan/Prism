#include <prism/global>
#include <prism/JsonObject>

PRISM_BEGIN_NAMESPACE

const bool
JsonObject::empty() const {
    return m_empty;
}

const int
JsonObject::count() const {
    if (empty())return 0;
    return 1;
}

const int
JsonObject::size() const {
    return count();
}

void
JsonObject::insert(const std::string& key, const std::string& value) {
    m_empty = false;
}

const bool operator==(const JsonObject& lhs, const JsonObject& rhs) {
    return true;
}

PRISM_END_NAMESPACE
