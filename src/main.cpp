#include "../src/header/InternalHeaders.h"
#include "../src/header/Tokenizer.h"
using namespace std;
#include "../src/header/Composite.h"
#include "../src/header/Tokens.h"
#include "Tokens.cpp"
#include "../src/header/Redirection.h"
#include "../src/header/helpers.h"
#include "../src/header/ExeDriver.h"



int main(int argc, char const *argv[]){

  bool EXIT_FLAG = false;
    
  while(!EXIT_FLAG){
      //print_host_user(); // print out login info
    
      //parsing begin
      string command_line;
      getline(cin, command_line);
      if(command_line == "exit"){
        Exit* exit_program  = new Exit();
        exit_program->run();
      }
      //tokenize input
      Tokenizer<string> token(command_line);
      token.parse(); // separate string
      check_comment(token.command_collection);
      
      //token.print(); //test to see what the token looks like
      ExeDriver(token.command_collection);//
      
  }
  return 0;
}
