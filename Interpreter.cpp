#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <math.h>

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
#include "headers/LoxInstance.h"
#include "headers/LoxClass.h"

using namespace std;

string Interpreter::visitBinarystring(Binary &expr){ return ""; }
string Interpreter::visitCallstring(Call &expr) { return ""; }
string Interpreter::visitGetstring(Get &expr) { return ""; }
string Interpreter::visitSetstring(Set &expr) { return ""; }
string Interpreter::visitThisstring(This &expr) { return ""; }
string Interpreter::visitGroupingstring(Grouping &expr){ return ""; }
string Interpreter::visitLiteralstring(Literal &expr){ return ""; }
string Interpreter::visitLogicalstring(Logical &expr) { return ""; }
string Interpreter::visitUnarystring(Unary &expr){ return ""; }
string Interpreter::visitVariablestring(Variable &expr){ return ""; }
string Interpreter::visitAssignstring(Assign& expr){ return "";}

string Interpreter::visitExpressionstring(Expression &stmt) { return ""; }
string Interpreter::visitFunctionstring(Function &stmt) { return ""; }
string Interpreter::visitClassstring(Class &stmt) { return ""; }
string Interpreter::visitPrintstring(Print &stmt) { return ""; }
string Interpreter::visitReturnstring(Return &stmt) { return ""; }
string Interpreter::visitVarstring(Var &stmt) { return ""; }
string Interpreter::visitBlockstring(Block &stmt) { return ""; }
string Interpreter::visitIfstring(If &stmt) { return ""; }
string Interpreter::visitWhilestring(While &stmt) { return ""; }

Interpreter::Interpreter() {
    globals->define(
        "clock",
        TokenLiteral(new LoxClock(), {false, true})
    );
    globals->define(
        "exit",
        TokenLiteral(new LoxExit(), {false, true})
    );
    globals->define(
        "print",
        TokenLiteral(new LoxPrint(), {false, true})
    );
    globals->define(
        "type",
        TokenLiteral(new LoxType(), {false, true})
    );
    globals->define(
        "Math",
        TokenLiteral(new LoxMath(), {false, true})
    );
    // globals->define(
    //     "PI",
    //     TokenLiteral(3.1415926535897932384626433, {false, true})
    // );
    // globals->define(
    //     "E",
    //     TokenLiteral(2.71828182845904523536028747135266249775724709369995, {false, true})
    // );
}
 
TokenLiteral Interpreter::evaluate(Expr* expr) {
    return expr->acceptTokenLiteral(this);
}

TokenLiteral Interpreter::execute(Stmt* statement) {
    return statement->acceptTokenLiteral(this);
}

TokenLiteral Interpreter::lookUpVariable(Token name, Expr* expr) {
    
    int distance = locals.find(expr)->second; 

    if (locals.count(expr) > 0) {
        return environment->getAt(distance, name.lexeme);
    } else {
        return globals->get(name);
    }

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
    if ((arguments.size() != function->arity()) && (function->arity() >= 0)) {
        throw RuntimeException(
            expr.paren, 
            "Expected " 
            + to_string(function->arity())
            + " arguments but got " 
            + to_string(arguments.size()) 
            + ".");
    }
    if ((arguments.size() > function->arity()) && (function->arity() < 0)) {
        throw RuntimeException(
            expr.paren, 
            "Expected not more than " 
            + to_string(-function->arity())
            + " arguments but got " 
            + to_string(arguments.size()) 
            + ".");
    }
    return function->call(this, arguments); 
}

TokenLiteral Interpreter::visitGetTokenLiteral(Get &expr) {
    TokenLiteral object = evaluate(expr.object);
    if(object.toInstance() != nullptr) {
        return object.toInstance()->get(expr.name);
    }
    if(dynamic_cast<LoxClass*>(object.toCallable()) != nullptr) {
        return dynamic_cast<LoxClass*>(object.toCallable())->findStaticMethod(expr.name.lexeme);
    }
    
    if(object.toInstance() != nullptr)
        throw RuntimeException(
            expr.name,
            "Can get only from class or instance.");
}
 
TokenLiteral Interpreter::visitSetTokenLiteral(Set &expr) {
    TokenLiteral object = evaluate(expr.object);
    if(object.toInstance() == nullptr) {
        throw RuntimeException(
            expr.name,
            "Only instances have fields.");
    }
    TokenLiteral value = evaluate(expr.value);
    object.toInstance()->set(expr.name, value);
    return value;
}

TokenLiteral Interpreter::visitThisTokenLiteral(This &expr) {
    return lookUpVariable(expr.keyword, &expr);
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
    return lookUpVariable(expr.name, &expr);
}

TokenLiteral Interpreter::visitFunctionTokenLiteral(Function &stmt) {
    LoxFunction *function = new LoxFunction(stmt, this->environment, false);
    environment->define(stmt.name, TokenLiteral(TokenLiteral(function), {false, stmt.isConst}));
    return TokenLiteral();
}

TokenLiteral Interpreter::visitClassTokenLiteral(Class &stmt) {
    environment->define(stmt.name.lexeme, TokenLiteral());
    map<string, LoxFunction*> methods = {};
    map<string, LoxFunction*> statics = {};
    for (Function* method: stmt.methods) {
        LoxFunction *function = new LoxFunction(*method, environment, method->name.lexeme.compare("constructor") == 0);
        methods.insert({method->name.lexeme, function});
    }
    for (Function* sMethod: stmt.statics) {
        LoxFunction *function = new LoxFunction(*sMethod, environment, false);
        if (methods.count(sMethod->name.lexeme) > 0)
            throw RuntimeException(
                sMethod->name,
                "Can't declare method with same name as static.");

        statics.insert({sMethod->name.lexeme, function});
    }
    LoxClass *LClass = new LoxClass(stmt.name.lexeme, statics, methods);
    environment->assign(stmt.name, LClass);
    return TokenLiteral();
}

TokenLiteral Interpreter::visitAssignTokenLiteral(Assign &expr) {
    TokenLiteral value = evaluate(expr.value);
    int distance = locals.find(&expr)->second;
    if (locals.count(&expr) > 0) {
        environment->assignAt(distance, expr.name, value);
    } else {
        globals->assign(expr.name, value);
    }
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
    return TokenLiteral(value, {true});
}

TokenLiteral Interpreter::visitVarTokenLiteral(Var &stmt) {
    TokenLiteral value = TokenLiteral();

    if (stmt.initializer != NULL) {
        value = evaluate(stmt.initializer);
    }

    value.isConst = stmt.isConst;

    environment->define(stmt.name, value);
    return TokenLiteral();
}

TokenLiteral Interpreter::visitBlockTokenLiteral(Block &stmt) {
    return executeBlock(stmt.statements, new Environment(environment));
}

TokenLiteral Interpreter::visitIfTokenLiteral(If& stmt) {
    TokenLiteral value;
    if (isTruthy(evaluate(stmt.condition))) {
        value = execute(stmt.thenBranch);
    } else if (stmt.elseBranch != NULL) {
        value = execute(stmt.elseBranch);
    }
    if (value.isReturn) return value;
    return TokenLiteral();
}

TokenLiteral Interpreter::visitWhileTokenLiteral(While &stmt) {
    TokenLiteral value;
    while(isTruthy(evaluate(stmt.condition))) {
        value = execute(stmt.body);
        if (value.isReturn) break;
    }

    if (value.isReturn) return value;
    return TokenLiteral();
}

TokenLiteral Interpreter::executeBlock(vector <Stmt*> statements, Environment *TempEnvironment) {
    Environment *previous = this->environment;
    TokenLiteral value;
    bool isReturn = false;
    try {
        this->environment = TempEnvironment;

        for (Stmt* statement : statements) {
            value = execute(statement);
            if (value.isReturn) {
                break;
            }
        }
        delete this->environment;
    } catch (RuntimeException e) {
        delete this->environment;
        this->environment = previous;
        throw e;
    }
    this->environment = previous;
    if (value.isReturn) return value;
    return TokenLiteral();
    // finally
}

void Interpreter::resolve(Expr* expr, int depth) {
        locals.insert({expr, depth});
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
            delete (statement);
            statement = nullptr;
        }
    } catch (RuntimeException error) {
        Clockwork::runtimeError(error);
    }
}