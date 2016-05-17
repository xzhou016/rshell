#include "../src/header/InternalHeaders.h"
#include "../src/header/Composite.h"
#include "../src/header/Tokenizer.h"
//#include "VarComposite.cpp"

using namespace std;
int main(int argc, char const *argv[]) {

  bool EXIT_FLAG = false;
    
  while(!EXIT_FLAG){
      //print_host_user(); // print out login info
    
      //parsing begin
      string command_line;
      getline(cin, command_line);
      if(command_line == "exit"){
        EXIT_FLAG = true;
        return 0;
      }

    
      //tokenize input
      Tokenizer<string> token(command_line) ;
      token.parse(); // separate string
      //token.print();
      
     //execvp(token.command_line)
     //token.setVector(check_comment(token.getVector()));
      check_comment(token.command_collection);
      //token.print();
    
      execute(token.command_collection,
              token.command_collection.size(),
              true, false , 0, 0);
      
  }
  return 0;
}
