#pragma once


#include <vector>

using namespace std;

#include "LoxCallable.h"
#include "TokenLiteral.h"
#include "Stmt.h"


class Interpreter;

class Environment;
class LoxInstance;

class LoxFunction: public LoxCallable {
    Function &declaration;
    Environment *closure;
    bool isInitializer;
public:
    LoxFunction(Function &declaration, Environment *closure, bool isInitializer);
    TokenLiteral bind(LoxInstance* binding);
    virtual int arity() override;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) override;
    virtual string toString() override;
};