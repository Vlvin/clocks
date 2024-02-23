#include "headers/LoxInstance.h"
#include "headers/LoxClass.h"
#include "headers/LoxFunction.h"

LoxInstance::LoxInstance(LoxClass* LClass) : LClass(LClass) {}

string LoxInstance::toString() {
    return "<Instance of " + LClass->name + ">";
}

TokenLiteral LoxInstance::get(string modulename, Token name) {
    if (fields.count(name.lexeme) > 0) {
        return fields.find(name.lexeme)->second;
    }

    LoxFunction *method = LClass->findMethod(name.lexeme);
    if (method != nullptr) {
        return method->bind(this);
    }

    LoxFunction *sMethod = LClass->findStaticMethod(name.lexeme);
    if (sMethod != nullptr) {
        return method;
    }
    throw RuntimeException(
        modulename,
        name,
        "Undefined property '" + name.lexeme + "'.");
}

TokenLiteral LoxInstance::set(Token name, TokenLiteral value) {
    if (fields.count(name.lexeme) > 0) {
        fields.find(name.lexeme)->second = value;
    } else {
        fields.insert({name.lexeme, value});
    }
    return value;
}