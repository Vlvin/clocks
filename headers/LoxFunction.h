#pragma once


#include <vector>

using namespace std;

#include "LoxCallable.h"
#include "Interpreter.h"
#include "TokenLiteral.h"
#include "Stmt.h"

class Environment;

class LoxFunction: public LoxCallable {
    Function &declaration;
    Environment *closure;
public:
    LoxFunction(Function &declaration, Environment *closure);
    virtual int arity() override;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) override;
    virtual string toString() override;
};