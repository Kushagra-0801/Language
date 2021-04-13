#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const unordered_map<string, unordered_map<string, vector<string>>> table_map{
    {"S",
     {
         {"$",
          {
              "PROGRAM",
              "$",
          }},
         {"import",
          {
              "PROGRAM",
              "$",
          }},
         {"mod",
          {
              "PROGRAM",
              "$",
          }},
         {"enum",
          {
              "PROGRAM",
              "$",
          }},
         {"struct",
          {
              "PROGRAM",
              "$",
          }},
         {"const",
          {
              "PROGRAM",
              "$",
          }},
         {"fn",
          {
              "PROGRAM",
              "$",
          }},
     }},
    {"PROGRAM",
     {
         {"$",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"import",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"mod",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"}",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"enum",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"struct",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"const",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
         {"fn",
          {
              "IMPORT_ITEMS",
              "CODE_ITEMS",
          }},
     }},
    {"IMPORT_ITEMS",
     {
         {"$",
          {
              "ε",
          }},
         {"import",
          {
              "IMPORT",
              "IMPORT_ITEMS",
          }},
         {"mod",
          {
              "ε",
          }},
         {"}",
          {
              "ε",
          }},
         {"enum",
          {
              "ε",
          }},
         {"struct",
          {
              "ε",
          }},
         {"const",
          {
              "ε",
          }},
         {"fn",
          {
              "ε",
          }},
     }},
    {"IMPORT",
     {
         {"import",
          {
              "import",
              "PATH_I",
              ";",
          }},
     }},
    {"PATH_I",
     {
         {"IDENT",
          {
              "IDENT",
              "PATH",
          }},
     }},
    {"PATH",
     {
         {";",
          {
              "ε",
          }},
         {"IDENT",
          {
              "ε",
          }},
         {"::",
          {
              "::",
              "PATH_I",
          }},
         {"{",
          {
              "ε",
          }},
         {"}",
          {
              "ε",
          }},
         {",",
          {
              "ε",
          }},
         {"(",
          {
              "ε",
          }},
         {")",
          {
              "ε",
          }},
         {"=",
          {
              "ε",
          }},
         {"LITERAL",
          {
              "ε",
          }},
         {"[",
          {
              "ε",
          }},
         {"]",
          {
              "ε",
          }},
         {".",
          {
              "ε",
          }},
         {"+=",
          {
              "ε",
          }},
         {"-=",
          {
              "ε",
          }},
         {"*=",
          {
              "ε",
          }},
         {"/=",
          {
              "ε",
          }},
         {"|=",
          {
              "ε",
          }},
         {"&=",
          {
              "ε",
          }},
         {"^=",
          {
              "ε",
          }},
         {"%=",
          {
              "ε",
          }},
     }},
    {"CODE_ITEMS",
     {
         {"$",
          {
              "ε",
          }},
         {"mod",
          {
              "ITEM",
              "CODE_ITEMS",
          }},
         {"}",
          {
              "ε",
          }},
         {"enum",
          {
              "ITEM",
              "CODE_ITEMS",
          }},
         {"struct",
          {
              "ITEM",
              "CODE_ITEMS",
          }},
         {"const",
          {
              "ITEM",
              "CODE_ITEMS",
          }},
         {"fn",
          {
              "ITEM",
              "CODE_ITEMS",
          }},
     }},
    {"ITEM",
     {
         {"mod",
          {
              "MODULE",
          }},
         {"enum",
          {
              "ENUM",
          }},
         {"struct",
          {
              "STRUCT",
          }},
         {"const",
          {
              "CONSTANT",
          }},
         {"fn",
          {
              "FUNCTION",
          }},
     }},
    {"MODULE",
     {
         {"mod",
          {
              "mod",
              "IDENT",
              "{",
              "PROGRAM",
              "}",
          }},
     }},
    {"ENUM",
     {
         {"enum",
          {
              "enum",
              "IDENT",
              "{",
              "VARIANTS",
              "}",
          }},
     }},
    {"VARIANTS",
     {
         {"IDENT",
          {
              "VARIANT",
              "EXTRA_VARIANT",
          }},
         {"}",
          {
              "ε",
          }},
     }},
    {"EXTRA_VARIANT",
     {
         {"}",
          {
              "ε",
          }},
         {",",
          {
              ",",
              "VARIANTS",
          }},
     }},
    {"VARIANT",
     {
         {"IDENT",
          {
              "IDENT",
              "REM",
          }},
     }},
    {"REM",
     {
         {"}",
          {
              "ε",
          }},
         {",",
          {
              "ε",
          }},
         {"(",
          {
              "(",
              "PATH_I",
              ")",
          }},
     }},
    {"STRUCT",
     {
         {"struct",
          {
              "struct",
              "IDENT",
              "{",
              "ARGS",
              "}",
          }},
     }},
    {"CONSTANT",
     {
         {"const",
          {
              "const",
              "IDENT",
              ":",
              "PATH_I",
              "=",
              "EXPR",
              ";",
          }},
     }},
    {"FUNCTION",
     {
         {"fn",
          {
              "fn",
              "IDENT",
              "(",
              "ARGS",
              ")",
              "->",
              "PATH_I",
              "{",
              "STMTS",
              "}",
          }},
     }},
    {"ARGS",
     {
         {"IDENT",
          {
              "ARG",
              "EXTRA_ARGS",
          }},
         {"}",
          {
              "ε",
          }},
         {")",
          {
              "ε",
          }},
     }},
    {"EXTRA_ARGS",
     {
         {"}",
          {
              "ε",
          }},
         {",",
          {
              ",",
              "ARGS",
          }},
         {")",
          {
              "ε",
          }},
     }},
    {"ARG",
     {
         {"IDENT",
          {
              "IDENT",
              ":",
              "PATH_I",
          }},
     }},
    {"STMTS",
     {
         {"IDENT",
          {
              "STMT",
              "STMTS",
          }},
         {"}",
          {
              "ε",
          }},
         {"break",
          {
              "STMT",
              "STMTS",
          }},
         {"continue",
          {
              "STMT",
              "STMTS",
          }},
         {"print",
          {
              "STMT",
              "STMTS",
          }},
         {"let",
          {
              "STMT",
              "STMTS",
          }},
         {"for",
          {
              "STMT",
              "STMTS",
          }},
         {"while",
          {
              "STMT",
              "STMTS",
          }},
         {"return",
          {
              "STMT",
              "STMTS",
          }},
         {"if",
          {
              "STMT",
              "STMTS",
          }},
     }},
    {"STMT",
     {
         {"IDENT",
          {
              "ASSIGNMENT",
          }},
         {"break",
          {
              "break",
              ";",
          }},
         {"continue",
          {
              "continue",
              ";",
          }},
         {"print",
          {
              "print",
              "EXPR",
              ";",
          }},
         {"let",
          {
              "BINDING",
          }},
         {"for",
          {
              "FOR_LOOP",
          }},
         {"while",
          {
              "WHILE_LOOP",
          }},
         {"return",
          {
              "RETURN",
          }},
         {"if",
          {
              "IF_ELSE",
          }},
     }},
    {"ASSIGNMENT",
     {
         {"IDENT",
          {
              "ACCESS_TYPE",
              "EQ_OP",
              "EXPR",
              ";",
          }},
     }},
    {"BINDING",
     {
         {"let",
          {
              "let",
              "IDENT",
              ":",
              "PATH_I",
              "=",
              "EXPR",
              ";",
          }},
     }},
    {"FOR_LOOP",
     {
         {"for",
          {
              "for",
              "IDENT",
              "in",
              "EXPR",
              "{",
              "STMTS",
              "}",
          }},
     }},
    {"WHILE_LOOP",
     {
         {"while",
          {
              "while",
              "EXPR",
              "{",
              "STMTS",
              "}",
          }},
     }},
    {"RETURN",
     {
         {"return",
          {
              "return",
              "EXPR",
              ";",
          }},
     }},
    {"IF_ELSE",
     {
         {"if",
          {
              "if",
              "EXPR",
              "{",
              "STMTS",
              "}",
              "NEXT",
          }},
     }},
    {"NEXT",
     {
         {"IDENT",
          {
              "ε",
          }},
         {"}",
          {
              "ε",
          }},
         {"break",
          {
              "ε",
          }},
         {"continue",
          {
              "ε",
          }},
         {"print",
          {
              "ε",
          }},
         {"let",
          {
              "ε",
          }},
         {"for",
          {
              "ε",
          }},
         {"while",
          {
              "ε",
          }},
         {"return",
          {
              "ε",
          }},
         {"if",
          {
              "ε",
          }},
         {"else",
          {
              "else",
              "ELSE_PART",
          }},
     }},
    {"ELSE_PART",
     {
         {"{",
          {
              "{",
              "STMTS",
              "}",
          }},
         {"if",
          {
              "IF_ELSE",
          }},
     }},
    {"EXPR",
     {
         {"IDENT",
          {
              "ACCESS_TYPE",
          }},
         {"(",
          {
              "(",
              "OPERATOR",
              "ARG_LIST",
              ")",
          }},
         {"LITERAL",
          {
              "LITERAL",
          }},
         {"[",
          {
              "[",
              "ARG_LIST",
              "]",
          }},
     }},
    {"ACCESS_TYPE",
     {
         {"IDENT",
          {
              "PATH_I",
              "ANY_ACCESS",
          }},
     }},
    {"ANY_ACCESS",
     {
         {";",
          {
              "MEMBER_ACCESS",
          }},
         {"IDENT",
          {
              "MEMBER_ACCESS",
          }},
         {"{",
          {
              "MEMBER_ACCESS",
          }},
         {"(",
          {
              "MEMBER_ACCESS",
          }},
         {")",
          {
              "MEMBER_ACCESS",
          }},
         {"=",
          {
              "MEMBER_ACCESS",
          }},
         {"LITERAL",
          {
              "MEMBER_ACCESS",
          }},
         {"[",
          {
              "MEMBER_ACCESS",
          }},
         {"]",
          {
              "MEMBER_ACCESS",
          }},
         {".",
          {
              "MEMBER_ACCESS",
          }},
         {"+=",
          {
              "MEMBER_ACCESS",
          }},
         {"-=",
          {
              "MEMBER_ACCESS",
          }},
         {"*=",
          {
              "MEMBER_ACCESS",
          }},
         {"/=",
          {
              "MEMBER_ACCESS",
          }},
         {"|=",
          {
              "MEMBER_ACCESS",
          }},
         {"&=",
          {
              "MEMBER_ACCESS",
          }},
         {"^=",
          {
              "MEMBER_ACCESS",
          }},
         {"%=",
          {
              "MEMBER_ACCESS",
          }},
     }},
    {"MEMBER_ACCESS",
     {
         {";",
          {
              "ε",
          }},
         {"IDENT",
          {
              "ε",
          }},
         {"{",
          {
              "ε",
          }},
         {"(",
          {
              "ε",
          }},
         {")",
          {
              "ε",
          }},
         {"=",
          {
              "ε",
          }},
         {"LITERAL",
          {
              "ε",
          }},
         {"[",
          {
              "ε",
          }},
         {"]",
          {
              "ε",
          }},
         {".",
          {
              ".",
              "IDENT",
              "MEMBER_ACCESS",
          }},
         {"+=",
          {
              "ε",
          }},
         {"-=",
          {
              "ε",
          }},
         {"*=",
          {
              "ε",
          }},
         {"/=",
          {
              "ε",
          }},
         {"|=",
          {
              "ε",
          }},
         {"&=",
          {
              "ε",
          }},
         {"^=",
          {
              "ε",
          }},
         {"%=",
          {
              "ε",
          }},
     }},
    {"OPERATOR",
     {
         {"IDENT",
          {
              "PATH_I",
          }},
         {"+",
          {
              "OP",
          }},
         {"-",
          {
              "OP",
          }},
         {"*",
          {
              "OP",
          }},
         {"/",
          {
              "OP",
          }},
         {"==",
          {
              "OP",
          }},
         {"|",
          {
              "OP",
          }},
         {"||",
          {
              "OP",
          }},
         {"&",
          {
              "OP",
          }},
         {"&&",
          {
              "OP",
          }},
         {"!",
          {
              "OP",
          }},
         {"~",
          {
              "OP",
          }},
         {">",
          {
              "OP",
          }},
         {"<",
          {
              "OP",
          }},
         {">=",
          {
              "OP",
          }},
         {"<=",
          {
              "OP",
          }},
         {"^",
          {
              "OP",
          }},
         {"%",
          {
              "OP",
          }},
     }},
    {"ARG_LIST",
     {
         {"IDENT",
          {
              "EXPR",
              "ARG_LIST",
          }},
         {"(",
          {
              "EXPR",
              "ARG_LIST",
          }},
         {")",
          {
              "ε",
          }},
         {"LITERAL",
          {
              "EXPR",
              "ARG_LIST",
          }},
         {"[",
          {
              "EXPR",
              "ARG_LIST",
          }},
         {"]",
          {
              "ε",
          }},
     }},
    {"OP",
     {
         {"+",
          {
              "+",
          }},
         {"-",
          {
              "-",
          }},
         {"*",
          {
              "*",
          }},
         {"/",
          {
              "/",
          }},
         {"==",
          {
              "==",
          }},
         {"|",
          {
              "|",
          }},
         {"||",
          {
              "||",
          }},
         {"&",
          {
              "&",
          }},
         {"&&",
          {
              "&&",
          }},
         {"!",
          {
              "!",
          }},
         {"~",
          {
              "~",
          }},
         {">",
          {
              ">",
          }},
         {"<",
          {
              "<",
          }},
         {">=",
          {
              ">=",
          }},
         {"<=",
          {
              "<=",
          }},
         {"^",
          {
              "^",
          }},
         {"%",
          {
              "%",
          }},
     }},
    {"EQ_OP",
     {
         {"=",
          {
              "=",
          }},
         {"+=",
          {
              "+=",
          }},
         {"-=",
          {
              "-=",
          }},
         {"*=",
          {
              "*=",
          }},
         {"/=",
          {
              "/=",
          }},
         {"|=",
          {
              "|=",
          }},
         {"&=",
          {
              "&=",
          }},
         {"^=",
          {
              "^=",
          }},
         {"%=",
          {
              "%=",
          }},
     }},

};
