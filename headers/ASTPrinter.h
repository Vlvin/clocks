#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Clockswork.h"
#include "Expr.h"
#include "Token.h"
#include "TokenLiteral.h"
#include "TokenType.h"
#include "VisitorExpr.h"

class ASTPrinter : public VisitorExpr {
public:

    string print(Expr *expr);
    string parenthesize(string name, vector<Expr*> vex);


    virtual string visitBinarystring(Binary &expr) override;
    virtual string visitGroupingstring(Grouping &expr) override;
    virtual string visitLiteralstring(Literal &expr) override;
    virtual string visitUnarystring(Unary &expr) override;

    virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) override;
    virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) override;
    virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) override;
    virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) override;

};