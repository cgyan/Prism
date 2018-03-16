#ifndef PRISM_PAIR_H_
#define PRISM_PAIR_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

template <typename T1, typename T2>
class Pair {
public:
    Pair() = default;
    Pair(const T1& first, const T2& second);
    Pair(const Pair<T1,T2>& rhs);
    Pair(Pair<T1,T2>&& rhs);
    Pair<T1,T2>& operator=(const Pair<T1,T2>& rhs);
    Pair<T1,T2>& operator=(Pair<T1,T2>&& rhs);

    void swap(Pair<T1,T2>& other);

public:
    T1 first{};
    T2 second{};
};

template <typename T1, typename T2>
const bool operator==(const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs);
template <typename T1, typename T2>
const bool operator!=(const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs);

template <typename T1, typename T2>
Pair<T1,T2>::Pair(const T1& first, const T2& second)
: first{first}, second{second}
{}

template <typename T1, typename T2>
Pair<T1,T2>::Pair(const Pair<T1,T2>& rhs)
: first{rhs.first}, second{rhs.second}
{}

template <typename T1, typename T2>
Pair<T1,T2>::Pair(Pair<T1,T2>&& rhs) {
    *this = std::move(rhs);
    Pair<T1,T2>().swap(rhs);
}

template <typename T1, typename T2>
Pair<T1,T2>&
Pair<T1,T2>::operator=(const Pair<T1,T2>& rhs) {
    if (*this != rhs) {
        first = rhs.first;
        second = rhs.second;
    }
    return *this;
}

template <typename T1, typename T2>
Pair<T1,T2>&
Pair<T1,T2>::operator=(Pair<T1,T2>&& rhs) {
    if (*this != rhs) {
        first = std::move(rhs.first);
        second = std::move(rhs.second);
        rhs = Pair<T1,T2>();
    }
    return *this;
}

template <typename T1, typename T2>
void
Pair<T1,T2>::swap(Pair<T1,T2>& other) {
    std::swap(this->first, other.first);
    std::swap(this->second, other.second);
}

template <typename T1, typename T2>
const bool
operator==(const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
const bool
operator!=(const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs) {
    return !(lhs == rhs);
}

template <typename T1, typename T2>
Pair<T1,T2>
make_pair(const T1& t=T1(), const T2& u=T2()) {
    return prism::Pair<T1,T2>(t,u);
}

PRISM_END_NAMESPACE

#endif
