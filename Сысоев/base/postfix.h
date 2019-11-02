#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string StringDecoder(string);

class TPostfix
{
  string infix;
  string postfix;
public:
  TPostfix()
  {
    infix = "a + b";
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  void SetInfix(string expression) { infix = StringDecoder(expression); }
  string ToPostfix();
  double Calculate(string a = ""); // Ввод переменных, вычисление по постфиксной форме
};



#endif
