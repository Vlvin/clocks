#include <iostream>
#include <string>
#include <map>

#include "headers/Clockswork.h" 
#include "headers/Token.h"
#include "headers/LoxClass.h"
#include "headers/TokenLiteral.h"
#include "headers/Environment.h"

using namespace std;

Environment::Environment() {
    enclosing = NULL;
}

Environment::Environment(Environment *enclosing) 
    : enclosing(enclosing) {}

Environment* Environment::ancestor(int distance) {
    Environment* environment = this;
    for (int i = 0; i < distance; i++) {
        environment = environment->enclosing;
    }
    return environment;
}

void Environment::define(string name, TokenLiteral value) {
    values.insert({name, value}); 
}

void Environment::define(Token name, TokenLiteral value) {
    if (values.count(name.lexeme) > 0)
        throw RuntimeException(get("__name__").toString(), name, "Redefenition of variable '" + name.lexeme + "'.");
    else
        values.insert({name.lexeme, value});
}

void Environment::assign(Token name, TokenLiteral value) {
    if (values.count(name.lexeme) > 0) {
        auto target = values.find(name.lexeme);
        if (((!target->second.isConst) || target->second.type == TokenLiteral::NIL)) {
            target->second = TokenLiteral(value, {target->second.isReturn, target->second.isConst});
            return;
        } else {
            string errorTarget = "variable";
            if (target->second.type == TokenLiteral::CALLABLE) {
                if (dynamic_cast<LoxClass*>(target->second.toCallable()) != nullptr)
                    errorTarget = "class";
                else
                    errorTarget = "function";
            }
            throw RuntimeException(get("__name__").toString(), name, "Const " + errorTarget + " '" + name.lexeme + "' can't be changed");
        }
    }

    if (enclosing != NULL) {
        enclosing->assign(name, value);
        return;
    }


    throw RuntimeException(get("__name__").toString(), name, "Undefined variable '" + name.lexeme + "'.");
}


void Environment::assignAt(int distance, Token name, TokenLiteral value) {
    Environment* onPosition = ancestor(distance);
    auto target = onPosition->values.find(name.lexeme);
    if ((!target->second.isConst || target->second.type == TokenLiteral::NIL))
        target->second = TokenLiteral(value, {target->second.isReturn, target->second.isConst});
    else {
        string errorTarget = "variable";
        if (target->second.type == TokenLiteral::CALLABLE) {
            if (dynamic_cast<LoxClass*>(target->second.toCallable()) != nullptr)
                errorTarget = "class";
            else
                errorTarget = "function";
        }
        throw RuntimeException(get("__name__").toString(), name, "Const " + errorTarget + " '" + name.lexeme + "' can't be changed");
    }
}

void Environment::include(Token source, Environment* toAdd, Environment* exceptions) {
    
    for (auto i = toAdd->values.begin(); i != toAdd->values.end(); i++) {
        if (isExists(i->first)) {
            if (exceptions->isExists(i->first)) {
                define(i->first, i->second);
            } else {
                throw RuntimeException(get("__name__").toString(), source, "Multiple declaration of '" + i->first + "' imported from " + source.lexeme + ".");
            }
        } else if (!isExists(i->first)) {
            define(i->first, i->second);
        }
    }
}

void Environment::merge(Environment* toAdd) {
    for (auto i = toAdd->values.begin(); i != toAdd->values.end(); i++) {
            define(i->first, i->second);
    }
}

bool Environment::isExists(string name) {
    if (values.count(name) > 0) {
        return true;
    }
    if (enclosing != NULL) {
        return enclosing->isExists(name);
    }
    return false;
}

TokenLiteral Environment::get(Token name){
    if (values.count(name.lexeme) > 0) {
        return values.find(name.lexeme)->second;
    }
    if (enclosing != NULL) {
        return enclosing->get(name);
    }
    throw RuntimeException(get("__name__").toString(), name , "Undefined variable '" + name.lexeme + "'.");
}
// DO NOT USE
TokenLiteral Environment::get(string name){
    if (values.count(name) > 0) {
        return values.find(name)->second;
    }
    if (enclosing != NULL) {
        return enclosing->get(name);
    }
    return TokenLiteral();
}

TokenLiteral Environment::getAt(int distance, string name) {
    return ancestor(distance)->values.find(name)->second;
}