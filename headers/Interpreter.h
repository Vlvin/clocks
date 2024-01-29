#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "TokenLiteral.h"
#include "Clockswork.h"
#include "Expr.h"
#include "Stmt.h"
#include "VisitorExpr.h"
#include "VisitorStmt.h"
#include "Token.h"
#include "TokenType.h"
#include "Environment.h"

class LoxCallable;


class Interpreter : public VisitorExpr, public VisitorStmt {
public:
    Environment *globals = new Environment();
    Environment *environment = globals;
private:
    vector<int> functionDistance = {};
    map<Expr*, int> locals = {};
    TokenLiteral evaluate(Expr *expr);
    TokenLiteral execute(Stmt *statement);
    TokenLiteral lookUpVariable(Token name, Expr* expr);

    TokenLiteral moduloDivision(TokenLiteral left, TokenLiteral right);

    string stringify(TokenLiteral literal);

    bool isTruthy(TokenLiteral literal);
    bool isEqual(TokenLiteral left, TokenLiteral right);
    void checkNumberOperand(Token oper, TokenLiteral operand);
    void checkNumberOperands(Token oper, TokenLiteral left, TokenLiteral right);
public:
    Interpreter();
    
    void resolve(Expr* expr, int depth);
    void interpret(vector<Stmt*> statements);
    void interpret(Expr* expr);
    TokenLiteral executeBlock(vector<Stmt*> statements, Environment *environment);

    virtual string visitBinarystring(Binary &expr) override;
    virtual string visitCallstring(Call &expr) override;
    virtual string visitGetstring(Get &expr) override;
    virtual string visitSetstring(Set &expr) override;
    virtual string visitThisstring(This &expr) override;
    virtual string visitGroupingstring(Grouping &expr) override;
    virtual string visitLiteralstring(Literal &expr) override;
    virtual string visitUnarystring(Unary &expr) override;
    virtual string visitVariablestring(Variable &expr) override;
    virtual string visitAssignstring(Assign &expr) override;
    virtual string visitLogicalstring(Logical &expr) override;

    virtual string visitExpressionstring(Expression &stmt) override;
    virtual string visitFunctionstring(Function &stmt) override;
    virtual string visitClassstring(Class &stmt) override;
    virtual string visitPrintstring(Print &stmt) override;
    virtual string visitReturnstring(Return &stmt) override;
    virtual string visitVarstring(Var &stmt) override;
    virtual string visitBlockstring(Block &stmt) override;
    virtual string visitIfstring(If &stmt) override;
    virtual string visitWhilestring(While &stmt) override;

    virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) override;
    virtual TokenLiteral visitCallTokenLiteral(Call &expr) override;
    virtual TokenLiteral visitGetTokenLiteral(Get &expr) override;
    virtual TokenLiteral visitSetTokenLiteral(Set &expr) override;
    virtual TokenLiteral visitThisTokenLiteral(This &expr) override;
    virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) override;
    virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) override;
    virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) override;
    virtual TokenLiteral visitVariableTokenLiteral(Variable &expr) override;
    virtual TokenLiteral visitAssignTokenLiteral(Assign &expr) override;
    virtual TokenLiteral visitLogicalTokenLiteral(Logical &expr) override;

    virtual TokenLiteral visitExpressionTokenLiteral(Expression &stmt) override;
    virtual TokenLiteral visitFunctionTokenLiteral(Function &stmt) override;
    virtual TokenLiteral visitClassTokenLiteral(Class &stmt) override;
    virtual TokenLiteral visitPrintTokenLiteral(Print &stmt) override;
    virtual TokenLiteral visitReturnTokenLiteral(Return &stmt) override;
    virtual TokenLiteral visitVarTokenLiteral(Var &stmt) override;
    virtual TokenLiteral visitBlockTokenLiteral(Block &stmt) override;
    virtual TokenLiteral visitIfTokenLiteral(If &stmt) override;
    virtual TokenLiteral visitWhileTokenLiteral(While &stmt) override;


};