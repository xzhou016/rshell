#include "../src/header/Tokens.h"

void Token::addArgs(string executable){
    args[args_index] = strdup(executable.c_str());
    internal_string = executable;
    //cout << executable << endl;
    args_index++;
}

bool Token::run(){
    
    pid_t pid = fork();
    int state;
    
    if(pid == -1 ){
        perror("fork failed");
        runState = false;
    }else if(pid == 0){
        args[args_index] = '\0'; //adds end of line to correct bad address error
        if(execvp(args[0], args) == -1){
            perror("execvp failed");
            runState = false;
        }
    }else if(pid > 0) {
        if(waitpid(pid, &state, 0) == -1)
            perror("Wait failed");
        runState = true;
    }
    
    return runState;
}

//special run function for redirection
bool Token::run(int in, int out){
    
    pid_t pid = fork();
    int state;
    
    if(pid == -1 ){
            perror("fork failed");
            runState = false;
        }else if(pid == 0){
            
            args[args_index] = '\0';
            
            //redirect in
            if( in < 0){
                perror("cannot open file");
                runState = false;
            }else if(dup2(in, 0) < 0){
                perror("cannot dup");
                runState = false;
                exit(1);
            }
            //redirect out
            if(out < 0 ){
                perror("cannot open file");
                runState = false;
            }else if(dup2(out, 1) < 0){
                perror("cannot dup");
                runState = false;
                exit(1);
            }
            
            //run the exevp
            if(execvp(args[0], args)){
                perror("cannot execvp");
                runState = false;
                exit(1);
            }
        }else if(pid > 0) {
            if(waitpid(pid, &state, 0) == -1)
                perror("Wait failed");
            runState = true;
        }
    return runState;
}


void Token::print(){
    cout << "[";
    for (int i = 0; i < args_index; i++) {
        cout << args[i] << " ";
    }cout <<"]"<< endl;
}

string Token::getString(){
    return internal_string;
}

char** Token::getArgs(){
    return args;
}