#include <prism/global>
#include <prism/JsonDoc>
#include <prism/JsonArray>
#include <prism/JsonToken>
#include <prism/JsonStringBuilder>
#include <prism/JsonLexer>
#include <prism/JsonLexerException>
#include <prism/JsonParserException>
#include <prism/JsonSymbols>
#include <prism/Stack>
#include <map>

PRISM_BEGIN_NAMESPACE

const bool equivalent(JsonSymbol symbol, JsonToken::Type type) {
    if (symbol == JsonSymbol::T_LeftBrace && type == JsonToken::Type::LeftBrace) return true;
    else if (symbol == JsonSymbol::T_RightBrace && type == JsonToken::Type::RightBrace) return true;
    else if (symbol == JsonSymbol::T_String && type == JsonToken::Type::String) return true;
    else if (symbol == JsonSymbol::T_Colon && type == JsonToken::Type::Colon) return true;
    else if (symbol == JsonSymbol::T_Comma && type == JsonToken::Type::Comma) return true;
    else if (symbol == JsonSymbol::T_Number && type == JsonToken::Type::Number) return true;
    else if (symbol == JsonSymbol::T_Bool && type == JsonToken::Type::BoolLiteral) return true;
    else if (symbol == JsonSymbol::T_Null && type == JsonToken::Type::NullLiteral) return true;
    else if (symbol == JsonSymbol::T_LeftBracket && type == JsonToken::Type::LeftBracket) return true;
    else if (symbol == JsonSymbol::T_RightBracket && type == JsonToken::Type::RightBracket) return true;
    return false;
}

class JsonDocImpl {
public:
    JsonDocImpl() = default;

    JsonDocImpl(const std::string& json) {
        try {
            parseJson(json);
        }
        catch (const JsonParserException& ex) {
            m_valid = false;
            m_errorMsg = ex.errorMsg();
        }
        catch (const JsonLexerException& ex) {
            m_valid = false;
            m_errorMsg = ex.errorMsg();
        }
    }

    JsonDocImpl(const JsonObject& object)
    : m_object{object}
    {}

    JsonDocImpl(const JsonDocImpl& copy)
    : m_valid{copy.m_valid}, m_object{copy.m_object}
    {}

    const std::string errorMessage() const {
        return m_errorMsg;
    }

    void parseJson(const std::string& json) {
        using SymbolStack = prism::Stack<JsonSymbol>;
        SymbolStack ss;
        ss.push(JsonSymbol::NT_S);
;
        using JsonValueStack = prism::Stack<JsonValue>;
        JsonValueStack valueStack;
        valueStack.push(JsonValue(JsonObject()));

        using KeyStack = prism::Stack<std::string>;
        KeyStack keyStack;
        std::string rootKey = "root";
        keyStack.push(rootKey);

        using ParseTable = std::map<JsonSymbol, std::map<JsonToken::Type, int>>;
        ParseTable table;
        table[JsonSymbol::NT_S][JsonToken::Type::LeftBrace] = 1;
        table[JsonSymbol::NT_T][JsonToken::Type::RightBrace] = 2;
        table[JsonSymbol::NT_T][JsonToken::Type::String] = 3;
        table[JsonSymbol::NT_M][JsonToken::Type::String] = 4;
        table[JsonSymbol::NT_P][JsonToken::Type::String] = 5;
        table[JsonSymbol::NT_V][JsonToken::Type::Number] = 6;
        table[JsonSymbol::NT_Q][JsonToken::Type::RightBrace] = 7;
        table[JsonSymbol::NT_V][JsonToken::Type::BoolLiteral] = 8;
        table[JsonSymbol::NT_V][JsonToken::Type::NullLiteral] = 9;
        table[JsonSymbol::NT_V][JsonToken::Type::String] = 10;
        table[JsonSymbol::NT_V][JsonToken::Type::LeftBracket] = 11;
        table[JsonSymbol::NT_R][JsonToken::Type::LeftBracket] = 12;
        table[JsonSymbol::NT_E][JsonToken::Type::Number] = 13;
        table[JsonSymbol::NT_F][JsonToken::Type::RightBracket] = 14;
        table[JsonSymbol::NT_Q][JsonToken::Type::RightBracket] = 15;
        table[JsonSymbol::NT_E][JsonToken::Type::RightBracket] = 16;
        table[JsonSymbol::NT_F][JsonToken::Type::Comma] = 17;
        table[JsonSymbol::NT_V][JsonToken::Type::LeftBrace] = 18;
        table[JsonSymbol::NT_Q][JsonToken::Type::Comma] = 19;
        table[JsonSymbol::NT_E][JsonToken::Type::String] = 20;
        table[JsonSymbol::NT_E][JsonToken::Type::LeftBracket] = 20;
        table[JsonSymbol::NT_E][JsonToken::Type::LeftBrace] = 20;
        table[JsonSymbol::NT_E][JsonToken::Type::BoolLiteral] = 20;
        table[JsonSymbol::NT_E][JsonToken::Type::NullLiteral] = 20;

        JsonLexer lexer(json);

        try {
            JsonToken token = lexer.getNextToken();

            while (!ss.empty()) {
                if (equivalent(ss.top(), token.type)) {
                    ss.pop();
                    token = lexer.getNextToken();
                }
                else {
                    switch(table[ss.top()][token.type]) {
                        case 1: // S => {T}
                        {
                            ss.pop();
                            ss.push(JsonSymbol::T_RightBrace);
                            ss.push(JsonSymbol::NT_T);
                            ss.push(JsonSymbol::T_LeftBrace);
                            valueStack.push(JsonValue(JsonObject()));
                            break;
                        }
                        case 2: // remove T
                        {
                            ss.pop();
                            JsonObject completedObj = valueStack.top().toObject();
                            valueStack.pop();
                            if (valueStack.top().isObject()) {
                                JsonObject parentObj = valueStack.top().toObject();
                                valueStack.pop();
                                parentObj.insert(keyStack.top(), completedObj);
                                keyStack.pop();
                                valueStack.push(JsonObject(parentObj));
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray parentArray = valueStack.top().toArray();
                                valueStack.pop();
                                parentArray.append(completedObj);
                                valueStack.push(JsonValue(parentArray));
                            }
                            break;
                        }
                        case 3: // T => M
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_M);
                            break;
                        }
                        case 4: // M => PQ
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_Q);
                            ss.push(JsonSymbol::NT_P);
                            break;
                        }
                        case 5: // P => String:V
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_V);
                            ss.push(JsonSymbol::T_Colon);
                            ss.push(JsonSymbol::T_String);
                            keyStack.push(std::string(token.value));
                            break;
                        }
                        case 6: // V => Number
                        {   ss.pop();
                            ss.push(JsonSymbol::T_Number);
                            if (valueStack.top().isObject()) {
                                JsonObject obj = valueStack.top().toObject();
                                valueStack.pop();
                                obj.insert(keyStack.top(), std::stod(token.value));
                                keyStack.pop();
                                valueStack.push(JsonValue(obj));
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray array = valueStack.top().toArray();
                                valueStack.pop();
                                array.append(std::stod(token.value));
                                valueStack.push(JsonValue(array));
                            }
                            break;
                        }
                        case 7: // remove Q
                        {
                            ss.pop();
                            JsonObject completedObj = valueStack.top().toObject();
                            valueStack.pop();
                            JsonObject parentObj = valueStack.top().toObject();
                            valueStack.pop();
                            parentObj.insert(keyStack.top(), completedObj);
                            keyStack.pop();
                            valueStack.push(JsonValue(parentObj));
                            break;
                        }
                        case 8: // V => Bool
                        {
                            ss.pop();
                            ss.push(JsonSymbol::T_Bool);
                            if (valueStack.top().isObject()) {
                                JsonObject obj = valueStack.top().toObject();
                                valueStack.pop();
                                if (token.value == "true") obj.insert(keyStack.top(), true);
                                else obj.insert(keyStack.top(), false);
                                keyStack.pop();
                                valueStack.push(JsonValue(obj));
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray parentArray = valueStack.top().toArray();
                                valueStack.pop();
                                if (token.value == "true") parentArray.append(JsonValue(true));
                                else parentArray.append(JsonValue(false));
                                valueStack.push(JsonValue(parentArray));
                            }
                            break;
                        }
                        case 9: // V => Null
                        {
                            ss.pop();
                            ss.push(JsonSymbol::T_Null);
                            if (valueStack.top().isObject()) {
                                JsonObject obj = valueStack.top().toObject();
                                valueStack.pop();
                                obj.insert(keyStack.top(), JsonValue());
                                keyStack.pop();
                                valueStack.push(JsonValue(obj));
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray parentArray = valueStack.top().toArray();
                                valueStack.pop();
                                parentArray.append(JsonValue());
                                valueStack.push(JsonValue(parentArray));
                            }
                            break;
                        }
                        case 10: // V => String
                        {
                            ss.pop();
                            ss.push(JsonSymbol::T_String);
                            if (valueStack.top().isObject()) {
                                JsonObject obj = valueStack.top().toObject();
                                valueStack.pop();
                                obj.insert(keyStack.top(), token.value);
                                keyStack.pop();
                                valueStack.push(JsonValue(obj));
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray array = valueStack.top().toArray();
                                valueStack.pop();
                                array.append(token.value);
                                valueStack.push(JsonValue(array));
                            }
                            break;
                        }
                        case 11: // V => R
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_R);
                            valueStack.push(JsonValue(JsonArray()));
                            break;
                        }
                        case 12: // R => [E]
                        {
                            ss.pop();
                            ss.push(JsonSymbol::T_RightBracket);
                            ss.push(JsonSymbol::NT_E);
                            ss.push(JsonSymbol::T_LeftBracket);
                            break;
                        }
                        case 13: // E => VF
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_F);
                            ss.push(JsonSymbol::NT_V);
                            break;
                        }
                        case 14: // remove F
                        {
                            ss.pop();
                            JsonArray completedArray = valueStack.top().toArray();
                            valueStack.pop();
                            if (valueStack.top().isObject()) {
                                JsonObject parentObj = valueStack.top().toObject();
                                valueStack.pop();
                                parentObj.insert(keyStack.top(), completedArray);
                                keyStack.pop();
                                valueStack.push(JsonValue(parentObj));
                            }

                            break;
                        }
                        case 15: // remove Q
                        {
                            ss.pop();
                            break;
                        }
                        case 16: // remove E
                        {
                            ss.pop();
                            JsonArray completedArray = valueStack.top().toArray();
                            valueStack.pop();
                            if (valueStack.top().isObject()) {
                                JsonObject parentObj = valueStack.top().toObject();
                                valueStack.pop();
                                parentObj.insert(keyStack.top(), completedArray);
                                keyStack.pop();
                                valueStack.push(parentObj);
                            }
                            else if (valueStack.top().isArray()) {
                                JsonArray parentArray = valueStack.top().toArray();
                                valueStack.pop();
                                parentArray.append(completedArray);
                                valueStack.push(JsonValue(parentArray));
                            }
                            break;
                        }
                        case 17: // F => ,E
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_E);
                            ss.push(JsonSymbol::T_Comma);
                            break;
                        }
                        case 18: // V => S
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_S);
                            break;
                        }
                        case 19: // Q => ,M
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_M);
                            ss.push(JsonSymbol::T_Comma);
                            break;
                        }
                        case 20: // E => VF
                        {
                            ss.pop();
                            ss.push(JsonSymbol::NT_F);
                            ss.push(JsonSymbol::NT_V);
                            break;
                        }
                        default:
                        {
                            throw JsonParserException(ss.top(), token.value);
                        }
                    }
                }
            }
        }
        catch (const JsonLexerException& ex)  {
            throw ex;
        }

        if (lexer.hasMoreTokens())
            throw JsonParserException("Error: Parse error - unexpected tokens after root object");

        JsonObject mainObj = valueStack.top().toObject();
        valueStack.pop();
        m_object = mainObj[rootKey].toObject();
    }

    const bool docIsEmpty() const {
        return m_object.empty();
    }

    const bool docIsValid() const {
        return m_valid;
    }

    const std::string invalidDocToString() const {
        return std::string("");
    }

    const std::string convertDocToJson() const {
        if (docIsValid()) {
            JsonStringBuilder sb;
            sb.append(m_object);
            return sb.toString();
        }
        return invalidDocToString();
    }

    JsonObject object() const {
        return m_object;
    }

    const bool operator==(const JsonDocImpl& rhs) const {
        if (m_valid == rhs.m_valid && m_object == rhs.m_object) {
            return true;
        }
        else return false;
    }
private:
    bool m_valid{true};
    JsonObject m_object{};
    std::string m_errorMsg;
};

JsonDoc::JsonDoc()
: m_impl{new JsonDocImpl}
{}

JsonDoc::JsonDoc(const std::string& json)
: m_impl{new JsonDocImpl(json)}
{}

JsonDoc::JsonDoc(const JsonObject& object)
: m_impl{new JsonDocImpl(object)}
{}

JsonDoc::JsonDoc(const JsonDoc& copy)
: m_impl{new JsonDocImpl(*copy.m_impl)}
{}

JsonDoc::JsonDoc(JsonDoc&& rhs)
: m_impl{new JsonDocImpl(*rhs.m_impl)}
{
    rhs.clear();
}

JsonDoc&
JsonDoc::operator=(const JsonDoc& rhs) {
    m_impl.reset(new JsonDocImpl(*rhs.m_impl));
    return *this;
}

JsonDoc&
JsonDoc::operator=(JsonDoc&& rhs) {
    *this = rhs;
    rhs.clear();
    return *this;
}

JsonDoc::~JsonDoc()
{}

const std::string
JsonDoc::errorMessage() const {
    return m_impl->errorMessage();
}

const bool
JsonDoc::valid() const {
    return m_impl->docIsValid();
}

const bool
JsonDoc::empty() const {
    return m_impl->docIsEmpty();
}

const std::string
JsonDoc::toJson() const {
    return m_impl->convertDocToJson();
}

void
JsonDoc::swap(JsonDoc& other) {
    std::swap(this->m_impl, other.m_impl);
}

void
JsonDoc::clear() {
    m_impl.reset(new JsonDocImpl);
}

JsonObject
JsonDoc::object() const {
    return m_impl->object();
}

const bool
operator==(const JsonDoc& lhs, const JsonDoc& rhs) {
    return *(lhs.m_impl) == *(rhs.m_impl);
}

const bool
operator!=(const JsonDoc& lhs, const JsonDoc& rhs) {
    return !(lhs == rhs);
}

std::ostream&
operator<<(std::ostream& out, const JsonDoc& doc) {
    out << doc.toJson();
    return out;
}

PRISM_END_NAMESPACE
