#include<bits/stdc++.h>
using namespace std;

// std::string tokenizer
vector<string> string_splitter(string str, char ch) {
  vector<string> v;
  string s = "";
  for(int i=0;i<str.length();i++) {
    if(str[i] == ch) {
      v.push_back(s);
      s = "";
    }
    else {s += str[i];}
  }
  return v;
}

// get the type of lexeme from the given token
string get_type(string str) {
  string s = "";
  for(int i=0;i<str.length();i++) {
    if(str[i] == ' ') {break;}
    else {s += str[i];}
  }
  return s;
}

// get the lexeme from the given token
string get_lexeme(string str) {
  string s = "";
  int coloncount = 0, icomcount = 0;
  for(int i=0;i<str.length()-1;i++) {
    if(str[i] == ':') {coloncount++;}
    else {
      if(coloncount == 2) {
         s += str[i];
      }
    }
  }
  s = s.substr(1);
  return s;
}


int main() {
  vector<string> terminals, nonterminals;
  
  // stores the ll(1) parser table
  map<string, map<string,string>> parser_table;

  // populating the parser table
  int n = 0;
  string str;
  ifstream InputFile("lltable.txt");
  while(getline(InputFile, str)) {
    vector<string> v;
    if(n == 0) {
      v = string_splitter(str, '`');
      for(int i=0;i<v.size();i++) {
        if(v[i].length() != 0) {
          terminals.push_back(v[i]);
        }
      }
    }
    else {
      v = string_splitter(str, '`');
      nonterminals.push_back(v[0]);
      for(int i=1;i<v.size();i++) {
        parser_table[v[0]][terminals[i-1]] = v[i];
      }
    }
    n++;
  }
  InputFile.close();
}