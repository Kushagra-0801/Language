// #include <string>
// #include <variant>
// #include <vector>

#include <bits/stdc++.h>

using namespace std;

const unordered_set<string> KEYWORDS{
    "if",   "else",   "import", "fn",  "struct", "let",   "mod",      "const",
    "enum", "return", "while",  "for", "in",     "break", "continue", "print"};

const unordered_set<string> OPERATORS{
    "+",  "-",  "*",  "/",  ":",  ".",  ";",  "::", "==", "+=",
    "-=", "*=", "=",  "/=", "|",  "||", "&",  "&&", "!",  "~",
    ">",  "<",  ">=", "<=", "[]", "{}", "()", "^",  "%",  "#",
};

struct Keyword {
  int id;
};

struct Identifier {
  string value;
};

struct Literal {
  string value;
};

class Token {
 public:
  int line;
  int col;
  //   variant<Literal, Identifier, Keyword> kind;
};

class Lexer {
 public:
  string file_contents;
  vector<Token> tokens;

  char get();
  char peek();

  int read_int() {
    int res;
    while (1) {
      char ch = peek();
      if (ch >= '0' && ch <= '9') {
        res *= 10;
        res += get() - '0';
      } else {
        break;
      }
    }
  }

 public:
  Lexer(string contents) { file_contents = contents; }
};

/* regex

int -> ([0-9]+)
float -> ([0-9]+\.[0-9]+((e|E)[0-9]+\.[0-9]+)?)
string -> ("[^"\\]*(?:\\.[^"\\]*)*")
identifier -> ([a-zA-Z_][0-9a-zA-Z_]*)

keywords -> (for | while | ...)

*/
