#include <iostream>
#include <string>
#include <vector>

#include "headers/Clockswork.h"
#include "headers/Expr.h"
#include "headers/Stmt.h"
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/TokenType.h"
#include "headers/VisitorExpr.h"
#include "headers/VisitorStmt.h"
#include "headers/Interpreter.h"

string Interpreter::visitBinarystring(Binary &expr){ return ""; }
string Interpreter::visitGroupingstring(Grouping &expr){ return ""; }
string Interpreter::visitLiteralstring(Literal &expr){ return ""; }
string Interpreter::visitUnarystring(Unary &expr){ return ""; }

string Interpreter::visitExpressionstring(Expression &stmt) { return ""; }
string Interpreter::visitPrintstring(Print &stmt) { return ""; }

TokenLiteral Interpreter::evaluate(Expr* expr) {
    return expr->acceptTokenLiteral(this);
}

TokenLiteral Interpreter::execute(Stmt* statement) {
    return statement->acceptTokenLiteral(this);
}

string Interpreter::stringify(TokenLiteral literal) {
    if (literal.type == TokenLiteral::NIL) return "nil";
    if (literal.type == TokenLiteral::NUMBER) {
        string text = literal.toString();
        if (endswith(text, ".000000")) {
            text = strrange(text, 0, text.length() - 7);
        }
        return text;
    }

    return literal.toString();
}

bool Interpreter::isTruthy(TokenLiteral literal) {
    if (literal.type == TokenLiteral::NIL) return false;
    if (literal.type == TokenLiteral::BOOLEAN) return literal.toNumber();
    return true;
}   

bool Interpreter::isEqual(TokenLiteral left, TokenLiteral right) {
    if ((left.type == TokenLiteral::NIL) && (right.type == TokenLiteral::NIL)) return true;
    if (left.type == TokenLiteral::NIL) return false;
    return left.equals(right);

}   

void Interpreter::checkNumberOperand(Token oper, TokenLiteral operand) {
    if ((operand.type == TokenLiteral::NUMBER) || (operand.type == TokenLiteral::BOOLEAN)) return;
    throw RuntimeException(oper, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token oper, TokenLiteral left, TokenLiteral right) {
    if (((left.type == TokenLiteral::NUMBER) || (left.type == TokenLiteral::BOOLEAN)) && ((right.type == TokenLiteral::NUMBER) || (right.type == TokenLiteral::BOOLEAN))) return;
    throw RuntimeException(oper, "Operands must be numbers.");
}

TokenLiteral Interpreter::visitBinaryTokenLiteral(Binary &expr) {
    TokenLiteral left = evaluate(expr.left);
    TokenLiteral right = evaluate(expr.right);
    switch (expr.oper.type) {
        case TokenType::GREATER:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() > right.toNumber();
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() >= right.toNumber();
        case TokenType::LESS:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() < right.toNumber();
        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() <= right.toNumber();
        case TokenType::BANG_EQUAL:
            return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL:
            return isEqual(left, right);
        case TokenType::MINUS:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() - right.toNumber();
        case TokenType::PLUS:
            if ((left.type == TokenLiteral::NUMBER) && (right.type == TokenLiteral::NUMBER)) {
                return left.toNumber() + right.toNumber();
            }
            if ((left.type == TokenLiteral::STRING) && (right.type == TokenLiteral::STRING)) {
                return left.toString() + right.toString();
            }
            throw RuntimeException(expr.oper, "Operands must be two numbers or two strings.");
        case TokenType::SLASH:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() / right.toNumber();
        case TokenType::STAR:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() * right.toNumber();

            
    }
    return TokenLiteral();
}

TokenLiteral Interpreter::visitGroupingTokenLiteral(Grouping &expr) {
    return evaluate(expr.expr);
}

TokenLiteral Interpreter::visitLiteralTokenLiteral(Literal &expr) {
    return expr.value;
}

TokenLiteral Interpreter::visitUnaryTokenLiteral(Unary &expr) {
    TokenLiteral right = evaluate(expr.right);

    switch (expr.oper.type) {
        case TokenType::MINUS:
            checkNumberOperand(expr.oper, right);
            return -(right.toNumber());
        case TokenType::BANG:
            return !isTruthy(right);
    }

    return TokenLiteral();
}


TokenLiteral Interpreter::visitExpressionTokenLiteral(Expression &stmt) {
    evaluate(stmt.expression);
    return TokenLiteral();
}

TokenLiteral Interpreter::visitPrintTokenLiteral(Print &stmt) {
    TokenLiteral value = evaluate(stmt.expression);
    cout << stringify(value);
    return TokenLiteral();
}

void Interpreter::interpret(Expr *expr) {
    try {
        TokenLiteral value = evaluate(expr);
        cout << (stringify(value)) << endl;
    } catch (RuntimeException error) {
        Clockwork::runtimeError(error);
    }
}

void Interpreter::interpret(vector<Stmt*> statements) {
    try {
        for (Stmt* statement: statements) {
            execute(statement);
        }
    } catch (RuntimeException error) {
        Clockwork::runtimeError(error);
    }
}