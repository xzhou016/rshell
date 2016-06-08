#ifndef COMPOSITE_H
#define COMPOSITE_H

using namespace std;

class ExecuteBase {
public:
    ExecuteBase(){};
    ~ExecuteBase(){};
    //virtual void run(int i){};
    virtual bool run() = 0;
    virtual bool run(int in, int out){ return false;};
    virtual void print(){};
    virtual string getString(){ return NULL;};
    virtual char** getArgs(){return NULL;};
    virtual void addArgs(string executable){};
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

    virtual string getString() {return "&&";};
    ExecuteBase* getLeft() {return left;};
    ExecuteBase* getRight() {return right;};

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
    virtual string getString() {return "||";};
    ExecuteBase* getLeft() {return left;};
    ExecuteBase* getRight() {return right;};

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
    virtual string getString() {return ";";};
};

class Exit : public ExecuteBase {
public:
    Exit(){};
    ~Exit(){};

    virtual bool run(){
        exit(1);
        //return true;
    }
    virtual string getString() { return NULL; };
};

#endif
