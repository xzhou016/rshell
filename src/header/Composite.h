#ifndef PARSE_H
#define PARSE_H
#include <iostream>

using namespace std;

//root class for accessing command object
class BaseCommand{
public:
  BaseCommand(){};
  ~BaseCommand(){};
  virtual void run(string command_line) = 0;
};

#endif
