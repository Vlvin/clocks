#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TokenLiteral {
    double d;
    string s;
public:
    enum lType {
        NUMBER,
        STRING,
        BOOLEAN,
        NIL
    };

    lType type;

    TokenLiteral();
    TokenLiteral(double d);
    TokenLiteral(string s);
    TokenLiteral(bool b);

    string toString();
    double toNumber();

    bool equals(TokenLiteral other);
};