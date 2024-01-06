#pragma once

#include <vector>
#include <string>

using namespace std;

#include "LoxCallable.h"

class LoxFunction;

class LoxClass: public LoxCallable {
    map<string, LoxFunction*> methods;
public:
    string name;
    LoxClass(string name, map<string, LoxFunction*> methods);
    LoxFunction *findMethod(string name);
    virtual int arity() override;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) override;
    virtual string toString() override;
};