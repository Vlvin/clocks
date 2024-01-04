#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Token.h"
#include "TokenLiteral.h"

using namespace std;

class Environment {
    map<string, TokenLiteral> values;
    public:

    Environment();
    Environment (Environment *enclosing);
    Environment *enclosing;
    Environment* ancestor(int distance);
    void define(string name, TokenLiteral value);
    void define(Token name, TokenLiteral value);
    void assign(Token name, TokenLiteral value);
    void assignAt(int distance, Token name, TokenLiteral value);

    TokenLiteral get(Token name);
    TokenLiteral getAt(int distance, string name);

};