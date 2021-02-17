#include <bits/stdc++.h>

#include "lexer.cpp"

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

  cout << lexer.file_contents << endl;
  return 0;
}
 