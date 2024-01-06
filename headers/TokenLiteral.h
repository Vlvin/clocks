#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LoxCallable;
class LoxInstance;

class TokenLiteral {
    double d;
    string s;
    LoxCallable* lc;
    LoxInstance* li;
    // you need LoxCallable here as a new type of var
public:
    bool isReturn;
    enum lType {
        NUMBER,
        STRING,
        BOOLEAN,
        CALLABLE,
        INSTANCE,
        NIL
    };

    lType type;

    TokenLiteral();
    TokenLiteral(double d);
    TokenLiteral(string s);
    TokenLiteral(LoxCallable* lc);
    TokenLiteral(LoxInstance* li);
    TokenLiteral(bool b);
    TokenLiteral(TokenLiteral tl, bool isReturn);

    LoxCallable* toCallable();
    LoxInstance* toInstance();
    string toString();
    double toNumber();

    bool equals(TokenLiteral other);
};