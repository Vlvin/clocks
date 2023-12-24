#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "headers/Standart.h"
#include "headers/Clockswork.h"
#include "headers/Expr.h"
#include "headers/Stmt.h"
#include "headers/Token.h"
#include "headers/TokenLiteral.h"
#include "headers/TokenType.h"
#include "headers/VisitorExpr.h"
#include "headers/VisitorStmt.h"
#include "headers/Environment.h"
#include "headers/Interpreter.h"
#include "headers/LoxCallable.h"
#include "headers/LoxFunction.h"

string Interpreter::visitBinarystring(Binary &expr){ return ""; }
string Interpreter::visitCallstring(Call &expr) { return ""; }
string Interpreter::visitGroupingstring(Grouping &expr){ return ""; }
string Interpreter::visitLiteralstring(Literal &expr){ return ""; }
string Interpreter::visitLogicalstring(Logical &expr) { return ""; }
string Interpreter::visitUnarystring(Unary &expr){ return ""; }
string Interpreter::visitVariablestring(Variable &expr){ return ""; }
string Interpreter::visitAssignstring(Assign& expr){ return "";}

string Interpreter::visitExpressionstring(Expression &stmt) { return ""; }
string Interpreter::visitFunctionstring(Function &stmt) { return ""; }
string Interpreter::visitPrintstring(Print &stmt) { return ""; }
string Interpreter::visitReturnstring(Return &stmt) { return ""; }
string Interpreter::visitVarstring(Var &stmt) { return ""; }
string Interpreter::visitBlockstring(Block &stmt) { return ""; }
string Interpreter::visitIfstring(If &stmt) { return ""; }
string Interpreter::visitWhilestring(While &stmt) { return ""; }

Interpreter::Interpreter() {
    globals->define(
        "clock",
        TokenLiteral(new LoxClock())
    );
}
 
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
            if (right.toNumber() == 0) throw RuntimeException(expr.oper, "Division by sero is forbidden.");
            return left.toNumber() / right.toNumber();
        case TokenType::STAR:
            checkNumberOperands(expr.oper, left, right);
            return left.toNumber() * right.toNumber();

            
    }
    return TokenLiteral();
}

TokenLiteral Interpreter::visitCallTokenLiteral(Call &expr) {
    TokenLiteral callee = evaluate(expr.callee);

    vector<TokenLiteral> arguments = {};
    for (Expr* argument: expr.arguments) {
        arguments.push_back(evaluate(argument));
    }

    LoxCallable* function = callee.toCallable();
    if (function == nullptr) {
        throw RuntimeException(expr.paren, "Can only call functions and classes.");
    }
    if (arguments.size() != function->arity()) {
        throw RuntimeException(
            expr.paren, 
            "Expected " 
            + to_string(function->arity())
            + " arguments but got " 
            + to_string(arguments.size()) 
            + ".");
    }
    return function->call(this, arguments); 
    
}

TokenLiteral Interpreter::visitGroupingTokenLiteral(Grouping &expr) {
    return evaluate(expr.expr);
}

TokenLiteral Interpreter::visitLiteralTokenLiteral(Literal &expr) {
    return expr.value;
}

TokenLiteral Interpreter::visitLogicalTokenLiteral(Logical &expr) {
    TokenLiteral left = evaluate(expr.left);

    if (expr.oper.type == TokenType::OR) {
        if (isTruthy(left)) return left;
    } else { 
        if (!isTruthy(left)) return left; 
    }

    return evaluate(expr.right);
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

TokenLiteral Interpreter::visitVariableTokenLiteral(Variable &expr) {
    return environment->get(expr.name);
}

TokenLiteral Interpreter::visitFunctionTokenLiteral(Function &stmt) {
    LoxFunction *function = new LoxFunction(stmt, this->environment);
    globals->define(stmt.name.lexeme, TokenLiteral(function));
    return TokenLiteral();
}

TokenLiteral Interpreter::visitAssignTokenLiteral(Assign &expr) {
    TokenLiteral value = evaluate(expr.value);
    environment->assign(expr.name, value);
    return value;
}


TokenLiteral Interpreter::visitExpressionTokenLiteral(Expression &stmt) {
    evaluate(stmt.expression);
    return TokenLiteral();
}

TokenLiteral Interpreter::visitPrintTokenLiteral(Print &stmt) {
    TokenLiteral value = evaluate(stmt.expression); 
    cout << stringify(value) << '\n';
    return TokenLiteral();
}

TokenLiteral Interpreter::visitReturnTokenLiteral(Return &stmt) {
    TokenLiteral value = TokenLiteral();
    if (stmt.value != NULL) { 
        value = evaluate(stmt.value);
    }
    throw value;
    return TokenLiteral();
}

TokenLiteral Interpreter::visitVarTokenLiteral(Var &stmt) {
    TokenLiteral value = TokenLiteral();

    if (stmt.initializer != NULL) {
        value = evaluate(stmt.initializer);
    }

    environment->define(stmt.name.lexeme, value);
    return TokenLiteral();
}

TokenLiteral Interpreter::visitBlockTokenLiteral(Block &stmt) {
    executeBlock(stmt.statements, new Environment(environment));
    return TokenLiteral();
}

TokenLiteral Interpreter::visitIfTokenLiteral(If& stmt) {
    if (isTruthy(evaluate(stmt.condition))) {
        execute(stmt.thenBranch);
    } else if (stmt.elseBranch != NULL) {
        execute(stmt.elseBranch);
    }
    return TokenLiteral();
}

TokenLiteral Interpreter::visitWhileTokenLiteral(While &stmt) {
    while(isTruthy(evaluate(stmt.condition))) {
        execute(stmt.body);
    }

    return TokenLiteral();
}

void Interpreter::executeBlock(vector <Stmt*> statements, Environment *environment) {
    Environment *previous = this->environment;
    try {
        this->environment = environment;

        for (Stmt* statement : statements) {
            execute(statement);
        }
    } catch (TokenLiteral tl) {
        this->environment = previous;
        throw tl;
    } catch (RuntimeException e) {
        this->environment = previous;
        throw e;
    }
    // finally
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