#include "../src/header/InternalHeaders.h"
#include "../src/header/Composite.h"
#include "../src/header/Tokenizer.h"

using namespace std;

int main(int argc, char const *argv[]) {

  //set to specific user login id
  char host[200];
  int host_name = gethostname(host, 200);
  char* user_name;

  //attempt to put user logins
  try{
    if (host_name != 0) {
      throw 4;
    }
    if (getlogin() == NULL) {
      throw "Login error";
    }else
      user_name= getlogin();

  }catch(string e){
    perror("Host has problems:");
  }catch(int e ){
    perror("User has errors:");
  }

  //display user login info
  cout << user_name << "@" << host << "$ ";

  //parsing begin
  string command_line;
  getline(cin, command_line);

  //cout << command_line << endl;




  return 0;
}
