
#include <iostream>
#include <string>
#include <vector>

#include "headers/Clockswork.h"
#include "headers/Expr.h"
#include "headers/Stmt.h"
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/TokenType.h"

#include "headers/Parser.h"

using namespace std;

Parser::Parser(vector<Token> tokens) 
    : tokens(tokens) {}

ParseError Parser::error(Token token, string message) {
    Clockwork::error(token, message);
    return ParseError();
}

void Parser::synchronize() {
        advance();

        while (!isAtEnd()) {
            if (previous().type == SEMICOLON) return;
        
            switch (peek().type) {
                case CLASS:
                case FUN:
                case VAR:
                case FOR:
                case IF:
                case WHILE:
                case PRINT:
                case RETURN:
                    return;
            }

            advance();
        }
    }


bool Parser::match(vector<TokenType> types) {
    for (TokenType type: types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return (peek().type == type);
}

bool Parser::isAtEnd() {
    return (peek().type == T_EOF);
}


Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current-1];
}

Token Parser::consume(TokenType type, string message) {
    if (check(type)) return advance();
    throw error(peek(), message);
}

vector<Stmt*> Parser::parse() {
    vector<Stmt*> statements = {};
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

Stmt* Parser::declaration() {
    try {
        if (match({VAR})) return varDeclaration();

        return statement();
    } catch (ParseError error) {
        synchronize();
        return NULL;
    }
}

Stmt* Parser::varDeclaration() {
    Token name = consume(IDENTIFIER, "Expect variable name");

    Expr* initializer = NULL;
    if (match({EQUAL})) {
        initializer = expression();
    }

    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(name, initializer);
}

Stmt* Parser::statement() {
    if (match({PRINT})) return printStatements();
    if (match({LEFT_BRACE})) {
        return new Block(block());
    }
    return expressionStatement();
}

Stmt* Parser::printStatements() {
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after value");
    return new Print(value);
}

Stmt* Parser::expressionStatement() {
    Expr* expr = expression();
    consume(SEMICOLON, "Expect ';' after value");
    return new Expression(expr);
}

vector<Stmt*> Parser::block() {
    vector<Stmt*> statements = {};
    while ((!check(RIGHT_BRACE)) && (!isAtEnd())) {
        statements.push_back(declaration());
    }

    consume(RIGHT_BRACE, "Expect '}' after block");
    return statements;
}

Expr* Parser::expression() {
    return assignment();
}

Expr* Parser::assignment() {
    Expr* expr = equality();

    if (match({EQUAL})) {
        Token equals = previous();
        Expr* value = assignment();
        Variable *assign = dynamic_cast<Variable *>(expr);
        if (assign != nullptr) {
            Token name = assign->name;
            return new Assign(name, value);
        }

        error(equals, "Invalid assignmnt target");
    }
    return expr;
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        Token oper = previous();
        Expr* right = comparison();
        expr = new Binary(expr, oper, right);
    }

    return expr;
}

Expr* Parser::comparison() {
    Expr* expr = term();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token oper = previous();
        Expr* right = term();
        expr = new Binary(expr, oper, right);
    }

    return expr;
}

Expr* Parser::term() {
    Expr* expr = factor();

    while (match({MINUS, PLUS})) {
        Token oper = previous();
        Expr* right = factor();
        expr = new Binary(expr, oper, right);
    }
    
    return expr;
}

Expr* Parser::factor() {
    Expr* expr = unary();

    while (match({SLASH, STAR})) {
        Token oper = previous();
        Expr* right = unary();
        expr = new Binary(expr, oper, right);
    }
    
    return expr;
}

Expr* Parser::unary() {

    if (match({BANG, MINUS})) {
        Token oper = previous();
        Expr* right = unary();
        return new Unary(oper, right);
    }

    return primary();
}

Expr* Parser::primary() {
    if (match({FALSE})) return new Literal(TokenLiteral(false));
    if (match({TRUE})) return new Literal(TokenLiteral(true));
    if (match({TokenType::NIL})) return new Literal(TokenLiteral());
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return new Literal(previous().literal);
    }
    if (match({IDENTIFIER})) {
        return new Variable(previous());
    }
    if (match({LEFT_PAREN})) {
        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression. ");
}
