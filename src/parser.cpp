#ifndef SHRIMP_PARSER
#define SHRIMP_PARSER

#include "lexer.cpp"

class LlNt {};

class Parser {
 public:
  vector<Token> tokens;
  stack<LlNt> s;
  Parser() = delete;
  Parser(vector<Token> &tokens) { this->tokens = tokens; }
};

#endif
