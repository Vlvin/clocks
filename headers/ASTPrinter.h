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
#include "VisitorStmt.h"

class ASTPrinter : public VisitorExpr, public VisitorStmt  {
public:

    string print(Expr *expr);
    string print(vector<Stmt*> statements);
    string parenthesize(string name, vector<Expr*> vex);

    virtual string visitBinarystring(Binary &expr) override;
    virtual string visitGroupingstring(Grouping &expr) override;
    virtual string visitLiteralstring(Literal &expr) override;
    virtual string visitUnarystring(Unary &expr) override;
    virtual string visitVariablestring(Variable &expr) override;
    virtual string visitAssignstring(Assign &expr) override;

    virtual string visitExpressionstring(Expression &stmt) override;
    virtual string visitPrintstring(Print &stmt) override;
    virtual string visitVarstring(Var &stmt) override;
    virtual string visitBlockstring(Block &stmt) override;
    virtual string visitIfstring(If &stmt) override;

    virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) override;
    virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) override;
    virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) override;
    virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) override;
    virtual TokenLiteral visitVariableTokenLiteral(Variable &expr) override;
    virtual TokenLiteral visitAssignTokenLiteral(Assign &expr) override;

    virtual TokenLiteral visitExpressionTokenLiteral(Expression &stmt) override;
    virtual TokenLiteral visitPrintTokenLiteral(Print &stmt) override;
    virtual TokenLiteral visitVarTokenLiteral(Var &stmt) override;
    virtual TokenLiteral visitBlockTokenLiteral(Block &stmt) override;
    virtual TokenLiteral visitIfTokenLiteral(If &stmt) override;

};