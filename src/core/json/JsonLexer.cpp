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
    JsonLexerImpl(const std::string& input);

    JsonToken getNextToken() override;
    const bool stringIsStillBeingProcessed() const override;
private:
    const bool foundWhitespace() const;
    const bool foundComma() const;
    const bool foundColon() const;
    const bool foundLeftCurlyBrace() const;
    const bool foundRightCurlyBrace() const;
    const bool foundLeftBracket() const;
    const bool foundRightBracket() const;
    const bool foundLiteralTrue() const;
    const bool foundLiteralFalse() const;
    const bool foundLiteralNull() const;
    const bool foundString() const;
    const bool foundNumber() const;
    const bool foundInvalidSequenceOfChars() const;
    void ignoreWhitespace();
private:
    std::string m_input;
    std::string::const_iterator lexemeBegin;
    std::string::const_iterator lexemeEnd;
    std::string::const_iterator inputEnd;
};

JsonLexerImpl::JsonLexerImpl(const std::string& input)
: m_input{input}
{
    lexemeBegin = m_input.cbegin();
    lexemeEnd = lexemeBegin;
    inputEnd = m_input.end();
}

const bool
JsonLexerImpl::stringIsStillBeingProcessed() const {
    if (lexemeBegin != inputEnd && lexemeEnd <= inputEnd) return true;
    return false;
}

const bool
JsonLexerImpl::foundWhitespace() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex("[[:blank:]]"));
}

const bool
JsonLexerImpl::foundComma() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(","));
}

const bool
JsonLexerImpl::foundLeftCurlyBrace() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\{)"));
}

const bool
JsonLexerImpl::foundColon() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(:)"));
}

const bool
JsonLexerImpl::foundRightCurlyBrace() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\})"));
}

const bool
JsonLexerImpl::foundLeftBracket() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\[)"));
}

const bool
JsonLexerImpl::foundRightBracket() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"(\])"));
}

const bool
JsonLexerImpl::foundLiteralTrue() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex("true"));
}

const bool
JsonLexerImpl::foundLiteralFalse() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex("false"));
}

const bool
JsonLexerImpl::foundLiteralNull() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex("null"));
}

const bool
JsonLexerImpl::foundString() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex(R"("[[:print:]]*")"));
}

const bool
JsonLexerImpl::foundNumber() const {
    return std::regex_match(lexemeBegin, lexemeEnd, std::regex("-?[0-9]"));
}


const bool
JsonLexerImpl::foundInvalidSequenceOfChars() const {
    return lexemeBegin != inputEnd;
}

void
JsonLexerImpl::ignoreWhitespace() {
    ++lexemeBegin;
    ++lexemeEnd;
}

JsonToken
JsonLexerImpl::getNextToken() {
    while (stringIsStillBeingProcessed()) {
        if (foundWhitespace()) {
            ignoreWhitespace();
        }
        else if (foundComma()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::Comma);
        }
        else if (foundLeftCurlyBrace()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::LeftBrace);
        }
        else if (foundColon()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::Colon);
        }
        else if (foundRightCurlyBrace()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::RightBrace);
        }
        else if (foundLeftBracket()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::LeftBracket);
        }
        else if (foundRightBracket()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::RightBracket);
        }
        else if (foundLiteralTrue()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::BoolLiteral, "true");
        }
        else if (foundLiteralFalse()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::BoolLiteral, "false");
        }
        else if (foundLiteralNull()) {
            lexemeBegin = lexemeEnd;
            return JsonToken(JsonToken::Type::NullLiteral);
        }
        else if (foundString()) {
            JsonToken token(JsonToken::Type::String, std::string(lexemeBegin+1, lexemeEnd-1));
            lexemeBegin = lexemeEnd;
            return token;
        }
        else if (foundNumber()) {
            std::string base = R"(-?(0|[1-9]+))";
            std::string optFraction = R"(\.?([0-9]+)?)";
            std::string optExponent = R"((e|E)?(-|\+)?([0-9]+)?)";
            std::regex rxNumber(base + optFraction + optExponent);

            while(std::regex_match(lexemeBegin, lexemeEnd, std::regex(rxNumber)) && lexemeEnd <= inputEnd) {
                ++lexemeEnd;
            }
            std::string numLexeme = std::string(lexemeBegin, --lexemeEnd);
            lexemeBegin += numLexeme.size();
            return JsonToken(JsonToken::Type::Number, numLexeme);
        }
        else {
            ++lexemeEnd;
        }
    } // end while loop

    if (foundInvalidSequenceOfChars()) {
        std::string msg = "Lexical error: unrecognized input";
        throw prism::JsonLexerException(msg);
    }

    // should never reach here as one of the conditionals above should return
    // otherwise the exception will be thrown
    return JsonToken();
}
//==============================================================================
// JsonLexer
//==============================================================================
JsonLexer::JsonLexer(const std::string& input)
: m_impl{new JsonLexerImpl{input}}
{}

const bool
JsonLexer::hasMoreTokens() const {
    return m_impl->stringIsStillBeingProcessed();
}

JsonToken
JsonLexer::getNextToken() {
    return m_impl->getNextToken();
}

PRISM_END_NAMESPACE
