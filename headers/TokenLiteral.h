#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LoxCallable;

class TokenLiteral {
    double d;
    string s;
    LoxCallable* lc;
    // you need LoxCallable here as a new type of var
public:
    enum lType {
        NUMBER,
        STRING,
        BOOLEAN,
        CALLABLE,
        NIL
    };

    lType type;

    TokenLiteral();
    TokenLiteral(double d);
    TokenLiteral(string s);
    TokenLiteral(LoxCallable* lc);
    TokenLiteral(bool b);

    LoxCallable* toCallable();
    string toString();
    double toNumber();

    bool equals(TokenLiteral other);
};