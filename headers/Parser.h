#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Clockswork.h"
#include "Expr.h"
#include "Stmt.h"
#include "Token.h"
#include "TokenLiteral.h"
#include "TokenType.h"

using namespace std;

class ParseError : public exception {};

class Parser {
    vector<Token> tokens;
    int current = 0;
    string modulename;

    void synchronize();

    Expr* expression();
    Expr* assignment();
    Expr* orr();
    Expr* aand();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* call();
    Expr* finishCall(Expr* callee);
    Expr* primary();

    Stmt* statement();
    Stmt* declaration();
    Stmt* constDeclaration();
    Stmt* varDeclaration(bool isConst);
    Stmt* classDeclaration(bool isConst);
    Stmt* function(string kind, bool isConst);
    Stmt* forStatement();
    Stmt* ifStatement();
    Stmt* whileStatement();
    Stmt* includeStatement();
    Stmt* returnStatement();
    Stmt* printStatements();
    vector<Stmt*> block();
    Stmt* expressionStatement();

    bool match(vector<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();

    Token advance();
    Token peek();
    Token previous();
    Token consume(TokenType type, string message);
    Token consumes(vector<TokenType> types, string message);

    ParseError error(string modulename, Token token, string message);
public:
    vector<Stmt*> parse(string modulename);

    Parser(vector<Token> tokens);
};
