#ifndef TOKENIZER_H
#define TOKENIZER_H

//#include <iostream>
#include <boost/tokenizer.hpp>
//#include <string>

using namespace std;
using namespace boost;
typedef tokenizer< char_separator<char> > Tok;

template <typename T>
class Tokenizer {
private:
  //parse and store all commands inside vector
  string command_line;
  vector<T> command_collection;

public:
  Tokenizer(string command){
    command_line = command;
  }

//take the command from user and shove them into a vector
  void parse(){
    char_separator<char> delim(" ", ";#");
    tokenizer< char_separator<char> > Tok(command_line, delim);

    for (Tok::iterator it = Tok.begin(); it != Tok.end(); it++) {
      command_collection.push_back(*it);
    }

  }

//look at the arguement given, debugging
  void print(){
    for (unsigned int i = 0; i < command_collection.size(); i++) {
      cout << "<" << command_collection.at(i) << ">";
    }cout << endl;
  }

};


#endif
