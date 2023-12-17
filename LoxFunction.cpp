#include <string>

using namespace std;

#include "headers/LoxFunction.h"
#include "headers/Environment.h"
#include "headers/Stmt.h"

LoxFunction::LoxFunction(Function &declaration) 
    : declaration(declaration) {}

int LoxFunction::arity() {
    return declaration.params.size();
}

TokenLiteral LoxFunction::call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
    Environment *environment = new Environment(interpreter->globals);
    for (int i = 0; i < declaration.params.size(); i++) {
        environment->define(declaration.params[i].lexeme, arguments[i]);
    }

    interpreter->executeBlock(declaration.body, environment);
    return TokenLiteral(); 
}

string LoxFunction::toString() {
    return "<fun " + declaration.name.lexeme + ">";
}