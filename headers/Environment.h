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
    void define(string name, TokenLiteral value);

    TokenLiteral get(Token name);
};