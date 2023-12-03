#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Clockswork.h"
#include "Expr.h"
#include "Stmt.h"
#include "Token.h"
#include "TokenLiteral.h"
#include "TokenType.h"
#include "VisitorExpr.h"
#include "VisitorStmt.h"

using namespace std;

class Environment {
    map<string, TokenLiteral> values;

public:

    Environment();
    Environment (Environment *enclosing);
    Environment *enclosing; // this is your problem now
    void define(string name, TokenLiteral value);
    void assign(Token name, TokenLiteral value);

    TokenLiteral get(Token name);
};