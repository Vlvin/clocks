#pragma once
#include <vector>
/**
 * One moment you need to know about this file
 * In nowaday concept 
 * you need to use it in TokenLiteral
 * But as you can see, you are using TL here so 
 * in case of basic include you will 
 * have circular import 
*/


#include "Interpreter.h"

class LoxCallable {
public:
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) = 0;
};