#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

using namespace std;
using namespace boost;
typedef tokenizer< char_separator<char> > Tok;

class Tokenizer {
private:
  //parse and store all commands inside vector
  string command_line;
  vector<BaseCommand*> command_collection;

public:
  Tokenizer(string command){
    command_line = command;
  }

//add commands into vector for execute
  void add_command(BaseCommand* cmd){
    command_collection.push_back(cmd);
  }

//take the command from user and b
  void parse(){
    char_separator<char> delim(" ", ";#");
    tokenizer< char_separator<char> > Tok(command_line, delim);

    
  }

};


#endif
