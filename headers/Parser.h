#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Clockswork.h"
#include "Expr.h"
#include "Token.h"
#include "TokenLiteral.h"
#include "TokenType.h"

using namespace std;

class ParseError : public exception {};

class Parser {
    vector<Token> tokens;
    int current = 0;

    void synchonize();

    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();

    bool match(vector<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();

    Token advance();
    Token peek();
    Token previous();
    Token consume(TokenType type, string message);
    
    ParseError error(Token token, string message);
public:
    Expr* parse();

    Parser(vector<Token> tokens);
};
