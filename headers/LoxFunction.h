#pragma once


#include <vector>

using namespace std;

#include "LoxCallable.h"
#include "Interpreter.h"
#include "TokenLiteral.h"
#include "Stmt.h"

class LoxFunction: public LoxCallable {
    Function &declaration;
public:
    LoxFunction(Function &declaration);
    virtual int arity() override;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) override;
    virtual string toString() override;
};