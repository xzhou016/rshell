#include "../src/header/InternalHeaders.h"
#include "../src/header/Composite.h"
#include "../src/header/Tokenizer.h"
#include "VarComposite.cpp"

int main(int argc, char const *argv[]) {


  print_host_user(); // print out login info

  //parsing begin
  string command_line;
  getline(cin, command_line);

  //tokenize input
  Tokenizer<string> token(command_line) ;
  token.parse(); // separate string
  //token.print();


  return 0;
}
