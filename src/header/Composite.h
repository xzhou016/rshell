#ifndef COMPOSITE_H
#define COMPOSITE_H
//#include <iostream>
//#include <string>

using namespace std;
void print_host_user(){
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
}



#endif
