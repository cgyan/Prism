#include <prism/global>
#include <prism/JsonLexer>
#include <prism/AbstractJsonLexerImpl>
#include <prism/JsonToken>
#include <prism/EmptyException>
#include <prism/JsonLexerException>
#include <string>
#include <regex>
#include <iostream>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonLexerImpl
//==============================================================================
class JsonLexerImpl : public AbstractJsonLexerImpl {
public:
    JsonLexerImpl() = default;
    std::queue<JsonToken>& tokens() override;
    void addToken(JsonToken::Type type, const std::string& val="") override;
    void tokenize(const std::string& input) override;
private:
    std::queue<JsonToken> m_tokens{};
};

std::queue<JsonToken>&
JsonLexerImpl::tokens() {
    return m_tokens;
}

void
JsonLexerImpl::addToken(JsonToken::Type type, const std::string& value) {
    JsonToken tk(type, value);
    m_tokens.push(tk);
}

void
JsonLexerImpl::tokenize(const std::string& input) {
    std::string::const_iterator lexemeBegin = input.cbegin();
    std::string::const_iterator lexemeEnd = lexemeBegin;
    std::string::const_iterator inputEnd = input.cend();

    while(lexemeBegin != inputEnd && lexemeEnd <= inputEnd) {
        if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("[[:blank:]]"))) {
            ++lexemeBegin;
            ++lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(","))) {
            addToken(JsonToken::Type::Comma);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\{)"))) {
            addToken(JsonToken::Type::LeftBrace);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(:)"))) {
            addToken(JsonToken::Type::Colon);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\})"))) {
            addToken(JsonToken::Type::RightBrace);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\[)"))) {
            addToken(JsonToken::Type::LeftBracket);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\])"))) {
            addToken(JsonToken::Type::RightBracket);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("true"))) {
            addToken(JsonToken::Type::BoolLiteral, "true");
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("false"))) {
            addToken(JsonToken::Type::BoolLiteral, "false");
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("null"))) {
            addToken(JsonToken::Type::NullLiteral);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"("[[:print:]]*")"))) {
            addToken(JsonToken::Type::String, std::string(lexemeBegin+1, lexemeEnd-1));
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("-?[0-9]"))) {
            std::string base = R"(-?(0|[1-9]+))";
            std::string optFraction = R"(\.?([0-9]+)?)";
            std::string optExponent = R"((e|E)?(-|\+)?([0-9]+)?)";
            std::regex rxNumber(base + optFraction + optExponent);

            while(std::regex_match(lexemeBegin, lexemeEnd, std::regex(rxNumber)) && lexemeEnd <= inputEnd) {
                ++lexemeEnd;
            }
            std::string numLexeme = std::string(lexemeBegin, --lexemeEnd);
            addToken(JsonToken::Type::Number, numLexeme);
            lexemeBegin += numLexeme.size();
        }
        else {
            ++lexemeEnd;
        }
    }
    if (lexemeBegin != inputEnd) {
        std::string msg = "Lexical error: unrecognized input";
        throw prism::JsonLexerException(msg);
    }
}
//==============================================================================
// JsonLexer
//==============================================================================
JsonLexer::JsonLexer(const std::string& input)
: m_impl{new JsonLexerImpl}
{
    try {
        m_impl->tokenize(input);
    }
    catch(const JsonLexerException& ex) {
        throw ex;
    }
}

const bool
JsonLexer::hasNext() const {
    if (m_impl->tokens().size()) return true;
    return false;
}

JsonToken
JsonLexer::next() {
    if (hasNext()) {
        JsonToken ret = m_impl->tokens().front();
        m_impl->tokens().pop();
        return ret;
    }
    throw EmptyException();
}

PRISM_END_NAMESPACE
