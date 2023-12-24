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

string ASTPrinter::print(vector<Stmt*> statements)  {
    string code = "";
    for (Stmt* statement: statements) {
        code += (statement->acceptstring(this));
    }
    return code;
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

string ASTPrinter::visitVariablestring(Variable &expr) {
    return expr.name.lexeme;
}

string ASTPrinter::visitAssignstring(Assign &expr) {
    return parenthesize("= " + expr.name.lexeme, {expr.value});
}



string ASTPrinter::visitExpressionstring(Expression &stmt) {
    return "EXPRESSION " + print(stmt.expression);
}
string ASTPrinter::visitPrintstring(Print &stmt) {
    return "PRINT " + print(stmt.expression);
}
string ASTPrinter::visitVarstring(Var &stmt) {
    return "VAR " + stmt.name.lexeme + " " + print(stmt.initializer);
}
string ASTPrinter::visitBlockstring(Block &stmt) {
    string parent = "BLOCK {";
    for (Stmt* statement: stmt.statements) {
        parent += " " + statement->acceptstring(this);
    }
    parent += "}";
    return parent;
}
string ASTPrinter::visitIfstring(If &stmt) {
    string toret = parenthesize("IF", {stmt.condition});
    toret += " THEN " + stmt.thenBranch->acceptstring(this);
    if (stmt.elseBranch != NULL) toret += " ELSE " + stmt.elseBranch->acceptstring(this);
    return toret;
}   


TokenLiteral ASTPrinter::visitBinaryTokenLiteral(Binary &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitGroupingTokenLiteral(Grouping &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitLiteralTokenLiteral(Literal &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitUnaryTokenLiteral(Unary &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitVariableTokenLiteral(Variable &expr) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitAssignTokenLiteral(Assign &expr) { return TokenLiteral(); }

TokenLiteral ASTPrinter::visitExpressionTokenLiteral(Expression &stmt) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitPrintTokenLiteral(Print &stmt) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitVarTokenLiteral(Var &stmt) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitBlockTokenLiteral(Block &stmt) { return TokenLiteral(); }
TokenLiteral ASTPrinter::visitIfTokenLiteral(If &stmt) { return TokenLiteral(); }
