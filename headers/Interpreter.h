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

class Interpreter : public VisitorExpr {

    TokenLiteral evaluate(Expr *expr);

    string stringify(TokenLiteral literal);

    bool isTruthy(TokenLiteral literal);
    bool isEqual(TokenLiteral left, TokenLiteral right);
    void checkNumberOperand(Token oper, TokenLiteral operand);
    void checkNumberOperands(Token oper, TokenLiteral left, TokenLiteral right);
public:

    void interpret(Expr *expr);

    virtual string visitBinarystring(Binary &expr) override;
    virtual string visitGroupingstring(Grouping &expr) override;
    virtual string visitLiteralstring(Literal &expr) override;
    virtual string visitUnarystring(Unary &expr) override;

    virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) override;
    virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) override;
    virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) override;
    virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) override;


};