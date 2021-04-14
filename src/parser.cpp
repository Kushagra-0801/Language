#ifndef SHRIMP_PARSER
#define SHRIMP_PARSER

#include "lexer.cpp"
class ParserError {
 public:
  int line;
  string val;
  ParserError(int line, string val) {
    this->line = line;
    this->val = val;
  }
  string to_str() {
    stringstream s;
    s << "Error {line: " << line << ", value: " << val << "}";
    return s.str();
  }
};
#include "c_table.hpp"
const string EPS = "ε";

void my_print(int n, string s) {
  for (int i = 0; i < n; i++) {
    cout << "  ";
  }
  cout << s << endl;
}

class Parser {
 public:
  vector<Token *> tokens;
  size_t i = 0;
  stack<pair<int, string>> s;
  Parser() = delete;
  Parser(vector<Token *> &tokens) {
    this->tokens = tokens;
    s.push({0, "S"});
  }
  vector<ParserError> parse() {
    vector<ParserError> err;
    while (!s.empty()) {
      if (i >= tokens.size()) {
        err.push_back(
            {tokens[tokens.size() - 1]->line, "expected tokens, found none"});
        break;
      }

      auto terminal = tokens[i]->normalize();
      if (terminal == "INVALID") {
        err.push_back(
            {tokens[i]->line, "Lexer error: INVALID TOKEN, skipping input"});
        i++;
        continue;
      }

      auto nt = s.top();
      s.pop();
      if (auto t = table_map.find(nt.second); t != table_map.end()) {
        if (auto rule = t->second.find(terminal); rule != t->second.end()) {
          if (rule->second[0] == "SYNCH") {
            err.push_back({tokens[i]->line, "Production skipped"});
            continue;
          } else {
            my_print(nt.first, nt.second);
            for (auto j = rule->second.crbegin(); j != rule->second.crend();
                 j++) {
              s.push({nt.first + 1, *j});
            }
          }
        } else {
          err.push_back(
              {tokens[i]->line, "Parser rule not found, skipping token"});
          i++;
          continue;
        }
      } else if (nt.second == EPS) {
      } else if (nt.second == "$") {
        my_print(nt.first, "$");
      } else if (terminal == nt.second) {
        if (terminal == "IDENT") {
          Identifier *ident = dynamic_cast<Identifier *>(tokens[i]);
          my_print(nt.first, terminal + ": " + ident->val);
        } else if (terminal == "LITERAL") {
          Literal *literal = dynamic_cast<Literal *>(tokens[i]);
          my_print(nt.first, terminal + ": " + literal->val);
        } else {
          my_print(nt.first, terminal);
        }
        i++;
      } else {
        err.push_back({tokens[i]->line,
                       "Expected token: " + nt.second + " Found: " + terminal});
      }
    }
    return err;
  }
};

#endif
