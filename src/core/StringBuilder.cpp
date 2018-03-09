#include <prism/global>
#include <prism/StringBuilder>
#include <string>
#include <sstream>

PRISM_BEGIN_NAMESPACE

class StringBuilderImpl {
public:
    StringBuilderImpl() = default;

    StringBuilderImpl(const std::string& string) {
        append(string);
    }

    const bool empty() const {
        return size() == 0;
    }

    const int size() const {
        return toString().size();
    }

    const std::string toString() const {
        return m_ss.str();
    }

    void clear() {
        m_ss = std::stringstream{};
    }

    void append(const char c) {
        m_ss << c;
    }

    void append(const char * string) {
        int i = 0;
        while (string[i] != '\0')
            append(string[i++]);
    }

    void append(const std::string& string) {
        m_ss << string;
    }

    void append(const bool b) {
        if (b) m_ss << "true";
        else m_ss << "false";
    }

    void append(const int i) {
        m_ss << i;
    }

    void append(const double d) {
        m_ss << d;
    }

    void prepend(const char c) {
        StringBuilder sb;
        sb.append(c);
        m_ss.str(sb.toString() + m_ss.str());
    }

    void prepend(const char * string) {
        StringBuilder sb;
        sb.append(string);
        m_ss.str(sb.toString() + m_ss.str());
    }

    void prepend(const std::string& string) {
        m_ss.str(string + m_ss.str());
    }

    void prepend(const bool b) {
        StringBuilder sb;
        sb.append(b);
        m_ss.str(sb.toString() + m_ss.str());
    }

    void prepend(const int i) {
        StringBuilder sb;
        sb.append(i);
        m_ss.str(sb.toString() + m_ss.str());
    }

    void prepend(const double d) {
        StringBuilder sb;
        sb.append(d);
        m_ss.str(sb.toString() + m_ss.str());
    }
private:
    std::stringstream m_ss;
};

StringBuilder::StringBuilder()
: m_impl{new StringBuilderImpl}
{}

StringBuilder::StringBuilder(const std::string& string)
: m_impl{new StringBuilderImpl(string)}
{}

const bool
StringBuilder::empty() const {
    return size() == 0;
}

const int
StringBuilder::size() const {
    return toString().size();
}

const std::string
StringBuilder::toString() const {
    return m_impl->toString();
}

void
StringBuilder::clear() {
    m_impl->clear();
}

void
StringBuilder::append(const char c) {
    m_impl->append(c);
}

void
StringBuilder::append(const char * string) {
    m_impl->append(string);
}

void
StringBuilder::append(const std::string& string) {
    m_impl->append(string);
}

void
StringBuilder::append(const bool b) {
    m_impl->append(b);
}

void
StringBuilder::append(const int i) {
    m_impl->append(i);
}

void
StringBuilder::append(const double d) {
    m_impl->append(d);
}

void
StringBuilder::prepend(const char c) {
    m_impl->prepend(c);
}

void
StringBuilder::prepend(const char * string) {
    m_impl->prepend(string);
}

void
StringBuilder::prepend(const std::string& string) {
    m_impl->prepend(string);
}

void
StringBuilder::prepend(const bool b) {
    m_impl->prepend(b);
}

void
StringBuilder::prepend(const int i) {
    m_impl->prepend(i);
}

void
StringBuilder::prepend(const double d) {
    m_impl->prepend(d);
}

PRISM_END_NAMESPACE
