#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "TokenType.h"
#include "TokenLiteral.h"

using namespace std;

class Token {
public:
    TokenType type;
    string lexeme;
    TokenLiteral literal;
    int line;
    static const char* TTT[42];
    Token(TokenType type, string lexeme, TokenLiteral literal, int line);
    string toString();
    bool operator==(Token other);
};