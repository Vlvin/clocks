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
#include "VisitorExpr.h"
#include "VisitorStmt.h"
#include "Environment.h"

class Interpreter : public VisitorExpr, public VisitorStmt {

    Environment *environment = new Environment();
    TokenLiteral evaluate(Expr *expr);
    TokenLiteral execute(Stmt *statement);

    string stringify(TokenLiteral literal);

    bool isTruthy(TokenLiteral literal);
    bool isEqual(TokenLiteral left, TokenLiteral right);
    void checkNumberOperand(Token oper, TokenLiteral operand);
    void checkNumberOperands(Token oper, TokenLiteral left, TokenLiteral right);
public:

    void interpret(vector<Stmt*> statements);
    void interpret(Expr* expr);
    void executeBlock(vector<Stmt*> statements, Environment *environment);

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


};