#ifndef REDIRECTION_H
#define REDIRECTION_H

class RedirectIn : public ExecuteBase {
private:
ExecuteBase* left;
ExecuteBase* right;

public: 
    RedirectIn(ExecuteBase* l, ExecuteBase* r)
    :left(l), right(r){};
    
    ~RedirectIn(){};
    
    //add data in right token to left token
    //and execute to the file with filename in right token
    virtual bool run(){
        cout << "in indirect out" << endl;
        
        left->addArgs(right->getString());
        //right->addArgs("\0");
        
        int in = open(right->getString().c_str(), O_RDONLY);
        
        if(left->run(in, 0)){
            close(in);
            return true;
        }
        
        close(in);
        return false;
        
    };
};

class RedirectOut : public ExecuteBase {
private:
ExecuteBase* left;
ExecuteBase* right;

public: 
    RedirectOut(ExecuteBase* l, ExecuteBase* r)
    :left(l), right(r){};
    
    ~RedirectOut(){};
    
    //add all the piping extensions in right token to left token
    // run with left token to read from file
    virtual bool run(){
        cout << "in indirect out" << endl;
        
        left->addArgs(right->getString());
        right->addArgs("\0");
        int out = open(right->getString().c_str(), 
                    O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        
        if(left->run(0, out)){
            close(out);
            return true;
        }
        
        close(out);
        return false;
    }
};

class Pipes : public ExecuteBase {
private: 
ExecuteBase* left;
ExecuteBase* right;

public: 
    Pipes(ExecuteBase* l, ExecuteBase* r)
    :left(l), right(r){};
    
    ~Pipes(){};
    
    //will take 2 ints
    virtual bool run() {return false;};

    virtual bool run(int in, int out){
        int pipefd[2];
        int piping = pipe(pipefd);
        if(piping < 0 ){
            perror("piping failed");
            return false;
            
        //replace std output with output part of pipe    
        }else if (!right->run(pipefd[0], out )){
            close(pipefd[0]);
            return false;
            
        //replace std input with input part of pipe 
        }else if (!left->run(in, pipefd[1]))
            close(pipefd[1]);
            return false;
        return true;
    }
};


#endif