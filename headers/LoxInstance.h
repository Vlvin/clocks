#pragma once

#include <string>
#include <map>
using namespace std;
#include "TokenLiteral.h"
#include "Token.h"

class LoxClass;

class LoxInstance {
    LoxClass* LClass;
    map<string, TokenLiteral> fields = {};
public:
    LoxInstance(LoxClass* LClass);
    string toString();
    TokenLiteral get(Token name);
    TokenLiteral set(Token name, TokenLiteral value);
};