#include <string>
#include <iostream>

using namespace std;

#include "headers/LoxFunction.h"
#include "headers/Environment.h"
#include "headers/TokenLiteral.h"
#include "headers/Clockswork.h"
#include "headers/Stmt.h"

LoxFunction::LoxFunction(Function &declaration, Environment *closure) 
    : declaration(declaration), closure(closure) {}
 
int LoxFunction::arity() {
    return declaration.params.size();
}  

TokenLiteral LoxFunction::call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
    Environment *environment = new Environment(closure);
    for (int i = 0; i < declaration.params.size(); i++) {
        environment->define(declaration.params[i].lexeme, arguments[i]);
    }
    try {
        interpreter->executeBlock(declaration.body, environment);
    } catch (TokenLiteral ret) {
        return ret;
    }
    return TokenLiteral(); 
}

string LoxFunction::toString() {
    return "<fun " + declaration.name.lexeme + ">";
}