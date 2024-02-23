
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
    : tokens(tokens), modulename("") {}

ParseError Parser::error(string modulename, Token token, string message) {
    Clockwork::error(modulename, token, message);
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
    throw error(modulename, peek(), message);
}

Token Parser::consumes(vector<TokenType> types, string message) {
    for (TokenType type: types) {
        if (check(type)) return advance();
    }
    throw error(modulename, peek(), message);
}

vector<Stmt*> Parser::parse(string modulename) {
    this->modulename = modulename;
    vector<Stmt*> statements = {};
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

Stmt* Parser::declaration() {
    try {
        if (match({FUN})) return function("function", false);
        if (match({VAR})) return varDeclaration(false);
        if (match({CLASS})) return classDeclaration(false);
        if (match({CONST})) return constDeclaration();
        return statement();
    } catch (ParseError error) {
        synchronize();
        return nullptr;
    }
}

Stmt* Parser::constDeclaration() {
    if (match({VAR})) return varDeclaration(true);
    if (match({FUN})) return function("function", true);
    if (match({CLASS})) return classDeclaration(true);
    throw error(modulename, peek(), "Expected type after keyword 'const'.");
}

Stmt* Parser::varDeclaration(bool isConst) {
    Token name = consume(IDENTIFIER, "Expect variable name");

    Expr* initializer = nullptr;
    if (match({EQUAL})) {
        initializer = expression();
    } 

    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(name, initializer, isConst);
}

Stmt* Parser::classDeclaration(bool isConst) {
    Token name = consume(IDENTIFIER, "Expect class name");
    Variable* superclass = nullptr;
    if (match({LESS})) {
        consume(IDENTIFIER, "Expect superclass name after '<' in class declaration");
        superclass = new Variable(previous());
    }
    consume(LEFT_BRACE, "Expect '{' before class body");
    vector<Function*> methods = {};
    vector<Function*> statics = {};
    while(!check(RIGHT_BRACE) && !isAtEnd()) {
        if (match({CONST})) {
            if (match({STATIC})) {
                Function* sMethod = (dynamic_cast<Function*>(function("static_method", false)));
                statics.push_back(sMethod);
            }
            else {
                Function* method = (dynamic_cast<Function*>(function("method", false)));
                methods.push_back(method);
            }
        } else {
            if (match({STATIC})) {
                Function* sMethod = (dynamic_cast<Function*>(function("static_method", true)));
                statics.push_back(sMethod);
            }
            else {
                Function* method = (dynamic_cast<Function*>(function("method", true)));
                methods.push_back(method);
            }
        }
    }
    
    consume(RIGHT_BRACE, "Expect '}' after class body");
    return new Class(name, superclass, statics, methods, isConst);
}

Stmt* Parser::function(string kind, bool isConst) {
    Token name = consume(IDENTIFIER, "Expect " + kind + " name.");

    consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
    vector<Token> parameters = {};
    if (!check(RIGHT_PAREN)) {
        do {
            if (parameters.size() >= 253) {
                error(modulename, peek(), "Can't have more than 253 parameters.");
            }
            parameters.push_back(
                consume(IDENTIFIER, "Expect parameter name.")
            );
        } while (match({COMMA}));
    }
    consume(RIGHT_PAREN, "Expected ')' after parameters");

    consume(LEFT_BRACE, "Expect '{' before " + kind + " body");
    vector<Stmt*> body = block();
    return new Function(name, parameters, body, isConst);
}

Stmt* Parser::statement() {
    if (match({FOR})) return forStatement();
    if (match({IF})) return ifStatement();
    if (match({PRINT})) return printStatements();
    if (match({RETURN})) return returnStatement();
    if (match({WHILE})) return whileStatement();
    if (match({INCLUDE})) return includeStatement();
    if (match({LEFT_BRACE})) {
        return new Block(block());
    }
    return expressionStatement();
}

Stmt* Parser::includeStatement() {
    Expr* modulename = expression();
    Token cModule = previous();
    consume(SEMICOLON, "Expect ';' after value");
    return new Include(cModule, modulename);
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

Stmt* Parser::ifStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    Expr *condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after if condition.");

    Stmt *thenBranch = statement();
    Stmt *elseBranch = nullptr;
    if (match({ELSE})) {
        elseBranch = statement();
    }

    return new If(condition, thenBranch, elseBranch);
}

Stmt* Parser::whileStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    Expr* condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition");
    Stmt* body = statement();

    return new While(condition, body);
}

Stmt* Parser::returnStatement() {
    Token keyword = previous();
    Expr* value = nullptr;
    if (!check(SEMICOLON)) {
        value = expression();
    }
    consume(SEMICOLON, "Expect ';' after return value.");
    return new Return(keyword, value);
}

Stmt* Parser::forStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'for'.");

    Stmt* initializer;
    if (match({SEMICOLON})) {
        initializer = nullptr;
    } else if (match({VAR})) {
        initializer = varDeclaration(false);
    } else {
        initializer = expressionStatement();
    }

    Expr* condition = nullptr;
    if (!check(SEMICOLON)) {
        condition = expression();
    }
    consume(SEMICOLON, "Expect ';' after loop condition.");

    Expr* increment = nullptr;
    if (!check(RIGHT_PAREN)) {
        increment = expression();
    }
    consume(RIGHT_PAREN, "Expeted ')' after for clauses.");
    
    Stmt* body = statement();

    if (increment != nullptr) {
        body = new Block({body,
                            new Expression(increment)});
    }

    if (condition == nullptr) condition = new Literal(true);
    body = new While(condition, body);

    if (initializer != nullptr) {
        body = new Block({initializer, body});
    }

    return body;
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
    Expr* expr = orr();

    if (match({EQUAL})) {
        Token equals = previous();
        Expr* value = assignment();
        Variable *variable = dynamic_cast<Variable *>(expr);
        Get *property = dynamic_cast<Get *>(expr);
        if (variable != nullptr) {
            Token name = variable->name;
            return new Assign(name, value);
        } else if (property != nullptr) {
            return new Set(property->object, property->name, value);
        }

        error(modulename, equals, "Invalid assignmnt target");
    }
    return expr;
}

Expr* Parser::orr() {
    Expr* expr = aand();

    while(match({OR})) {
        Token oper = previous();
        Expr* right = aand();
        expr = new Logical(expr, oper, right);
    }

    return expr;
}

Expr* Parser::aand() {
    Expr* expr = equality();

    while(match({AND})) {
        Token oper = previous();
        Expr* right = equality();
        expr = new Logical(expr, oper, right);
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

    while (match({SLASH, STAR, MOD})) {
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

    return call();
}

Expr* Parser::call() {
    Expr* expr = primary();
    while (true) {
        if (match({LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match({DOT})) {
            Token name = consume(IDENTIFIER, "Expected member name after '.'.");
            expr = new Get(expr, name);
        } else {
            break;
        }
    }

    return expr;
}

Expr* Parser::finishCall(Expr* callee) {
    vector<Expr*> arguments = {};
    if (!check(RIGHT_PAREN)) {
        do {
            if (arguments.size() >= 253) {
                error(
                    modulename, 
                    peek(),
                    "Can't have more than 253 arguments."
                );
            }
            arguments.push_back(expression());
        } while(match({COMMA}));
    }

    Token paren = consume(
        RIGHT_PAREN,
        "Expect ')' after arguments.");
    
    return new Call(callee, paren, arguments);
}

Expr* Parser::primary() {
    if (match({THIS})) return new This(previous());
    if (match({SUPER})) return new Super(previous());
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

    throw error(modulename, peek(), "Expect expression. ");
}
