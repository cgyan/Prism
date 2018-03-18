#ifndef PRISM_JSON_OBJECT_ITERATOR_H_
#define PRISM_JSON_OBJECT_ITERATOR_H_

#include <prism/global>
#include <prism/Vector>
#include <prism/JsonValue>
#include <type_traits>
#include <map>
#include <string>

PRISM_BEGIN_NAMESPACE

template <bool IsConst>
class JsonObjectIterator {
public:
    using iterator = JsonObjectIterator<false>;
    using const_iterator = JsonObjectIterator<true>;
    using Self = typename std::conditional<IsConst, const_iterator, iterator>::type;
    using value_type = JsonValue;
private:
    using MemberOrderPtr = Vector<std::string>*;
    using MapPtr = std::map<std::string, JsonValue>*;
public:
    JsonObjectIterator() = default;

    JsonObjectIterator(MemberOrderPtr memberOrder, MapPtr map, const int index=0)
    : memberOrder{memberOrder}, map{map}, index{index}
    {}

    JsonObjectIterator(const JsonObjectIterator<false>& copy)
    : memberOrder{copy.memberOrder}, map{copy.map}, index{copy.index}
    {}

    std::pair<const std::string, JsonValue>&
    operator*() const {
        std::string key = (*memberOrder)[index];
        std::map<std::string, JsonValue>::iterator it = map->find(key);
        return *it;
    }

    Self&
    operator++() {
        return *this += 1;
    }

    Self
    operator++(int) {
        JsonObjectIterator copy = *this;
        *this += 1;
        return copy;
    }

    Self&
    operator+=(const int num) {
        index += num;
        return *this;
    }

    Self
    operator--(int) {
        JsonObjectIterator copy = *this;
        *this += -1;
        return copy;
    }

    Self&
    operator--() {
        return *this += -1;
    }

    Self&
    operator-=(const int num) {
        return *this += -num;
    }

    Self
    operator+(const int distance) {
        Self copy = *this;
        return copy += distance;
    }

    Self
    operator-(const int distance) {
        Self copy = *this;
        return copy += -distance;
    }

    const int
    operator-(JsonObjectIterator other) {
        return this->index - other.index;
    }

    const bool operator==(const Self& rhs) const {
        return this->index == rhs.index;
    }

    const bool operator!=(const Self& rhs) const {
        return this->index != rhs.index;
    }

public:
    MemberOrderPtr memberOrder;
    MapPtr map;
    int index;
};

PRISM_END_NAMESPACE

#endif
