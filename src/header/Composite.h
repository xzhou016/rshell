#ifndef COMPOSITE_H
#define COMPOSITE_H
//#include <iostream>
#include <string.h>

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
      throw "e";
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

template <typename T>
void Vec_print(vector<T> print){
  for ( typename vector<T>::iterator i = print.begin(); i != print.end(); ++i ) {
    cout << *i << " ";
  }//cout << ",";
}

template <typename T>
void check_comment(vector<T> &tokens){
  //int index = 0;
  for (unsigned int i = 0; i < tokens.size(); ++i) {
    //index++;
    //cout << tokens.size();
    for (unsigned int j = 0; j < tokens.at(i).size(); ++j) {
      
      T temp_compare = tokens.at(i);
      if(temp_compare.at(j) == '#'){
        cout << i ;
        tokens.erase(tokens.begin() + i , tokens.end());
       return;
      }
    }
  }
  
}

template <typename T>
bool driver(vector<T> &parsing_exe ){
  char** parser = new char*[256];
  
  //Vec_print(parsing_exe);
  int i;
  
  for(i = 0; i < parsing_exe.size(); i++){
    char* handle = strdup(parsing_exe[i].c_str());
    parser[i] = handle;
    //cout << parser[i];
  }
  
  parser[i] = '\0';
  
  int status;
  pid_t pid = fork();
  if(pid == 0){
    if(execvp(parser[0], parser) == -1){
      perror("exec");
      exit(1);
      return false;
    }
    return true;
  }else if (pid > 0){
    if(waitpid(pid, &status, 0) == -1){
      perror("Waitpid errors");
    }
    return true;
  }
  
  return false;
  
}

template <typename T>
void execute (vector<T> &token, int size, 
              bool previous, bool two_step_prev,
              int connector1, int connector2){
                
  //cout << "Before: "; Vec_print(token); cout << "With size: " << token.size() << endl;
  
  if(size < 1){
    //cout << "No arguements" << endl;
    return;
  }
  
  connector2 = connector1;
  
  vector<T> temp;
  int index = 0;
  //Vec_print(token);
  
  while((index < size) && (token[index] != ";") &&  (token[index] != "&&") && (token[index] != "||")){
    temp.push_back(token[index]);
    index++;
  }
  
  string tmp_con;
  //cout << index <<" "<< size << endl;
  
  //Vec_print(temp);
  // if(index < size){
  //   tmp_con = token[index - 1];
  // }
  // }else if(index == size){
  //   tmp_con = "&&";
  // }
  //cout << connector << endl;
  //cout << temp[index - 1]<< endl;
  if(token[index] == ";"){
    connector1 = 1;
  }else if(token[index] == "||"){
    connector1 = 2;
  }else if(token[index] == "&&") {
    connector1 = 3;
  }else 
    connector1 = 0;
  
  //Vec_print(temp);

  //remember previous two connectors
  previous = driver(temp);
  two_step_prev = previous;

  


  // /token.erase(token.begin(), token.begin() + index);
  cout << connector1 << endl;
  

  switch(connector1){
    case 0 : {
      token.erase(token.begin(), token.begin() + index);
      //cout << "After: "; Vec_print(token); cout << "With size: " << token.size() << endl;
      execute(token, token.size(), previous, two_step_prev, connector1, connector2);
    }break;
    case 1 : {
      token.erase(token.begin(), token.begin() + index + 1);
      //cout << "After: "; Vec_print(token); cout << "With size: " << token.size() << endl;
      execute(token, token.size(), previous, two_step_prev, connector1, connector2);
      
    }
      break;
    case 2 : {
      token.erase(token.begin(), token.begin() + index + 1);
      //cout << "After: "; Vec_print(token); cout << "With size: " << token.size() << endl;
      if((two_step_prev == true ) && (connector2 == 2)){
        previous = true;
      }
      execute(token, token.size(), previous, two_step_prev, connector1, connector2);
    } break;
    case 3 : {
      token.erase(token.begin(), token.begin() + index + 1);
      //cout << "After: "; Vec_print(token); cout << "With size: " << token.size() << endl;
      previous = true;
      execute(token, token.size(), previous, two_step_prev, connector1, connector2);
    } break;
    default:
    cout << "Invalid connector!"<<endl;
    break;
      
  }
  
  //cout << previous << endl;
}


#endif
