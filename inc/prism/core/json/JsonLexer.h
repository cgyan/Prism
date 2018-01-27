#include <prism/global>
#include <prism/JsonToken>
#include <prism/EmptyException>
#include <string>
#include <queue>
#include <regex>
#include <ostream>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonLexer
//==============================================================================
class JsonLexer {
public:
    JsonLexer() = default;
    JsonLexer(const std::string& input);
    const bool hasNext() const;
    JsonToken next();
private:
    void tokenize(const std::string& input);
    void addToken(JsonToken::LexemeType type, const std::string& val="");
private:
    std::queue<JsonToken> tokens;
};

JsonLexer::JsonLexer(const std::string& input) {
    tokenize(input);
}

const bool
JsonLexer::hasNext() const {
    if (tokens.size()) return true;
    return false;
}

JsonToken
JsonLexer::next() {
    if (hasNext()) {
        JsonToken ret = tokens.front();
        tokens.pop();
        return ret;
    }
    throw EmptyException();
}

void
JsonLexer::addToken(JsonToken::LexemeType type, const std::string& value) {
    JsonToken tk(type, value);
    tokens.push(tk);
}

void
JsonLexer::tokenize(const std::string& input) {
    std::string::const_iterator lexemeBegin = input.cbegin();
    std::string::const_iterator lexemeEnd = lexemeBegin;
    std::string::const_iterator inputEnd = input.cend();

    while(lexemeBegin != inputEnd && lexemeEnd <= inputEnd) {
        if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("[[:blank:]]"))) {
            ++lexemeBegin;
            ++lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(","))) {
            addToken(JsonToken::LexemeType::COMMA);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\{)"))) {
            addToken(JsonToken::LexemeType::LEFT_BRACE);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(:)"))) {
            addToken(JsonToken::LexemeType::COLON);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\})"))) {
            addToken(JsonToken::LexemeType::RIGHT_BRACE);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\[)"))) {
            addToken(JsonToken::LexemeType::LEFT_BRACKET);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\])"))) {
            addToken(JsonToken::LexemeType::RIGHT_BRACKET);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("true"))) {
            addToken(JsonToken::LexemeType::BOOL_LITERAL, "true");
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("false"))) {
            addToken(JsonToken::LexemeType::BOOL_LITERAL, "false");
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex("null"))) {
            addToken(JsonToken::LexemeType::NULL_LITERAL);
            lexemeBegin = lexemeEnd;
        }
        else if (std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"("[[:print:]]*")"))) {
            addToken(JsonToken::LexemeType::STRING, std::string(lexemeBegin+1, lexemeEnd-1));
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
            addToken(JsonToken::LexemeType::NUMBER, numLexeme);
            lexemeBegin += numLexeme.size();
        }
        else {
            ++lexemeEnd;
        }
    }
}

PRISM_END_NAMESPACE
