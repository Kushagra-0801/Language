/*
Shrimp

Team Members (Group 5)
1. Shreyas R        (2018A7PS0430H)
2. Sudheer Kumar    (2018A7PS0199H)
3. Shivang Shah     (2018A7PS0295H)
4. Kushagra Gupta   (2018A7PS0208H)
*/

#include <bits/stdc++.h>

#include "lexer.cpp"
#include "parser.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "No input files" << endl;
    return 1;
  } else if (argc > 2) {
    cerr << "Multiple files not supported" << endl;
    return 2;
  }

  ifstream codefile(argv[1]);
  string contents;
  string line;
  while (getline(codefile, line)) {
    contents.append(line);
    contents.push_back('\n');
  }

  Lexer lexer(contents);
  lexer.lex();
  for (auto token : lexer.tokens) {
    cout << token->to_str() << endl;
  }

  Parser parser(lexer.tokens);
  auto errors = parser.parse();

  if (!errors.empty()) {
    cout << "\n*******Errors*********\n";
    for (auto val : errors) {
      cout << val.to_str() << endl;
    }
  }
  return 0;
}
