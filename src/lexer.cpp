#include <bits/stdc++.h>
using namespace std;

const unordered_map<const string, int> KEYWORDS{
    {"if", 0}, {"else", 1},   {"import", 2}, {"fn",3}, {"struct",4}, {"let",5}, {"mod",6}, {"const",7},
    {"enum",8 }, {"return",9}, {"while",10}, {"for",11}, {"in",12}, {"break", 13}, {"continue", 14}, {"print", 15}
};

const unordered_map<const string, int> SYMBOLS{
    {"+",0},  {"-", 1},  {"*", 2},  {"/", 3},  {":", 4},  {".", 5},  {";", 6},  {"::", 7}, {"==", 8}, {"+=", 9},
    {"-=", 10}, {"*=", 11}, {"=", 12},  {"/=", 13}, {"|",14},  {"||",15}, {"&",16},  {"&&", 17}, {"!",18},  {"~",19},
    {">",20},  {"<",21},  {">=",22}, {"<=",23}, {"[",24}, {"]", 25}, {"{",26}, {"}", 27}, {"(",28}, {")", 29},
    {"^", 30},  {"%", 31},  {"#", 32}
};

class Token{
 public:
  int line;
  Token()=delete;
  Token(int line) {this->line = line;}
};

class Keyword : public Token {
  int id;
  public:
    Keyword(int line, int id) : Token(line) { this->id = id; }
};

class Identifier : public Token  {
  string value;
  public:
    Identifier(int line, string val) : Token(line) { this->value = val; }
};

class Literal : public Token  {
  string value;
  public:
    Literal(int line, string val) : Token(line) { this->value = val; }
};

class Symbol : public Token {
  int id;
};

class Lexer {
 public:
  string file_contents;
  vector<Token> tokens;
  int idx;
  int line;

  char get() {
    return file_contents[idx++];
  }

  char peek() {
    return file_contents[idx];
  }

  char peek_next() {
    return file_contents[idx + 1];
  }
  
  void lexWord() {
    size_t end = idx;
    while(end < file_contents.size()) {
      char ch = file_contents[end];
      if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch <= '9')) {
        end++;
      } else {
        break;
      }
    }
    string word(file_contents.begin() + idx, file_contents.begin() + end);
    if (KEYWORDS.find(word) !=  KEYWORDS.end()) {
      int id = KEYWORDS.find(word)->second;
      tokens.push_back(Keyword(line, id));
    } else {
      tokens.push_back(Identifier(line, word));
    }
    
    idx = end;
  }

  void lexNumber() {
    size_t end;
    stod(file_contents, &end);
    tokens.push_back(Literal(line, file_contents.substr(idx, end)));
    idx += end;
  }

  void lexString() {

  }

  void lexChar() {

  }
  void lexSymbol() {}
  void skip() {}
    
  Lexer(string contents) { file_contents = contents; line = 1; }

  void lex() {
    while (idx < file_contents.size()) {
      if ((peek() >= 'a' && peek() <= 'z') || (peek() >= 'A' && peek() <= 'Z') || (peek() == '_')) {
        lexWord();
      } else if (peek() >= '0' && peek() <= '9') {
        lexNumber();
      } else if (peek() == '"') {
        lexString();
      } else if (peek() == '\'') {
        lexChar();
      } else if (peek() == '\n') {
        line += 1;
      } else if (peek() == ' ') {
        idx += 1;
        continue;
      } else {
        lexSymbol(); 
      }
    }
  } 
};
 