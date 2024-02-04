#pragma once

#include <string>
#include <map>
using namespace std;
#include "TokenLiteral.h"
#include "Token.h"

class LoxClass;

class LoxInstance {
    map<string, TokenLiteral> fields = {};
public:
    LoxClass* LClass;
    LoxInstance(LoxClass* LClass);
    virtual string toString();
    virtual TokenLiteral get(Token name);
    virtual TokenLiteral set(Token name, TokenLiteral value);
};