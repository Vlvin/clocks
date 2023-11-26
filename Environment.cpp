#include <iostream>
#include <string>
#include <map>

#include "headers/Clockswork.h"
#include "headers/Expr.h"
#include "headers/Stmt.h"
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/TokenType.h"
#include "headers/VisitorExpr.h"
#include "headers/VisitorStmt.h"
#include "headers/Environment.h"

using namespace std;

void Environment::define(string name, TokenLiteral value) {
    values.insert({name, value});
}

void Environment::assign(Token name, TokenLiteral value) {
    if (values.count(name.lexeme) > 0) {
            values.insert({name.lexeme, value});
        return;
    }

    throw RuntimeException(name, "Undefined variable '" + name.lexeme + "'.");
}

TokenLiteral Environment::get(Token name){
    if (values.count(name.lexeme) > 0) {
        return values.find(name.lexeme)->second;
    }
    throw RuntimeException(name , "Undefined variable '" + name.lexeme + "'.");
}