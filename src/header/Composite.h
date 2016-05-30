#ifndef COMPOSITE_H
#define COMPOSITE_H

using namespace std;

class ExecuteBase {
public:
    ExecuteBase(){};
    ~ExecuteBase(){};
    //virtual void run(int i){};
    virtual bool run() = 0;
    virtual void print(){};
    virtual string getString(){ return NULL;};
};

class AndConnector : public ExecuteBase {
private:
ExecuteBase* left;
ExecuteBase* right;
 
public:
    
    AndConnector(ExecuteBase* l, ExecuteBase* r) //
    :left(l), right(r){};
    
    AndConnector(ExecuteBase* l):left(l){}; //left node constructor
    
    ~AndConnector(){};
    
    virtual bool run() {
        if(left->run()){
            if(right->run())
                return true;
            return false;
        }else 
            return false;
    };
    
};

class OrConnector : public ExecuteBase {
private:
ExecuteBase* left;
ExecuteBase* right;
 
public:
    OrConnector(ExecuteBase* l, ExecuteBase* r)
    :left(l), right(r){};
    ~OrConnector(){};
    
    virtual bool run(){
        if(!left->run()) {
            if(right->run())
                return true;
            return false;
        }else
            return false;
    };    
};

class CommaConnector : public ExecuteBase {
private:
    ExecuteBase* child;

public:
    CommaConnector(ExecuteBase* c)
    :child(c){};
    ~CommaConnector(){};

    virtual bool run(){
        if(child->run())
            return true;
        else 
            return false;
    };
};

class Exit : public ExecuteBase {
public:
    Exit(){};
    ~Exit(){};
    
    virtual bool run(){ 
        exit(0);
        //return true;
    }
};

#endif