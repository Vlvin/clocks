#pragma once

#include <vector>
#include <string>

using namespace std;

#include "LoxCallable.h"

class LoxFunction;

class LoxClass: public LoxCallable {
    map<string, LoxFunction*> methods;
    map<string, LoxFunction*> statics;
public:
    LoxClass* superclass;
    string name;
    LoxClass(string name, LoxClass* superclass, map<string, LoxFunction*> statics, map<string, LoxFunction*> methods);
    LoxFunction *findMethod(string name);
    LoxFunction *findStaticMethod(string name);
    virtual int arity() override;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) override;
    virtual string toString() override;
};