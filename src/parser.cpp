#ifndef SHRIMP_PARSER
#define SHRIMP_PARSER

#include "lexer.cpp"
class Error {};
#include "c_table.hpp"

class Parser {
 public:
  vector<Token *> tokens;
  size_t i = 0;
  stack<string> s;
  Parser() = delete;
  Parser(vector<Token *> &tokens) {
    this->tokens = tokens;
    s.push("S");
  }
  vector<Error> parse() {
    while (!s.empty()) {
      auto nt = s.top();
      s.pop();
      auto terminal = tokens[i]->normalize();
      cout << nt << " : " << terminal << endl;

      if (auto t = table_map.find(nt); t != table_map.end()) {
        if (auto rule = t->second.find(terminal); rule != t->second.end()) {
          for (auto j = rule->second.crbegin(); j != rule->second.crend();
               j++) {
            s.push(*j);
          }
        } else {
          cerr << "Encountered Error" << endl;
          exit(0);
        }
      } else if (nt == "EPS") {
      } else if (nt == "$") {
        cout << "$ : " << i << " " << tokens.size() << endl;
      } else if (terminal == nt) {
        i++;
      }
    }
    return {};
  }
};

#endif
