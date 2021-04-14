#ifndef SHRIMP_LEXER
#define SHRIMP_LEXER

/*
Shrimp

Team Members (Group 5)
1. Shreyas R        (2018A7PS0430H)
2. Sudheer Kumar    (2018A7PS0199H)
3. Shivang Shah     (2018A7PS0295H)
4. Kushagra Gupta   (2018A7PS0208H)
*/

#include <bits/stdc++.h>
using namespace std;

const unordered_map<string, int> KEYWORDS{
    {"if", 0},     {"else", 1},   {"import", 2},    {"fn", 3},
    {"struct", 4}, {"let", 5},    {"mod", 6},       {"const", 7},
    {"enum", 8},   {"return", 9}, {"while", 10},    {"for", 11},
    {"in", 12},    {"break", 13}, {"continue", 14}, {"print", 15}};

const string REVERSE_KEYWORD[] = {
    "if",   "else",   "import", "fn",  "struct", "let",   "mod",      "const",
    "enum", "return", "while",  "for", "in",     "break", "continue", "print"};

const unordered_map<string, int> SYMBOLS{
    {"+", 0},  {"-", 1},   {"*", 2},   {"/", 3},   {":", 4},   {".", 5},
    {";", 6},  {"::", 7},  {"==", 8},  {"+=", 9},  {"-=", 10}, {"*=", 11},
    {"=", 12}, {"/=", 13}, {"|", 14},  {"||", 15}, {"&", 16},  {"&&", 17},
    {"!", 18}, {"~", 19},  {">", 20},  {"<", 21},  {">=", 22}, {"<=", 23},
    {"[", 24}, {"]", 25},  {"{", 26},  {"}", 27},  {"(", 28},  {")", 29},
    {"^", 30}, {"%", 31},  {"|=", 32}, {"&=", 33}, {"^=", 34}, {"%=", 35},
    {",", 36}, {"->", 37}};

class Token {
 public:
  int line;
  Token() = delete;
  Token(int line) { this->line = line; }
  virtual string to_str() { return "Token {line: something}"; }
  virtual string normalize() { return "Token"; }
};

class Keyword : public Token {
 public:
  int val;
  Keyword(int line, int id) : Token(line) { this->val = id; }
  string to_str() {
    string v = REVERSE_KEYWORD[val];
    stringstream s;
    s << "Keyword {line: " << line << ", value: \"" << v << "\"}";
    return s.str();
  }
  string normalize() { return REVERSE_KEYWORD[val]; }
};

class Identifier : public Token {
 public:
  string val;

  Identifier(int line, string val) : Token(line) { this->val = val; }
  string to_str() {
    stringstream s;
    s << "Identifier {line: " << line << ", value: \"" << val << "\"}";
    return s.str();
  }
  string normalize() { return "IDENT"; }
};

class Literal : public Token {
 public:
  string val;

  Literal(int line, string val) : Token(line) { this->val = val; }
  string to_str() {
    stringstream s;
    s << "Literal {line: " << line << ", value: " << val << "}";
    return s.str();
  }
  string normalize() { return "LITERAL"; }
};

class Symbol : public Token {
 public:
  int val;

  Symbol(int line, int val) : Token(line) { this->val = val; }
  string to_str() {
    string v;
    for (auto &[s, i] : SYMBOLS) {
      if (val == i) {
        v = s;
        break;
      }
    }
    stringstream s;
    s << "Symbol {line: " << line << ", value: \"" << v << "\"}";
    return s.str();
  };
  string normalize() {
    string v;
    for (auto &[s, i] : SYMBOLS) {
      if (val == i) {
        v = s;
        break;
      }
    }
    return v;
  }
};

class Eof : public Token {
 public:
  Eof(int line) : Token(line) {}
  string to_str() {
    stringstream s;
    s << "Eof {line: " << line << ", value: $}";
    return s.str();
  }
  string normalize() { return "$"; }
};

class Invalid : public Token {
 public:
  string val;

  Invalid(int line, string details) : Token(line) { this->val = details; }
  string to_str() {
    stringstream s;
    s << "Invalid {line: " << line << ", error: " << val << "}";
    return s.str();
  }
  string normalize() { return "INVALID"; }
};

class Lexer {
 public:
  string file_contents;
  vector<Token *> tokens;
  size_t idx = 0;
  int line;

  char peek() { return file_contents[idx]; }

  char peek_next() { return file_contents[idx + 1]; }

  void lexWord() {
    size_t end = idx;
    while (end < file_contents.size()) {
      char ch = file_contents[end];
      if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' ||
          (ch >= '0' && ch <= '9')) {
        end++;
      } else {
        break;
      }
    }
    string word(file_contents.begin() + idx, file_contents.begin() + end);
    if (auto id = KEYWORDS.find(word); id != KEYWORDS.end()) {
      tokens.push_back(new Keyword(line, id->second));
    } else {
      tokens.push_back(new Identifier(line, word));
    }
    idx = end;
  }

  void lexNumber() {
    size_t end;
    stod(file_contents.substr(idx), &end);
    tokens.push_back(new Literal(line, file_contents.substr(idx, end)));
    idx += end;
  }

  void lexString() {
    string s;
    auto l = line;
    size_t i;
    for (i = idx + 1; i < file_contents.size() - 1; i++) {
      char c = file_contents[i];
      if (c == '"') {
        break;
      } else if (c == '\n') {
        line += 1;
        s.push_back('\n');
      } else if (c == '\\') {
        c = file_contents[++i];
        if (c == 'n') {
          s.push_back('\n');
        } else if (c == 't') {
          s.push_back('\t');
        } else if (c == 'r') {
          s.push_back('\r');
        } else {
          tokens.push_back(new Invalid(line, "Invalid escape code"));
          idx = i;
          while (idx < file_contents.size() &&
                 (file_contents[idx] != '\n' || file_contents[idx] != '"'))
            idx++;
          idx += 1;
          return;
        }
      } else {
        s.push_back(c);
      }
    }
    if (file_contents[i] == '"') {
      tokens.push_back(new Literal(l, s));
    } else {
      tokens.push_back(new Invalid(l, "Unterminated string"));
    }
    idx = i + 1;
  }

  void lexChar() {
    if (idx + 1 < file_contents.size()) {
      char ch = file_contents[idx + 1];
      if (isgraph(ch) && ch != '\\' && ch != '\'') {
        if (idx + 2 < file_contents.size() && file_contents[idx + 2] == '\'') {
          tokens.push_back(new Literal(line, file_contents.substr(idx, 3)));
          idx += 3;
        } else {
          tokens.push_back(new Invalid(line, "Unterminated character literal"));
          while (idx < file_contents.size() && !isspace(file_contents[idx]))
            idx++;
        }
      } else if (ch == '\'') {
        tokens.push_back(new Invalid(line, "Empty Character Literal"));
        idx += 2;
      } else if (ch == '\\') {
        if (idx + 3 < file_contents.size() && file_contents[idx + 3] == '\'') {
          char c = file_contents[idx + 2];
          switch (c) {
            case 'n':
            case 'r':
            case 't':
              tokens.push_back(new Literal(line, file_contents.substr(idx, 4)));
              break;
            default:
              tokens.push_back(new Invalid(line, "Unknown escape code"));
          }
          idx += 4;
        } else {
          tokens.push_back(new Invalid(line, "Unterminated character literal"));
          while (idx < file_contents.size() && !isspace(file_contents[idx]))
            idx++;
        }
      } else {
        tokens.push_back(new Invalid(line, "Invalid character"));
        while (idx < file_contents.size() && !isspace(file_contents[idx]))
          idx++;
      }
    } else {
      tokens.push_back(new Invalid(line, "Unterminated character literal"));
      while (idx < file_contents.size() && !isspace(file_contents[idx])) idx++;
    }
  }

  void lexSymbol() {
    auto search = [this](string s) {
      if (auto it = SYMBOLS.find(s); it != SYMBOLS.end()) {
        tokens.push_back(new Symbol(line, it->second));
        idx += s.size();
        return true;
      } else {
        return false;
      }
    };
    if (idx + 1 < file_contents.size()) {
      auto sym = file_contents.substr(idx, 2);
      if (!search(sym)) {
        auto sym = file_contents.substr(idx, 1);
        if (!search(sym)) {
          tokens.push_back(new Invalid(line, "Unknown Symbol"));
          idx += 1;
        }
      }
    } else {
      auto sym = file_contents.substr(idx, 1);
      if (!search(sym)) {
        tokens.push_back(new Invalid(line, "Unknown Symbol"));
        idx += 1;
      }
    }
  }

  Lexer(string contents) {
    file_contents = contents;
    line = 1;
  }

  void lex() {
    while (idx < file_contents.size()) {
      if ((peek() >= 'a' && peek() <= 'z') ||
          (peek() >= 'A' && peek() <= 'Z') || (peek() == '_')) {
        lexWord();
      } else if (peek() >= '0' && peek() <= '9') {
        lexNumber();
      } else if (peek() == '"') {
        lexString();
      } else if (peek() == '\'') {
        lexChar();
      } else if (peek() == '\n') {
        line += 1;
        idx += 1;
      } else if (peek() == ' ') {
        idx += 1;
      } else if (peek() == '#') {
        while (idx < file_contents.size() && file_contents[idx] != '\n') idx++;
      } else {
        lexSymbol();
      }
    }
    tokens.push_back(new Eof(this->line));
  }
};

#endif
