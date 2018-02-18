#include <prism/global>
#include <prism/JsonDoc>
#include <prism/JsonLexer>
#include <prism/JsonToken>
#include <prism/Stack>
#include <map>

PRISM_BEGIN_NAMESPACE

JsonDoc::JsonDoc(const JsonObject& obj) {
    m_json = R"({ "pi" : 3.14 })";
}

JsonDoc::JsonDoc(const std::string& json) {
    // parse(json);
}

JsonDoc::JsonDoc(const JsonDoc& copy) {
    m_valid = copy.m_valid;
    m_json = copy.m_json;
}

// enum class Symbols {
//     // non terminals
//     NT_S, NT_T, NT_M, NT_P, NT_Q, NT_R, NT_E, NT_F, NT_V,
//     // terminals
//     T_LeftBrace, T_RightBrace, T_LeftBracket, T_RightBracket,
//     T_Colon, T_Comma, T_String, T_Number, T_Bool, T_Null, T_EOS
// };

// Symbols lexer(JsonToken::Type type) {
//     switch (type) {
//         case JsonToken::Type::LeftBrace: return Symbols::T_LeftBrace;
//         case JsonToken::Type::RightBrace: return Symbols::T_RightBrace;
//         case JsonToken::Type::LeftBracket: return Symbols::T_LeftBracket;
//         case JsonToken::Type::RightBracket: return Symbols::T_RightBracket;
//         case JsonToken::Type::Comma: return Symbols::T_Comma;
//         case JsonToken::Type::Colon: return Symbols::T_Colon;
//         case JsonToken::Type::String: return Symbols::T_String;
//         case JsonToken::Type::Number: return Symbols::T_Number;
//         case JsonToken::Type::BoolLiteral: return Symbols::T_Bool;
//         case JsonToken::Type::NullLiteral: return Symbols::T_Null;
//     }
// }

// void
// JsonDoc::parse(const std::string& json) {
//     using SymbolStack = Stack<Symbols>;
//     SymbolStack ss;
//
//     try {
//         enum class Rules {
//             Rule1, Rule2, Rule3, Rule4, Rule5, Rule6, Rule7, Rule8, Rule9,
//             Rule10, Rule11, Rule12, Rule13, Rule14, Rule15
//         };
//
//         ss.push(Symbols::T_EOS);
//         ss.push(Symbols::NT_S);
//
//         using ParseTable = std::map<Symbols, std::map<JsonToken::Type, Rules>>;
//         ParseTable table;
//         table[Symbols::NT_S][JsonToken::Type::LeftBracket] = Rules::Rule1;
//         table[Symbols::NT_T][JsonToken::Type::String] = Rules::Rule2;
//         table[Symbols::NT_M][JsonToken::Type::String] = Rules::Rule3;
//         table[Symbols::NT_P][JsonToken::Type::String] = Rules::Rule4;
//         table[Symbols::NT_Q][JsonToken::Type::Comma] = Rules::Rule5;
//         table[Symbols::NT_R][JsonToken::Type::LeftBracket] = Rules::Rule6;
//         table[Symbols::NT_E][JsonToken::Type::String] = Rules::Rule7;
//         table[Symbols::NT_E][JsonToken::Type::Number] = Rules::Rule7;
//         table[Symbols::NT_E][JsonToken::Type::BoolLiteral] = Rules::Rule7;
//         table[Symbols::NT_E][JsonToken::Type::NullLiteral] = Rules::Rule7;
//         table[Symbols::NT_F][JsonToken::Type::Comma] = Rules::Rule8;
//         table[Symbols::NT_V][JsonToken::Type::LeftBrace] = Rules::Rule9;
//         table[Symbols::NT_V][JsonToken::Type::LeftBracket] = Rules::Rule10;
//         table[Symbols::NT_V][JsonToken::Type::String] = Rules::Rule11;
//         table[Symbols::NT_V][JsonToken::Type::Number] = Rules::Rule12;
//         table[Symbols::NT_V][JsonToken::Type::BoolLiteral] = Rules::Rule13;
//         table[Symbols::NT_V][JsonToken::Type::NullLiteral] = Rules::Rule14;
//         table[Symbols::NT_T][JsonToken::Type::RightBrace] = Rules::Rule15;
//         table[Symbols::NT_Q][JsonToken::Type::RightBrace] = Rules::Rule15;
//         table[Symbols::NT_F][JsonToken::Type::RightBracket] = Rules::Rule15;
//
//         JsonLexer lex(json);
//
//         while(lex.hasNext()) {
//             JsonToken token = lex.next();
//             if (ss.top() == lexer(token.type)) {
//                 ss.pop();
//             }
//             else {
//                 switch(table[ss.top()][token.type]) {
//                     case Rules::Rule1: // S => {T}
//                         ss.pop();
//                         ss.push(Symbols::T_RightBrace);
//                         ss.push(Symbols::NT_T);
//                         ss.push(Symbols::T_LeftBrace);
//                         break;
//                     case Rules::Rule2: // T => M
//                         ss.pop();
//                         ss.push(Symbols::NT_M);
//                         break;
//                     case Rules::Rule3: // M => PQ
//                         ss.pop();
//                         ss.push(Symbols::NT_Q);
//                         ss.push(Symbols::NT_P);
//                         break;
//                     case Rules::Rule4: // P => String:V
//                         ss.pop();
//                         ss.push(Symbols::NT_V);
//                         ss.push(Symbols::T_Colon);
//                         ss.push(Symbols::T_String);
//                         break;
//                     case Rules::Rule5: // Q => ,M
//                         ss.pop();
//                         ss.push(Symbols::NT_M);
//                         ss.push(Symbols::T_Comma);
//                         break;
//                     case Rules::Rule6: // R => [E]
//                         ss.pop();
//                         ss.push(Symbols::T_RightBracket);
//                         ss.push(Symbols::NT_E);
//                         ss.push(Symbols::T_LeftBracket);
//                         break;
//                     case Rules::Rule7: // String/Number/Bool/Null => VF
//                         ss.pop();
//                         ss.push(Symbols::NT_F);
//                         ss.push(Symbols::NT_V);
//                         break;
//                     case Rules::Rule8: // F => ,E
//                         ss.pop();
//                         ss.push(Symbols::NT_E);
//                         ss.push(Symbols::T_Comma);
//                         break;
//                     case Rules::Rule9: // V => S
//                         ss.pop();
//                         ss.push(Symbols::NT_S);
//                         break;
//                     case Rules::Rule10: // V => R
//                         ss.pop();
//                         ss.push(Symbols::NT_R);
//                         break;
//                     case Rules::Rule11: // V => String
//                         ss.pop();
//                         ss.push(Symbols::T_String);
//                         break;
//                     case Rules::Rule12: // V => Number
//                         ss.pop();
//                         ss.push(Symbols::T_Number);
//                         break;
//                     case Rules::Rule13: // V => Bool
//                         ss.pop();
//                         ss.push(Symbols::T_Bool);
//                         break;
//                     case Rules::Rule14: // V => Null
//                         ss.pop();
//                         ss.push(Symbols::T_Null);
//                         break;
//                     case Rules::Rule15:
//                         ss.pop();
//                         break;
//                 }
//             }
//         }
//     }
//     catch(const JsonLexerException& ex) {
//         m_valid = false;
//         return;
//     }
//     std::cout << "Successfully finished parsing" << std::endl;
//     std::cout << ss.size() << std::endl;
// }

const bool
JsonDoc::isValid() const {
    return m_valid;
}

const std::string
JsonDoc::toJson() const {
    return m_json;
}

void
JsonDoc::swap(JsonDoc& other) {
    std::string a = m_json;
    m_json = other.m_json;
    other.m_json = a;

    bool b = m_valid;
    m_valid = other.m_valid;
    other.m_valid = b;
}

const int
JsonDoc::numKeys() const {
    return 1;
}

JsonDoc
JsonDoc::fromJson(const std::string& json) {
    return JsonDoc(json);
}

JsonDoc
JsonDoc::fromObject(const JsonObject& obj) {
    return JsonDoc(obj);
}

const bool
operator==(const JsonDoc& lhs, const JsonDoc& rhs) {
    if (lhs.isValid() && rhs.isValid()) {
        if (lhs.toJson() == rhs.toJson())
            return true;
    }
    return false;
}

PRISM_END_NAMESPACE
