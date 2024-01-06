#include "headers/Resolver.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;


Resolver::Resolver(Interpreter *interpreter) : interpreter(interpreter) {
    scopes = {};
}

void Resolver::resolve(vector<Stmt*> statements) {
    for (Stmt* statement: statements) {
        resolve(statement);
    }
}

void Resolver::resolve(Stmt* stmt) {
    stmt->acceptTokenLiteral(this);
}

void Resolver::resolve(Expr* expr) {
    expr->acceptTokenLiteral(this);
}

void Resolver::resolveLocal(Expr* expr, Token name) {
    for (int i = scopes.size() - 1; i >= 0; i--) {
        if(scopes[i].count(name.lexeme) > 0) {
            interpreter->resolve(expr, scopes.size() - (i+1));
            return;
        }
    }
}

void Resolver::resolveFunction(Function& function, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;
    beginScope();
    for( Token param: function.params) {
        declare(param);
        define(param);
    }
    resolve(function.body);
    endScope();
    currentFunction = enclosingFunction;
}

void Resolver::beginScope() {
    scopes.push_back(map<string, bool>());
}

void Resolver::endScope() {
    scopes.pop_back();
}

void Resolver::declare(Token name) {
    if(scopes.empty()) return;
    map<string, bool> &scope = scopes.at(scopes.size()-1);
    if (scope.count(name.lexeme) > 0) {
        Clockwork::error(
            name,
            "Already a variable with this name in this scope."
            );
    }
    scope.insert({name.lexeme, false});
}

void Resolver::define(Token name) {
    if (scopes.empty()) return;
    scopes.at(scopes.size()-1).find(name.lexeme)->second = true;
}

string Resolver::visitExpressionstring(Expression &stmt) {    return "";};
string Resolver::visitFunctionstring(Function &stmt) {    return "";};
string Resolver::visitClassstring(Class& stmt) { return "";};
string Resolver::visitReturnstring(Return &stmt) {    return "";};
string Resolver::visitPrintstring(Print &stmt) {    return "";};
string Resolver::visitVarstring(Var &stmt) {    return "";};
string Resolver::visitBlockstring(Block &stmt) {    return "";};
string Resolver::visitIfstring(If &stmt) {    return "";};
string Resolver::visitWhilestring(While &stmt) {    return "";};
//you work here

TokenLiteral Resolver::visitExpressionTokenLiteral(Expression &stmt) {
    resolve(stmt.expression);
    return TokenLiteral();
};

TokenLiteral Resolver::visitFunctionTokenLiteral(Function &stmt) {
    declare(stmt.name);
    define(stmt.name);
    resolveFunction(stmt, FunctionType::FUNCTION);
    return TokenLiteral();
};


TokenLiteral Resolver::visitClassTokenLiteral(Class& stmt) { 
    ClassType enclosingClass = currentClass;
    currentClass = ClassType::CLASS;
    declare(stmt.name);
    define(stmt.name);
    beginScope();
    scopes.at(scopes.size()-1).insert({"this", true});
    for (Function* method: stmt.methods) {
        FunctionType declaration = FunctionType::METHOD;
        if (method->name.lexeme.compare("constructor") == 0) 
            declaration = FunctionType::INITIALIZER;
        resolveFunction(*method, declaration);
    }
    endScope();
    currentClass = enclosingClass;
    return TokenLiteral();
};

TokenLiteral Resolver::visitReturnTokenLiteral(Return &stmt) {
    if (currentFunction == FunctionType::FNONE) {
        Clockwork::error(
            stmt.keyword,
            "Can't return from top-level code.");
    }
    if (stmt.value != nullptr) {
        if (currentFunction == FunctionType::INITIALIZER) {
            Clockwork::error(
                stmt.keyword,
                "Can't return from class constructor.");
        }
        resolve(stmt.value);
    }
    return TokenLiteral();
};

TokenLiteral Resolver::visitPrintTokenLiteral(Print &stmt) {
    resolve(stmt.expression);
    return TokenLiteral();
};

TokenLiteral Resolver::visitVarTokenLiteral(Var &stmt) {
    declare(stmt.name);
    if (stmt.initializer != nullptr) {
        resolve(stmt.initializer);
    }
    define(stmt.name);
    return TokenLiteral();
};

TokenLiteral Resolver::visitBlockTokenLiteral(Block &stmt) {
    beginScope();
    resolve(stmt.statements);
    endScope();
    return TokenLiteral();
};

TokenLiteral Resolver::visitIfTokenLiteral(If &stmt) {
    resolve(stmt.condition);
    resolve(stmt.thenBranch);
    if(stmt.elseBranch != nullptr) 
        resolve(stmt.elseBranch);
    return TokenLiteral();
};

TokenLiteral Resolver::visitWhileTokenLiteral(While &stmt) {
    resolve(stmt.condition);
    resolve(stmt.body);
    return TokenLiteral();
};

string Resolver::visitBinarystring(Binary &expr) {    return "";};
string Resolver::visitCallstring(Call &expr) {    return "";};
string Resolver::visitGetstring(Get &expr) {    return "";};
string Resolver::visitSetstring(Set &expr) {    return "";};
string Resolver::visitThisstring(This &expr) {    return "";};
string Resolver::visitGroupingstring(Grouping &expr) {    return "";};
string Resolver::visitLiteralstring(Literal &expr) {    return "";};
string Resolver::visitLogicalstring(Logical &expr) {    return "";};
string Resolver::visitUnarystring(Unary &expr) {    return "";};
string Resolver::visitVariablestring(Variable &expr) {    return "";};
string Resolver::visitAssignstring(Assign &expr) {    return "";};

TokenLiteral Resolver::visitBinaryTokenLiteral(Binary &expr) {
    resolve(expr.left);
    resolve(expr.right);
    return TokenLiteral();
};

TokenLiteral Resolver::visitCallTokenLiteral(Call &expr) {
    resolve(expr.callee);
    for(Expr* arg: expr.arguments) {
        resolve(arg);
    }
    return TokenLiteral();
};

TokenLiteral Resolver::visitGetTokenLiteral(Get &expr) {
    resolve(expr.object);
    return TokenLiteral();
}
TokenLiteral Resolver::visitSetTokenLiteral(Set &expr) {
    resolve(expr.value);
    resolve(expr.object);
    return TokenLiteral();
}

TokenLiteral Resolver::visitThisTokenLiteral(This &expr) {
    if (currentClass == ClassType::CNONE) {
        Clockwork::error(
            expr.keyword,
            "Can't use 'this' outside of a class.");
    }
    resolveLocal(&expr, expr.keyword);
    return TokenLiteral();
}

TokenLiteral Resolver::visitGroupingTokenLiteral(Grouping &expr) {
    resolve(expr.expr);
    return TokenLiteral();
};

TokenLiteral Resolver::visitLiteralTokenLiteral(Literal &expr) {
    return TokenLiteral();
};

TokenLiteral Resolver::visitLogicalTokenLiteral(Logical &expr) {
    resolve(expr.left);
    resolve(expr.right);
    return TokenLiteral();
};

TokenLiteral Resolver::visitUnaryTokenLiteral(Unary &expr) {
    resolve(expr.right);
    return TokenLiteral();
};

TokenLiteral Resolver::visitVariableTokenLiteral(Variable &expr) {
    if ((!scopes.empty()) && ((scopes.at(scopes.size()-1).find(expr.name.lexeme)->second) == false)) {
            Clockwork::error(
                expr.name,
                "Can't read local variable in its own initializer."
            );
        }
    resolveLocal(&expr, expr.name);
    return TokenLiteral();
};

TokenLiteral Resolver::visitAssignTokenLiteral(Assign &expr) {
    resolve(expr.value);
    resolveLocal(&expr, expr.name);
    return TokenLiteral();
};
