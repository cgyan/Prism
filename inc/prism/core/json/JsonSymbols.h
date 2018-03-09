#ifndef PRISM_JSON_SYMBOLS_H_
#define PRISM_JSON_SYMBOLS_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

enum class JsonSymbol {
    // non-terminal symbols
    NT_S,
    NT_T,
    NT_M,
    NT_P,
    NT_Q,
    NT_V,
    NT_R,
    NT_E,
    NT_F,
    // terminal symbols
    T_LeftBrace,
    T_RightBrace,
    T_LeftBracket,
    T_RightBracket,
    T_String,
    T_Colon,
    T_Comma,
    T_Number,
    T_Bool,
    T_Null
};

PRISM_END_NAMESPACE

#endif
