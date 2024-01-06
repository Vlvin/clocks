#include <string>
#include <iostream>

using namespace std;

#include "headers/LoxFunction.h"
#include "headers/LoxInstance.h"
#include "headers/Environment.h"
#include "headers/TokenLiteral.h"
#include "headers/Interpreter.h"
#include "headers/Clockswork.h"
#include "headers/Stmt.h"

LoxFunction::LoxFunction(Function &declaration, Environment *closure, bool isInitializer) 
    : declaration(declaration), closure(closure), isInitializer(isInitializer) {}
 
int LoxFunction::arity() {
    return declaration.params.size();
}

TokenLiteral LoxFunction::bind(LoxInstance* binding) {
    Environment *environment = new Environment(closure);
    environment->define("this", binding);
    return new LoxFunction(declaration, environment, isInitializer);
}

TokenLiteral LoxFunction::call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
    Environment *LocalEnvironment = new Environment(closure);
    for (int i = 0; i < declaration.params.size(); i++) {
        LocalEnvironment->define(declaration.params[i], arguments[i]);
    }
    if (isInitializer) return TokenLiteral(closure->getAt(0, "this"));
    return TokenLiteral(interpreter->executeBlock(declaration.body, LocalEnvironment), false);
}

string LoxFunction::toString() {
    return "<fun " + declaration.name.lexeme + ">";
}