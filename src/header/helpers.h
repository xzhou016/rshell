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
      //cout << "Can't get user name." ;
      //throw "e";
    }else
      user_name= getlogin();

  }catch(int e){
    perror("Host has problems:");
  }

  //display user login info
  cout << user_name << "@" << host << "$ ";
}

template <typename T>
void check_comment(vector<T> &tokens){
  for (unsigned int i = 0; i < tokens.size(); ++i) {
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