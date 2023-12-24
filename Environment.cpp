#include <iostream>
#include <string>
#include <map>

#include "headers/Clockswork.h" 
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/Environment.h"

using namespace std;

Environment::Environment() {
    enclosing = NULL;
}

Environment::Environment(Environment *enclosing) 
    : enclosing(enclosing) {}

void Environment::define(string name, TokenLiteral value) {
    values.insert({name, value}); 
}
 
void Environment::assign(Token name, TokenLiteral value) {
    if (values.count(name.lexeme) > 0) {
        values.find(name.lexeme)->second = value;
        return;
    }
    if (enclosing != NULL) {
        enclosing->assign(name, value);
        return;
    }


    throw RuntimeException(name, "Undefined variable '" + name.lexeme + "'.");
}

TokenLiteral Environment::get(Token name){
    if (values.count(name.lexeme) > 0) {
        return values.find(name.lexeme)->second;
    }
    if (enclosing != NULL) {
        return enclosing->get(name);
    }
    throw RuntimeException(name , "Undefined variable '" + name.lexeme + "'.");
}