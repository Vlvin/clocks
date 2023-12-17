#pragma once
#include <vector>
#include <string>
/**
 * One moment you need to know about this file
 * In nowaday concept 
 * you need to use it in TokenLiteral
 * But as you can see, you are using TL here so 
 * in case of basic include you will 
 * have circular import 
*/

#include "TokenLiteral.h"
#include "Interpreter.h"

class LoxCallable {
public:
    virtual int arity() = 0;
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) = 0;
    virtual string toString() = 0;
};