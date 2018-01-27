#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class JsonObject {
public:
    const bool empty() const;
    const int count() const;
    const int size() const;
    void insert(const std::string& key, const std::string& value);
private:
    bool m_empty{true};
};

const bool operator==(const JsonObject& lhs, const JsonObject& rhs);

PRISM_END_NAMESPACE
