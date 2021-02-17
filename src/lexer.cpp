#include <bits/stdc++.h>
using namespace std;

const unordered_map<string, int> KEYWORDS{
    {"if", 0},     {"else", 1},   {"import", 2},    {"fn", 3},
    {"struct", 4}, {"let", 5},    {"mod", 6},       {"const", 7},
    {"enum", 8},   {"return", 9}, {"while", 10},    {"for", 11},
    {"in", 12},    {"break", 13}, {"continue", 14}, {"print", 15}};

const unordered_map<string, int> SYMBOLS{
    {"+", 0},  {"-", 1},   {"*", 2},   {"/", 3},   {":", 4},   {".", 5},
    {";", 6},  {"::", 7},  {"==", 8},  {"+=", 9},  {"-=", 10}, {"*=", 11},
    {"=", 12}, {"/=", 13}, {"|", 14},  {"||", 15}, {"&", 16},  {"&&", 17},
    {"!", 18}, {"~", 19},  {">", 20},  {"<", 21},  {">=", 22}, {"<=", 23},
    {"[", 24}, {"]", 25},  {"{", 26},  {"}", 27},  {"(", 28},  {")", 29},
    {"^", 30}, {"%", 31},  {"|=", 32}, {"&=", 33}, {"^=", 34}, {"%", 35},
    {"%=", 36}};

class Token {
 public:
  int line;
  Token() = delete;
  Token(int line) { this->line = line; }
};

class Keyword : public Token {
  int id;

 public:
  Keyword(int line, int id) : Token(line) { this->id = id; }
};

class Identifier : public Token {
  string value;

 public:
  Identifier(int line, string val) : Token(line) { this->value = val; }
};

class Literal : public Token {
  string value;

 public:
  Literal(int line, string val) : Token(line) { this->value = val; }
};

class Symbol : public Token {
  int id;

 public:
  Symbol(int line, int id) : Token(line) { this->id = id; }
};

class Invalid : public Token {
  string details;

 public:
  Invalid(int line, string details) : Token(line) { this->details = details; }
};

class Lexer {
 public:
  string file_contents;
  vector<Token> tokens;
  size_t idx;
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
      tokens.push_back(Keyword(line, id->second));
    } else {
      tokens.push_back(Identifier(line, word));
    }
    idx = end;
  }

  void lexNumber() {
    size_t end;
    stod(file_contents.substr(idx), &end);
    tokens.push_back(Literal(line, file_contents.substr(idx, end)));
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
      } else if (c == '\\') {
        c = file_contents[++i];
        if (c == 'n') {
          s.push_back('\n');
        } else if (c == 't') {
          s.push_back('\t');
        } else if (c == 'r') {
          s.push_back('\r');
        } else {
          tokens.push_back(Invalid(line, "Invalid escape code"));
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
      tokens.push_back(Literal(l, s));
    } else {
      tokens.push_back(Invalid(l, "Unterminated string"));
    }
    idx = i + 1;
  }

  void lexChar() {
    if (idx + 2 < file_contents.size()) {
      char ch = file_contents[idx + 1];
      if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' ||
          (ch >= '0' && ch <= '9') || ch == ' ') {
        if (file_contents[idx + 2] == '\'') {
          tokens.push_back(Literal(line, file_contents.substr(idx, 3)));
          idx += 3;
        } else {
          tokens.push_back(Invalid(line, "Unterminated character literal"));
        }
      } else if (ch == '\\' && idx + 3 < file_contents.size()) {
        ch = file_contents[idx + 2];
        if (file_contents[idx + 3] == '\'') {
          switch (ch) {
            case 'n':
            case 'r':
            case 't':
              tokens.push_back(Literal(line, file_contents.substr(idx, 4)));
              idx += 4;
              break;
            default:
              tokens.push_back(Invalid(line, "Unknown escape code"));
          }
        } else {
          tokens.push_back(Invalid(line, "Unterminated character literal"));
        }
      } else {
        tokens.push_back(Invalid(line, "Charcater outside normal ascii"));
      }
    } else {
      tokens.push_back(Invalid(line, "Unterminated character literal"));
    }
  }

  void lexSymbol() {
    auto search = [this](string s) {
      if (auto it = SYMBOLS.find(s); it != SYMBOLS.end()) {
        tokens.push_back(Symbol(line, it->second));
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
          tokens.push_back(Invalid(line, "Unknown Symbol"));
          idx += 1;
        }
      }
    } else {
      auto sym = file_contents.substr(idx, 1);
      if (!search(sym)) {
        tokens.push_back(Invalid(line, "Unknown Symbol"));
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
        line += 1;
        while (idx < file_contents.size() && file_contents[idx++] != '\n')
          ;
      } else {
        lexSymbol();
      }
    }
  }
};
