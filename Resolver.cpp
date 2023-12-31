#include "headers/Resolver.h"


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

void Resolver::beginScope() {
    scopes.push(map<string, bool>());
}

void Resolver::endScope() {
    scopes.pop();
}

string Resolver::visitExpressionstring(Expression &stmt) {

};

string Resolver::visitFunctionstring(Function &stmt) {

};

string Resolver::visitReturnstring(Return &stmt) {

};

string Resolver::visitPrintstring(Print &stmt) {

};

string Resolver::visitVarstring(Var &stmt) {

};

string Resolver::visitBlockstring(Block &stmt) {
    beginScope();
    resolve(stmt.statements);
    endScope();
    return TokenLiteral();
};

string Resolver::visitIfstring(If &stmt) {

};

string Resolver::visitWhilestring(While &stmt) {

};

TokenLiteral Resolver::visitExpressionTokenLiteral(Expression &stmt) {

};

TokenLiteral Resolver::visitFunctionTokenLiteral(Function &stmt) {

};

TokenLiteral Resolver::visitReturnTokenLiteral(Return &stmt) {

};

TokenLiteral Resolver::visitPrintTokenLiteral(Print &stmt) {

};

TokenLiteral Resolver::visitVarTokenLiteral(Var &stmt) {

};

TokenLiteral Resolver::visitBlockTokenLiteral(Block &stmt) {

};

TokenLiteral Resolver::visitIfTokenLiteral(If &stmt) {

};

TokenLiteral Resolver::visitWhileTokenLiteral(While &stmt) {

};

string Resolver::visitBinarystring(Binary &expr) {

};

string Resolver::visitCallstring(Call &expr) {

};

string Resolver::visitGroupingstring(Grouping &expr) {

};

string Resolver::visitLiteralstring(Literal &expr) {

};

string Resolver::visitLogicalstring(Logical &expr) {

};

string Resolver::visitUnarystring(Unary &expr) {

};

string Resolver::visitVariablestring(Variable &expr) {

};

string Resolver::visitAssignstring(Assign &expr) {

};

TokenLiteral Resolver::visitBinaryTokenLiteral(Binary &expr) {

};

TokenLiteral Resolver::visitCallTokenLiteral(Call &expr) {

};

TokenLiteral Resolver::visitGroupingTokenLiteral(Grouping &expr) {

};

TokenLiteral Resolver::visitLiteralTokenLiteral(Literal &expr) {

};

TokenLiteral Resolver::visitLogicalTokenLiteral(Logical &expr) {

};

TokenLiteral Resolver::visitUnaryTokenLiteral(Unary &expr) {

};

TokenLiteral Resolver::visitVariableTokenLiteral(Variable &expr) {

};

TokenLiteral Resolver::visitAssignTokenLiteral(Assign &expr) {

};
