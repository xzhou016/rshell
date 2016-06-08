#ifndef TOKENS_H
#define TOKENS_H

#include <string.h>

class Token : public ExecuteBase {
private:
    char** args; //special token list for execvp
    int args_index; //count the index 
    bool runState;
    string internal_string;
public:
    Token(){
        this->args = new char*[256];
        this->args_index = 0;
        this->runState = false;
    };
    ~Token(){};
    
    // add a token to char** for execution
    void addArgs(string executable);
    
    virtual bool run();
    virtual bool run(int in, int out);
    
    virtual void print();
    
    string getString();
    
    char** getArgs();
    
};

#endif