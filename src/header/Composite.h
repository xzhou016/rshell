#ifndef COMPOSITE_H
#define COMPOSITE_H

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

//base class for executing commands
class BaseCommand{
  BaseCommand::BaseCommand(){};

  virtual int run() = 0;
}

//root of a single command
class Executable : public BaseCommand{
private:
  string command;
  int PID;
public:

}



class VarComposite : public BaseCommand
{
		private:
	    int PID;
	    vector<BaseCommand*> CMContainer;

		public:
		VarComposite();
		~VarComposite();
		//void add(string command);
		//void ANDhandler(string command);
		//void ORhandler(string command);
    int run();

};



#endif
