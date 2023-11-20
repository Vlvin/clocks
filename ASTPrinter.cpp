#include <iostream>
#include <string>
#include <vector>

#include "headers/Clockswork.h"
#include "headers/Expr.h"
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/TokenType.h"
#include "headers/VisitorExpr.h"
#include "headers/ASTPrinter.h"
#include "headers/VisitorStmt.h"



string ASTPrinter::print(Expr *expr)  {
    return expr->acceptstring(this);
}

string ASTPrinter::parenthesize(string name, vector<Expr*> exprV) {
    string retline = "(";
    // operation name
    retline += name;
    for (Expr* expr: exprV) {
        retline += " ";
        // each in op
        retline += (expr->acceptstring(this));
    }
    retline += ")";

    return retline;
}


string ASTPrinter::visitBinarystring(Binary &expr) {
    return parenthesize(expr.oper.lexeme, {expr.left, expr.right});
}

string ASTPrinter::visitGroupingstring(Grouping &expr) {
    return parenthesize("group", {expr.expr});

}

string ASTPrinter::visitLiteralstring(Literal &expr) {
    if (expr.value.type == TokenLiteral::NIL) return "nil";
    return expr.value.toString();
}

string ASTPrinter::visitUnarystring(Unary &expr) {
    return parenthesize(expr.oper.lexeme, {expr.right});

}


TokenLiteral ASTPrinter::visitBinaryTokenLiteral(Binary &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitGroupingTokenLiteral(Grouping &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitLiteralTokenLiteral(Literal &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitUnaryTokenLiteral(Unary &expr) { return TokenLiteral(); }
